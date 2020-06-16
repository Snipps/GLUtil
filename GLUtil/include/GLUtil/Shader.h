#pragma once

#include "Common.h"
#include "Object.h"

#include <string>

namespace GLUtil {

enum class ShaderType : uint32_t
{
	Vertex = 0x8B31,
	Fragment = 0x8B30,
	Geometry = 0x8DD9,
	TessControl = 0x8E88,
	TessEvaluation = 0x8E87,
	Compute = 0x91B9
};

enum class ShaderParam : uint32_t
{
	Type = 0x8B4F,
	DeleteStatus = 0x8B80,
	CompileStatus = 0x8B81,
	InfoLogLength = 0x8B84,
	SourceLength = 0x8B88
};

enum class ShaderSourceType
{
	String,
	File
};

void GetShaderPrecisionFormat(ShaderType type, uint32_t precisionType, int32_t* range, int32_t* precision);

class Shader : public GLObject
{
public:
	Shader() = delete;
	Shader(const Shader&) = delete;
	Shader(Shader&&) noexcept = default;
	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&&) noexcept = default;

	Shader(ShaderType type);
	Shader(uint32_t shader);
	Shader(ShaderType type, ShaderSourceType srcType, const char* src);
	virtual ~Shader();

	Shader& Source(int32_t count, const char* const* strings, const int32_t* lengths);
	Shader& Source(const char* src);
	bool SourceFile(const char* filename);
	bool Source(ShaderSourceType srcType, const char* src);

	bool Compile();

	int32_t GetInfoLog(int32_t maxLength, char* infoLog) const;
	std::string GetInfoLog() const;
	int32_t GetSource(int32_t bufSize, char* src) const;
	std::string GetSource() const;

	void GetParam(ShaderParam pname, int32_t* value) const;
	
	int32_t GetParamI(ShaderParam pname) const;

	ShaderType GetType() const;
	bool IsTaggedForDelete() const;
	bool IsCompiled() const;
	int32_t GetInfoLogLength() const;
	int32_t GetSourceLength() const;
};

}