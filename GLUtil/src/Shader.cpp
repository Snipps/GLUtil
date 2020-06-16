#include <GLUtil/Shader.h>

#include <glad/glad.h>

#include <cstring>
#include <cstdio>
#include <memory>

#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

Shader::Shader(ShaderType type)
{
	GLUTIL_GL_CALL(SetID(glCreateShader(ENUM(type))));
}

Shader::Shader(uint32_t shader) :
	GLObject(shader)
{}

Shader::Shader(ShaderType type, ShaderSourceType srcType, const char* src) :
	Shader(type)
{
	Source(srcType, src);
}

Shader::~Shader()
{
	if (*this) {
		GLUTIL_GL_CALL(glDeleteShader(*this));
	}
}

Shader& Shader::Source(int32_t count, const char* const* strings, const int32_t* lengths)
{
	GLUTIL_GL_CALL(glShaderSource(*this, count, strings, lengths));
	return *this;
}

Shader& Shader::Source(const char* src)
{
	int32_t len = strlen(src);
	return Source(1, &src, &len);
}

bool Shader::SourceFile(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file) {
		fseek(file, 0L, SEEK_END);
		long size = ftell(file);
		fseek(file, 0L, SEEK_SET);
		std::unique_ptr<char[]> src(new(std::nothrow) char[size]);
		if (src) {
			memset(src.get(), 0, size);
			fread(src.get(), 1, size, file);
			fclose(file);
		} else {
			fclose(file);
			return false;
		}

		Source(src.get());
		return true;
	}

	return false;
}

bool Shader::Source(ShaderSourceType srcType, const char* src)
{
	if (srcType == ShaderSourceType::File)
		return SourceFile(src);
	Source(src);
	return true;
}

bool Shader::Compile()
{
	GLUTIL_GL_CALL(glCompileShader(*this));
	return IsCompiled();
}

int32_t Shader::GetInfoLog(int32_t maxLength, char* infoLog) const
{
	int32_t logLen;
	GLUTIL_GL_CALL(glGetShaderInfoLog(*this, maxLength, &logLen, infoLog));
	return logLen;
}

std::string Shader::GetInfoLog() const
{
	int32_t logLen = GetInfoLogLength();
	if (!logLen)
		return std::string();
	std::unique_ptr<char[]> logBuf(new(std::nothrow) char[logLen]);
	if (!logBuf)
		return "Failed to allocate buffer for shader log";
	GetInfoLog(logLen, logBuf.get());
	return std::string(logBuf.get());
}

int32_t Shader::GetSource(int32_t bufSize, char* src) const
{
	int32_t srcLen;
	GLUTIL_GL_CALL(glGetShaderSource(*this, bufSize, &srcLen, src));
	return srcLen;
}

std::string Shader::GetSource() const
{
	int32_t srcLen = GetSourceLength();
	if (!srcLen)
		return std::string();
	std::unique_ptr<char[]> srcBuf(new(std::nothrow) char[srcLen]);
	if (!srcBuf)
		return "Failed to allocate buffer for shader source";
	GetSource(srcLen, srcBuf.get());
	return std::string(srcBuf.get());
}

void Shader::GetParam(ShaderParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetShaderiv(*this, ENUM(pname), value));
}

int32_t Shader::GetParamI(ShaderParam pname) const
{
	int32_t value;
	GetParam(pname, &value);
	return value;
}

ShaderType Shader::GetType() const
{
	return static_cast<ShaderType>(GetParamI(ShaderParam::Type));
}

bool Shader::IsTaggedForDelete() const
{
	return GetParamI(ShaderParam::DeleteStatus) == GL_TRUE;
}

bool Shader::IsCompiled() const
{
	return GetParamI(ShaderParam::CompileStatus) == GL_TRUE;
}

int32_t Shader::GetInfoLogLength() const
{
	return GetParamI(ShaderParam::InfoLogLength);
}

int32_t Shader::GetSourceLength() const
{
	return GetParamI(ShaderParam::SourceLength);
}

}