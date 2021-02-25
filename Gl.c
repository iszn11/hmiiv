#include "Common.h"
#include "Gl.h"

void* wglGetProcAddress(const c8*);
#define GET_PROC_ADDRESS(name) _ ## name = (name ## _t)wglGetProcAddress(#name)

glCreateBuffers_t _glCreateBuffers;
glNamedBufferStorage_t _glNamedBufferStorage;
glCreateVertexArrays_t _glCreateVertexArrays;
glVertexArrayVertexBuffer_t _glVertexArrayVertexBuffer;
glEnableVertexArrayAttrib_t _glEnableVertexArrayAttrib;
glVertexArrayAttribFormat_t _glVertexArrayAttribFormat;
glVertexArrayAttribBinding_t _glVertexArrayAttribBinding;
glDeleteBuffers_t _glDeleteBuffers;
glDeleteVertexArrays_t _glDeleteVertexArrays;
glCreateShader_t _glCreateShader;
glShaderSource_t _glShaderSource;
glCompileShader_t _glCompileShader;

glCreateProgram_t _glCreateProgram;
glAttachShader_t _glAttachShader;
glLinkProgram_t _glLinkProgram;
glDetachShader_t _glDetachShader;
glDeleteShader_t _glDeleteShader;
glDeleteProgram_t _glDeleteProgram;
glGetShaderiv_t _glGetShaderiv;
glGetProgramiv_t _glGetProgramiv;
glGetUniformLocation_t _glGetUniformLocation;
glGetShaderInfoLog_t _glGetShaderInfoLog;

glCreateTextures_t _glCreateTextures;
glTextureStorage2D_t _glTextureStorage2D;
glTextureSubImage2D_t _glTextureSubImage2D;
glTextureParameteri_t _glTextureParameteri;
glTextureParameterfv_t _glTextureParameterfv;
glGenerateTextureMipmap_t _glGenerateTextureMipmap;
glDeleteTextures_t _glDeleteTextures;

glBindVertexArray_t _glBindVertexArray;
glUseProgram_t _glUseProgram;
glBindTextureUnit_t _glBindTextureUnit;
glDrawArrays_t _glDrawArrays;

glProgramUniform1f_t glProgramUniform1f;
glProgramUniform2f_t glProgramUniform2f;
glProgramUniformMatrix3fv_t glProgramUniformMatrix3fv;

#undef glClear
#undef glClearColor
#undef glViewport

void glClear(u32 mask);
void glClearColor(float red, float green, float blue, float alpha);
void glViewport(i32 x, i32 y, i32 width, i32 height);

glClear_t _glClear;
glClearColor_t _glClearColor;
glViewport_t _glViewport;

u32 glCreateBuffer()
{
	u32 ret;
	glCreateBuffers(1, &ret);
	return ret;
}

u32 glCreateVertexArray()
{
	u32 ret;
	glCreateVertexArrays(1, &ret);
	return ret;
}

u32 glCreateTexture(u32 target)
{
	u32 ret;
	glCreateTextures(target, 1, &ret);
	return ret;
}

void glDeleteBuffer(const u32 buffer)
{
	glDeleteBuffers(1, &buffer);
}

void glDeleteVertexArray(const u32 array)
{
	glDeleteVertexArrays(1, &array);
}

void glDeleteTexture(const u32 texture)
{
	glDeleteTextures(1, &texture);
}

void InitGl()
{
	GET_PROC_ADDRESS(glCreateBuffers);
	GET_PROC_ADDRESS(glNamedBufferStorage);
	GET_PROC_ADDRESS(glCreateVertexArrays);
	GET_PROC_ADDRESS(glVertexArrayVertexBuffer);
	GET_PROC_ADDRESS(glEnableVertexArrayAttrib);
	GET_PROC_ADDRESS(glVertexArrayAttribFormat);
	GET_PROC_ADDRESS(glVertexArrayAttribBinding);
	GET_PROC_ADDRESS(glDeleteBuffers);
	GET_PROC_ADDRESS(glDeleteVertexArrays);

	GET_PROC_ADDRESS(glCreateShader);
	GET_PROC_ADDRESS(glShaderSource);
	GET_PROC_ADDRESS(glCompileShader);
	GET_PROC_ADDRESS(glCreateProgram);
	GET_PROC_ADDRESS(glAttachShader);
	GET_PROC_ADDRESS(glLinkProgram);
	GET_PROC_ADDRESS(glDetachShader);
	GET_PROC_ADDRESS(glDeleteShader);
	GET_PROC_ADDRESS(glDeleteProgram);
	GET_PROC_ADDRESS(glGetShaderiv);
	GET_PROC_ADDRESS(glGetProgramiv);
	GET_PROC_ADDRESS(glGetUniformLocation);
	GET_PROC_ADDRESS(glGetShaderInfoLog);

	GET_PROC_ADDRESS(glCreateTextures);
	GET_PROC_ADDRESS(glTextureStorage2D);
	GET_PROC_ADDRESS(glTextureSubImage2D);
	GET_PROC_ADDRESS(glTextureParameteri);
	GET_PROC_ADDRESS(glTextureParameterfv);
	GET_PROC_ADDRESS(glGenerateTextureMipmap);
	GET_PROC_ADDRESS(glDeleteTextures);

	GET_PROC_ADDRESS(glBindVertexArray);
	GET_PROC_ADDRESS(glUseProgram);
	GET_PROC_ADDRESS(glBindTextureUnit);
	GET_PROC_ADDRESS(glDrawArrays);

	GET_PROC_ADDRESS(glProgramUniform1f);
	GET_PROC_ADDRESS(glProgramUniform2f);
	GET_PROC_ADDRESS(glProgramUniformMatrix3fv);

	_glClear = &glClear;
	_glClearColor = &glClearColor;
	_glViewport = &glViewport;
}
