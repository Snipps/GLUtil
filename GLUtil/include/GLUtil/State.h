#pragma once

#include "Common.h"
#include "Vec.h"

namespace GLUtil {

enum class Capability
{
	Blend,
	ClipDistance,
	ColorLogicOp,
	CullFace,
	DebugOutput,
	DebugOutputSynchronous,
	DepthClamp,
	DepthTest,
	FramebufferSRGB,
	LineSmooth,
	Multisample,
	PolygonOffsetFill,
	PolygonOffsetLine,
	PolygonOffsetPoint,
	PolygonSmooth,
	PrimitiveRestart,
	PrimitiveRestartFixedIndex,
	RasterizerDiscard,
	SampleAlphaToCoverage,
	SampleAlphaToOne,
	SampleCoverage,
	SampleShading,
	SampleMask,
	ScissorTest,
	StencilTest,
	TextureCubemapSeamless,
	ProgramPointSize
};

enum class StateProp : uint32_t
{
	ActiveTexture,
	AliasedLineWidthRange,
	ArrayBufferBinding,
	BlendEnabled,
	BlendColor,
	BlendDstAlpha,
	BlendDstRGB,
	BlendEquationRGB,
	BlendEquationAlpha,
	BlendSrcAlpha,
	BlendSrcRGB,
	ColorClearValue,
	ColorLogicOp,
	ColorWriteMask,
	CompressedTextureFormats,
	MaxComputeShaderStorageBlocks,
	MaxCombinedShaderStorageBlocks,
	MaxComputeUniformBlocks,
	MaxComputeTextureImageUnits,
	MaxComputeUniformComponents,
	MaxComputeAtomicCounters,
	MaxComputeAtomicCounterBuffers,
	MaxCombinedComputeUniformComponents,
	MaxComputeWorkGroupInvocations,
	MaxComputeWorkGroupCount,
	MaxComputeWorkGroupSize,
	DispatchIndirectBufferBinding,
	MaxDebugGroupStackDepth,
	DebugGroupStackDepth,
	ContextFlags,
	CullFaceEnabled,
	CurrentProgram,
	DepthClearValue,
	DepthFunc,
	DepthRange,
	DepthTest,
	DepthWriteMask,
	DitherEnabled,
	DoublebufferEnabled,
	DrawBuffer,
	DrawFramebufferBinding,
	ReadFramebufferBinding,
	ElementArrayBufferBinding,
	FragmentShaderDerivativeHint,
	ImplementationColorReadFormat,
	ImplementationColorReadType,
	LineSmoothEnabled,
	LineSmoothHint,
	LineWidth,
	LayerProvokingVertex,
	LogicOpMode,
	MajorVersion,
	Max3DTextureSize,
	MaxClipDistances,
	MaxColorTextureSamples,
	MaxCombinedAtomicCounters,
	MaxCombinedFragmentUniformComponents,
	MaxCombinedGeometryUniformComponents,
	MaxCombinedTextureImageUnits,
	MaxCombinedUniformBlocks,
	MaxCombinedVertexUniformComponents,
	MaxCubeMapTextureSize,
	MaxDepthTextureSamples,
	MaxDrawBuffers,
	MaxDualSourceDrawBuffers,
	MaxElementsIndices,
	MaxElementsVertices,
	MaxFragmentAtomicCounters,
	MaxFragmentShaderStorageBlocks,
	MaxFragmentInputComponents,
	MaxFragmentUniformComponents,
	MaxFragmentUniformVectors,
	MaxFragmentUniformBlocks,
	MaxFramebufferWidth,
	MaxFramebufferHeight,
	MaxFramebufferLayers,
	MaxFramebufferSamples,
	MaxGeometryAtomicCounters,
	MaxGeometryShaderStorageBlocks,
	MaxGeometryInputComponents,
	MaxGeometryOutputComponents,
	MaxGeometryTextureImageUnits,
	MaxGeometryUniformBlocks,
	MaxGeometryUniformComponents,
	MaxIntegerSamples,
	MinMapBufferAlignment,
	MaxLabelLength,
	MaxProgramTexelOffset,
	MinProgramTexelOffset,
	MaxRectangleTextureSize,
	MaxRenderbufferSize,
	MaxSampleMaskWords,
	MaxServerWaitTimeout,
	MaxShaderStorageBufferBindings,
	MaxTessControlAtomicCounters,
	MaxEvaluationAtomicCounters,
	MaxTessControlShaderStorageBlocks,
	MaxTessEvaluationShaderStorageBlocks,
	MaxTextureBufferSize,
	MaxTextureLodBias,
	MaxTextureSize,
	MaxUniformBufferBindings,
	MaxUniformBlockSize,
	MaxUniformLocations,
	MaxVaryingComponents,
	MaxVaryingVectors,
	MaxVaryingFloats,
	MaxVertexAtomicCounters,
	MaxVertexAttribs,
	MaxVertexShaderStorageBlocks,
	MaxVertexTextureImageUnits,
	MaxVertexUniformComponents,
	MaxVertexUniformVectors,
	MaxVertexOutputComponents,
	MaxVertexUniformBlocks,
	MaxViewportDims,
	MaxViewpors,
	MinorVersion,
	NumCompressedTextureFormats,
	NumExtensions,
	NumProgramBinaryFormats,
	NumShaderBinaryFormats,
	PackAlignment,
	PackImageHeight,
	PackLsbFirst,
	PackRowLength,
	PackSkipImages,
	PackSkipPixels,
	PackSkipRows,
	PackSwapBytes,
	PixelPackBufferBinding,
	PixelUnpakcBufferBinding,
	PointFadeThresholdSize,
	PrimitiveRestartIndex,
	ProgramBinaryFormats,
	ProgramPipelineBinding,
	ProgramPointSize,
	ProvokingVertex,
	PointSize,
	PointSizeGranularity,
	PointSizeRange,
	PolygonOffsetFactor,
	PolygonOffsetUnits,
	PolygonOffsetFill,
	PolygonOffsetLine,
	PolygonOffsetPoint,
	PolygonSmooth,
	PolygonSmoothHint,
	ReadBuffer,
	RenderbufferBinding,
	SampleBuffers,
	SampleCoverageValue,
	SampleCoverageInvert,
	SampleMaskValue,
	SamplerBinding,
	Samples,
	ScissorBox,
	ScissorTest,
	ShaderCompiler,
	ShaderStorageBufferBinding,
	ShaderStorageBufferOffsetAlignment,
	ShaderStorageBufferStart,
	ShaderStorageBufferSize,
	SmoothLineWidthRange,
	SmoothLineWidthGranularity,
	StencilBackFail,
	StencilBackFunc,
	SteniclBackPassDepthFail,
	StencilBackPassDepthPass,
	StencilBackRef,
	StencilBackValueMask,
	StencilBackWriteMask,
	StencilClearValue,
	StencilFail,
	StencilFunc,
	StencilPassDepthFail,
	StencilPassDepthPass,
	StencilRef,
	StencilTest,
	StencilValueMask,
	StencilWriteMask,
	Stereo,
	SubpixelBits,
	TextureBinding1D,
	TextureBinding1DArray,
	TextureBinding2D,
	TextureBinding2DArray,
	TextureBinding2DMultisample,
	TextureBinding2DMultisampleArray,
	TextureBinding3D,
	TextureBindingBuffer,
	TextureBindingCubeMap,
	TextureBindingRectangle,
	TextureCompressionHint,
	TextureBufferOffsetAlignment,
	Timestamp,
	TransformFeedbackBufferBinding,
	TransformFeedbackBufferStart,
	TransformFeedbackBufferSize,
	UniformBufferBinding,
	UniformBufferOffsetAlignment,
	UniformBufferSize,
	UniformBufferStart,
	UnpackAlignment,
	UnpackImageHeight,
	UnpackLsbFirst,
	UnpackRowLength,
	UnpackSkipImages,
	UnpackSkipPixels,
	UnpackSkipRows,
	UnpackSwapBytes,
	VertexArrayBinding,
	VertexBindingDivisor,
	VertexBindingOffset,
	VertexBindingStride,
	MaxVertexAttribRelativeOffset,
	MaxVertexAttribBindings,
	Viewport,
	ViewportBoundsRange,
	ViewportIndexProvokingVertex,
	ViewportSubpixelBits,
	MaxElementIndex
};

enum class BlendEquation : uint32_t
{
	Add,
	Subtract,
	ReverseSubtract,
	Min,
	Max
};

enum class BlendFunc : uint32_t
{
	Zero,
	One,
	SrcColor,
	OneMinusSrcColor,
	DstColor,
	OneMinusDstColor,
	SrcAlpha,
	OneMinusSrcAlpha,
	DstAlpha,
	OneMinusDstAlpha,
	ConstantColor,
	OneMinusConstantColor,
	ConstantAlpha,
	OneMinusConstantAlpha,
	Src1Color,
	OneMinusSrc1Color,
	Src1Alpha,
	OneMinusSrc1Alpha
};

enum class Origin : uint32_t
{
	LowerLeft,
	UpperLeft
};

enum class ClipControlDepthMode : uint32_t
{
	NegativeOneToOne,
	ZeroToOne
};

enum class Face : uint32_t
{
	Front,
	Back,
	FrontAndBack
};

enum class FrontFaceMode : uint32_t
{
	Clockwise,
	CounterClockwise
};

enum class Hint : uint32_t
{
	FragmentShaderDerivative,
	LineSmooth,
	PolygonSmooth,
	TextureCompression
};

enum class HintPreference : uint32_t
{
	Fastest,
	Nicest,
	DontCare
};

enum class LogicOp : uint32_t
{
	Clear,
	Set,
	Copy,
	CopyInverted,
	NoOp,
	Invert,
	And,
	Nand,
	Or,
	Nor,
	Xor,
	Equiv,
	AndReverse,
	AndInverted,
	OrReverse,
	OrInverted
};

enum class PixelStoreParam : uint32_t
{
	PackSwapBytes,
	PackLsbFirst,
	PackRowLength,
	PackImageHeight,
	PackSkipPixels,
	PackSkipRows,
	PackSkipImages,
	PackAlignment,
	UnpackSwapBytes,
	UnpackLsbFirst,
	UnpackRowLength,
	UnpackImageHeight,
	UnpackSkipPixels,
	UnpackSkipRows,
	UnpackSkipImages,
	UnpackAlignment
};

enum class PolygonMode : uint32_t
{
	Point,
	Line,
	Fill
};

enum class PointParam : uint32_t
{
	FadeThresholdSize,
	SpriteCoordOrigin
};

enum class StencilOp : uint32_t
{
	Keep,
	Zero,
	Replace,
	Increment,
	IncrementWrap,
	Decrement,
	DecrementWrap,
	Invert
};

void SetHint(Hint hint, HintPreference preference);

void SetFragmentShaderDerivativeHint(HintPreference preference);
void SetLineSmoothHint(HintPreference preference);
void SetPolygonSmoothHint(HintPreference preference);
void SetTextureCompressionHint(HintPreference preference);

HintPreference GetFragmentShaderDerivativeHint();
HintPreference GetLineSmoothHint();
HintPreference GetPolygonSmoothHint();
HintPreference GetTextureCompressionHint();

void SetViewport(Vec2i offset, Vec2i size);
void SetViewport(Box box);
void SetViewport(uint32_t index, Vec2i offset, Vec2i size);
void SetViewport(uint32_t index, Box box);
void SetViewportArray(uint32_t first, int32_t count, const Box* boxes);

Box GetViewport();
Box GetViewport(uint32_t index);
Vec2i GetMaxViewportSize();
int32_t GetMaxViewports();
Vec2i GetViewportBoundsRange();
int32_t GetViewportSubpixelBits();

void SetDepthClearValueD(double depth);
void SetDepthClearValueF(float depth);
void SetDepthFunc(CompareFunc func);
void SetDepthMask(bool flag);
void SetDepthRangeD(double near, double far);
void SetDepthRangeF(float near, float far);
void SetDepthRangeArray(uint32_t first, int32_t count, const double* v);
void SetDepthRangeIndexed(uint32_t index, double near, double far);

float GetDepthClearValueF();
double GetDepthClearValueD();
int32_t GetDepthClearValueI();
int64_t GetDepthClearValueI64();
CompareFunc GetDepthFunc();
bool GetDepthMask();
Vec2f GetDepthRangeF();
Vec2d GetDepthRangeD();
Vec2i GetDepthRangeI();
Vec2i64 GetDepthRangeI64();
Vec2f GetDepthRangeF(uint32_t index);
Vec2d GetDepthRangeD(uint32_t index);
Vec2i GetDepthRangeI(uint32_t index);
Vec2i64 GetDepthRangeI64(uint32_t index);
bool GetDepthTest();

void SetStencilClearValue(int32_t value);
void SetStencilFunc(CompareFunc func, int32_t ref, uint32_t mask);
void SetStencilFunc(Face face, CompareFunc func, int32_t ref, uint32_t mask);
void SetStencilWriteMask(uint32_t mask);
void SetStencilWriteMask(Face face, uint32_t mask);
void SetStencilOp(StencilOp stencilFail, StencilOp depthFailStencilFail, StencilOp depthPassStencilPass);
void SetStencilOp(Face face, StencilOp stencilFail, StencilOp depthFailStencilFail, StencilOp depthPassStencilPass);

int32_t GetStencilClearValue();
CompareFunc GetStencilFunc();
int32_t GetStencilRef();
uint32_t GetStencilValueMask();
CompareFunc GetStencilBackFunc();
int32_t GetStencilBackRef();
uint32_t GetStencilBackValueMask();
uint32_t GetStencilWriteMask();
uint32_t GetStencilBackWriteMask();
StencilOp GetStencilFailOp();
StencilOp GetStencilPassDepthFailOp();
StencilOp GetStencilPassDepthPassOp();
StencilOp GetStencilBackFailOp();
StencilOp GetStencilBackPassDepthFailOp();
StencilOp GetStencilBackPassDepthPassOp();
bool GetStencilTest();

void SetScissorBox(Vec2i offset, Vec2i size);
void SetScissorBox(Box box);
void SetScissorBox(uint32_t index, Vec2i offset, Vec2i size);
void SetScissorBox(uint32_t index, Box box);
void SetScissorBoxArray(uint32_t first, int32_t count, const Box* boxes);

Box GetScissorBox();
Box GetScissorBox(uint32_t index);
bool GetScissorTest();

void SetBlendColor(Vec4f color);
void SetBlendEquation(BlendEquation mode);
void SetBlendEquation(uint32_t buf, BlendEquation mode);
void SetBlendEquation(BlendEquation modeRGB, BlendEquation modeAlpha);
void SetBlendEquation(uint32_t buf, BlendEquation modeRGB, BlendEquation modeAlpha);

void SetBlendFunc(BlendFunc srcFactor, BlendFunc dstFactor);
void SetBlendFunc(uint32_t buf, BlendFunc srcFactor, BlendFunc dstFactor);
void SetBlendFunc(BlendFunc srcRGB, BlendFunc dstRGB, BlendFunc srcAlpha, BlendFunc dstAlpha);
void SetBlendFunc(uint32_t buf, BlendFunc srcRGB, BlendFunc dstRGB, BlendFunc srcAlpha, BlendFunc dstAlpha);

Vec4f GetBlendColor();
BlendEquation GetBlendEquationRGB();
BlendEquation GetBlendEquationAlpha();
BlendEquation GetBlendEquationRGB(uint32_t index);
BlendEquation GetBlendEquationAlpha(uint32_t index);
BlendFunc GetBlendSrcRGBFunc();
BlendFunc GetBlendSrcAlphaFunc();
BlendFunc GetBlendDstRGBFunc();
BlendFunc GetBlendDstAlphaFunc();
BlendFunc GetBlendSrcRGBFunc(uint32_t index);
BlendFunc GetBlendSrcAlphaFunc(uint32_t index);
BlendFunc GetBlendDstRGBFunc(uint32_t index);
BlendFunc GetBlendDstAlphaFunc(uint32_t index);
bool GetBlend();

void SetClearColor(Vec4f color);
void SetClampColor(uint32_t target, bool clamp);
void SetClampColor(bool clamp);
void SetColorWriteMask(Vec4b mask);
void SetColorWriteMask(uint32_t buf, bool r, bool g, bool b, bool a);
void SetLogicOpMode(LogicOp mode);

Vec4f GetClearColor();
bool GetClampColor();
Vec4b GetColorWriteMask();
Vec4b GetColorWriteMask(uint32_t index);
LogicOp GetLogicOpMode();

void SetSampleCoverage(float value, bool invert);

float GetSampleCoverage();
bool GetSampleCoverageInvert();

void SetFrontFaceMode(FrontFaceMode mode);
void SetCullFace(Face face);

FrontFaceMode GetFrontFaceMode();
Face GetCullFace();

void SetClipControl(Origin origin, ClipControlDepthMode depth);
// TODO: find clip control gets

void SetLineWidth(float width);

float GetLineWidth();

void SetPointSize(float size);
void SetPointParamF(PointParam pname, float value);
void SetPointParamI(PointParam pname, int32_t value);
void SetPointParam(PointParam pname, const float* value);
void SetPointParam(PointParam pname, const int32_t* value);
// left off here with gets

void SetPolygonMode(Face face, PolygonMode mode);
void SetPolygonOffset(float factor, float units);

void SetPixelStoreParamF(PixelStoreParam pname, float value);
void SetPixelStoreParamI(PixelStoreParam pname, int32_t value);

void EnableCapability(Capability cap);
void EnableCapability(Capability cap, uint32_t index);
void DisableCapability(Capability cap);
void DisableCapability(Capability cap, uint32_t index);
void SetCapability(Capability cap, bool enabled);
void SetCapability(Capability cap, uint32_t index, bool enabled);

bool IsCapabilityEnabled(Capability cap);
bool IsCapabilityEnabled(Capability cap, uint32_t index);

void GetBool(StateProp pname, unsigned char* value);
void GetBool(StateProp pname, uint32_t index, unsigned char* value);
void GetDouble(StateProp pname, double* value);
void GetDouble(StateProp pname, uint32_t index, double* value);
void GetFloat(StateProp pname, float* value);
void GetFloat(StateProp pname, uint32_t index, float* value);
void GetInt(StateProp pname, int32_t* value);
void GetInt(StateProp pname, uint32_t index, int32_t* value);
void GetInt64(StateProp pname, int64_t* value);
void GetInt64(StateProp pname, uint32_t index, int64_t* value);

bool GetBool(StateProp pname);
bool GetBool(StateProp pname, uint32_t index);
double GetDouble(StateProp pname);
double GetDouble(StateProp pname, uint32_t index);
float GetFloat(StateProp pname);
float GetFloat(StateProp pname, uint32_t index);
int32_t GetInt(StateProp pname);
int32_t GetInt(StateProp pname, uint32_t index);
int64_t GetInt64(StateProp pname);
int64_t GetInt64(StateProp pname, uint32_t index);

} // namespace GLUtil