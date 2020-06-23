#include <GLUtil/Program.h>

#include <glad/glad.h>

#include <memory>

#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

int32_t ProgramResource::GetName(int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetProgramResourceName(mProgram, ENUM(mInterface), mIndex, bufSize, &length, name));
	return length;
}

std::string ProgramResource::GetName() const
{
	int32_t bufSize = GetNameLength();
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetName(bufSize, buf.get());
	return std::string(buf.get(), length);
}

void ProgramResource::GetProps(int32_t propCount, const ProgramResourceProp* props, int32_t bufSize, int32_t* length, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetProgramResourceiv(mProgram, ENUM(mInterface), mIndex, propCount, reinterpret_cast<const GLenum*>(props), bufSize, length, value));
}

void ProgramResource::GetProp(ProgramResourceProp prop, int32_t bufSize, int32_t* length, int32_t* value) const
{
	GetProps(1, &prop, bufSize, length, value);
}

int32_t ProgramResource::GetPropI(ProgramResourceProp prop) const
{
	int32_t value = 0;
	int32_t length = 0;
	GetProp(prop, 1, &length, &value);
	return value;
}

int32_t ProgramResource::GetNameLength() const
{
	return GetPropI(ProgramResourceProp::NameLength);
}

DataType ProgramResource::GetType() const
{
	return static_cast<DataType>(GetPropI(ProgramResourceProp::Type));
}

int32_t ProgramResource::GetArraySize() const
{
	return GetPropI(ProgramResourceProp::ArraySize);
}

int32_t ProgramResource::GetOffset() const
{
	return GetPropI(ProgramResourceProp::Offset);
}

int32_t ProgramResource::GetBlockIndex() const
{
	return GetPropI(ProgramResourceProp::BlockIndex);
}

int32_t ProgramResource::GetArrayStride() const
{
	return GetPropI(ProgramResourceProp::ArraySize);
}

int32_t ProgramResource::GetMatrixStride() const
{
	return GetPropI(ProgramResourceProp::MatrixStride);
}

bool ProgramResource::IsRowMajor() const
{
	return GetPropI(ProgramResourceProp::IsRowMajor) == GL_TRUE;
}

int32_t ProgramResource::GetAtomicCounterBufferIndex() const
{
	return GetPropI(ProgramResourceProp::AtomicCounterBufferIndex);
}

int32_t ProgramResource::GetTextureBuffer() const
{
	return GetPropI(ProgramResourceProp::TextureBuffer);
}

int32_t ProgramResource::GetBufferBinding() const
{
	return GetPropI(ProgramResourceProp::BufferBinding);
}


int32_t ProgramResource::GetBufferDataSize() const
{
	return GetPropI(ProgramResourceProp::BufferDataSize);
}

int32_t ProgramResource::GetNumActiveVariables() const
{
	return GetPropI(ProgramResourceProp::NumActiveVariables);
}

std::vector<int32_t> ProgramResource::GetActiveVariables() const
{
	int32_t count = GetNumActiveVariables();
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	int32_t length = 0;
	GetProp(ProgramResourceProp::ActiveVariables, count, &length, v.data());
	return std::move(v);
}

bool ProgramResource::IsReferencedByVertexShader() const
{
	return GetPropI(ProgramResourceProp::ReferencedByVertexShader) == GL_TRUE;
}

bool ProgramResource::IsReferencedByTessControlShader() const
{
	return GetPropI(ProgramResourceProp::ReferencedByTessControlShader) == GL_TRUE;
}

bool ProgramResource::IsReferencedByTessEvaluationShader() const
{
	return GetPropI(ProgramResourceProp::ReferencedByTessEvaluationShader) == GL_TRUE;
}

bool ProgramResource::IsReferencedByGeometryShader() const
{
	return GetPropI(ProgramResourceProp::ReferencedByGeometryShader) == GL_TRUE;
}

bool ProgramResource::IsReferencedByFragmentShader() const
{
	return GetPropI(ProgramResourceProp::ReferencedByFragmentShader) == GL_TRUE;
}

bool ProgramResource::IsReferencedByComputeShader() const
{
	return GetPropI(ProgramResourceProp::ReferencedByComputeShader) == GL_TRUE;
}

int32_t ProgramResource::GetNumCompatibleSubroutines() const
{
	return GetPropI(ProgramResourceProp::NumCompatibleSubroutines);
}

std::vector<int32_t> ProgramResource::GetCompatibleSubroutines() const
{
	int32_t count = GetNumCompatibleSubroutines();
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	int32_t length = 0;
	GetProp(ProgramResourceProp::CompatibleSubroutines, count, &length, v.data());
	return std::move(v);
}

int32_t ProgramResource::GetTopLevelArraySize() const
{
	return GetPropI(ProgramResourceProp::TopLevelArraySize);
}

int32_t ProgramResource::GetTopLevelArrayStride() const
{
	return GetPropI(ProgramResourceProp::TopLevelArrayStride);
}

int32_t ProgramResource::GetLocation() const
{
	return GetPropI(ProgramResourceProp::Location);
}

int32_t ProgramResource::GetLocationIndex() const
{
	return GetPropI(ProgramResourceProp::LocationIndex);
}

bool ProgramResource::IsPerPatch() const
{
	return GetPropI(ProgramResourceProp::IsPerPatch) == GL_TRUE;
}

int32_t ProgramResource::GetLocationComponent() const
{
	return GetPropI(ProgramResourceProp::LocationComponent);
}

int32_t ProgramResource::GetTransformFeedbackBufferIndex() const
{
	return GetPropI(ProgramResourceProp::TransformFeedbackBufferIndex);
}

int32_t ProgramResource::GetTransformFeedbackBufferStride() const
{
	return GetPropI(ProgramResourceProp::TransformFeedbackBufferStride);
}

ProgramUniformBlock& ProgramUniformBlock::Binding(uint32_t binding)
{
	GLUTIL_GL_CALL(glUniformBlockBinding(mProgram, mIndex, binding));
	return *this;
}

int32_t ProgramUniformBlock::GetName(int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveUniformBlockName(mProgram, mIndex, bufSize, &length, name));
	return length;
}

std::string ProgramUniformBlock::GetName() const
{
	int32_t bufSize = GetNameLength();
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetName(bufSize, buf.get());
	return std::string(buf.get(), length);
}

void ProgramUniformBlock::GetParam(UniformBlockParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveUniformBlockiv(mProgram, mIndex, ENUM(pname), value));
}

int32_t ProgramUniformBlock::GetParamI(UniformBlockParam pname) const
{
	int32_t value = 0;
	GetParam(pname, &value);
	return value;
}

uint32_t ProgramUniformBlock::GetBinding() const
{
	return GetParamI(UniformBlockParam::Binding);
}

int32_t ProgramUniformBlock::GetDataSize() const
{
	return GetParamI(UniformBlockParam::DataSize);
}

int32_t ProgramUniformBlock::GetNameLength() const
{
	return GetParamI(UniformBlockParam::NameLength);
}

int32_t ProgramUniformBlock::GetNumActiveUniforms() const
{
	return GetParamI(UniformBlockParam::NumActiveUniforms);
}

std::vector<int32_t> ProgramUniformBlock::GetActiveUniformIndices() const
{
	int32_t count = GetNumActiveUniforms();
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	GetParam(UniformBlockParam::ActiveUniformIndices, v.data());
	return std::move(v);
}

bool ProgramUniformBlock::IsReferencedByVertexShader() const
{
	return GetParamI(UniformBlockParam::ReferencedByVertexShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByTessControlShader() const
{
	return GetParamI(UniformBlockParam::ReferencedByTessControlShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByTessEvaluationShader() const
{
	return GetParamI(UniformBlockParam::ReferencedByTessEvaluationShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByGeometryShader() const
{
	return GetParamI(UniformBlockParam::ReferencedByGeometryShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByFragmentShader() const
{
	return GetParamI(UniformBlockParam::ReferencedByFragmentShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByComputeShader() const
{
	return GetParamI(UniformBlockParam::ReferencedByComputeShader) == GL_TRUE;
}

int32_t ProgramUniform::GetName(int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveUniformName(mProgram, mIndex, bufSize, &length, name));
	return length;
}

std::string ProgramUniform::GetName() const
{
	int32_t bufSize = GetNameLength();
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetName(bufSize, buf.get());
	return std::string(buf.get(), length);
}

void ProgramUniform::GetParam(UniformParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveUniformsiv(mProgram, 1, &mIndex, ENUM(pname), value));
}

int32_t ProgramUniform::GetParamI(UniformParam pname) const
{
	int32_t value = 0;
	GetParam(pname, &value);
	return value;
}

DataType ProgramUniform::GetType() const
{
	return static_cast<DataType>(GetParamI(UniformParam::Type));
}

int32_t ProgramUniform::GetSize() const
{
	return GetParamI(UniformParam::Size);
}

int32_t ProgramUniform::GetNameLength() const
{
	return GetParamI(UniformParam::NameLength);
}

uint32_t ProgramUniform::GetBlockIndex() const
{
	return GetParamI(UniformParam::BlockIndex);
}

int32_t ProgramUniform::GetOffset() const
{
	return GetParamI(UniformParam::Offset);
}

int32_t ProgramUniform::GetArrayStride() const
{
	return GetParamI(UniformParam::ArrayStride);
}

int32_t ProgramUniform::GetMatrixStride() const
{
	return GetParamI(UniformParam::MatrixStride);
}

bool ProgramUniform::IsRowMajor() const
{
	return GetParamI(UniformParam::IsRowMajor) == GL_TRUE;
}

uint32_t ProgramUniform::GetAtomicCounterBufferIndex() const
{
	return GetParamI(UniformParam::AtomicCounterBufferIndex);
}

void ProgramUniform::Get(float* value) const
{
	GLUTIL_GL_CALL(glGetUniformfv(mProgram, mLocation, value));
}

void ProgramUniform::Get(int32_t* value) const
{
	GLUTIL_GL_CALL(glGetUniformiv(mProgram, mLocation, value));
}

void ProgramUniform::Get(uint32_t* value) const
{
	GLUTIL_GL_CALL(glGetUniformuiv(mProgram, mLocation, value));
}

void ProgramUniform::Get(double* value) const
{
	GLUTIL_GL_CALL(glGetUniformdv(mProgram, mLocation, value));
}

void ProgramUniform::Get(int32_t bufSize, float* value) const
{
	GLUTIL_GL_CALL(glGetnUniformfv(mProgram, mLocation, bufSize, value));
}

void ProgramUniform::Get(int32_t bufSize, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetnUniformiv(mProgram, mLocation, bufSize, value));
}

void ProgramUniform::Get(int32_t bufSize, uint32_t* value) const
{
	GLUTIL_GL_CALL(glGetnUniformuiv(mProgram, mLocation, bufSize, value));
}

void ProgramUniform::Get(int32_t bufSize, double* value) const
{
	GLUTIL_GL_CALL(glGetnUniformdv(mProgram, mLocation, bufSize, value));
}

float ProgramUniform::GetFloat() const
{
	float v = 0;
	Get(&v);
	return v;
}

Vec2f ProgramUniform::GetFloatVec2() const\
{
	Vec2f v;
	Get(v.v);
	return v;
}

Vec3f ProgramUniform::GetFloatVec3() const
{
	Vec3f v;
	Get(v.v);
	return v;
}

Vec4f ProgramUniform::GetFloatVec4() const
{
	Vec4f v;
	Get(v.v);
	return v;
}

Mat2f ProgramUniform::GetFloatMat2() const
{
	Mat2f v;
	Get(v.v);
	return v;
}

Mat3f ProgramUniform::GetFloatMat3() const
{
	Mat3f v;
	Get(v.v);
	return v;
}

Mat4f ProgramUniform::GetFloatMat4() const
{
	Mat4f v;
	Get(v.v);
	return v;
}

Mat2x3f ProgramUniform::GetFloatMat2x3() const
{
	Mat2x3f v;
	Get(v.v);
	return v;
}

Mat2x4f ProgramUniform::GetFloatMat2x4() const
{
	Mat2x4f v;
	Get(v.v);
	return v;
}

Mat3x2f ProgramUniform::GetFloatMat3x2() const
{
	Mat3x2f v;
	Get(v.v);
	return v;
}

Mat3x4f ProgramUniform::GetFloatMat3x4() const
{
	Mat3x4f v;
	Get(v.v);
	return v;
}

Mat4x2f ProgramUniform::GetFloatMat4x2() const
{
	Mat4x2f v;
	Get(v.v);
	return v;
}

Mat4x3f ProgramUniform::GetFloatMat4x3() const
{
	Mat4x3f v;
	Get(v.v);
	return v;
}

int32_t ProgramUniform::GetInt() const
{
	int32_t v = 0;
	Get(&v);
	return v;
}

Vec2i ProgramUniform::GetIntVec2() const
{
	Vec2i v;
	Get(v.v);
	return v;
}

Vec3i ProgramUniform::GetIntVec3() const
{
	Vec3i v;
	Get(v.v);
	return v;
}

Vec4i ProgramUniform::GetIntVec4() const
{
	Vec4i v;
	Get(v.v);
	return v;
}

int32_t ProgramUniform::GetUnsignedInt() const
{
	int32_t v = 0;
	Get(&v);
	return v;
}

Vec2i ProgramUniform::GetUnsignedIntVec2() const
{
	Vec2i v;
	Get(v.v);
	return v;
}

Vec3i ProgramUniform::GetUnsignedIntVec3() const
{
	Vec3i v;
	Get(v.v);
	return v;
}

Vec4i ProgramUniform::GetUnsignedIntVec4() const
{
	Vec4i v;
	Get(v.v);
	return v;
}


double ProgramUniform::GetDouble() const
{
	double v = 0;
	Get(&v);
	return v;
}

Vec2d ProgramUniform::GetDoubleVec2() const
{
	Vec2d v;
	Get(v.v);
	return v;
}

Vec3d ProgramUniform::GetDoubleVec3() const
{
	Vec3d v;
	Get(v.v);
	return v;
}

Vec4d ProgramUniform::GetDoubleVec4() const
{
	Vec4d v;
	Get(v.v);
	return v;
}

Mat2d ProgramUniform::GetDoubleMat2() const
{
	Mat2d v;
	Get(v.v);
	return v;
}

Mat3d ProgramUniform::GetDoubleMat3() const
{
	Mat3d v;
	Get(v.v);
	return v;
}

Mat4d ProgramUniform::GetDoubleMat4() const
{
	Mat4d v;
	Get(v.v);
	return v;
}

Mat2x3d ProgramUniform::GetDoubleMat2x3() const
{
	Mat2x3d v;
	Get(v.v);
	return v;
}

Mat2x4d ProgramUniform::GetDoubleMat2x4() const
{
	Mat2x4d v;
	Get(v.v);
	return v;
}

Mat3x2d ProgramUniform::GetDoubleMat3x2() const
{
	Mat3x2d v;
	Get(v.v);
	return v;
}

Mat3x4d ProgramUniform::GetDoubleMat3x4() const
{
	Mat3x4d v;
	Get(v.v);
	return v;
}

Mat4x2d ProgramUniform::GetDoubleMat4x2() const
{
	Mat4x2d v;
	Get(v.v);
	return v;
}

Mat4x3d ProgramUniform::GetDoubleMat4x3() const
{
	Mat4x3d v;
	Get(v.v);
	return v;
}

ProgramUniform& ProgramUniform::Set(float v)
{
	GLUTIL_GL_CALL(glProgramUniform1f(mProgram, mLocation, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(float x, float y)
{
	GLUTIL_GL_CALL(glProgramUniform2f(mProgram, mLocation, x, y));
	return *this;
}

ProgramUniform& ProgramUniform::SetFloat2V(const float* v)
{
	GLUTIL_GL_CALL(glProgramUniform2fv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec2f& v)
{
	return SetFloat2V(v.v);
}

ProgramUniform& ProgramUniform::Set(float x, float y, float z)
{
	GLUTIL_GL_CALL(glProgramUniform3f(mProgram, mLocation, x, y, z));
	return *this;
}

ProgramUniform& ProgramUniform::SetFloat3V(const float* v)
{
	GLUTIL_GL_CALL(glProgramUniform3fv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec3f& v)
{
	return SetFloat3V(v.v);
}

ProgramUniform& ProgramUniform::Set(float x, float y, float z, float w)
{
	GLUTIL_GL_CALL(glProgramUniform4f(mProgram, mLocation, x, y, z, w));
	return *this;
}

ProgramUniform& ProgramUniform::SetFloat4V(const float* v)
{
	GLUTIL_GL_CALL(glProgramUniform4fv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec4f& v)
{
	return SetFloat4V(v.v);
}

ProgramUniform& ProgramUniform::SetFloat2x2V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix2fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat2f& v)
{
	return SetFloat2x2V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat3x3V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix3fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat3f& v)
{
	return SetFloat3x3V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat4x4V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix4fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat4f& v)
{
	return SetFloat4x4V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat2x3V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix2x3fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat2x3f& v)
{
	return SetFloat2x3V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat2x4V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix2x4fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat2x4f& v)
{
	return SetFloat2x4V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat3x2V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix3x2fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat3x2f& v)
{
	return SetFloat3x2V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat3x4V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix3x4fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat3x4f& v)
{
	return SetFloat3x4V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat4x2V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix4x2fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat4x2f& v)
{
	return SetFloat4x2V(v.v, true);
}

ProgramUniform& ProgramUniform::SetFloat4x3V(const float* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix4x3fv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat4x3f& v)
{
	return SetFloat4x3V(v.v, true);
}

ProgramUniform& ProgramUniform::Set(int32_t v)
{
	GLUTIL_GL_CALL(glProgramUniform1i(mProgram, mLocation, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(int32_t x, int32_t y)
{
	GLUTIL_GL_CALL(glProgramUniform2i(mProgram, mLocation, x, y));
	return *this;
}

ProgramUniform& ProgramUniform::SetInt2V(const int32_t* v)
{
	GLUTIL_GL_CALL(glProgramUniform2iv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec2i& v)
{
	return SetInt2V(v.v);
}

ProgramUniform& ProgramUniform::Set(int32_t x, int32_t y, int32_t z)
{
	GLUTIL_GL_CALL(glProgramUniform3i(mProgram, mLocation, x, y, z));
	return *this;
}

ProgramUniform& ProgramUniform::SetInt3V(const int32_t* v)
{
	GLUTIL_GL_CALL(glProgramUniform3iv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec3i& v)
{
	return SetInt3V(v.v);
}

ProgramUniform& ProgramUniform::Set(int32_t x, int32_t y, int32_t z, int32_t w)
{
	GLUTIL_GL_CALL(glProgramUniform4i(mProgram, mLocation, x, y, z, w));
	return *this;
}

ProgramUniform& ProgramUniform::SetInt4V(const int32_t* v)
{
	GLUTIL_GL_CALL(glProgramUniform4iv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec4i& v)
{
	return SetInt4V(v.v);
}


ProgramUniform& ProgramUniform::Set(uint32_t v)
{
	GLUTIL_GL_CALL(glProgramUniform1ui(mProgram, mLocation, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(uint32_t x, uint32_t y)
{
	GLUTIL_GL_CALL(glProgramUniform2ui(mProgram, mLocation, x, y));
	return *this;
}

ProgramUniform& ProgramUniform::SetUnsignedInt2V(const uint32_t* v)
{
	GLUTIL_GL_CALL(glProgramUniform2uiv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec2ui& v)
{
	return SetUnsignedInt2V(v.v);
}

ProgramUniform& ProgramUniform::Set(uint32_t x, uint32_t y, uint32_t z)
{
	GLUTIL_GL_CALL(glProgramUniform3ui(mProgram, mLocation, x, y, z));
	return *this;
}

ProgramUniform& ProgramUniform::SetUnsignedInt3V(const uint32_t* v)
{
	GLUTIL_GL_CALL(glProgramUniform3uiv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec3ui& v)
{
	return SetUnsignedInt3V(v.v);
}

ProgramUniform& ProgramUniform::Set(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
	GLUTIL_GL_CALL(glProgramUniform4ui(mProgram, mLocation, x, y, z, w));
	return *this;
}

ProgramUniform& ProgramUniform::SetUnsignedInt4V(const uint32_t* v)
{
	GLUTIL_GL_CALL(glProgramUniform4uiv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec4ui& v)
{
	return SetUnsignedInt4V(v.v);
}

ProgramUniform& ProgramUniform::Set(double v)
{
	GLUTIL_GL_CALL(glProgramUniform1d(mProgram, mLocation, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(double x, double y)
{
	GLUTIL_GL_CALL(glProgramUniform2d(mProgram, mLocation, x, y));
	return *this;
}

ProgramUniform& ProgramUniform::SetDouble2V(const double* v)
{
	GLUTIL_GL_CALL(glProgramUniform2dv(mProgram, mLocation, 1, v));
}

ProgramUniform& ProgramUniform::Set(const Vec2d& v)
{
	return SetDouble2V(v.v);
}

ProgramUniform& ProgramUniform::Set(double x, double y, double z)
{
	GLUTIL_GL_CALL(glProgramUniform3d(mProgram, mLocation, x, y, z));
	return *this;
}

ProgramUniform& ProgramUniform::SetDouble3V(const double* v)
{
	GLUTIL_GL_CALL(glProgramUniform3dv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec3d& v)
{
	return SetDouble3V(v.v);
}

ProgramUniform& ProgramUniform::Set(double x, double y, double z, double w)
{
	GLUTIL_GL_CALL(glProgramUniform4d(mProgram, mLocation, x, y, z, w));
	return *this;
}

ProgramUniform& ProgramUniform::SetDouble4V(const double* v)
{
	GLUTIL_GL_CALL(glProgramUniform4dv(mProgram, mLocation, 1, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Vec4d& v)
{
	return SetDouble4V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble2x2V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix2dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat2d& v)
{
	return SetDouble2x2V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble3x3V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix3dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat3d& v)
{
	return SetDouble3x3V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble4x4V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix4dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat4d& v)
{
	return SetDouble4x4V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble2x3V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix2x3dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat2x3d& v)
{
	return SetDouble2x3V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble2x4V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix2x4dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat2x4d& v)
{
	return SetDouble3x4V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble3x2V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix3x2dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat3x2d& v)
{
	return SetDouble3x2V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble3x4V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix3x4dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat3x4d& v)
{
	return SetDouble3x4V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble4x2V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix4x2dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat4x2d& v)
{
	return SetDouble4x2V(v.v);
}

ProgramUniform& ProgramUniform::SetDouble4x3V(const double* v, bool transpose)
{
	GLUTIL_GL_CALL(glProgramUniformMatrix4x3dv(mProgram, mLocation, 1, transpose, v));
	return *this;
}

ProgramUniform& ProgramUniform::Set(const Mat4x3d& v)
{
	return SetDouble4x3V(v.v);
}














}