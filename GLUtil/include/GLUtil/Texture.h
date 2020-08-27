#pragma once

#include "Common.h"
#include "Object.h"
#include "Vec.h"
#include "Sampler.h"

namespace GLUtil {

enum class TextureInternalFormat : uint32_t
{
	R8 = 0x8229,
	R8Snorm = 0x8F94,
	R16 = 0x822A,
	R16Snorm = 0x8F98,
	RG8 = 0x822B,
	RG8Snorm = 0x8F95,
	RG16Snorm = 0x8F99,
	R3G3B2 = 0x2A10,
	RGB4 = 0x804F,
	RGB5 = 0x8050,
	RGB8 = 0x8051,
	RGB8Snorm = 0x8F96,
	RGB10 = 0x8052,
	RGB12 = 0x8053,
	RGB16Snorm = 0x8F9A,
	RGBA2 = 0x8055,
	RGBA4 = 0x8056,
	RGB5A1 = 0x8057,
	RGBA8 = 0x8058,
	RGBA8Snorm = 0x8F97,
	RGB10A2 = 0x8059,
	RGB10A2UI = 0x906F,
	RGBA12 = 0x805A,
	RGBA16 = 0x805B,
	SRGB8 = 0x8C41,
	SRGB8A8 = 0x8C43,
	R16F = 0x822D,
	RG16F = 0x822F,
	RGB16F = 0x881B,
	RGBA16F = 0x881A,
	R32F = 0x822E,
	RG32F = 0x8230,
	RGB32F = 0x8815,
	RGBA32F = 0x8814,
	RG11FB10F = 0x8C3A,
	RGB9E5 = 0x8C3D,
	R8I = 0x8231,
	R8UI = 0x8232,
	R16I = 0x8233,
	R16UI = 0x8234,
	RG8I = 0x8237,
	RG8UI = 0x8238,
	RG16I = 0x8239,
	RG16UI = 0x823A,
	RG32I = 0x8235,
	RG32UI = 0x8236,
	RGB8I = 0x8D8F,
	RGB8UI = 0x8D7D,
	RGB16I = 0x8D89,
	RGB16UI = 0x8D77,
	RGB32I = 0x8D83,
	RGB32UI = 0x8D71,
	RGBA8I = 0x8D8E,
	RGBA8UI = 0x8D7C,
	RGBA16I = 0x8D88,
	RGBA16UI = 0x8D76,
	RGBA32I = 0x8D82,
	RGBA32UI = 0x8D70,

	RGB_DXT1 = 0x83F0,
	SRGBA_DXT1 = 0x8C4C,
	RGBA_DXT1 = 0x83F1,
	SRGBA_DXT1 = 0x8C4D,
	RGBA_DXT3 = 0x83F2,
	SRGBA_DXT3 = 0x8C4E,
	RGBA_DXT5 = 0x83F3,
	SRGBA_DXT5 = 0x8C4F
};

enum class TextureBaseFormat : uint32_t
{
	R = 0x1903,
	RG = 0x8227,
	RGB = 0x1907,
	RGBA = 0x1908
};

enum class TextureTarget : uint32_t
{
	Tex1D = 0x0DE0,
	Tex2D = 0x0DE1,
	Tex3D = 0x806F,
	Tex1DArray = 0x8C18,
	Tex2DArray = 0x8C1A,
	TexRectangle = 0x84F5,
	TexCubeMap = 0x8513,
	TexCubeMapArray = 0x9009,
	TexBuffer = 0x8C2A,
	Tex2DMultisample = 0x9100,
	Tex2DMultisampleArray = 0x9102,
	TexCubeMapPositiveX = 0x8515,
	TexCubeMapNegativeX = 0x8516,
	TexCubeMapPositiveY = 0x8517,
	TexCubeMapNegativeY  = 0x8518,
	TexCubeMapPositiveZ = 0x8519,
	TexCubeMapNegativeZ = 0x851A
};

enum class TextureBinding : uint32_t
{
	Tex1D = 0x8068,
	Tex2D = 0x8069,
	Tex3D = 0x806A,
	Tex1DArray = 0x8C1C,
	Tex2DArray = 0x8C1D,
	TexRectangle = 0x84F6,
	TexCubeMap = 0x8514,
	TexCubeMapArray = 0x900A,
	TexBuffer = 0x8C2C,
	Tex2DMultisample = 0x9104,
	Tex2DMultisampleArray = 0x9105
};

enum class TextureProp : uint32_t
{
	DepthStencilMode = 0x90EA,
	MagFilter = 0x2800,
	MinFilter = 0x2801,
	MinLod = 0x813A,
	MaxLod = 0x813B,
	BaseLevel = 0x813C,
	MaxLevel = 0x813D,
	SwizzleR = 0x8E42,
	SwizzleG = 0x8E43,
	SwizzleB = 0x8E44,
	SwizzleA = 0x8E45,
	SwizzleRGBA = 0x8E46,
	WrapS = 0x2802,
	WrapT = 0x2803,
	WrapR = 0x8072,
	BorderColor = 0x1004,
	CompareMode = 0x884C,
	CompareFunc = 0x884D,
	ViewMinLevel = 0x82DB,
	ViewNumLevels = 0x82DC,
	ViewMinLayer = 0x82DD,
	ViewNumLayers = 0x82DE,
	NumImmutableLevels = 0x82DF,
	ImageFormatCompatibilityType = 0x90C7,
	IsImmutableFormat = 0x912F,
	Target = 0x1006
};

enum class TextureParam : uint32_t
{
	DepthStencilMode = 0x90EA,
	BaseLevel = 0x813C,
	BorderColor = 0x1004,
	CompareFunc = 0x884D,
	CompareMode = 0x884C,
	LodBias = 0x8501,
	MinFilter = 0x2801,
	MagFilter = 0x2800,
	MinLod = 0x813A,
	MaxLod = 0x813B,
	MaxLevel = 0x813D,
	SwizzleR = 0x8E42,
	SwizzleG = 0x8E43,
	SwizzleB = 0x8E44,
	SwizzleA = 0x8E45,
	SwizzleRGBA = 0x8E46,
	WrapS = 0x2802,
	WrapT = 0x2803,
	WrapR = 0x8072
};

enum class TextureDepthStencilMode : uint32_t
{
	DepthComponent = 0x1902,
	StencilIndex = 0x1901
};

enum class TextureSwizzle : uint32_t
{
	Red = 0x1903,
	Green = 0x1904,
	Blue = 0x1905,
	Alpha = 0x1906,
	Zero = 0,
	One = 1
};
enum class ImageFormatCompatibilityType : uint32_t
{
	BySize = 0x90C8,
	ByClass = 0x90C9,
	None = 0
};

enum class TextureLevelProp : uint32_t
{
	Width = 0x1000,
	Height = 0x1001,
	Depth = 0x8071,
	InternalFormat = 0x1003,
	RedType = 0x8C10,
	GreenType = 0x8C11,
	BlueType = 0x8C12,
	AlphaType = 0x8C13,
	DepthType = 0x8C16,
	RedSize = 0x805C,
	GreenSize = 0x805D,
	BlueSize = 0x805E,
	AlphaSize = 0x805F,
	DepthSize = 0x884A,
	StencilSize = 0x88F1,
	IsCompressed = 0x86A1,
	CompressedImageSize = 0x86A0,
	BufferOffset = 0x919D,
	BufferSize = 0x919E
};

enum class TextureComponentType : uint32_t
{
	None = 0,
	SignedNormalized = 0x8F9C,
	UnsignedNormalized = 0x8C17,
	Float = 0x1406,
	Int = 0x1404,
	UnsignedInt = 0x1405
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
	int32_t GetLevelStencilSize(int32_t level) const;
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

} // namespace GLUtil