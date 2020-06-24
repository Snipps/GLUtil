#pragma once

#include "Common.h"
#include "Object.h"
#include "Math.h"
#include "Shader.h"

#include <vector>

namespace GLUtil {

enum class TransformFeedbackBufferMode : uint32_t
{
	SeparateAttribs = 0x8C8D,
	InterleavedAttribs = 0x8C8C
};

enum class PrimitiveType : uint32_t
{
	Points = 0x0000,
	Lines = 0x0001,
	LineStrip = 0x0003,
	LineLoop = 0x0002,
	//https://www.khronos.org/opengl/wiki/Geometry_Shader says this exists but not in glad.h
	//LineList = , 
	LineStripAdjacency = 0x000B,
	LinesAdjacency = 0x000A,
	Triangles = 0x0004,
	TriangleStrip = 0x0005,
	TriangleFan = 0x0006,
	TriangleStripAdjacency = 0x000D,
	TrianglesAdjacency = 0x000C,
	Patches = 0x000E
};

enum class ProgramProp : uint32_t
{
	DeleteStatus = 0x8B80,
	LinkStatus = 0x8B82,
	ValidateStatus = 0x8B83,
	InfoLogLength = 0x8B84,
	NumAttachedShaders = 0x8B85,
	NumActiveAtomicCounterBuffers = 0x92D9,
	NumActiveAttributes = 0x8B89,
	ActiveAttributeMaxLength = 0x8B8A,
	NumActiveUniforms = 0x8B86,
	ActiveUniformMaxLength = 0x8B87,
	BinaryLength = 0x8741,
	ComputeWorkgroupSize = 0x8267,
	TransformFeedbackBufferMode = 0x8C7F,
	NumTransformFeedbackVaryings = 0x8C83,
	TransformFeedbackVaryingMaxLength = 0x8C76,
	GeometryVerticesOut = 0x8916,
	GeometryInputType = 0x8917,
	GeometryOutputType = 0x8918
};

enum class AtomicCounterBufferProp : uint32_t
{
	Binding = 0x92C1,
	DataSize = 0x92C4,
	NumActiveAtomicCounters = 0x92C5,
	ActiveAtomicCounterIndices = 0x92C6,
	ReferencedByVertexShader = 0x92C7,
	ReferencedByTessControlShader = 0x92C8,
	ReferencedByTessEvaluationShader = 0x92C9,
	ReferencedByGeometryShader = 0x92CA,
	ReferencedByFragmentShader = 0x92CB,
	ReferencedByComputeShader = 0x90ED,
};

enum class SubroutineUniformProp : uint32_t
{
	NumCompatibleSubroutines = 0x8E4A,
	CompatibleSubroutines = 0x8E4B,
	Size = 0x8A38,
	NameLength = 0x8A39
};

enum class ProgramStageProp : uint32_t
{
	NumActiveSubroutineUniforms = 0x8DE6,
	NumActiveSubroutineUniformLocations = 0x8E47,
	NumActiveSubroutines = 0x8DE5,
	ActiveSubroutineMaxLength = 0x8E48,
	ActiveSubroutineUniformMaxLength = 0x8E49
};

enum class UniformProp : uint32_t
{
	Type = 0x8A37,
	Size = 0x8A38,
	NameLength = 0x8A39,
	BlockIndex = 0x8A3A,
	Offset = 0x8A3B,
	ArrayStride = 0x8A3C,
	MatrixStride = 0x8A3D,
	IsRowMajor = 0x8A3E,
	AtomicCounterBufferIndex = 0x92DA
};

enum class UniformBlockProp : uint32_t
{
	Binding = 0x8A3F,
	DataSize = 0x8A40,
	NameLength = 0x8A41,
	NumActiveUniforms = 0x8A42,
	ActiveUniformIndices = 0x8A43,
	ReferencedByVertexShader = 0x8A44,
	ReferencedByTessControlShader = 0x84F0,
	ReferencedByTessEvaluationShader = 0x84F1,
	ReferencedByGeometryShader = 0x8A45,
	ReferencedByFragmentShader = 0x8A46,
	ReferencedByComputeShader = 0x90EC
};

enum class ProgramInterface : uint32_t
{
	AtomicCounterBuffer = 0x92C0,
	TransformFeedbackBuffer = 0x8C8E,
	ProgramInput = 0x92E3,
	ProgramOutput = 0x92E4,
	Uniform = 0x92E1,
	TransformFeedbackVarying = 0x92F4,
	BufferVariable = 0x92E5,
	VertexSubroutineUniform = 0x92EE,
	TessControlSubroutineUniform = 0x92EF,
	TessEvaluationSubroutineUniform = 0x92F0,
	GeometrySubroutineUniform = 0x92F1,
	FragmentSubroutineUniform = 0x92F2,
	ComputeSubroutineUniform = 0x92F3,
	VertexSubroutine = 0x92E8,
	TessControlSubroutine = 0x92E9,
	TessEvaluationSubroutine = 0x92EA,
	GeometrySubroutine = 0x92EB,
	FragmentSubroutine = 0x92EC,
	ComputeSubroutine = 0x92ED,
	UniformBlock = 0x92E2,
	ShaderStorageBlock = 0x92E6,
	//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgramResource.xhtml says this exists but not in glad.h
	//AtomicCounterShader = ,
};

enum class ProgramResourceProp
{
	NameLength = 0x92F9,
	Type = 0x92FA,
	ArraySize = 0x92FB,
	Offset = 0x92FC,
	BlockIndex = 0x92FD,
	ArrayStride = 0x92FE,
	MatrixStride = 0x92FF,
	IsRowMajor = 0x9300,
	AtomicCounterBufferIndex = 0x9301,
	TextureBuffer = 0x8C2A,
	BufferBinding = 0x9302,
	BufferDataSize = 0x9303,
	NumActiveVariables = 0x9304,
	ActiveVariables = 0x9305,
	ReferencedByVertexShader = 0x9306,
	ReferencedByTessControlShader = 0x9307,
	ReferencedByTessEvaluationShader = 0x9308,
	ReferencedByGeometryShader = 0x9309,
	ReferencedByFragmentShader = 0x930A,
	ReferencedByComputeShader = 0x930B,
	NumCompatibleSubroutines = 0x8E4A,
	CompatibleSubroutines = 0x8E4B,
	TopLevelArraySize = 0x930C,
	TopLevelArrayStride = 0x930D,
	Location = 0x930E,
	LocationIndex = 0x930F,
	IsPerPatch = 0x92E7,
	LocationComponent = 0x934A,
	TransformFeedbackBufferIndex = 0x934B,
	TransformFeedbackBufferStride = 0x934C
};

enum class ProgramParam : uint32_t
{
	BinaryRetrievableHint,
	Seperable
};

class ActiveAttrib
{
private:
	char* mName;
	int32_t mNameLength;
	int32_t mSize;
	DataType mType;

	friend class Program;
	
	ActiveAttrib();
public:
	ActiveAttrib(const ActiveAttrib&) = delete;
	ActiveAttrib& operator=(const ActiveAttrib&) = delete;

	ActiveAttrib(ActiveAttrib&& other) noexcept;
	~ActiveAttrib();

	ActiveAttrib& operator=(ActiveAttrib&& other) noexcept;

	const char* GetName() const;
	int32_t GetNameLength() const;
	int32_t GetSize() const;
	DataType GetType() const;
};

struct AttachedShaders
{
	int32_t count;
	uint32_t shaders[6];
};

class ProgramBinary
{
private:
	void* mBinary;
	int32_t mLength;
	uint32_t mFormat;

	friend class Program;

	ProgramBinary();
public:
	ProgramBinary(const ProgramBinary&) = delete;
	ProgramBinary& operator=(const ProgramBinary&) = delete;;

	ProgramBinary(ProgramBinary&& other) noexcept;
	~ProgramBinary();

	ProgramBinary& operator=(ProgramBinary&& other) noexcept;

	const void* GetBinary() const;
	int32_t GetLength() const;
	uint32_t GetFormat() const;
};

class ProgramResource
{
private:
	uint32_t mProgram;
	ProgramInterface mInterface;
	uint32_t mIndex;
public:
	ProgramResource(const ProgramResource&) = default;
	ProgramResource(ProgramResource&&) noexcept = default;
	ProgramResource& operator=(const ProgramResource&) = default;
	ProgramResource& operator=(ProgramResource&&) noexcept = default;
	~ProgramResource() = default;

	ProgramResource();
	ProgramResource(uint32_t program, ProgramInterface interface, uint32_t index);

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

	uint32_t GetProgram() const;
	ProgramInterface GetInterface() const;
	uint32_t GetIndex() const;
};

class ProgramUniformBlock
{
private:
	uint32_t mProgram;
	uint32_t mIndex;
public:
	ProgramUniformBlock(const ProgramUniformBlock&) = default;
	ProgramUniformBlock(ProgramUniformBlock&&) noexcept = default;
	ProgramUniformBlock& operator=(const ProgramUniformBlock&) = default;
	ProgramUniformBlock& operator=(ProgramUniformBlock&&) noexcept = default;
	~ProgramUniformBlock() = default;

	ProgramUniformBlock();
	ProgramUniformBlock(uint32_t program, uint32_t index);

	ProgramUniformBlock& Binding(uint32_t binding);

	int32_t GetName(int32_t bufSize, char* name) const;
	std::string GetName() const;

	void GetProp(UniformBlockProp pname, int32_t* value) const;
	int32_t GetPropI(UniformBlockProp pname) const;

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

	uint32_t GetProgram() const;
	uint32_t GetIndex() const;
};

class ProgramUniform
{
private:
	uint32_t mProgram;
	int32_t mLocation;
	uint32_t mIndex;
public:
	ProgramUniform(const ProgramUniform&) = default;
	ProgramUniform(ProgramUniform&&) noexcept = default;
	ProgramUniform& operator=(const ProgramUniform&) = default;
	ProgramUniform& operator=(ProgramUniform&&) noexcept = default;
	~ProgramUniform() = default;

	ProgramUniform();
	ProgramUniform(uint32_t program, int32_t location, uint32_t index);

	int32_t GetName(int32_t bufSize, char* name) const;
	std::string GetName() const;

	void GetProp(UniformProp pname, int32_t* value) const;
	int32_t GetPropI(UniformProp pname) const;

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

	uint32_t GetProgram() const;
	int32_t GetLocation() const;
	uint32_t GetIndex() const;
};

class ProgramAtomicCounterBuffer
{
private:
	uint32_t mProgram;
	uint32_t mBufferIndex;
public:
	ProgramAtomicCounterBuffer(const ProgramAtomicCounterBuffer&) = default;
	ProgramAtomicCounterBuffer(ProgramAtomicCounterBuffer&&) noexcept = default;
	ProgramAtomicCounterBuffer& operator=(const ProgramAtomicCounterBuffer&) = default;
	ProgramAtomicCounterBuffer& operator=(ProgramAtomicCounterBuffer&&) noexcept = default;
	~ProgramAtomicCounterBuffer() = default;

	ProgramAtomicCounterBuffer();
	ProgramAtomicCounterBuffer(uint32_t program, uint32_t bufferIndex);

	void GetProp(AtomicCounterBufferProp pname, int32_t* value) const;
	int32_t GetPropI(AtomicCounterBufferProp pname) const;

	uint32_t GetBinding() const;
	int32_t GetDataSize() const;
	int32_t GetNumActiveAtomicCounters() const;
	std::vector<int32_t> GetActiveAtomicCounterIndices() const;
	bool IsReferencedByVertexShader() const;
	bool IsReferencedByTessControlShader() const;
	bool IsReferencedByTesEvaluationShader() const;
	bool IsReferencedByGeometryShader() const;
	bool IsReferencedByFragmentShader() const;
	bool IsReferencedByComputeShader() const;

	uint32_t GetProgram() const;
	uint32_t GetBufferIndex() const;
};

class ProgramSubroutineUniform
{
private:
	uint32_t mProgram;
	ShaderType mShaderType;
	uint32_t mIndex;
public:
	ProgramSubroutineUniform(const ProgramSubroutineUniform&) = default;
	ProgramSubroutineUniform(ProgramSubroutineUniform&&) noexcept = default;
	ProgramSubroutineUniform& operator=(const ProgramSubroutineUniform&) = default;
	ProgramSubroutineUniform& operator=(ProgramSubroutineUniform&&) noexcept = default;
	~ProgramSubroutineUniform() = default;

	ProgramSubroutineUniform();
	ProgramSubroutineUniform(uint32_t program, ShaderType shaderType, uint32_t index);

	int32_t GetName(int32_t bufSize, char* name) const;
	std::string GetName() const;

	void GetProp(SubroutineUniformProp pname, int32_t* value) const;
	int32_t GetPropI(SubroutineUniformProp pname) const;

	int32_t GetNumCompatibleSubroutines() const;
	std::vector<int32_t> GetCompatibleSubroutines() const;
	int32_t GetSize() const;
	int32_t GetNameLength() const;

	uint32_t GetProgram() const;
	ShaderType GetShaderType() const;
	uint32_t GetIndex() const;
};

class ProgramStage
{
private:
	uint32_t mProgram;
	ShaderType mShaderType;
public:
	ProgramStage(const ProgramStage&) = default;
	ProgramStage(ProgramStage&&) noexcept = default;
	ProgramStage& operator=(const ProgramStage&) = default;
	ProgramStage& operator=(ProgramStage&&) noexcept = default;
	~ProgramStage() = default;

	ProgramStage();
	ProgramStage(uint32_t program, ShaderType shaderType);

	void GetProp(ProgramStageProp pname, int32_t* value) const;
	int32_t GetPropI(ProgramStageProp pname) const;

	int32_t GetNumActiveSubroutineUniforms() const;
	int32_t GetNumActiveSubroutineUniformLocations() const;
	int32_t GetNumActiveSubroutines() const;
	int32_t GetActiveSubroutineMaxLength() const;
	int32_t GetActiveSubroutineUniformMaxLength() const;

	uint32_t GetProgram() const;
	ShaderType GetShaderType() const;
};

class Program : GLObject
{
public:
	Program(const Program&) = delete;
	Program(Program&&) noexcept = default;
	Program& operator=(const Program&) = delete;
	Program& operator=(Program&&) noexcept = default;

	Program();
	Program(uint32_t program);
	virtual ~Program();

	Program& AttachShader(uint32_t shader);
	Program& DetachShader(uint32_t shader);
	void GetAttachedShaders(int32_t maxCount, int32_t* count, uint32_t* shaders) const;
	AttachedShaders GetAttachedShaders() const;

	bool Binary(uint32_t format, const void* binary, int32_t length);
	void GetBinary(int32_t bufSize, int32_t* length, uint32_t* format, void* binary) const;
	ProgramBinary GetBinary() const;

	bool Link();
	bool Validate();

	void Use() const;

	int32_t GetAttribLocation(const char* name) const;
	int32_t GetFragDataIndex(const char* name) const;
	int32_t GetFragDataLocation(const char* name) const;

	int32_t GetUniformLocation(const char* name) const;
	void GetUniformIndices(int32_t count, const char** names, uint32_t* indices) const;
	uint32_t GetUniformIndex(const char* name) const;
	ProgramUniform GetUniform(const char* name) const;

	uint32_t GetUniformBlockIndex(const char* name) const;
	ProgramUniformBlock GetUniformBlock(const char* name) const;

	uint32_t GetSubroutineIndex(ShaderType shaderType, const char* name) const;

	int32_t GetSubroutineUniformLocation(ShaderType shaderType, const char* name) const;
	ProgramSubroutineUniform GetSubroutineUniform(ShaderType shaderType, const char* name) const;

	uint32_t GetResourceIndex(ProgramInterface interface, const char* name) const;
	int32_t GetResourceLocation(ProgramInterface interface, const char* name) const;
	int32_t GetResourceLocationIndex(ProgramInterface interface, const char* name) const;
	ProgramResource GetResource(ProgramInterface interface, const char* name) const;

	Program& BindAttribLocation(uint32_t index, const char* name);
	Program& BindFragDataLocation(uint32_t colorNumber, const char* name);
	Program& BindFragDataLocationIndexed(uint32_t colorNumber, uint32_t index, const char* name);
	Program& StorageBlockBinding(uint32_t index, uint32_t binding);
	Program& UniformBlockBinding(uint32_t index, uint32_t binding);

	int32_t GetInfoLog(int32_t maxLength, char* log) const;
	std::string GetInfoLog() const;

	void GetActiveAttrib(uint32_t index, int32_t nameBufSize, int32_t* nameLength, int32_t* size, DataType* type, char* name) const;
	ActiveAttrib GetActiveAttrib(uint32_t index) const;

	int32_t GetActiveSubroutineName(ShaderType shaderType, uint32_t index, int32_t bufSize, char* name) const;
	std::string GetActiveSubroutineName(ShaderType shaderType, uint32_t index) const;

	ProgramStage GetStage(ShaderType shaderType) const;

	Program& SetParam(ProgramParam pname, int32_t value);
	Program& SetBinaryRetrievableHint(bool binaryRetrievable);
	Program& SetSeperable(bool seperable);

	void GetProp(ProgramProp pname, int32_t* value) const;
	int32_t GetPropI(ProgramProp pname) const;

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

} // namespace GLUtil