#pragma once

#define GL_CLAMP_TO_BORDER 0x812D
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_COMPILE_STATUS 0x8B81
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_DYNAMIC_STORAGE_BIT 0x0100
#define GL_FLOAT 0x1406
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_LINEAR 0x2601
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_LINK_STATUS 0x8B82
#define GL_MIRRORED_REPEAT 0x8370
#define GL_MIRROR_CLAMP_TO_EDGE 0x8743
#define GL_NEAREST 0x2600
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_REPEAT 0x2901
#define GL_RGBA 0x1908
#define GL_RGBA8 0x8058
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_BORDER_COLOR 0x1004
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_UNSIGNED_BYTE 0x1401
#define GL_VERTEX_SHADER 0x8B31

typedef void (*glCreateBuffers_t)(i32 n, u32* buffers);
typedef void (*glNamedBufferStorage_t)(u32 buffer, i64 size, const void* data, u32 flags);
typedef void (*glCreateVertexArrays_t)(i32 n, u32* arrays);
typedef void (*glVertexArrayVertexBuffer_t)(u32 vaobj, u32 bindingindex, u32 buffer, i64 offset, i32 stride);
typedef void (*glEnableVertexArrayAttrib_t)(u32 vaobj, u32 index);
typedef void (*glVertexArrayAttribFormat_t)(u32 vaobj, u32 attribindex, i32 size, u32 type, u8 normalized, u32 relativeOffset);
typedef void (*glVertexArrayAttribBinding_t)(u32 vaobj, u32 attribindex, u32 bindingindex);
typedef void (*glDeleteBuffers_t)(i32 n, const u32* buffers);
typedef void (*glDeleteVertexArrays_t)(i32 n, const u32* arrays);

typedef u32  (*glCreateShader_t)(u32 shaderType);
typedef void (*glShaderSource_t)(u32 shader, i32 count, const c8** string, const i32* length);
typedef void (*glCompileShader_t)(u32 shader);
typedef u32  (*glCreateProgram_t)();
typedef void (*glAttachShader_t)(u32 program, u32 shader);
typedef void (*glLinkProgram_t)(u32 program);
typedef void (*glDetachShader_t)(u32 program, u32 shader);
typedef void (*glDeleteShader_t)(u32 shader);
typedef void (*glDeleteProgram_t)(u32 program);
typedef void (*glGetShaderiv_t)(u32 shader, u32 pname, i32* params);
typedef void (*glGetProgramiv_t)(u32 program, u32 pname, i32* params);
typedef i32 (*glGetUniformLocation_t)(u32 program, const c8* name);
typedef void (*glGetShaderInfoLog_t)(u32 shader, i32 bufSize, i32* length, c8* infoLog);

typedef void (*glCreateTextures_t)(u32 target, i32 n, u32* textures);
typedef void (*glTextureStorage2D_t)(u32 texture, i32 levels, u32 internalformat, i32 width, i32 height);
typedef void (*glTextureSubImage2D_t)(u32 texture, i32 level, i32 xoffset, i32 yoffset, i32 width, i32 height, u32 format, u32 type, const void* pixels);
typedef void (*glTextureParameteri_t)(u32 texture, u32 pname, i32 param);
typedef void (*glTextureParameterfv_t)(u32 texture, u32 pname, const float* param);
typedef void (*glGenerateTextureMipmap_t)(u32 texture);
typedef void (*glDeleteTextures_t)(i32 n, const u32* textures);

typedef void (*glBindVertexArray_t)(u32 array);
typedef void (*glUseProgram_t)(u32 program);
typedef void (*glBindTextureUnit_t)(u32 unit, u32 texture);
typedef void (*glDrawArrays_t)(u32 mode, i32 first, i32 count);

typedef void (*glProgramUniform1f_t)(u32 program, i32 location, float v0);
typedef void (*glProgramUniform2f_t)(u32 program, i32 location, float v0, float v1);
typedef void (*glProgramUniformMatrix3fv_t)(u32 program, i32 location, i32 count, bool transpose, const float* value);

typedef void (*glClear_t)(u32 mask);
typedef void (*glClearColor_t)(float red, float green, float blue, float alpha);
typedef void (*glViewport_t)(i32 x, i32 y, i32 width, i32 height);

extern glCreateBuffers_t _glCreateBuffers;
extern glNamedBufferStorage_t _glNamedBufferStorage;
extern glCreateVertexArrays_t _glCreateVertexArrays;
extern glVertexArrayVertexBuffer_t _glVertexArrayVertexBuffer;
extern glEnableVertexArrayAttrib_t _glEnableVertexArrayAttrib;
extern glVertexArrayAttribFormat_t _glVertexArrayAttribFormat;
extern glVertexArrayAttribBinding_t _glVertexArrayAttribBinding;
extern glDeleteBuffers_t _glDeleteBuffers;
extern glDeleteVertexArrays_t _glDeleteVertexArrays;

extern glCreateShader_t _glCreateShader;
extern glShaderSource_t _glShaderSource;
extern glCompileShader_t _glCompileShader;
extern glCreateProgram_t _glCreateProgram;
extern glAttachShader_t _glAttachShader;
extern glLinkProgram_t _glLinkProgram;
extern glDetachShader_t _glDetachShader;
extern glDeleteShader_t _glDeleteShader;
extern glDeleteProgram_t _glDeleteProgram;
extern glGetShaderiv_t _glGetShaderiv;
extern glGetProgramiv_t _glGetProgramiv;
extern glGetUniformLocation_t _glGetUniformLocation;
extern glGetShaderInfoLog_t _glGetShaderInfoLog;

extern glCreateTextures_t _glCreateTextures;
extern glTextureStorage2D_t _glTextureStorage2D;
extern glTextureSubImage2D_t _glTextureSubImage2D;
extern glTextureParameteri_t _glTextureParameteri;
extern glTextureParameterfv_t _glTextureParameterfv;
extern glBindTextureUnit_t _glBindTextureUnit;
extern glGenerateTextureMipmap_t _glGenerateTextureMipmap;
extern glDeleteTextures_t _glDeleteTextures;

extern glBindVertexArray_t _glBindVertexArray;
extern glUseProgram_t _glUseProgram;
extern glBindTextureUnit_t _glBindTextureUnit;
extern glDrawArrays_t _glDrawArrays;

extern glProgramUniform1f_t _glProgramUniform1f;
extern glProgramUniform2f_t _glProgramUniform2f;
extern glProgramUniformMatrix3fv_t _glProgramUniformMatrix3fv;

extern glClear_t _glClear;
extern glClearColor_t _glClearColor;
extern glViewport_t _glViewport;

#define glCreateBuffers _glCreateBuffers
#define glNamedBufferStorage _glNamedBufferStorage
#define glCreateVertexArrays _glCreateVertexArrays
#define glVertexArrayVertexBuffer _glVertexArrayVertexBuffer
#define glEnableVertexArrayAttrib _glEnableVertexArrayAttrib
#define glVertexArrayAttribFormat _glVertexArrayAttribFormat
#define glVertexArrayAttribBinding _glVertexArrayAttribBinding
#define glDeleteBuffers _glDeleteBuffers
#define glDeleteVertexArrays _glDeleteVertexArrays

#define glCreateShader _glCreateShader
#define glShaderSource _glShaderSource
#define glCompileShader _glCompileShader
#define glCreateProgram _glCreateProgram
#define glAttachShader _glAttachShader
#define glLinkProgram _glLinkProgram
#define glDetachShader _glDetachShader
#define glDeleteShader _glDeleteShader
#define glDeleteProgram _glDeleteProgram
#define glGetShaderiv _glGetShaderiv
#define glGetProgramiv _glGetProgramiv
#define glGetUniformLocation _glGetUniformLocation
#define glGetShaderInfoLog _glGetShaderInfoLog

#define glCreateTextures _glCreateTextures
#define glTextureStorage2D _glTextureStorage2D
#define glTextureSubImage2D _glTextureSubImage2D
#define glTextureParameteri _glTextureParameteri
#define glTextureParameterfv _glTextureParameterfv
#define glGenerateTextureMipmap _glGenerateTextureMipmap
#define glDeleteTextures _glDeleteTextures

#define glBindVertexArray _glBindVertexArray
#define glUseProgram _glUseProgram
#define glBindTextureUnit _glBindTextureUnit
#define glDrawArrays _glDrawArrays

#define glProgramUniform1f _glProgramUniform1f
#define glProgramUniform2f _glProgramUniform2f
#define glProgramUniformMatrix3fv _glProgramUniformMatrix3fv

#define glClear _glClear
#define glClearColor _glClearColor
#define glViewport _glViewport

u32 glCreateBuffer();
u32 glCreateVertexArray();
u32 glCreateTexture(u32 target);
void glDeleteBuffer(u32 buffer);
void glDeleteVertexArray(u32 array);
void glDeleteTexture(u32 texture);
