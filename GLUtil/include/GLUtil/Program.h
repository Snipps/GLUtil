#pragma once

#include "Common.h"
#include "Object.h"
#include "Math.h"
#include "Shader.h"

#include <vector>

namespace GLUtil {

enum class TransformFeedbackBufferMode : uint32_t
{
	SeparateAttribs,
	InterleavedAttribs
};

enum class PrimitiveType : uint32_t
{
	Points,
	Lines,
	LineStrip,
	LineLoop,
	LineList,
	LineStripAdjacency,
	LinesAdjacency,
	Triangles,
	TriangleStrip,
	TriangleFan,
	TriangleStripAdjacency,
	TrianglesAdjacency,
	Patches
};

enum class ProgramParam : uint32_t
{
	DeleteStatus,
	LinkStatus,
	ValidateStatus,
	InfoLogLength,
	NumAttachedShaders,
	NumActiveAtomicCounterBuffers,
	NumActiveAttributes,
	ActiveAttributeMaxLength,
	NumActiveUniforms,
	ActiveUniformMaxLength,
	BinaryLength,
	ComputeWorkgroupSize,
	TransformFeedbackBufferMode,
	NumTransformFeedbackVaryings,
	TransformFeedbackVaryingMaxLength,
	GeometryVerticesOut,
	GeometryInputType,
	GeometryOutputType
};

enum class AtomicCounterBufferParam : uint32_t
{
	Binding,
	DataSize,
	NumActiveAtomicCounters,
	ActiveAtomicCounterIndices,
	ReferencedByVertexShader,
	ReferencedByTessControlShader,
	ReferencedByTessEvaluationShader,
	ReferencedByGeometryShader,
	ReferencedByFragmentShader,
	ReferencedByComputeShader,
};

enum class SubroutineUniformParam : uint32_t
{
	NumCompatibleSubroutines,
	CompatibleSubroutines,
	Size,
	NameLength
};

enum class ProgramStageParam : uint32_t
{
	NumActiveSubroutineUniforms,
	NumActiveSubroutineUniformLocations,
	NumActiveSubroutines,
	ActiveSubroutineMaxLength,
	ActiveSubroutineUniformMaxLength
};

enum class UniformParam : uint32_t
{
	Type,
	Size,
	NameLength,
	BlockIndex,
	Offset,
	ArrayStride,
	MatrixStride,
	IsRowMajor,
	AtomicCounterBufferIndex
};

enum class UniformBlockParam : uint32_t
{
	Binding,
	DataSize,
	NameLength,
	NumActiveUniforms,
	ActiveUniformIndices,
	ReferencedByVertexShader,
	ReferencedByTessControlShader,
	ReferencedByTessEvaluationShader,
	ReferencedByGeometryShader,
	ReferencedByFragmentShader,
	ReferencedByComputeShader
};

enum class ProgramInterface : uint32_t
{
	AtomicCounterBuffer,
	TransformFeedbackBuffer,
	ProgramInput,
	ProgramOutput,
	Uniform,
	TransformFeedbackVarying,
	BufferVariable,
	VertexSubroutineUniform,
	TessControlSubroutineUniform,
	TessEvaluationSubroutineUniform,
	GeometrySubroutineUniform,
	FragmentSubroutineUniform,
	ComputeSubroutineUniform,
	VertexSubroutine,
	TessControlSubroutine,
	TessEvaluationSubroutine,
	GeometrySubroutine,
	FragmentSubroutine,
	ComputeSubroutine,
	UniformBlock,
	ShaderStorageBlock,
	AtomicCounterShader,
};

enum class ProgramResourceProp
{
	NameLength,
	Type,
	ArraySize,
	Offset,
	BlockIndex,
	ArrayStride,
	MatrixStride,
	IsRowMajor,
	AtomicCounterBufferIndex,
	TextureBuffer,
	BufferBinding,
	BufferDataSize,
	NumActiveVariables,
	ActiveVariables,
	ReferencedByVertexShader,
	ReferencedByTessControlShader,
	ReferencedByTessEvaluationShader,
	ReferencedByGeometryShader,
	ReferencedByFragmentShader,
	ReferencedByComputeShader,
	NumCompatibleSubroutines,
	CompatibleSubroutines,
	TopLevelArraySize,
	TopLevelArrayStride,
	Location,
	LocationIndex,
	IsPerPatch,
	LocationComponent,
	TransformFeedbackBufferIndex,
	TransformFeedbackBufferStride
};

struct ActiveAttrib
{
	char* name;
	int32_t nameLength;
	DataType type;
	int32_t size;

	~ActiveAttrib();
};

struct ActiveUniform
{
	char* name;
	int32_t nameLength;
	DataType type;
	int32_t size;

	~ActiveUniform();
};

struct AttachedShaders
{
	int32_t count;
	uint32_t shaders[6];
};

class ProgramResource
{
private:
	uint32_t mProgram;
	ProgramInterface mInterface;
	uint32_t mIndex;
public:
	int32_t GetName(int32_t bufSize, char* name) const;
	std::string GetName() const;

	void GetProps(int32_t propCount, const ProgramResourceProp* props, int32_t bufSize, int32_t* length, int32_t* value) const;
	void GetProp(ProgramResourceProp prop, int32_t bufSize, int32_t* length, int32_t* value) const;
	int32_t GetPropI(ProgramResourceProp prop) const;

	int32_t GetNameLength() const;
	DataType GetType() const;
	int32_t GetArraySize() const;
	int32_t GetOffset() const;
	int32_t GetBlockIndex() const;
	int32_t GetArrayStride() const;
	int32_t GetMatrixStride() const;
	bool IsRowMajor() const;
	int32_t GetAtomicCounterBufferIndex() const;
	int32_t GetTextureBuffer() const;
	int32_t GetBufferBinding() const;
	int32_t GetBufferDataSize() const;
	int32_t GetNumActiveVariables() const;
	std::vector<int32_t> GetActiveVariables() const;
	bool IsReferencedByVertexShader() const;
	bool IsReferencedByTessControlShader() const;
	bool IsReferencedByTessEvaluationShader() const;
	bool IsReferencedByGeometryShader() const;
	bool IsReferencedByFragmentShader() const;
	bool IsReferencedByComputeShader() const;
	int32_t GetNumCompatibleSubroutines() const;
	std::vector<int32_t> GetCompatibleSubroutines() const;
	int32_t GetTopLevelArraySize() const;
	int32_t GetTopLevelArrayStride() const;
	int32_t GetLocation() const;
	int32_t GetLocationIndex() const;
	bool IsPerPatch() const;
	int32_t GetLocationComponent() const;
	int32_t GetTransformFeedbackBufferIndex() const;
	int32_t GetTransformFeedbackBufferStride() const;
};

class ProgramUniformBlock
{
private:
	uint32_t mProgram;
	uint32_t mIndex;
public:
	ProgramUniformBlock& Binding(uint32_t binding);

	int32_t GetName(int32_t bufSize, char* name) const;
	std::string GetName() const;

	void GetParam(UniformBlockParam pname, int32_t* value) const;
	int32_t GetParamI(UniformBlockParam pname) const;

	uint32_t GetBinding() const;
	int32_t GetDataSize() const;
	int32_t GetNameLength() const;
	int32_t GetNumActiveUniforms() const;
	std::vector<int32_t> GetActiveUniformIndices() const;
	bool IsReferencedByVertexShader() const;
	bool IsReferencedByTessControlShader() const;
	bool IsReferencedByTessEvaluationShader() const;
	bool IsReferencedByGeometryShader() const;
	bool IsReferencedByFragmentShader() const;
	bool IsReferencedByComputeShader() const;
};

class ProgramUniform
{
private:
	uint32_t mProgram;
	int32_t mLocation;
	uint32_t mIndex;
public:
	int32_t GetName(int32_t bufSize, char* name) const;
	std::string GetName() const;

	void GetParam(UniformParam pname, int32_t* value) const;
	int32_t GetParamI(UniformParam pname) const;

	DataType GetType() const;
	int32_t GetSize() const;
	int32_t GetNameLength() const;
	uint32_t GetBlockIndex() const;
	int32_t GetOffset() const;
	int32_t GetArrayStride() const;
	int32_t GetMatrixStride() const;
	bool IsRowMajor() const;
	uint32_t GetAtomicCounterBufferIndex() const;

	void Get(float* value) const;
	void Get(int32_t* value) const;
	void Get(uint32_t* value) const;
	void Get(double* value) const;
	void Get(int32_t bufSize, float* value) const;
	void Get(int32_t bufSize, int32_t* value) const;
	void Get(int32_t bufSize, uint32_t* value) const;
	void Get(int32_t bufSize, double* value) const;

	float GetFloat() const;
	Vec2f GetFloatVec2() const;
	Vec3f GetFloatVec3() const;
	Vec4f GetFloatVec4() const;
	Mat2f GetFloatMat2() const;
	Mat3f GetFloatMat3() const;
	Mat4f GetFloatMat4() const;
	Mat2x3f GetFloatMat2x3() const;
	Mat2x4f GetFloatMat2x4() const;
	Mat3x2f GetFloatMat3x2() const;
	Mat3x4f GetFloatMat3x4() const;
	Mat4x2f GetFloatMat4x2() const;
	Mat4x3f GetFloatMat4x3() const;

	int32_t GetInt() const;
	Vec2i GetIntVec2() const;
	Vec3i GetIntVec3() const;
	Vec4i GetIntVec4() const;

	int32_t GetUnsignedInt() const;
	Vec2i GetUnsignedIntVec2() const;
	Vec3i GetUnsignedIntVec3() const;
	Vec4i GetUnsignedIntVec4() const;

	double GetDouble() const;
	Vec2d GetDoubleVec2() const;
	Vec3d GetDoubleVec3() const;
	Vec4d GetDoubleVec4() const;
	Mat2d GetDoubleMat2() const;
	Mat3d GetDoubleMat3() const;
	Mat4d GetDoubleMat4() const;
	Mat2x3d GetDoubleMat2x3() const;
	Mat2x4d GetDoubleMat2x4() const;
	Mat3x2d GetDoubleMat3x2() const;
	Mat3x4d GetDoubleMat3x4() const;
	Mat4x2d GetDoubleMat4x2() const;
	Mat4x3d GetDoubleMat4x3() const;

	ProgramUniform& Set(float v);
	ProgramUniform& Set(float x, float y);
	ProgramUniform& SetFloat2V(const float* v);
	ProgramUniform& Set(const Vec2f& v);
	ProgramUniform& Set(float x, float y, float z);
	ProgramUniform& SetFloat3V(const float* v);
	ProgramUniform& Set(const Vec3f& v);
	ProgramUniform& Set(float x, float y, float z, float w);
	ProgramUniform& SetFloat4V(const float* v);
	ProgramUniform& Set(const Vec4f& v);
	ProgramUniform& SetFloat2x2V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat2f& v);
	ProgramUniform& SetFloat3x3V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat3f& v);
	ProgramUniform& SetFloat4x4V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat4f& v);
	ProgramUniform& SetFloat2x3V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat2x3f& v);
	ProgramUniform& SetFloat2x4V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat2x4f& v);
	ProgramUniform& SetFloat3x2V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat3x2f& v);
	ProgramUniform& SetFloat3x4V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat3x4f& v);
	ProgramUniform& SetFloat4x2V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat4x2f& v);
	ProgramUniform& SetFloat4x3V(const float* v, bool transpose = false);
	ProgramUniform& Set(const Mat4x3f& v);

	ProgramUniform& Set(int32_t v);
	ProgramUniform& Set(int32_t x, int32_t y);
	ProgramUniform& SetInt2V(const int32_t* v);
	ProgramUniform& Set(const Vec2i& v);
	ProgramUniform& Set(int32_t x, int32_t y, int32_t z);
	ProgramUniform& SetInt3V(const int32_t* v);
	ProgramUniform& Set(const Vec3i& v);
	ProgramUniform& Set(int32_t x, int32_t y, int32_t z, int32_t w);
	ProgramUniform& SetInt4V(const int32_t* v);
	ProgramUniform& Set(const Vec4i& v);
	
	ProgramUniform& Set(uint32_t v);
	ProgramUniform& Set(uint32_t x, uint32_t y);
	ProgramUniform& SetUnsignedInt2V(const uint32_t* v);
	ProgramUniform& Set(const Vec2ui& v);
	ProgramUniform& Set(uint32_t x, uint32_t y, uint32_t z);
	ProgramUniform& SetUnsignedInt3V(const uint32_t* v);
	ProgramUniform& Set(const Vec3ui& v);
	ProgramUniform& Set(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
	ProgramUniform& SetUnsignedInt4V(const uint32_t* v);
	ProgramUniform& Set(const Vec4ui& v);

	ProgramUniform& Set(double v);
	ProgramUniform& Set(double x, double y);
	ProgramUniform& SetDouble2V(const double* v);
	ProgramUniform& Set(const Vec2d& v);
	ProgramUniform& Set(double x, double y, double z);
	ProgramUniform& SetDouble3V(const double* v);
	ProgramUniform& Set(const Vec3d& v);
	ProgramUniform& Set(double x, double y, double z, double w);
	ProgramUniform& SetDouble4V(const double* v);
	ProgramUniform& Set(const Vec4d& v);
	ProgramUniform& SetDouble2x2V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat2d& v);
	ProgramUniform& SetDouble3x3V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat3d& v);
	ProgramUniform& SetDouble4x4V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat4d& v);
	ProgramUniform& SetDouble2x3V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat2x3d& v);
	ProgramUniform& SetDouble2x4V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat2x4d& v);
	ProgramUniform& SetDouble3x2V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat3x2d& v);
	ProgramUniform& SetDouble3x4V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat3x4d& v);
	ProgramUniform& SetDouble4x2V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat4x2d& v);
	ProgramUniform& SetDouble4x3V(const double* v, bool transpose = false);
	ProgramUniform& Set(const Mat4x3d& v);
};

class PorgramAtomicCounterBuffer
{
private:
	uint32_t mProgram;
	uint32_t mBufferIndex;
public:
	void GetActiveAtomicCounterBufferParam(uint32_t bufferIndex, AtomicCounterBufferParam pname, int32_t* value) const;
	int32_t GetActiveAtomicCounterBufferParamI(uint32_t bufferIndex, AtomicCounterBufferParam pname) const;

	uint32_t GetActiveAtomicCounterBufferBinding(uint32_t bufferIndex) const;
	int32_t GetActiveAtomicCounterBufferDataSize(uint32_t bufferIndex) const;
	int32_t GetActiveAtomicCounterBufferNumActiveAtomicCounters(uint32_t bufferIndex) const;
	std::vector<int32_t> GetActiveAtomicCounterBufferAtomicCounterIndices(uint32_t bufferIndex) const;
	bool IsActiveAtomicCounterBufferReferencedByVertexShader(uint32_t bufferIndex) const;
	bool IsActiveAtomicCounterBufferReferencedByTessControlShader(uint32_t bufferIndex) const;
	bool IsActiveAtomicCounterBufferReferencedByTesEvaluationShader(uint32_t bufferIndex) const;
	bool IsActiveAtomicCounterBufferReferencedByGeometryShader(uint32_t bufferIndex) const;
	bool IsActiveAtomicCounterBufferReferencedByFragmentShader(uint32_t bufferIndex) const;
	bool IsActiveAtomicCounterBufferReferencedByComputeShader(uint32_t bufferIndex) const;
};

class ProgramSubroutine
{
private:
	int32_t GetActiveSubroutineName(ShaderType shaderType, uint32_t index, int32_t bufSize, char* name) const;
	std::string GetActiveSubroutineName(ShaderType shaderType, uint32_t index) const;

	int32_t GetActiveSubroutineUniformName(ShaderType shaderType, uint32_t index, int32_t bufSize, char* name) const;
	std::string GetActiveSubroutineUniformName(ShaderType shaderType, uint32_t index) const;

	void GetActiveSubroutineUniformParam(ShaderType shaderType, uint32_t index, SubroutineUniformParam pname, int32_t* value) const;
	int32_t GetActiveSubroutineUniformParamI(ShaderType shaderType, uint32_t index, SubroutineUniformParam pname) const;

	int32_t GetActiveSubroutineUniformNumCompatibleSubroutines(ShaderType shaderType, uint32_t index) const;
	std::vector<int32_t> GetActiveSubroutineUniformCompatibleSubroutines(ShaderType shaderType, uint32_t index) const;
	int32_t GetActiveSubroutineUniformSize(ShaderType shaderType, uint32_t index) const;
	int32_t GetActiveSubroutineUniformNameLength(ShaderType shaderType, uint32_t index) const;
};

class Program : GLObject
{
public:
	Program& BindAttribLocation(uint32_t index, const char* name);
	Program& BindFragDataLocation(uint32_t colorNumber, const char* name);
	Program& BindFragDataLocationIndexed(uint32_t colorNumber, uint32_t index, const char* name);
	Program& StorageBlockBinding(uint32_t index, uint32_t binding);
	int32_t GetAttribLocation(const char* name) const;
	int32_t GetFragDataIndex(const char* name) const;
	int32_t GetFragDataLocation(const char* name) const;

	Program& AttachShader(uint32_t shader);
	Program& DetachShader(uint32_t shader);
	void GetAttachedShaders(int32_t maxCount, int32_t* count, uint32_t* shaders) const;
	AttachedShaders GetAttachedShaders() const;

	bool Link();
	bool Validate();

	bool Binary(uint32_t format, const void* binary, int32_t length);
	void GetBinary(int32_t bufSize, int32_t* length, uint32_t* format, void* binary) const;
	std::vector<char> GetBinary(uint32_t* format = nullptr) const;

	int32_t GetInfoLog(int32_t maxLength, char* log) const;
	std::string GetInfoLog() const;

	void GetActiveAttrib(uint32_t index, int32_t nameBufSize, int32_t* nameLength, int32_t* size, DataType* type, char* name) const;
	ActiveAttrib GetActiveAttrib(uint32_t index) const;
	
	int32_t GetUniformLocation(const char* name) const;
	uint32_t GetUniformBlockIndex(const char* name) const;

	uint32_t GetSubroutineIndex(ShaderType shaderType, const char* name) const;
	int32_t GetSubroutineUniformLocation(ShaderType shaderType, const char* name) const;

	uint32_t GetResourceIndex(ProgramInterface interface, const char* name) const;
	int32_t GetResourceLocation(ProgramInterface interface, const char* name) const;
	int32_t GetResourceLocationIndex(ProgramInterface interface, const char* name) const;

	void GetStageParam(ShaderType shaderType, ProgramStageParam pname, int32_t* value) const;
	int32_t GetStageParamI(ShaderType shaderType, ProgramStageParam pname) const;

	int32_t GetStageNumActiveSubroutineUniforms(ShaderType shaderType) const;
	int32_t GetStageNumActiveSubroutineUniformLocations(ShaderType shaderType) const;
	int32_t GetStageNumActiveSubroutines(ShaderType shaderType) const;
	int32_t GetStageActiveSubroutineMaxLength(ShaderType shaderType) const;
	int32_t GetStageActiveSubroutineUniformMaxLength(ShaderType shaderType) const;

	void GetParam(ProgramParam pname, int32_t* value) const;
	int32_t GetParamI(ProgramParam pname) const;

	bool IsFlaggedForDelete() const;
	bool IsLinked() const;
	bool IsValidated() const;
	int32_t GetInfoLogLength() const;
	int32_t GetNumAttachedShaders() const;
	int32_t GetNumActiveAtomicCounterBuffers() const;
	int32_t GetNumActiveAttributes() const;
	int32_t GetActiveAttributeMaxLength() const;
	int32_t GetNumActiveUniforms() const;
	int32_t GetActiveUniformMaxLength() const;
	int32_t GetBinaryLength() const;
	Vec3i GetComputeWorkgroupSize() const;
	TransformFeedbackBufferMode GetTansformFeedbackBufferMode() const;
	int32_t GetNumTransformFeedbackVaryings() const;
	int32_t GetTransformFeedbackVaryingMaxLength() const;
	int32_t GetGeometryVerticesOut() const;
	PrimitiveType GetGeometryInputType() const;
	PrimitiveType GetGeometryOutputType() const;
};

}