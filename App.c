#include "Image.h"

#include "Common.h"

#include "Gl.h"
#include "Memory.h"
#include "System.h"

const float VERTS[] = {
	-1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f, 1.0f, 1.0f
};

const c8 VERT_CODE[] =
"#version 460 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec2 aUV;\n"
"uniform mat3 _ScreenMatrix;\n"
"uniform mat3 _Transform;\n"
"uniform vec2 _TextureSize;\n"
"out vec2 uv;\n"
"void main()\n"
"{\n"
"    vec3 p = _ScreenMatrix * _Transform * vec3(aPos, 1.0);\n"
"    gl_Position = vec4(p.xy, 0.0, 1.0);\n"
"    uv = aUV * _TextureSize;\n"
"}";

const c8* const FRAG_CODE =
"#version 460 core\n"
"in vec2 uv;\n"
"uniform sampler2D _Image;\n"
"uniform vec2 _TextureSize;\n"
"uniform float _PixelsPerTexel;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"    vec2 f = fract(uv);\n"
"    float smoothedPpt = 0.5 * _PixelsPerTexel;\n"
"    vec2 interp = clamp(f * smoothedPpt, 0.0, 0.5) + clamp((f - 1.0) * smoothedPpt + 0.5, 0.0, 0.5);\n"
"    vec2 coords = (floor(uv) + interp) / _TextureSize;\n"
"    color = texture2D(_Image, coords);\n"
"}";

const float ZOOM_DELTA = 1.2f;
const float UNZOOM_DELTA = 0.83333333333f;

static void UpdateTransform();
static bool LoadImage(const u16* filename);
static bool CompileShader(const c8* vertCode, const c8* fragCode, u32* program);

static u32 vbo;
static u32 vao;
static u32 program;
static u32 texture;

static i32 _ScreenMatrix = -1;
static i32 _Transform = -1;
static i32 _TextureSize = -1;
static i32 _PixelsPerTexel = -1;

static i32 imageW;
static i32 imageH;
static i32 windowW;
static i32 windowH;
static float zoom = 1.0f;
static float panX;
static float panY;

bool Init(const u16* const filepath)
{
	bool error;

	vbo = glCreateBuffer();
	glNamedBufferStorage(vbo, sizeof(VERTS), VERTS, GL_DYNAMIC_STORAGE_BIT);

	vao = glCreateVertexArray();

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 4 * sizeof(float));

	glEnableVertexArrayAttrib(vao, 0);
	glEnableVertexArrayAttrib(vao, 1);

	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, 0, 0);
	glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, 0, 2 * sizeof(float));

	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribBinding(vao, 1, 0);

	TRY(!CompileShader(VERT_CODE, FRAG_CODE, &program));

	_ScreenMatrix = glGetUniformLocation(program, "_ScreenMatrix");
	_Transform = glGetUniformLocation(program, "_Transform");
	_TextureSize = glGetUniformLocation(program, "_TextureSize");
	_PixelsPerTexel = glGetUniformLocation(program, "_PixelsPerTexel");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (filepath)
	{
		LoadImage(filepath);
		ResizeWindow(imageW, imageH);
	}

	return true;
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(vao);
	glBindTextureUnit(0, texture);

	UpdateTransform();

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Deinit()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(program);
}

void OnResize(const i32 width, const i32 height)
{
	windowW = width;
	windowH = height;
	glViewport(0, 0, width, height);
}

void OnDrag(const i32 dragX, const i32 dragY)
{
	panX += dragX;
	panY += dragY;
}

void OnScroll(const i32 scrollDelta, const i32 mouseX, const i32 mouseY)
{
	float mouseImageX = mouseX - 0.5f * windowW;
	float mouseImageY = mouseY - 0.5f * windowH;
	float zoomK = 1.0f;
	if (scrollDelta > 0)
	{
		for (i32 i = 0; i < scrollDelta; ++i) zoomK *= ZOOM_DELTA;
	}
	else
	{
		for (i32 i = 0; i > scrollDelta; --i) zoomK *= UNZOOM_DELTA;
	}
	panX = panX * zoomK + mouseImageX * (1.0f - zoomK);
	panY = panY * zoomK + mouseImageY * (1.0f - zoomK);

	zoom *= zoomK;
	if (zoom < 0.0001f) zoom = 0.0001f;
}

static void UpdateTransform()
{
	float screenMatrix[9] = {
		2.0f / windowW, 0.0f, 0.0f,
		0.0f, -2.0f / windowH, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	float transform[9] = {
		0.5f * imageW * zoom, 0.0f, 0.0f,
		0.0f, 0.5f * imageH * zoom, 0.0f,
		panX, panY, 1.0f
	};

	glProgramUniformMatrix3fv(program, _ScreenMatrix, 1, false, screenMatrix);
	glProgramUniformMatrix3fv(program, _Transform, 1, false, transform);
	glProgramUniform2f(program, _TextureSize, (float)imageW, (float)imageH);
	glProgramUniform1f(program, _PixelsPerTexel, zoom);
}

static bool LoadImage(const u16* const filename)
{
	bool error;

	u8* data;
	u64 length;
	TRY(!ReadFileAlloc(filename, &data, &length));

	i32 n;
	u8* const image = stbi_load_from_memory(data, (i32)length, &imageW, &imageH, &n, STBI_rgb_alpha);
	if (!image)
	{
		const c8* const reason = stbi_failure_reason();
		DebugPrint(reason);
		Dealloc(data);
		return false;
	}

	if (texture != 0) glDeleteTexture(texture);
	texture = glCreateTexture(GL_TEXTURE_2D);
	glTextureStorage2D(texture, 4, GL_RGBA8, imageW, imageH);
	glTextureSubImage2D(texture, 0, 0, 0, imageW, imageH, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateTextureMipmap(texture);
	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	stbi_image_free(image);
	Dealloc(data);
	return true;
}

static bool CompileShader(const c8* vertCode, const c8* fragCode, u32* const programPtr)
{
	c8 feedback[1000];

	i32 status;

	const u32 vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertCode, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertShader, sizeof(feedback), NULL, feedback);
		DebugPrint(feedback);
		glDeleteShader(vertShader);
		return false;
	}

	const u32 fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCode, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fragShader, sizeof(feedback), NULL, feedback);
		DebugPrint(feedback);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		return false;
	}

	const u32 program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);

	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	if (status) *programPtr = program;
	if (!status)
	{
		DebugPrint("LINK ERROR\n");
	}
	return status;
}
