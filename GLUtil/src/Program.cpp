#include <GLUtil/Program.h>

#include <glad/gl.h>

#include <memory>
#include <cstdlib>
#include <cstring>

#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

ActiveAttrib::ActiveAttrib() :
	mName(nullptr), mNameLength(0), mSize(0), mType(static_cast<DataType>(0))
{}

ActiveAttrib::ActiveAttrib(ActiveAttrib&& other) noexcept
{
	mName = other.mName;
	mNameLength = other.mNameLength;
	mSize = other.mSize;
	mType = other.mType;

	other.mName = nullptr;
	other.mNameLength = 0;
	other.mSize = 0;
	other.mType = static_cast<DataType>(0);
}

ActiveAttrib::~ActiveAttrib()
{
	free(mName);
}

ActiveAttrib& ActiveAttrib::operator=(ActiveAttrib&& other) noexcept
{
	char* tmpName = mName;
	int32_t tmpNameLength = mNameLength;
	int32_t tmpSize = mSize;
	DataType tmpType = other.mType;

	mName = other.mName;
	mNameLength = other.mNameLength;
	mSize = other.mSize;
	mType = other.mType;

	other.mName = tmpName;
	other.mNameLength = tmpNameLength;
	other.mSize = tmpSize;
	other.mType = tmpType;

	return *this;
}

const char* ActiveAttrib::GetName() const
{
	return mName;
}

int32_t ActiveAttrib::GetNameLength() const
{
	return mNameLength;
}

int32_t ActiveAttrib::GetSize() const
{
	return mSize;
}

DataType ActiveAttrib::GetType() const
{
	return mType;
}

ProgramBinary::ProgramBinary() :
	mBinary(nullptr), mLength(0), mFormat(0)
{}

/*
ProgramBinary::ProgramBinary(const ProgramBinary& other)
{
	mBinary = malloc(other.mLength);
	if (mBinary) {
		mLength = other.mLength;
		mFormat = other.mFormat;
		memcpy(mBinary, other.mBinary, mLength);
	} else {
		mLength = 0;
		mFormat = 0;
	}
}
*/

ProgramBinary::ProgramBinary(ProgramBinary&& other) noexcept
{
	mBinary = other.mBinary;
	mLength = other.mLength;
	mFormat = other.mFormat;

	other.mBinary = nullptr;
	other.mLength = 0;
	other.mFormat = 0;
}

ProgramBinary::~ProgramBinary()
{
	free(mBinary);
}

/*
ProgramBinary& ProgramBinary::operator=(const ProgramBinary& other)
{
	if (mLength >= other.mLength) {
		memset((char*)mBinary + other.mLength, 0, mLength - other.mLength);
	} else {
		free(mBinary);
		mBinary = malloc(other.mLength);
		if (!mBinary) {
			mLength = 0;
			mFormat = 0;
			return *this;
		}
	}

	memcpy(mBinary, other.mBinary, other.mLength);
	mLength = other.mLength;
	mFormat = other.mFormat;
	return *this;
}
*/

ProgramBinary& ProgramBinary::operator=(ProgramBinary&& other) noexcept
{
	void* tmpBinary = mBinary;
	int32_t tmpLength = mLength;
	uint32_t tmpFormat = mFormat;

	mBinary = other.mBinary;
	mLength = other.mLength;
	mFormat = other.mFormat;

	other.mBinary = tmpBinary;
	other.mLength = tmpLength;
	other.mFormat = tmpFormat;

	return *this;
}

const void* ProgramBinary::GetBinary() const
{
	return mBinary;
}

int32_t ProgramBinary::GetLength() const
{
	return mLength;
}

uint32_t ProgramBinary::GetFormat() const
{
	return mFormat;
}

ProgramResource::ProgramResource() :
	mProgram(0), mInterface(static_cast<ProgramInterface>(0)), mIndex(0)
{}

ProgramResource::ProgramResource(uint32_t program, ProgramInterface interface, uint32_t index) :
	mProgram(program), mInterface(interface), mIndex(index)
{}

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

uint32_t ProgramResource::GetProgram() const
{
	return mProgram;
}

ProgramInterface ProgramResource::GetInterface() const
{
	return mInterface;
}

uint32_t ProgramResource::GetIndex() const
{
	return mIndex;
}

ProgramUniformBlock::ProgramUniformBlock() :
	mProgram(0), mIndex(0)
{}

ProgramUniformBlock::ProgramUniformBlock(uint32_t program, uint32_t index) :
	mProgram(program), mIndex(index)
{}

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

void ProgramUniformBlock::GetProp(UniformBlockProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveUniformBlockiv(mProgram, mIndex, ENUM(pname), value));
}

int32_t ProgramUniformBlock::GetPropI(UniformBlockProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

uint32_t ProgramUniformBlock::GetBinding() const
{
	return GetPropI(UniformBlockProp::Binding);
}

int32_t ProgramUniformBlock::GetDataSize() const
{
	return GetPropI(UniformBlockProp::DataSize);
}

int32_t ProgramUniformBlock::GetNameLength() const
{
	return GetPropI(UniformBlockProp::NameLength);
}

int32_t ProgramUniformBlock::GetNumActiveUniforms() const
{
	return GetPropI(UniformBlockProp::NumActiveUniforms);
}

std::vector<int32_t> ProgramUniformBlock::GetActiveUniformIndices() const
{
	int32_t count = GetNumActiveUniforms();
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	GetProp(UniformBlockProp::ActiveUniformIndices, v.data());
	return std::move(v);
}

bool ProgramUniformBlock::IsReferencedByVertexShader() const
{
	return GetPropI(UniformBlockProp::ReferencedByVertexShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByTessControlShader() const
{
	return GetPropI(UniformBlockProp::ReferencedByTessControlShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByTessEvaluationShader() const
{
	return GetPropI(UniformBlockProp::ReferencedByTessEvaluationShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByGeometryShader() const
{
	return GetPropI(UniformBlockProp::ReferencedByGeometryShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByFragmentShader() const
{
	return GetPropI(UniformBlockProp::ReferencedByFragmentShader) == GL_TRUE;
}

bool ProgramUniformBlock::IsReferencedByComputeShader() const
{
	return GetPropI(UniformBlockProp::ReferencedByComputeShader) == GL_TRUE;
}

uint32_t ProgramUniformBlock::GetProgram() const
{
	return mProgram;
}

uint32_t ProgramUniformBlock::GetIndex() const
{
	return mIndex;
}

ProgramUniform::ProgramUniform() :
	mProgram(0), mLocation(0), mIndex(0)
{}

ProgramUniform::ProgramUniform(uint32_t program, int32_t location, uint32_t index) :
	mProgram(program), mLocation(location), mIndex(index)
{}

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

void ProgramUniform::GetProp(UniformProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveUniformsiv(mProgram, 1, &mIndex, ENUM(pname), value));
}

int32_t ProgramUniform::GetPropI(UniformProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

DataType ProgramUniform::GetType() const
{
	return static_cast<DataType>(GetPropI(UniformProp::Type));
}

int32_t ProgramUniform::GetSize() const
{
	return GetPropI(UniformProp::Size);
}

int32_t ProgramUniform::GetNameLength() const
{
	return GetPropI(UniformProp::NameLength);
}

uint32_t ProgramUniform::GetBlockIndex() const
{
	return GetPropI(UniformProp::BlockIndex);
}

int32_t ProgramUniform::GetOffset() const
{
	return GetPropI(UniformProp::Offset);
}

int32_t ProgramUniform::GetArrayStride() const
{
	return GetPropI(UniformProp::ArrayStride);
}

int32_t ProgramUniform::GetMatrixStride() const
{
	return GetPropI(UniformProp::MatrixStride);
}

bool ProgramUniform::IsRowMajor() const
{
	return GetPropI(UniformProp::IsRowMajor) == GL_TRUE;
}

uint32_t ProgramUniform::GetAtomicCounterBufferIndex() const
{
	return GetPropI(UniformProp::AtomicCounterBufferIndex);
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
	return *this;
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

uint32_t ProgramUniform::GetProgram() const
{
	return mProgram;
}

int32_t ProgramUniform::GetLocation() const
{
	return mLocation;
}

uint32_t ProgramUniform::GetIndex() const
{
	return mIndex;
}

ProgramAtomicCounterBuffer::ProgramAtomicCounterBuffer() :
	mProgram(0), mBufferIndex(0)
{}

ProgramAtomicCounterBuffer::ProgramAtomicCounterBuffer(uint32_t program, uint32_t bufferIndex) :
	mProgram(program), mBufferIndex(bufferIndex)
{}

void ProgramAtomicCounterBuffer::GetProp(AtomicCounterBufferProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveAtomicCounterBufferiv(mProgram, mBufferIndex, ENUM(pname), value));
}

int32_t ProgramAtomicCounterBuffer::GetPropI(AtomicCounterBufferProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

uint32_t ProgramAtomicCounterBuffer::GetBinding() const
{
	return GetPropI(AtomicCounterBufferProp::Binding);
}

int32_t ProgramAtomicCounterBuffer::GetDataSize() const
{
	return GetPropI(AtomicCounterBufferProp::DataSize);
}

int32_t ProgramAtomicCounterBuffer::GetNumActiveAtomicCounters() const
{
	return GetPropI(AtomicCounterBufferProp::NumActiveAtomicCounters);
}

std::vector<int32_t> ProgramAtomicCounterBuffer::GetActiveAtomicCounterIndices() const
{
	int32_t count = GetNumActiveAtomicCounters();
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	GetProp(AtomicCounterBufferProp::ActiveAtomicCounterIndices, v.data());
	return std::move(v);
}

bool ProgramAtomicCounterBuffer::IsReferencedByVertexShader() const
{
	return GetPropI(AtomicCounterBufferProp::ReferencedByVertexShader) == GL_TRUE;
}

bool ProgramAtomicCounterBuffer::IsReferencedByTessControlShader() const
{
	return GetPropI(AtomicCounterBufferProp::ReferencedByTessControlShader) == GL_TRUE;
}

bool ProgramAtomicCounterBuffer::IsReferencedByTesEvaluationShader() const
{
	return GetPropI(AtomicCounterBufferProp::ReferencedByTessEvaluationShader) == GL_TRUE;
}

bool ProgramAtomicCounterBuffer::IsReferencedByGeometryShader() const
{
	return GetPropI(AtomicCounterBufferProp::ReferencedByGeometryShader) == GL_TRUE;
}

bool ProgramAtomicCounterBuffer::IsReferencedByFragmentShader() const
{
	return GetPropI(AtomicCounterBufferProp::ReferencedByFragmentShader) == GL_TRUE;
}

bool ProgramAtomicCounterBuffer::IsReferencedByComputeShader() const
{
	return GetPropI(AtomicCounterBufferProp::ReferencedByComputeShader) == GL_TRUE;
}

uint32_t ProgramAtomicCounterBuffer::GetProgram() const
{
	return mProgram;
}

uint32_t ProgramAtomicCounterBuffer::GetBufferIndex() const
{
	return mBufferIndex;
}

ProgramSubroutineUniform::ProgramSubroutineUniform() :
	mProgram(0), mShaderType(static_cast<ShaderType>(0)), mIndex(0)
{}

ProgramSubroutineUniform::ProgramSubroutineUniform(uint32_t program, ShaderType shaderType, uint32_t index) :
	mProgram(program), mShaderType(shaderType), mIndex(index)
{}

int32_t ProgramSubroutineUniform::GetName(int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveSubroutineUniformName(mProgram, ENUM(mShaderType), mIndex, bufSize, &length, name));
	return length;
}

std::string ProgramSubroutineUniform::GetName() const
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

void ProgramSubroutineUniform::GetProp(SubroutineUniformProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetActiveSubroutineUniformiv(mProgram, ENUM(mShaderType), mIndex, ENUM(pname), value));
}

int32_t ProgramSubroutineUniform::GetPropI(SubroutineUniformProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

int32_t ProgramSubroutineUniform::GetNumCompatibleSubroutines() const
{
	return GetPropI(SubroutineUniformProp::NumCompatibleSubroutines);
}

std::vector<int32_t> ProgramSubroutineUniform::GetCompatibleSubroutines() const
{
	int32_t count = GetNumCompatibleSubroutines();
	if (!count)
		return std::vector<int32_t>();

	std::vector<int32_t> v(count, 0);
	GetProp(SubroutineUniformProp::CompatibleSubroutines, v.data());
	return std::move(v);
}

int32_t ProgramSubroutineUniform::GetSize() const
{
	return GetPropI(SubroutineUniformProp::Size);
}

int32_t ProgramSubroutineUniform::GetNameLength() const
{
	return GetPropI(SubroutineUniformProp::NameLength);
}

uint32_t ProgramSubroutineUniform::GetProgram() const
{
	return mProgram;
}

ShaderType ProgramSubroutineUniform::GetShaderType() const
{
	return mShaderType;
}

uint32_t ProgramSubroutineUniform::GetIndex() const
{
	return mIndex;
}

ProgramStage::ProgramStage() :
	mProgram(0), mShaderType(static_cast<ShaderType>(0))
{}

ProgramStage::ProgramStage(uint32_t program, ShaderType shaderType) :
	mProgram(program), mShaderType(shaderType)
{}

void ProgramStage::GetProp(ProgramStageProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetProgramStageiv(mProgram, ENUM(mShaderType), ENUM(pname), value));
}

int32_t ProgramStage::GetPropI(ProgramStageProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

int32_t ProgramStage::GetNumActiveSubroutineUniforms() const
{
	return GetPropI(ProgramStageProp::NumActiveSubroutineUniforms);
}

int32_t ProgramStage::GetNumActiveSubroutineUniformLocations() const
{
	return GetPropI(ProgramStageProp::NumActiveSubroutineUniformLocations);
}

int32_t ProgramStage::GetNumActiveSubroutines() const
{
	return GetPropI(ProgramStageProp::NumActiveSubroutines);
}

int32_t ProgramStage::GetActiveSubroutineMaxLength() const
{
	return GetPropI(ProgramStageProp::ActiveSubroutineMaxLength);
}

int32_t ProgramStage::GetActiveSubroutineUniformMaxLength() const
{
	return GetPropI(ProgramStageProp::ActiveSubroutineUniformMaxLength);
}

uint32_t ProgramStage::GetProgram() const
{
	return mProgram;
}

ShaderType ProgramStage::GetShaderType() const
{
	return mShaderType;
}

Program::Program() :
	GLObject(glCreateProgram())
{}

Program::Program(uint32_t program) :
	GLObject(program)
{}

Program::~Program()
{
	if (*this)
		glDeleteProgram(*this);
}

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

void Program::GetAttachedShaders(int32_t maxCount, int32_t* count, uint32_t* shaders) const
{
	GLUTIL_GL_CALL(glGetAttachedShaders(*this, maxCount, count, shaders));
}

AttachedShaders Program::GetAttachedShaders() const
{
	AttachedShaders r = { 0, { 0, 0, 0, 0, 0, 0 } };
	GetAttachedShaders(6, &r.count, r.shaders);
	return r;
}

bool Program::Binary(uint32_t format, const void* binary, int32_t length)
{
	GLUTIL_GL_CALL(glProgramBinary(*this, format, binary, length));
	return IsLinked();
}

void Program::GetBinary(int32_t bufSize, int32_t* length, uint32_t* format, void* binary) const
{
	GLUTIL_GL_CALL(glGetProgramBinary(*this, bufSize, length, format, binary));
}

ProgramBinary Program::GetBinary() const
{
	ProgramBinary binary;

	int32_t binaryLength = GetBinaryLength();
	if (!binaryLength)
		return std::move(binary);

	binary.mBinary = malloc(binaryLength);
	if (!binary.mBinary)
		return std::move(binary);

	GetBinary(binaryLength, &binary.mLength, &binary.mFormat, binary.mBinary);
	return std::move(binary);
}

bool Program::Link()
{
	GLUTIL_GL_CALL(glLinkProgram(*this));
	return IsLinked();
}

bool Program::Validate()
{
	GLUTIL_GL_CALL(glValidateProgram(*this));
	return IsValidated();
}

void Program::Use() const
{
	GLUTIL_GL_CALL(glUseProgram(*this));
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

int32_t Program::GetUniformLocation(const char* name) const
{
	GLUTIL_GL_CALL(int32_t loc = glGetUniformLocation(*this, name));
	return loc;
}

void Program::GetUniformIndices(int32_t count, const char** names, uint32_t* indices) const
{
	GLUTIL_GL_CALL(glGetUniformIndices(*this, count, names, indices));
}

uint32_t Program::GetUniformIndex(const char* name) const
{
	uint32_t index = 0;
	GetUniformIndices(1, &name, &index);
	return index;
}

ProgramUniform Program::GetUniform(const char* name) const
{
	return ProgramUniform(*this, GetUniformLocation(name), GetUniformIndex(name));
}

uint32_t Program::GetUniformBlockIndex(const char* name) const
{
	GLUTIL_GL_CALL(int32_t index = glGetUniformBlockIndex(*this, name));
	return index;
}

ProgramUniformBlock Program::GetUniformBlock(const char* name) const
{
	return ProgramUniformBlock(*this, GetUniformBlockIndex(name));
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

ProgramSubroutineUniform Program::GetSubroutineUniform(ShaderType shaderType, const char* name) const
{
	// TODO: GetSubroutineUniformLocation might not be correct here
	return ProgramSubroutineUniform(*this, shaderType, GetSubroutineUniformLocation(shaderType, name));
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

ProgramResource Program::GetResource(ProgramInterface interface, const char* name) const
{
	return ProgramResource(*this, interface, GetResourceIndex(interface, name));
}

Program& Program::BindAttribLocation(uint32_t index, const char* name)
{
	GLUTIL_GL_CALL(glBindAttribLocation(*this, index, name));
	return *this;
}

Program& Program::BindFragDataLocation(uint32_t colorNumber, const char* name)
{
	GLUTIL_GL_CALL(glBindFragDataLocation(*this, colorNumber, name));
	return *this;
}

Program& Program::BindFragDataLocationIndexed(uint32_t colorNumber, uint32_t index, const char* name)
{
	GLUTIL_GL_CALL(glBindFragDataLocationIndexed(*this, colorNumber, index, name));
	return *this;
}

Program& Program::StorageBlockBinding(uint32_t index, uint32_t binding)
{
	GLUTIL_GL_CALL(glShaderStorageBlockBinding(*this, index, binding));
	return *this;
}

Program& Program::UniformBlockBinding(uint32_t index, uint32_t binding)
{
	GLUTIL_GL_CALL(glUniformBlockBinding(*this, index, binding));
	return *this;
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

void Program::GetActiveAttrib(uint32_t index, int32_t nameBufSize, int32_t* nameLength, int32_t* size, DataType* type, char* name) const
{
	GLUTIL_GL_CALL(glGetActiveAttrib(*this, index, nameBufSize, nameLength, size, reinterpret_cast<GLenum*>(type), name));
}

ActiveAttrib Program::GetActiveAttrib(uint32_t index) const
{
	ActiveAttrib attrib;

	int32_t bufSize = GetActiveAttributeMaxLength();
	if (!bufSize)
		return std::move(attrib);

	attrib.mName = reinterpret_cast<char*>(calloc(bufSize, 1));
	if (!attrib.mName)
		return std::move(attrib);

	GetActiveAttrib(index, bufSize, &attrib.mNameLength, &attrib.mSize, &attrib.mType, attrib.mName);
	return std::move(attrib);
}

int32_t Program::GetActiveSubroutineName(ShaderType shaderType, uint32_t index, int32_t bufSize, char* name) const
{
	int32_t length = 0;
	GLUTIL_GL_CALL(glGetActiveSubroutineName(*this, ENUM(shaderType), index, bufSize, &length, name));
	return length;
}

std::string Program::GetActiveSubroutineName(ShaderType shaderType, uint32_t index) const
{
	int32_t bufSize = GetStage(shaderType).GetActiveSubroutineMaxLength();
	if (!bufSize)
		return std::string();

	std::unique_ptr<char[]> buf(new(std::nothrow) char[bufSize]);
	if (!buf)
		return std::string();

	int32_t length = GetActiveSubroutineName(shaderType, index, bufSize, buf.get());
	return std::string(buf.get(), length);
}

ProgramStage Program::GetStage(ShaderType shaderType) const
{
	return ProgramStage(*this, shaderType);
}

Program& Program::SetParam(ProgramParam pname, int32_t value)
{
	GLUTIL_GL_CALL(glProgramParameteri(*this, ENUM(pname), value));
	return *this;
}

Program& Program::SetBinaryRetrievableHint(bool binaryRetrievable)
{
	return SetParam(ProgramParam::BinaryRetrievableHint, binaryRetrievable);
}

Program& Program::SetSeperable(bool seperable)
{
	return SetParam(ProgramParam::Seperable, seperable);
}

void Program::GetProp(ProgramProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetProgramiv(*this, ENUM(pname), value));
}

int32_t Program::GetPropI(ProgramProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

bool Program::IsFlaggedForDelete() const
{
	return GetPropI(ProgramProp::DeleteStatus) == GL_TRUE;
}

bool Program::IsLinked() const
{
	return GetPropI(ProgramProp::LinkStatus) == GL_TRUE;
}

bool Program::IsValidated() const
{
	return GetPropI(ProgramProp::ValidateStatus) == GL_TRUE;
}

int32_t Program::GetInfoLogLength() const
{
	return GetPropI(ProgramProp::InfoLogLength);
}

int32_t Program::GetNumAttachedShaders() const
{
	return GetPropI(ProgramProp::NumAttachedShaders);
}

int32_t Program::GetNumActiveAtomicCounterBuffers() const
{
	return GetPropI(ProgramProp::NumActiveAtomicCounterBuffers);
}

int32_t Program::GetNumActiveAttributes() const
{
	return GetPropI(ProgramProp::NumActiveAttributes);
}

int32_t Program::GetActiveAttributeMaxLength() const
{
	return GetPropI(ProgramProp::ActiveAttributeMaxLength);
}

int32_t Program::GetNumActiveUniforms() const
{
	return GetPropI(ProgramProp::NumActiveUniforms);
}

int32_t Program::GetActiveUniformMaxLength() const
{
	return GetPropI(ProgramProp::ActiveUniformMaxLength);
}

int32_t Program::GetBinaryLength() const
{
	return GetPropI(ProgramProp::BinaryLength);
}

Vec3i Program::GetComputeWorkgroupSize() const
{
	Vec3i r;
	GetProp(ProgramProp::ComputeWorkgroupSize, r.v);
	return r;
}

TransformFeedbackBufferMode Program::GetTansformFeedbackBufferMode() const
{
	return static_cast<TransformFeedbackBufferMode>(GetPropI(ProgramProp::TransformFeedbackBufferMode));
}

int32_t Program::GetNumTransformFeedbackVaryings() const
{
	return GetPropI(ProgramProp::NumTransformFeedbackVaryings);
}

int32_t Program::GetTransformFeedbackVaryingMaxLength() const
{
	return GetPropI(ProgramProp::TransformFeedbackVaryingMaxLength);
}

int32_t Program::GetGeometryVerticesOut() const
{
	return GetPropI(ProgramProp::GeometryVerticesOut);
}

PrimitiveType Program::GetGeometryInputType() const
{
	return static_cast<PrimitiveType>(GetPropI(ProgramProp::GeometryInputType));
}

PrimitiveType Program::GetGeometryOutputType() const
{
	return static_cast<PrimitiveType>(GetPropI(ProgramProp::GeometryOutputType));
}

} // namespace GLUtil