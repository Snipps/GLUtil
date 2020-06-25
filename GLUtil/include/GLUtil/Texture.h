#pragma once

#include "Common.h"
#include "Object.h"
#include "Math.h"

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

};

enum class TextureBinding : uint32_t
{

};

enum class TextureProp : uint32_t
{

};

enum class TextureParam : uint32_t
{
	
};

enum class TextureCompareMode : uint32_t
{
	RefToTexture,
	None
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

enum class TextureFilter : uint32_t
{
	Nearest,
	Linear,
	NearestMipmapNearest,
	LinearMipmapNearest,
	NearestMipmapLinear,
	LinearMipmapLinear
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
	TextureTarget target;
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

TextureBinding TextureTargetToBinding(TextureTarget target);
TextureTarget TextureBindingToTarget(TextureBinding binding);
uint32_t GetBoundTexture(TextureBinding binding);
uint32_t GetBoundTexture(TextureTarget target);

namespace DSA {

class Texture : GLObject
{
public:
	Texture(const Texture&) = delete;
	Texture(Texture&&) noexcept = default;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) noexcept = default;

	Texture();
	Texture(uint32_t texture);
	virtual ~Texture();

	Texture& Storage1D(int32_t levels, TextureInternalFormat format, int32_t width);
	Texture& Storage2D(int32_t levels, TextureInternalFormat format, int32_t width, int32_t height);
	Texture& Storage2D(int32_t levels, TextureInternalFormat format, Vec2i size);
	Texture& Storage2DMultisample(int32_t samples, TextureInternalFormat format, int32_t width, int32_t height, bool fixedSampleLocations);
	Texture& Storage2DMultisample(int32_t samples, TextureInternalFormat format, Vec2i size, bool fixedSampleLocations);
	Texture& Storage3D(int32_t levels, TextureInternalFormat format, int32_t width, int32_t height, int32_t depth);
	Texture& Storage3D(int32_t levels, TextureInternalFormat format, Vec3i size);
	Texture& Storage3DMultisample(int32_t samples, TextureInternalFormat format, int32_t width, int32_t height, int32_t depth, bool fixedSampleLocations);
	Texture& Storage3DMultisample(int32_t samples, TextureInternalFormat format, Vec3i size, bool fixedSampleLocations);

	Texture& Image1D(int32_t level, TextureInternalFormat internalFormat, int32_t width, int32_t border, TextureBaseFormat format, DataType type, const void* data);
	Texture& CompressedImage1D(int32_t level, TextureInternalFormat format, int32_t width, int32_t border, int32_t imageSize, const void* data);
	Texture& Image2D(int32_t level, TextureInternalFormat internalFormat, int32_t width, int32_t height, int32_t border, TextureBaseFormat format, DataType type, const void* data);
	Texture& Image2D(int32_t level, TextureInternalFormat internalForamt, Vec2i size, int32_t border, TextureBaseFormat format, DataType type, const void* data);
	Texture& Image2DMultisample(int32_t samples, TextureInternalFormat format, int32_t width, int32_t height, bool fixedSampleLocations);
	Texture& Image2DMultisample(int32_t samples, TextureInternalFormat format, Vec2i size, bool fixedSampleLocations);
	Texture& CompressedImage2D(int32_t level, TextureInternalFormat format, int32_t width, int32_t height, int32_t border, int32_t imageSize, const void* data);
	Texture& CompressedImage2D(int32_t level, TextureInternalFormat format, Vec2i size, int32_t border, int32_t imageSize, const void* data);
	Texture& Image3D(int32_t level, TextureInternalFormat internalFormat, int32_t width, int32_t height, int32_t depth, int32_t border, TextureBaseFormat format, DataType type, const void* data);
	Texture& Image3D(int32_t level, TextureInternalFormat internalFormat, Vec3i size, int32_t border, TextureBaseFormat format, DataType type, const void* data);
	Texture& Image3DMultisample(int32_t samples, TextureInternalFormat format, int32_t width, int32_t height, int32_t depth, bool fixedSampleLocations);
	Texture& Image3DMultisample(int32_t samples, TextureInternalFormat format, Vec3i size, bool fixedSampleLocations);
	Texture& CompressedImage3D(int32_t level, TextureInternalFormat format, int32_t width, int32_t height, int32_t depth, int32_t border, int32_t imageSize, const void* data);
	Texture& CompressedImage3D(int32_t level, TextureInternalFormat format, Vec3i size, int32_t border, int32_t imageSize, const void* data);

	Texture& SubImage(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& CompressedSubImage1D(int32_t level, int32_t x, int32_t width, TextureInternalFormat format, int32_t imageSize, const void* data);
	Texture& SubImage2D(int32_t level, int32_t x, int32_t y, int32_t width, int32_t height, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& SubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& CompressedSubImage2D(int32_t level, int32_t x, int32_t y, int32_t width, int32_t height, TextureInternalFormat format, int32_t imageSize, const void* data);
	Texture& CompressedSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureInternalFormat format, int32_t imageSize, const void* data);
	Texture& SubImage3D(int32_t level, int32_t x, int32_t y, int32_t z, int32_t width, int32_t height, int32_t depth, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& SubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, const void* pixels);
	Texture& CompressedSubImage3D(int32_t level, int32_t x, int32_t y, int32_t z, int32_t width, int32_t height, int32_t depth, TextureInternalFormat format, int32_t imageSize, const void* data);
	Texture& CompressedSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureInternalFormat format, int32_t imageSize, const void* data);

	Texture& ClearImage(int32_t level, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage1D(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage2D(int32_t level, int32_t x, int32_t y, int32_t width, int32_t height, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage3D(int32_t level, int32_t x, int32_t y, int32_t z, int32_t width, int32_t height, int32_t depth, TextureBaseFormat format, DataType type, const void* data);
	Texture& ClearSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, const void* data);

	void Bind(TextureTarget target) const;
	void Bind(TextureTarget target, uint32_t unit) const;
	void Bind(uint32_t unit);

	void GetLevelProp(int32_t level, TextureLevelProp pname, int32_t* value) const;
	void GetLevelProp(int32_t level, TextureLevelProp pname, float* value) const;

	int32_t GetLevelPropI(int32_t level, TextureLevelProp pname) const;
	float GetLevelPropF(int32_t level, TextureLevelProp pname) const;

	int32_t GetLevelWidth(int32_t level) const;
	int32_t GetLevelHeight(int32_t level) const;
	int32_t GetLevelDepth(int32_t level) const;
	Vec2i GetLevleSize2D(int32_t level) const;
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

	Texture& SetParam(TextureParam pname, int32_t value);
	Texture& SetParam(TextureParam pname, float value);
	Texture& SetParam(TextureParam pname, const int32_t* values);
	Texture& SetParam(TextureParam pname, const float* values);
	Texture& SetParamInteger(TextureParam pname, const int32_t* values);
	Texture& SetParamInteger(TextureParam pname, const uint32_t* values);

	Texture& SetDepthStencilMode(TextureDepthStencilMode mode);
	Texture& SetBaseLevel(int32_t baseLevel);
	Texture& SetBorderColor(Vec4f color);
	Texture& SetBorderColor(Vec4i color);
	Texture& SetBorderColorInteger(Vec4i color);
	Texture& SetBorderColorInteger(Vec4ui color);
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
	int32_t GetPropIntegerI(TextureProp pname) const;
	uint32_t GetPropIntegerUI(TextureProp pname) const;

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