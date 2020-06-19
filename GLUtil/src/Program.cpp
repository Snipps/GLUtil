#include <GLUtil/Program.h>

#include <glad/glad.h>

#include <memory>

#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

Program& Program::AttachShader(uint32_t shader)
{
	GLUTIL_GL_CALL(glAttachShader(*this, shader));
	return *this;
}

Program& Program::DetachShader(uint32_t shader)
{
	GLUTIL_GL_CALL(glDetachShader(*this, shader));
	return *this;
}

bool Program::Link()
{
	GLUTIL_GL_CALL(glLinkProgram(*this));
	return IsLinked();
}

void Program::GetAttachedShaders(int32_t maxCount, int32_t* count, uint32_t* shaders) const
{
	GLUTIL_GL_CALL(glGetAttachedShaders(*this, maxCount, count, shaders));
}

AttachedShaders Program::GetAttachedShaders() const
{
	AttachedShaders shaders = { 0, { 0, 0, 0, 0, 0, 0 } };
	GetAttachedShaders(6, &shaders.count, shaders.shaders);
	return shaders;
}

void Program::GetActiveAtomicCounterBufferParam(uint32_t bufferIndex, AtomicCounterBufferParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveAtomicCounterBufferiv(*this, bufferIndex, ENUM(pname), value));
}

int32_t Program::GetActiveAtomicCounterBufferParamI(uint32_t bufferIndex, AtomicCounterBufferParam pname) const
{
	int32_t value = 0;
	GetActiveAtomicCounterBufferParam(bufferIndex, pname, &value);
	return value;
}

uint32_t Program::GetActiveAtomicCounterBufferBinding(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::Binding);
}

int32_t Program::GetActiveAtomicCounterBufferDataSize(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::DataSize);
}

int32_t Program::GetActiveAtomicCounterBufferNumActiveAtomicCounters(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::NumActiveAtomicCounters);
}

std::vector<int32_t> Program::GetActiveAtomicCounterBufferAtomicCounterIndices(uint32_t bufferIndex) const
{
	int32_t count = GetActiveAtomicCounterBufferNumActiveAtomicCounters(bufferIndex);
	if (!count)
		return std::vector<int32_t>();
	std::vector<int32_t> v(count, 0);
	GetActiveAtomicCounterBufferParam(bufferIndex, AtomicCounterBufferParam::ActiveAtomicCounterIndices, v.data());
	return std::move(v);
}

bool Program::IsActiveAtomicCounterBufferReferencedByVertexShader(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::ReferencedByVertexShader) == GL_TRUE;
}

bool Program::IsActiveAtomicCounterBufferReferencedByTessControlShader(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::ReferencedByTessControlShader) == GL_TRUE;
}

bool Program::IsActiveAtomicCounterBufferReferencedByTesEvaluationShader(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::ReferencedByTessEvaluationShader) == GL_TRUE;
}

bool Program::IsActiveAtomicCounterBufferReferencedByGeometryShader(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::ReferencedByGeometryShader) == GL_TRUE;
}

bool Program::IsActiveAtomicCounterBufferReferencedByFragmentShader(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::ReferencedByFragmentShader) == GL_TRUE;
}

bool Program::IsActiveAtomicCounterBufferReferencedByComputeShader(uint32_t bufferIndex) const
{
	return GetActiveAtomicCounterBufferParamI(bufferIndex, AtomicCounterBufferParam::ReferencedByComputeShader) == GL_TRUE;
}

int32_t Program::GetAttribLocation(const char* name) const
{
	GLUTIL_GL_CALL(int32_t loc = glGetAttribLocation(*this, name));
	return loc;
}

int32_t Program::GetFragDataIndex(const char* name) const
{
	GLUTIL_GL_CALL(int32_t index = glGetFragDataIndex(*this, name));
	return index;
}

int32_t Program::GetFragDataLocation(const char* name) const
{
	GLUTIL_GL_CALL(int32_t loc = glGetFragDataLocation(*this, name));
	return loc;
}

void Program::GetActiveAttrib(uint32_t index, int32_t nameBufSize, int32_t* nameLength, int32_t* size, DataType* type, char* name) const
{
	GLUTIL_GL_CALL(glGetActiveAttrib(*this, index, nameBufSize, nameLength, size, reinterpret_cast<GLenum*>(type), name));
}

ActiveAttrib Program::GetActiveAttrib(uint32_t index) const
{
	const ActiveAttrib def = { std::string(), static_cast<DataType>(0), 0 };

	int32_t maxLength = GetActiveAttributeMaxLength();
	if (!maxLength)
		return def;

	std::unique_ptr<char[]> buf(new(std::nothrow) char[maxLength]);
	if (!buf)
		return def;

	GLsizei length = 0;
	GLint size = 0;
	DataType type = static_cast<DataType>(0);
	GetActiveAttrib(index, maxLength, &length, &size, &type, buf.get());
	if (!length)
		return def;

	ActiveAttrib r = { std::string(buf.get(), length), type, size };
	return std::move(r);
}

int32_t Program::GetUniformLocation(const char* name) const
{
	GLUTIL_GL_CALL(int32_t loc = glGetUniformLocation(*this, name));
	return loc;
}

void Program::GetActiveUniform(uint32_t index, int32_t nameBufSize, int32_t* nameLength, int32_t* size, DataType* type, char* name) const
{
	GLUTIL_GL_CALL(glGetActiveUniform(*this, index, nameBufSize, nameLength, size, reinterpret_cast<GLenum*>(type), name));
}

ActiveUniform Program::GetActiveUniform(uint32_t index) const
{
	const ActiveUniform def = { std::string(), static_cast<DataType>(0), 0 };

	int32_t maxLength = GetActiveUniformMaxLength();
	if (!maxLength)
		return def;

	std::unique_ptr<char[]> buf(new(std::nothrow) char[maxLength]);
	if (!buf)
		return def;

	GLsizei length = 0;
	GLint size = 0;
	DataType type = static_cast<DataType>(0);
	GetActiveUniform(index, maxLength, &length, &size, &type, buf.get());
	if (!length)
		return def;

	ActiveUniform r = { std::string(buf.get(), length), type, size };
	return std::move(r);
}

int32_t Program::GetActiveUniformName(uint32_t index, int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveUniformName(*this, index, bufSize, &length, name));
	return length;
}

std::string Program::GetActiveUniformName(uint32_t index) const
{
	int32_t bufSize = GetActiveUniformMaxLength();
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetActiveUniformName(index, bufSize, buf.get());
	return std::string(buf.get(), length);
}

void Program::GetActiveUniformsParam(int32_t count, const uint32_t* indices, UniformParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveUniformsiv(*this, count, indices, ENUM(pname), value));
}

void Program::GetActiveUniformParam(uint32_t index, UniformParam pname, int32_t* value) const
{
	GetActiveUniformsParam(1, &index, pname, value);
}

int32_t Program::GetActiveUniformParamI(uint32_t index, UniformParam pname) const
{
	int32_t value = 0;
	GetActiveUniformParam(index, pname, &value);
	return value;
}

DataType Program::GetActiveUniformType(uint32_t index) const
{
	return static_cast<DataType>(GetActiveUniformParamI(index, UniformParam::Type));
}

int32_t Program::GetActiveUniformSize(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::Size);
}

int32_t Program::GetActiveUniformNameLength(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::NameLength);
}

uint32_t Program::GetActiveUniformBlockIndex(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::BlockIndex);
}

int32_t Program::GetActiveUniformOffset(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::Offset);
}

int32_t Program::GetActiveUniformArrayStride(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::ArrayStride);
}

int32_t Program::GetActiveUniformMatrixStride(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::MatrixStride);
}

bool Program::IsActiveUniformRowMajor(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::IsRowMajor) == GL_TRUE;
}

uint32_t Program::GetActiveUniformAtomicCounterBufferIndex(uint32_t index) const
{
	return GetActiveUniformParamI(index, UniformParam::AtomicCounterBufferIndex);
}

void Program::GetUniform(int32_t location, float* value) const
{
	GLUTIL_GL_CALL(glGetUniformfv(*this, location, value));
}

void Program::GetUniform(int32_t location, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetUniformiv(*this, location, value));
}

void Program::GetUniform(int32_t location, uint32_t* value) const
{
	GLUTIL_GL_CALL(glGetUniformuiv(*this, location, value));
}

void Program::GetUniform(int32_t location, double* value) const
{
	GLUTIL_GL_CALL(glGetUniformdv(*this, location, value));
}

void Program::GetUniform(int32_t location, int32_t bufSize, float* value) const
{
	GLUTIL_GL_CALL(glGetnUniformfv(*this, location, bufSize, value));
}

void Program::GetUniform(int32_t location, int32_t bufSize, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetnUniformiv(*this, location, bufSize, value));
}

void Program::GetUniform(int32_t location, int32_t bufSize, uint32_t* value) const
{
	GLUTIL_GL_CALL(glGetnUniformuiv(*this, location, bufSize, value));
}

void Program::GetUniform(int32_t location, int32_t bufSize, double* value) const
{
	GLUTIL_GL_CALL(glGetnUniformdv(*this, location, bufSize, value));
}

float Program::GetUniformFloat(int32_t location) const
{
	float r = 0;
	GetUniform(location, &r);
	return r;
}

Vec2f Program::GetUniformFloatVec2(int32_t location) const
{
	Vec2f r;
	GetUniform(location, r.v);
	return r;
}

Vec3f Program::GetUniformFloatVec3(int32_t location) const
{
	Vec3f r;
	GetUniform(location, r.v);
	return r;
}

Vec4f Program::GetUniformFloatVec4(int32_t location) const
{
	Vec4f r;
	GetUniform(location, r.v);
	return r;
}

Mat2f Program::GetUniformFloatMat2(int32_t location) const
{
	Mat2f r;
	GetUniform(location, r.v);
	return r;
}

Mat3f Program::GetUniformFloatMat3(int32_t location) const
{
	Mat3f r;
	GetUniform(location, r.v);
	return r;
}

Mat4f Program::GetUniformFloatMat4(int32_t location) const
{
	Mat4f r;
	GetUniform(location, r.v);
	return r;
}

Mat2x3f Program::GetUniformFloatMat2x3(int32_t location) const
{
	Mat2x3f r;
	GetUniform(location, r.v);
	return r;
}

Mat2x4f Program::GetUniformFloatMat2x4(int32_t location) const
{
	Mat2x4f r;
	GetUniform(location, r.v);
	return r;
}

Mat3x2f Program::GetUniformFloatMat3x2(int32_t location) const
{
	Mat3x2f r;
	GetUniform(location, r.v);
	return r;
}

Mat3x4f Program::GetUniformFloatMat3x4(int32_t location) const
{
	Mat3x4f r;
	GetUniform(location, r.v);
	return r;
}

Mat4x2f Program::GetUniformFloatMat4x2(int32_t location) const
{
	Mat4x2f r;
	GetUniform(location, r.v);
	return r;
}

Mat4x3f Program::GetUniformFloatMat4x3(int32_t location) const
{
	Mat4x3f r;
	GetUniform(location, r.v);
	return r;
}

int32_t Program::GetUniformInt(int32_t location) const
{
	int32_t r = 0;
	GetUniform(location, &r);
	return r;
}

Vec2i Program::GetUniformIntVec2(int32_t location) const
{
	Vec2i r;
	GetUniform(location, r.v);
	return r;
}

Vec3i Program::GetUniformIntVec3(int32_t location) const
{
	Vec3i r;
	GetUniform(location, r.v);
	return r;
}

Vec4i Program::GetUniformIntVec4(int32_t location) const
{
	Vec4i r;
	GetUniform(location, r.v);
	return r;
}

int32_t Program::GetUniformUnsignedInt(int32_t location) const
{
	int32_t r = 0;
	GetUniform(location, &r);
	return r;
}

Vec2i Program::GetUniformUnsignedIntVec2(int32_t location) const
{
	Vec2i r;
	GetUniform(location, r.v);
	return r;
}

Vec3i Program::GetUniformUnsignedIntVec3(int32_t location) const
{
	Vec3i r;
	GetUniform(location, r.v);
	return r;
}

Vec4i Program::GetUniformUnsignedIntVec4(int32_t location) const
{
	Vec4i r;
	GetUniform(location, r.v);
	return r;
}

double Program::GetUniformDouble(int32_t location) const
{
	double r = 0;
	GetUniform(location, &r);
	return r;
}

Vec2d Program::GetUniformDoubleVec2(int32_t location) const
{
	Vec2d r;
	GetUniform(location, r.v);
	return r;
}

Vec3d Program::GetUniformDoubleVec3(int32_t location) const
{
	Vec3d r;
	GetUniform(location, r.v);
	return r;
}

Vec4d Program::GetUniformDoubleVec4(int32_t location) const
{
	Vec4d r;
	GetUniform(location, r.v);
	return r;
}

Mat2d Program::GetUniformDoubleMat2(int32_t location) const
{
	Mat2d r;
	GetUniform(location, r.v);
	return r;
}

Mat3d Program::GetUniformDoubleMat3(int32_t location) const
{
	Mat3d r;
	GetUniform(location, r.v);
	return r;
}

Mat4d Program::GetUniformDoubleMat4(int32_t location) const
{
	Mat4d r;
	GetUniform(location, r.v);
	return r;
}

Mat2x3d Program::GetUniformDoubleMat2x3(int32_t location) const
{
	Mat2x3d r;
	GetUniform(location, r.v);
	return r;
}

Mat2x4d Program::GetUniformDoubleMat2x4(int32_t location) const
{
	Mat2x4d r;
	GetUniform(location, r.v);
	return r;
}

Mat3x2d Program::GetUniformDoubleMat3x2(int32_t location) const
{
	Mat3x2d r;
	GetUniform(location, r.v);
	return r;
}

Mat3x4d Program::GetUniformDoubleMat3x4(int32_t location) const
{
	Mat3x4d r;
	GetUniform(location, r.v);
	return r;
}

Mat4x2d Program::GetUniformDoubleMat4x2(int32_t location) const
{
	Mat4x2d r;
	GetUniform(location, r.v);
	return r;
}

Mat4x3d Program::GetUniformDoubleMat4x3(int32_t location) const
{
	Mat4x3d r;
	GetUniform(location, r.v);
	return r;
}

uint32_t Program::GetUniformBlockIndex(const char* name) const
{
	GLUTIL_GL_CALL(uint32_t index = glGetUniformBlockIndex(*this, name));
	return index;
}

int32_t Program::GetActiveUniformBlockName(uint32_t index, int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveUniformBlockName(*this, index, bufSize, &length, name));
	return length;
}

std::string Program::GetActiveUniformBlockName(uint32_t index) const
{
	int32_t bufSize = GetActiveUniformBlockNameLength(index);
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetActiveUniformBlockName(index, bufSize, buf.get());
	return std::string(buf.get(), length);
}

void Program::GetActiveUniformBlockParam(uint32_t index, UniformBlockParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveUniformBlockiv(*this, index, ENUM(pname), value));
}

int32_t Program::GetActiveUniformBlockParamI(uint32_t index, UniformBlockParam pname) const
{
	int32_t value = 0;
	GetActiveUniformBlockParam(index, pname, &value);
	return value;
}

uint32_t Program::GetActiveUniformBlockBinding(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::Binding);
}

int32_t Program::GetActiveUniformBlockDataSize(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::DataSize);
}

int32_t Program::GetActiveUniformBlockNameLength(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::NameLength);
}

int32_t Program::GetActiveUniformBlockNumActiveUniforms(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::NumActiveUniforms);
}

std::vector<int32_t> Program::GetActiveUniformBlockActiveUniformIndices(uint32_t index) const
{
	int32_t count = GetActiveUniformBlockNumActiveUniforms(index);
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	GetActiveUniformBlockParam(index, UniformBlockParam::ActiveUniformIndices, v.data());
	return std::move(v);
}

bool Program::IsActiveUniformBlockReferencedByVertexShader(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::ReferencedByVertexShader) == GL_TRUE;
}

bool Program::IsActiveUniformBlockReferencedByTessControlShader(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::ReferencedByTessControlShader) == GL_TRUE;
}

bool Program::IsActiveUniformBlockReferencedByTessEvaluationShader(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::ReferencedByTessEvaluationShader) == GL_TRUE;
}

bool Program::IsActiveUniformBlockReferencedByGeometryShader(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::ReferencedByGeometryShader) == GL_TRUE;
}

bool Program::IsActiveUniformBlockReferencedByFragmentShader(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::ReferencedByFragmentShader) == GL_TRUE;
}

bool Program::IsActiveUniformBlockReferencedByComputeShader(uint32_t index) const
{
	return GetActiveUniformBlockParamI(index, UniformBlockParam::ReferencedByComputeShader) == GL_TRUE;
}

uint32_t Program::GetSubroutineIndex(ShaderType shaderType, const char* name) const
{
	GLUTIL_GL_CALL(uint32_t index = glGetSubroutineIndex(*this, ENUM(shaderType), name));
	return index;
}

int32_t Program::GetSubroutineUniformLocation(ShaderType shaderType, const char* name) const
{
	GLUTIL_GL_CALL(int32_t loc = glGetSubroutineUniformLocation(*this, ENUM(shaderType), name));
	return loc;
}

int32_t Program::GetActiveSubroutineName(ShaderType shaderType, uint32_t index, int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveSubroutineName(*this, ENUM(shaderType), index, bufSize, &length, name));
	return length;
}

std::string Program::GetActiveSubroutineName(ShaderType shaderType, uint32_t index) const
{
	int32_t bufSize = GetStageActiveSubroutineMaxLength(shaderType);
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetActiveSubroutineName(shaderType, index, bufSize, buf.get());
	return std::string(buf.get(), length);
}

int32_t Program::GetActiveSubroutineUniformName(ShaderType shaderType, uint32_t index, int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveSubroutineUniformName(*this, ENUM(shaderType), index, bufSize, &length, name));
	return length;
}

std::string Program::GetActiveSubroutineUniformName(ShaderType shaderType, uint32_t index) const
{
	int32_t bufSize = GetStageActiveSubroutineUniformMaxLength(shaderType);
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetActiveSubroutineUniformName(shaderType, index, bufSize, buf.get());
	return std::string(buf.get(), length);
}

void Program::GetActiveSubroutineUniformParam(ShaderType shaderType, uint32_t index, SubroutineUniformParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveSubroutineUniformiv(*this, ENUM(shaderType), index, ENUM(pname), value));
}

int32_t Program::GetActiveSubroutineUniformParamI(ShaderType shaderType, uint32_t index, SubroutineUniformParam pname) const
{
	int32_t value = 0;
	GetActiveSubroutineUniformParam(shaderType, index, pname, &value);
	return value;
}

int32_t Program::GetActiveSubroutineUniformNumCompatibleSubroutines(ShaderType shaderType, uint32_t index) const
{
	return GetActiveSubroutineUniformParamI(shaderType, index, SubroutineUniformParam::NumCompatibleSubroutines);
}

std::vector<int32_t> Program::GetActiveSubroutineUniformCompatibleSubroutines(ShaderType shaderType, uint32_t index) const
{
	int32_t count = GetActiveSubroutineUniformNumCompatibleSubroutines(shaderType, index);
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	GetActiveSubroutineUniformParam(shaderType, index, SubroutineUniformParam::CompatibleSubroutines, v.data());
	return std::move(v);
}

int32_t Program::GetActiveSubroutineUniformSize(ShaderType shaderType, uint32_t index) const
{
	return GetActiveSubroutineUniformParamI(shaderType, index, SubroutineUniformParam::Size);
}

int32_t Program::GetActiveSubroutineUniformNameLength(ShaderType shaderType, uint32_t index) const
{
	return GetActiveSubroutineUniformParamI(shaderType, index, SubroutineUniformParam::NameLength);
}

void Program::GetStageParam(ShaderType shaderType, ProgramStageParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetProgramStageiv(*this, ENUM(shaderType), ENUM(pname), value));
}

int32_t Program::GetStageParamI(ShaderType shaderType, ProgramStageParam pname) const
{
	int32_t value = 0;
	GetStageParam(shaderType, pname, &value);
	return value;
}

int32_t Program::GetStageNumActiveSubroutineUniforms(ShaderType shaderType) const
{
	return GetStageParamI(shaderType, ProgramStageParam::NumActiveSubroutineUniforms);
}

int32_t Program::GetStageNumActiveSubroutineUniformLocations(ShaderType shaderType) const
{
	return GetStageParamI(shaderType, ProgramStageParam::NumActiveSubroutineUniformLocations);
}

int32_t Program::GetStageNumActiveSubroutines(ShaderType shaderType) const
{
	return GetStageParamI(shaderType, ProgramStageParam::NumActiveSubroutines);
}

int32_t Program::GetStageActiveSubroutineMaxLength(ShaderType shaderType) const
{
	return GetStageParamI(shaderType, ProgramStageParam::ActiveSubroutineMaxLength);
}

int32_t Program::GetStageActiveSubroutineUniformMaxLength(ShaderType shaderType) const
{
	return GetStageParamI(shaderType, ProgramStageParam::ActiveSubroutineUniformMaxLength);
}

uint32_t Program::GetResourceIndex(ProgramInterface interface, const char* name) const
{
	GLUTIL_GL_CALL(uint32_t index = glGetProgramResourceIndex(*this, ENUM(interface), name));
	return index;
}

int32_t Program::GetResourceLocation(ProgramInterface interface, const char* name) const
{
	GLUTIL_GL_CALL(int32_t loc = glGetProgramResourceLocation(*this, ENUM(interface), name));
	return loc;
}

int32_t Program::GetResourceLocationIndex(ProgramInterface interface, const char* name) const
{
	GLUTIL_GL_CALL(int32_t locIndex = glGetProgramResourceLocationIndex(*this, ENUM(interface), name));
	return locIndex;
}

int32_t Program::GetResourceName(ProgramInterface interface, uint32_t index, int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetProgramResourceName(*this, ENUM(interface), index, bufSize, &length, name));
	return length;
}

std::string Program::GetResourceName(ProgramInterface interface, uint32_t index) const
{
	int32_t bufSize = GetResourceNameLength(interface, index);
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetResourceName(interface, index, bufSize, buf.get());
	return std::string(buf.get(), length);
}

void Program::GetResourceProps(ProgramInterface interface, uint32_t index, int32_t propCount, const ProgramResourceProp* props, int32_t bufSize, int32_t* length, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetProgramResourceiv(*this, ENUM(interface), index, propCount, reinterpret_cast<const GLenum*>(props), bufSize, length, value));
}

void Program::GetResourceProp(ProgramInterface interface, uint32_t index, ProgramResourceProp prop, int32_t bufSize, int32_t* length, int32_t* value) const
{
	GetResourceProps(interface, index, 1, &prop, bufSize, length, value);
}

int32_t Program::GetResourcePropI(ProgramInterface interface, uint32_t index, ProgramResourceProp prop) const
{
	int32_t value = 0;
	int32_t length = 0;
	GetResourceProp(interface, index, prop, 1, &length, &value);
	return value;
}

int32_t Program::GetResourceNameLength(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::NameLength);
}

DataType Program::GetResourceType(ProgramInterface interface, uint32_t index) const\
{
	return static_cast<DataType>(GetResourcePropI(interface, index, ProgramResourceProp::Type));
}

int32_t Program::GetResourceArraySize(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ArraySize);
}

int32_t Program::GetResourceOffset(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::Offset);
}

int32_t Program::GetResourceBlockIndex(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::BlockIndex);
}

int32_t Program::GetResourceArrayStride(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ArrayStride);
}

int32_t Program::GetResourceMatrixStride(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::MatrixStride);
}

bool Program::IsResourceRowMajor(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::IsRowMajor) == GL_TRUE;
}

int32_t Program::GetResourceAtomicCounterBufferIndex(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::AtomicCounterBufferIndex);
}

int32_t Program::GetResourceTextureBuffer(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::TextureBuffer);
}

int32_t Program::GetResourceBufferBinding(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::BufferBinding);
}

int32_t Program::GetResourceBufferDataSize(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::BufferDataSize);
}

int32_t Program::GetResourceNumActiveVariables(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::NumActiveVariables);
}

std::vector<int32_t> Program::GetResourceActiveVariables(ProgramInterface interface, uint32_t index) const
{
	int32_t count = GetResourceNumActiveVariables(interface, index);
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	int32_t length = 0;
	GetResourceProp(interface, index, ProgramResourceProp::ActiveVariables, count, &length, v.data());
	return std::move(v);
}

bool Program::IsResourceReferencedByVertexShader(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ReferencedByVertexShader) == GL_TRUE;
}

bool Program::IsResourceReferencedByTessControlShader(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ReferencedByTessControlShader) == GL_TRUE;
}

bool Program::IsResourceReferencedByTessEvaluationShader(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ReferencedByTessEvaluationShader) == GL_TRUE;
}

bool Program::IsResourceReferencedByGeometryShader(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ReferencedByGeometryShader) == GL_TRUE;
}

bool Program::IsResourceReferencedByFragmentShader(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ReferencedByFragmentShader) == GL_TRUE;
}

bool Program::IsResourceReferencedByComputeShader(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::ReferencedByComputeShader) == GL_TRUE;
}

int32_t Program::GetResourceNumCompatibleSubroutines(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::NumCompatibleSubroutines);
}

std::vector<int32_t> Program::GetResourceCompatibleSubroutines(ProgramInterface interface, uint32_t index) const
{
	int32_t count = GetResourceNumCompatibleSubroutines(interface, index);
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	int32_t length = 0;
	GetResourceProp(interface, index, ProgramResourceProp::CompatibleSubroutines, count, &length, v.data());
	return std::move(v);
}

int32_t Program::GetResourceTopLevelArraySize(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::TopLevelArraySize);
}

int32_t Program::GetResourceTopLevelArrayStride(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::TopLevelArrayStride);
}

int32_t Program::GetResourceLocation(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::Location);
}

int32_t Program::GetResourceLocationIndex(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::LocationIndex);
}

bool Program::IsResourcePerPatch(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::IsPerPatch) == GL_TRUE;
}

int32_t Program::GetResourceLocationComponent(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::LocationComponent);
}

int32_t Program::GetResourceTransformFeedbackBufferIndex(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::TransformFeedbackBufferIndex);
}

int32_t Program::GetResourceTransformFeedbackBufferStride(ProgramInterface interface, uint32_t index) const
{
	return GetResourcePropI(interface, index, ProgramResourceProp::TransformFeedbackBufferStride);
}

void Program::GetBinary(int32_t bufSize, int32_t* length, uint32_t* format, void* binary) const
{
	GLUTIL_GL_CALL(glGetProgramBinary(*this, bufSize, length, format, binary));
}

std::vector<char> Program::GetBinary(uint32_t* format) const
{
	uint32_t tmp = 0;
	if (!format)
		format = &tmp;

	int32_t size = GetBinaryLength();
	if (!size)
		return std::vector<char>();

	std::vector<char> v(size, 0);
	GetBinary(size, nullptr, format, v.data());
	return std::move(v);
}

int32_t Program::GetInfoLog(int32_t maxLength, char* log) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetProgramInfoLog(*this, maxLength, &length, log));
	return length;
}

std::string Program::GetInfoLog() const
{
	int32_t bufSize = GetInfoLogLength();
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetInfoLog(bufSize, buf.get());
	return std::string(buf.get(), length);
}

void Program::GetParam(ProgramParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetProgramiv(*this, ENUM(pname), value));
}

int32_t Program::GetParamI(ProgramParam pname) const
{
	int32_t value = 0;
	GetParam(pname, &value);
	return value;
}

bool Program::IsFlaggedForDelete() const
{
	return GetParamI(ProgramParam::DeleteStatus) == GL_TRUE;
}

bool Program::IsLinked() const
{
	return GetParamI(ProgramParam::LinkStatus) == GL_TRUE;
}

bool Program::IsValidated() const
{
	return GetParamI(ProgramParam::ValidateStatus) == GL_TRUE;
}

int32_t Program::GetInfoLogLength() const
{
	return GetParamI(ProgramParam::InfoLogLength) == GL_TRUE;
}

int32_t Program::GetNumAttachedShaders() const
{
	return GetParamI(ProgramParam::NumAttachedShaders);
}

int32_t Program::GetNumActiveAtomicCounterBuffers() const
{
	return GetParamI(ProgramParam::NumActiveAtomicCounterBuffers);
}
int32_t Program::GetNumActiveAttributes() const
{
	return GetParamI(ProgramParam::NumActiveAttributes);
}

int32_t Program::GetActiveAttributeMaxLength() const
{
	return GetParamI(ProgramParam::ActiveAttributeMaxLength);
}

int32_t Program::GetNumActiveUniforms() const
{
	return GetParamI(ProgramParam::NumActiveUniforms);
}

int32_t Program::GetActiveUniformMaxLength() const
{
	return GetParamI(ProgramParam::ActiveUniformMaxLength);
}

int32_t Program::GetBinaryLength() const
{
	return GetParamI(ProgramParam::BinaryLength);
}

Vec3i Program::GetComputeWorkgroupSize() const
{
	Vec3i r;
	GetParam(ProgramParam::ComputeWorkgroupSize, r.v);
	return r;
}

TransformFeedbackBufferMode Program::GetTansformFeedbackBufferMode() const
{
	return static_cast<TransformFeedbackBufferMode>(GetParamI(ProgramParam::TransformFeedbackBufferMode));
}

int32_t Program::GetNumTransformFeedbackVaryings() const
{
	return GetParamI(ProgramParam::NumTransformFeedbackVaryings);
}

int32_t Program::GetTransformFeedbackVaryingMaxLength() const
{
	return GetParamI(ProgramParam::TransformFeedbackVaryingMaxLength);
}

int32_t Program::GetGeometryVerticesOut() const
{
	return GetParamI(ProgramParam::GeometryVerticesOut);
}

PrimitiveType Program::GetGeometryInputType() const
{
	return static_cast<PrimitiveType>(GetParamI(ProgramParam::GeometryInputType));
}

PrimitiveType Program::GetGeometryOutputType() const
{
	return static_cast<PrimitiveType>(GetParamI(ProgramParam::GeometryOutputType));
}

}