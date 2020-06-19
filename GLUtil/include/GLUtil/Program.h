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
	std::string name;
	DataType type;
	int32_t size;
};

struct ActiveUniform
{
	std::string name;
	DataType type;
	int32_t size;
};

struct AttachedShaders
{
	int32_t count;
	uint32_t shaders[6];
};

class Program : GLObject
{
public:
	Program& BindAttribLocation(uint32_t index, const char* name);
	Program& BindFragDataLocation(uint32_t colorNumber, const char* name);
	Program& BindFragDataLocationIndexed(uint32_t colorNumber, uint32_t index, const char* name);
	Program& StorageBlockBinding(uint32_t index, uint32_t binding);

	Program& AttachShader(uint32_t shader);
	Program& DetachShader(uint32_t shader);

	bool Binary(uint32_t format, const void* binary, int32_t length);
	bool Link();
	bool Validate();

	void GetAttachedShaders(int32_t maxCount, int32_t* count, uint32_t* shaders) const;
	AttachedShaders GetAttachedShaders() const;

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

	int32_t GetAttribLocation(const char* name) const;
	int32_t GetFragDataIndex(const char* name) const;
	int32_t GetFragDataLocation(const char* name) const;

	void GetActiveAttrib(uint32_t index, int32_t nameBufSize, int32_t* nameLength, int32_t* size, DataType* type, char* name) const;
	ActiveAttrib GetActiveAttrib(uint32_t index) const;
	
	int32_t GetUniformLocation(const char* name) const;

	void GetActiveUniform(uint32_t index, int32_t nameBufSize, int32_t* nameLength, int32_t* size, DataType* type, char* name) const;
	ActiveUniform GetActiveUniform(uint32_t index) const;

	int32_t GetActiveUniformName(uint32_t index, int32_t bufSize, char* name) const;
	std::string GetActiveUniformName(uint32_t index) const;

	void GetActiveUniformsParam(int32_t count, const uint32_t* indices, UniformParam pname, int32_t* value) const;
	void GetActiveUniformParam(uint32_t index, UniformParam pname, int32_t* value) const;
	int32_t GetActiveUniformParamI(uint32_t index, UniformParam pname) const;

	DataType GetActiveUniformType(uint32_t index) const;
	int32_t GetActiveUniformSize(uint32_t index) const;
	int32_t GetActiveUniformNameLength(uint32_t index) const;
	uint32_t GetActiveUniformBlockIndex(uint32_t index) const;
	int32_t GetActiveUniformOffset(uint32_t index) const;
	int32_t GetActiveUniformArrayStride(uint32_t index) const;
	int32_t GetActiveUniformMatrixStride(uint32_t index) const;
	bool IsActiveUniformRowMajor(uint32_t index) const;
	uint32_t GetActiveUniformAtomicCounterBufferIndex(uint32_t index) const;

	void GetUniform(int32_t location, float* value) const;
	void GetUniform(int32_t location, int32_t* value) const;
	void GetUniform(int32_t location, uint32_t* value) const;
	void GetUniform(int32_t location, double* value) const;
	void GetUniform(int32_t location, int32_t bufSize, float* value) const;
	void GetUniform(int32_t location, int32_t bufSize, int32_t* value) const;
	void GetUniform(int32_t location, int32_t bufSize, uint32_t* value) const;
	void GetUniform(int32_t location, int32_t bufSize, double* value) const;

	float GetUniformFloat(int32_t location) const;
	Vec2f GetUniformFloatVec2(int32_t location) const;
	Vec3f GetUniformFloatVec3(int32_t location) const;
	Vec4f GetUniformFloatVec4(int32_t location) const;
	Mat2f GetUniformFloatMat2(int32_t location) const;
	Mat3f GetUniformFloatMat3(int32_t location) const;
	Mat4f GetUniformFloatMat4(int32_t location) const;
	Mat2x3f GetUniformFloatMat2x3(int32_t location) const;
	Mat2x4f GetUniformFloatMat2x4(int32_t location) const;
	Mat3x2f GetUniformFloatMat3x2(int32_t location) const;
	Mat3x4f GetUniformFloatMat3x4(int32_t location) const;
	Mat4x2f GetUniformFloatMat4x2(int32_t location) const;
	Mat4x3f GetUniformFloatMat4x3(int32_t location) const;

	int32_t GetUniformInt(int32_t location) const;
	Vec2i GetUniformIntVec2(int32_t location) const;
	Vec3i GetUniformIntVec3(int32_t location) const;
	Vec4i GetUniformIntVec4(int32_t location) const;

	int32_t GetUniformUnsignedInt(int32_t location) const;
	Vec2i GetUniformUnsignedIntVec2(int32_t location) const;
	Vec3i GetUniformUnsignedIntVec3(int32_t location) const;
	Vec4i GetUniformUnsignedIntVec4(int32_t location) const;

	double GetUniformDouble(int32_t location) const;
	Vec2d GetUniformDoubleVec2(int32_t location) const;
	Vec3d GetUniformDoubleVec3(int32_t location) const;
	Vec4d GetUniformDoubleVec4(int32_t location) const;
	Mat2d GetUniformDoubleMat2(int32_t location) const;
	Mat3d GetUniformDoubleMat3(int32_t location) const;
	Mat4d GetUniformDoubleMat4(int32_t location) const;
	Mat2x3d GetUniformDoubleMat2x3(int32_t location) const;
	Mat2x4d GetUniformDoubleMat2x4(int32_t location) const;
	Mat3x2d GetUniformDoubleMat3x2(int32_t location) const;
	Mat3x4d GetUniformDoubleMat3x4(int32_t location) const;
	Mat4x2d GetUniformDoubleMat4x2(int32_t location) const;
	Mat4x3d GetUniformDoubleMat4x3(int32_t location) const;

	uint32_t GetUniformBlockIndex(const char* name) const;

	Program& UniformBlockBinding(uint32_t index, uint32_t binding);

	int32_t GetActiveUniformBlockName(uint32_t index, int32_t bufSize, char* name) const;
	std::string GetActiveUniformBlockName(uint32_t index) const;

	void GetActiveUniformBlockParam(uint32_t index, UniformBlockParam pname, int32_t* value) const;
	int32_t GetActiveUniformBlockParamI(uint32_t index, UniformBlockParam pname) const;

	uint32_t GetActiveUniformBlockBinding(uint32_t index) const;
	int32_t GetActiveUniformBlockDataSize(uint32_t index) const;
	int32_t GetActiveUniformBlockNameLength(uint32_t index) const;
	int32_t GetActiveUniformBlockNumActiveUniforms(uint32_t index) const;
	std::vector<int32_t> GetActiveUniformBlockActiveUniformIndices(uint32_t index) const;
	bool IsActiveUniformBlockReferencedByVertexShader(uint32_t index) const;
	bool IsActiveUniformBlockReferencedByTessControlShader(uint32_t index) const;
	bool IsActiveUniformBlockReferencedByTessEvaluationShader(uint32_t index) const;
	bool IsActiveUniformBlockReferencedByGeometryShader(uint32_t index) const;
	bool IsActiveUniformBlockReferencedByFragmentShader(uint32_t index) const;
	bool IsActiveUniformBlockReferencedByComputeShader(uint32_t index) const;

	uint32_t GetSubroutineIndex(ShaderType shaderType, const char* name) const;
	int32_t GetSubroutineUniformLocation(ShaderType shaderType, const char* name) const;

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

	void GetStageParam(ShaderType shaderType, ProgramStageParam pname, int32_t* value) const;
	int32_t GetStageParamI(ShaderType shaderType, ProgramStageParam pname) const;

	int32_t GetStageNumActiveSubroutineUniforms(ShaderType shaderType) const;
	int32_t GetStageNumActiveSubroutineUniformLocations(ShaderType shaderType) const;
	int32_t GetStageNumActiveSubroutines(ShaderType shaderType) const;
	int32_t GetStageActiveSubroutineMaxLength(ShaderType shaderType) const;
	int32_t GetStageActiveSubroutineUniformMaxLength(ShaderType shaderType) const;

	uint32_t GetResourceIndex(ProgramInterface interface, const char* name) const;
	int32_t GetResourceLocation(ProgramInterface interface, const char* name) const;
	int32_t GetResourceLocationIndex(ProgramInterface interface, const char* name) const;

	int32_t GetResourceName(ProgramInterface interface, uint32_t index, int32_t bufSize, char* name) const;
	std::string GetResourceName(ProgramInterface interface, uint32_t index) const;

	void GetResourceProps(ProgramInterface interface, uint32_t index, int32_t propCount, const ProgramResourceProp* props, int32_t bufSize, int32_t* length, int32_t* value) const;
	void GetResourceProp(ProgramInterface interface, uint32_t index, ProgramResourceProp prop, int32_t bufSize, int32_t* length, int32_t* value) const;
	int32_t GetResourcePropI(ProgramInterface interface, uint32_t index, ProgramResourceProp prop) const;

	int32_t GetResourceNameLength(ProgramInterface interface, uint32_t index) const;
	DataType GetResourceType(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceArraySize(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceOffset(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceBlockIndex(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceArrayStride(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceMatrixStride(ProgramInterface interface, uint32_t index) const;
	bool IsResourceRowMajor(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceAtomicCounterBufferIndex(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceTextureBuffer(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceBufferBinding(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceBufferDataSize(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceNumActiveVariables(ProgramInterface interface, uint32_t index) const;
	std::vector<int32_t> GetResourceActiveVariables(ProgramInterface interface, uint32_t index) const;
	bool IsResourceReferencedByVertexShader(ProgramInterface interface, uint32_t index) const;
	bool IsResourceReferencedByTessControlShader(ProgramInterface interface, uint32_t index) const;
	bool IsResourceReferencedByTessEvaluationShader(ProgramInterface interface, uint32_t index) const;
	bool IsResourceReferencedByGeometryShader(ProgramInterface interface, uint32_t index) const;
	bool IsResourceReferencedByFragmentShader(ProgramInterface interface, uint32_t index) const;
	bool IsResourceReferencedByComputeShader(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceNumCompatibleSubroutines(ProgramInterface interface, uint32_t index) const;
	std::vector<int32_t> GetResourceCompatibleSubroutines(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceTopLevelArraySize(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceTopLevelArrayStride(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceLocation(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceLocationIndex(ProgramInterface interface, uint32_t index) const;
	bool IsResourcePerPatch(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceLocationComponent(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceTransformFeedbackBufferIndex(ProgramInterface interface, uint32_t index) const;
	int32_t GetResourceTransformFeedbackBufferStride(ProgramInterface interface, uint32_t index) const;

	void GetBinary(int32_t bufSize, int32_t* length, uint32_t* format, void* binary) const;
	std::vector<char> GetBinary(uint32_t* format = nullptr) const;

	int32_t GetInfoLog(int32_t maxLength, char* log) const;
	std::string GetInfoLog() const;

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