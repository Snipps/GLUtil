#pragma once

#include "Common.h"
#include "Object.h"
#include "Vec.h"
#include "Sampler.h"

namespace GLUtil {

enum class TextureInternalFormat : uint32_t
{
	R8,
	R8Snorm,
	R16,
	R16Snorm,
	RG8,
	RG8Snorm,
	RG16Snorm,
	R3G3B2,
	RGB4,
	RGB5,
	RGB8,
	RGB8Snorm,
	RGB10,
	RGB12,
	RGB16Snorm,
	RGBA2,
	RGBA4,
	RGB5A1,
	RGBA8,
	RGBA8Snorm,
	RGB10A2,
	RGB10A2UI,
	RGBA12,
	RGBA16,
	SRGB8,
	SRGB8A8,
	R16F,
	RG16F,
	RGB16F,
	RGBA16F,
	R32F,
	RG32F,
	RGB32F,
	RGBA32F,
	RG11FB10F,
	RGB9E5,
	R8I,
	R8UI,
	R16I,
	R16UI,
	RG8I,
	RG8UI,
	RG16I,
	RG16UI,
	RG32I,
	RG32UI,
	RGB8I,
	RGB8UI,
	RGB16I,
	RGB16UI,
	RGB32I,
	RGB32UI,
	RGBA8I,
	RGBA8UI,
	RGBA16I,
	RGBA16UI,
	RGBA32I,
	RGBA32UI
};

enum class TextureBaseFormat : uint32_t
{
	R,
	RG,
	RGB,
	RGBA
};

enum class TextureTarget : uint32_t
{
	Tex1D,
	Tex2D,
	Tex3D,
	Tex1DArray,
	Tex2DArray,
	TexRectangle,
	TexCubeMap,
	TexCubeMapArray,
	TexBuffer,
	Tex2DMultisample,
	Tex2DMultisampleArray,
	TexCubeMapPositiveX,
	TexCubeMapNegativeX,
	TexCubeMapPositiveY,
	TexCubeMapNegativeY,
	TexCubeMapPositiveZ,
	TexCubeMapNegativeZ
};

enum class TextureBinding : uint32_t
{
	Tex1D,
	Tex2D,
	Tex3D,
	Tex1DArray,
	Tex2DArray,
	TexRectangle,
	TexCubeMap,
	TexCubeMapArray,
	TexBuffer,
	Tex2DMultisample,
	Tex2DMultisampleArray
};

enum class TextureProp : uint32_t
{
	DepthStencilMode,
	MagFilter,
	MinFilter,
	MinLod,
	MaxLod,
	BaseLevel,
	MaxLevel,
	SwizzleR,
	SwizzleG,
	SwizzleB,
	SwizzleA,
	SwizzleRGBA,
	WrapS,
	WrapT,
	WrapR,
	BorderColor,
	CompareMode,
	CompareFunc,
	ViewMinLevel,
	ViewNumLevels,
	ViewMinLayer,
	ViewNumLayers,
	NumImmutableLevels,
	ImageFormatCompatibilityType,
	IsImmutableFormat,
	Target
};

enum class TextureParam : uint32_t
{
	DepthStencilMode,
	BaseLevel,
	BorderColor,
	CompareFunc,
	CompareMode,
	LodBias,
	MinFilter,
	MagFilter,
	MinLod,
	MaxLod,
	MaxLevel,
	SwizzleR,
	SwizzleG,
	SwizzleB,
	SwizzleA,
	SwizzleRGBA,
	WrapS,
	WrapT,
	WrapR
};

enum class TextureDepthStencilMode : uint32_t
{
	DepthComponent,
	StencilIndex
};

enum class TextureSwizzle : uint32_t
{
	Red,
	Green,
	Blue,
	Alpha,
	Zero,
	One
};

enum class TextureWrap : uint32_t
{
	ClampToEdge,
	ClampToBorder,
	MirroredRepeat,
	Repeat,
	MirrorClampToEdge
};

enum class ImageFormatCompatibilityType : uint32_t
{
	BySize,
	ByClass,
	None
};

enum class TextureLevelProp : uint32_t
{
	Width,
	Height,
	Depth,
	InternalFormat,
	RedType,
	GreenType,
	BlueType,
	AlphaType,
	DepthType,
	RedSize,
	GreenSize,
	BlueSize,
	AlphaSize,
	DepthSize,
	IsCompressed,
	CompressedImageSize,
	BufferOffset,
	BufferSize
};

enum class TextureComponentType : uint32_t
{
	None,
	SignedNormalized,
	UnsignedNormalized,
	Float,
	Int,
	UnsignedInt
};

struct TextureSwizzleRGBA
{
	TextureSwizzle swizzles[4];
};

class TextureBind
{
private:
	TextureTarget mTarget;
	uint32_t mPrev;
public:
	TextureBind() = delete;
	TextureBind(const TextureBind&) = delete;
	TextureBind(TextureBind&&) = delete;
	TextureBind& operator=(const TextureBind&) = delete;
	TextureBind& operator=(TextureBind&&) = delete;
	
	TextureBind(TextureTarget target, uint32_t texture);
	~TextureBind();
};

class ScopeActiveTexture
{
private:
	uint32_t mPrev;
public:
	ScopeActiveTexture() = delete;
	ScopeActiveTexture(const ScopeActiveTexture&) = delete;
	ScopeActiveTexture(ScopeActiveTexture&&) = delete;
	ScopeActiveTexture& operator=(const ScopeActiveTexture&) = delete;
	ScopeActiveTexture& operator=(ScopeActiveTexture&&) = delete;

	ScopeActiveTexture(uint32_t unit);
	~ScopeActiveTexture();
};

TextureBinding TextureTargetToBinding(TextureTarget target);
TextureTarget TextureBindingToTarget(TextureBinding binding);
uint32_t GetBoundTexture(TextureBinding binding);
uint32_t GetBoundTexture(TextureTarget target);
uint32_t GetActiveTextureUnit();
void SetActiveTextureUnit(uint32_t unit);

namespace DSA {

class Texture : GLObject
{
public:
	Texture() = delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&) noexcept = default;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) noexcept = default;

	Texture(TextureTarget target);
	Texture(const char* filename, bool genMipmap = false);
	Texture(uint32_t texture);
	virtual ~Texture();

	bool LoadFile(const char* filename, bool genMipmap = false);

	Texture& Storage1D(int32_t levels, TextureInternalFormat format, int32_t width);
	Texture& Storage2D(int32_t levels, TextureInternalFormat format, Vec2i size);
	Texture& Storage2DMultisample(int32_t samples, TextureInternalFormat format, Vec2i size, bool fixedSampleLocations);
	Texture& Storage3D(int32_t levels, TextureInternalFormat format, Vec3i size);
	Texture& Storage3DMultisample(int32_t samples, TextureInternalFormat format, Vec3i size, bool fixedSampleLocations);

	Texture& Image1D(int32_t level, TextureInternalFormat internalFormat, int32_t width, int32_t border, TextureBaseFormat format, DataType type, const void* data, TextureTarget target = TextureTarget::Tex1D);
	Texture& CompressedImage1D(int32_t level, TextureInternalFormat format, int32_t width, int32_t border, int32_t imageSize, const void* data, TextureTarget target = TextureTarget::Tex1D);
	Texture& Image2D(int32_t level, TextureInternalFormat internalFormat, Vec2i size, int32_t border, TextureBaseFormat format, DataType type, const void* data, TextureTarget target = TextureTarget::Tex2D);
	Texture& Image2DMultisample(int32_t samples, TextureInternalFormat format, Vec2i size, bool fixedSampleLocations, TextureTarget target = TextureTarget::Tex2DMultisample);
	Texture& CompressedImage2D(int32_t level, TextureInternalFormat format, Vec2i size, int32_t border, int32_t imageSize, const void* data, TextureTarget target = TextureTarget::Tex2D);
	Texture& Image3D(int32_t level, TextureInternalFormat internalFormat, Vec3i size, int32_t border, TextureBaseFormat format, DataType type, const void* data, TextureTarget target = TextureTarget::Tex3D);
	Texture& Image3DMultisample(int32_t samples, TextureInternalFormat format, Vec3i size, bool fixedSampleLocations, TextureTarget target = TextureTarget::Tex2DMultisampleArray);
	Texture& CompressedImage3D(int32_t level, TextureInternalFormat format, Vec3i size, int32_t border, int32_t imageSize, const void* data, TextureTarget target = TextureTarget::Tex3D);

	Texture& SubImage1D(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& CompressedSubImage1D(int32_t level, int32_t x, int32_t width, TextureInternalFormat format, int32_t imageSize, const void* data);
	Texture& SubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& CompressedSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureInternalFormat format, int32_t imageSize, const void* data);
	Texture& SubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& CompressedSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureInternalFormat format, int32_t imageSize, const void* data);

	Texture& Buffer(TextureInternalFormat format, uint32_t buffer);
	Texture& BufferRange(TextureInternalFormat format, uint32_t buffer, intptr_t offset, int32_t size);

	Texture& View(TextureTarget target, uint32_t texture, TextureInternalFormat format, uint32_t minLevel, uint32_t levels, uint32_t minLayer, uint32_t layers);

	Texture& ClearImage(int32_t level, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage1D(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, const void* data);

	Texture& CopyReadBufferImage1D(int32_t level, int32_t x, Vec2i srcOffset, int32_t width);
	Texture& CopyReadBufferImage2D(int32_t level, Vec2i offset, Vec2i srcOffset, Vec2i size);
	Texture& CopyReadBufferImage3D(int32_t level, Vec3i offset, Vec2i srcOffset, Vec2i size);

	Texture& CopyImageSubData1D(uint32_t srcName, TextureTarget srcTarget, int32_t srcLevel, int32_t srcX, TextureTarget target, int32_t level, int32_t x, int32_t width);
	Texture& CopyImageSubData2D(uint32_t srcName, TextureTarget srcTarget, int32_t srcLevel, Vec2i srcOffset, TextureTarget target, int32_t level, Vec2i offset, Vec2i size);
	Texture& CopyImageSubData3D(uint32_t srcName, TextureTarget srcTarget, int32_t srcLevel, Vec3i srcOffset, TextureTarget target, int32_t level, Vec3i offset, Vec3i size);

	Texture& GenerateMipmap();

	Texture& InvalidateImage(int32_t level);
	Texture& InvalidateSubImage1D(int32_t level, int32_t x, int32_t width);
	Texture& InvalidateSubImage2D(int32_t level, Vec2i offset, Vec2i size);
	Texture& InvalidateSubImage3D(int32_t level, Vec3i offset, Vec3i size);

	void Bind(TextureTarget target) const;
	void Bind(TextureTarget target, uint32_t unit) const;
	void Bind(uint32_t unit) const;

	void BindImage(uint32_t unit, int32_t level, bool layered, int32_t layer, Access access, TextureInternalFormat format) const;

	void GetCompressedImage(int32_t level, int32_t bufSize, void* pixels) const;
	void GetCompressedSubImage1D(int32_t level, int32_t x, int32_t width, int32_t bufSize, void* pixels) const;
	void GetCompressedSubImage2D(int32_t level, Vec2i offset, Vec2i size, int32_t bufSize, void* pixels) const;
	void GetCompressedSubImage3D(int32_t level, Vec3i offset, Vec3i size, int32_t bufSize, void* pixels) const;

	void GetImage(int32_t level, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels) const;
	void GetSubImage1D(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels);
	void GetSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels);
	void GetSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels);

	void GetLevelProp(int32_t level, TextureLevelProp pname, int32_t* value) const;
	void GetLevelProp(int32_t level, TextureLevelProp pname, float* value) const;

	int32_t GetLevelPropI(int32_t level, TextureLevelProp pname) const;
	float GetLevelPropF(int32_t level, TextureLevelProp pname) const;

	int32_t GetLevelWidth(int32_t level) const;
	int32_t GetLevelHeight(int32_t level) const;
	int32_t GetLevelDepth(int32_t level) const;
	Vec2i GetLevelSize2D(int32_t level) const;
	Vec3i GetLevelSize3D(int32_t level) const;
	TextureInternalFormat GetLevelInternalFormat(int32_t level) const;
	TextureComponentType GetLevelRedType(int32_t level) const;
	TextureComponentType GetLevelGreenType(int32_t level) const;
	TextureComponentType GetLevelBlueType(int32_t level) const;
	TextureComponentType GetLevelAlphaType(int32_t level) const;
	TextureComponentType GetLevelDepthType(int32_t level) const;
	int32_t GetLevelRedSize(int32_t level) const;
	int32_t GetLevelGreenSize(int32_t level) const;
	int32_t GetLevelBlueSize(int32_t level) const;
	int32_t GetLevelAlphaSize(int32_t level) const;
	int32_t GetLevelDepthSize(int32_t level) const;
	bool IsLevelCompressed(int32_t level) const;
	int32_t GetLevelCompressedImageSize(int32_t level) const;
	int32_t GetLevelBufferOffset(int32_t level) const;
	int32_t GetLevelBufferSize(int32_t level) const;

	Texture& SetParamI(TextureParam pname, int32_t value);
	Texture& SetParamF(TextureParam pname, float value);
	Texture& SetParam(TextureParam pname, const int32_t* values);
	Texture& SetParam(TextureParam pname, const float* values);
	Texture& SetParamInteger(TextureParam pname, const int32_t* values);
	Texture& SetParamInteger(TextureParam pname, const uint32_t* values);

	Texture& SetDepthStencilMode(TextureDepthStencilMode mode);
	Texture& SetBaseLevel(int32_t baseLevel);
	Texture& SetBorderColorF(Vec4f color);
	Texture& SetBorderColorI(Vec4i color);
	Texture& SetBorderColorIntegerI(Vec4i color);
	Texture& SetBorderColorIntegerUI(Vec4ui color);
	Texture& SetCompareFunc(CompareFunc func);
	Texture& SetCompareMode(TextureCompareMode mode);
	Texture& SetLodBias(float bias);
	Texture& SetMinFilter(TextureFilter filter);
	Texture& SetMagFilter(TextureFilter filter);
	Texture& SetMinLod(float minLod);
	Texture& SetMaxLod(float maxLod);
	Texture& SetMaxLevel(int32_t maxLevel);
	Texture& SetSwizzleR(TextureSwizzle swizzle);
	Texture& SetSwizzleG(TextureSwizzle swizzle);
	Texture& SetSwizzleB(TextureSwizzle swizzle);
	Texture& SetSwizzleA(TextureSwizzle swizzle);
	Texture& SetSwizzleRGBA(TextureSwizzleRGBA swizzles);
	Texture& SetWrapS(TextureWrap wrap);
	Texture& SetWrapT(TextureWrap wrap);
	Texture& SetWrapR(TextureWrap wrap);

	void GetProp(TextureProp pname, float* value) const;
	void GetProp(TextureProp pname, int32_t* value) const;
	void GetPropInteger(TextureProp pname, int32_t* value) const;
	void GetPropInteger(TextureProp pname, uint32_t* value) const;

	float GetPropF(TextureProp pname) const;
	int32_t GetPropI(TextureProp pname) const;

	TextureDepthStencilMode GetDepthStencilMode() const;
	TextureFilter GetMagFilter() const;
	TextureFilter GetMinFilter() const;
	float GetMinLod() const;
	float GetMaxLod() const;
	int32_t GetBaseLevel() const;
	int32_t GetMaxLevel() const;
	TextureSwizzle GetSwizzleR() const;
	TextureSwizzle GetSwizzleG() const;
	TextureSwizzle GetSwizzleB() const;
	TextureSwizzle GetSwizzleA() const;
	TextureSwizzleRGBA GetSwizzleRGBA() const;
	TextureWrap GetWrapS() const;
	TextureWrap GetWrapT() const;
	TextureWrap GetWrapR() const;
	Vec4f GetBorderColorF() const;
	Vec4i GetBorderColorI() const;
	Vec4i GetBorderColorIntegerI() const;
	Vec4ui GetBorderColorIntegerUI() const;
	TextureCompareMode GetCompareMode() const;
	CompareFunc GetCompareFunc() const;
	int32_t GetViewMinLevel() const;
	int32_t GetViewNumLevels() const;
	int32_t GetViewMinLayer() const;
	int32_t GetViewNumLayers() const;
	int32_t GetNumImmutableLevels() const;
	ImageFormatCompatibilityType GetImageFormatCompatibilityType() const;
	bool IsImmutableFormat() const;
	TextureTarget GetTarget() const;
};

} // namespace DSA

} // namespace GLUtil