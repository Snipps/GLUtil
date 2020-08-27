#include <GLUtil/Texture.h>

#include <glad/gl.h>
#include <stb/image.h>

#include <cmath>
#include <algorithm>

#define TEXTURE_BIND TextureBind _bind(target, *this)
#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

TextureBind::TextureBind(TextureTarget target, uint32_t texture) :
	mTarget(target), mPrev(GetBoundTexture(target))
{
	GLUTIL_GL_CALL(glBindTexture(ENUM(target), texture));
}

TextureBind::~TextureBind()
{
	GLUTIL_GL_CALL(glBindTexture(ENUM(mTarget), mPrev));
}

ScopeActiveTexture::ScopeActiveTexture(uint32_t unit) :
	mPrev(GetActiveTextureUnit())
{
	GLUTIL_GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
}

ScopeActiveTexture::~ScopeActiveTexture()
{
	GLUTIL_GL_CALL(glActiveTexture(GL_TEXTURE0 + mPrev));
}

TextureBinding TextureTargetToBinding(TextureTarget target)
{
	switch (target) {
		case TextureTarget::Tex1D:
			return TextureBinding::Tex1D;
		case TextureTarget::Tex2D:
			return TextureBinding::Tex2D;
		case TextureTarget::Tex3D:
			return TextureBinding::Tex3D;
		case TextureTarget::Tex1DArray:
			return TextureBinding::Tex1DArray;
		case TextureTarget::Tex2DArray:
			return TextureBinding::Tex2DArray;
		case TextureTarget::TexRectangle:
			return TextureBinding::TexRectangle;
		case TextureTarget::TexCubeMap:
			return TextureBinding::TexCubeMap;
		case TextureTarget::TexCubeMapArray:
			return TextureBinding::TexCubeMapArray;
		case TextureTarget::TexBuffer:
			return TextureBinding::TexBuffer;
		case TextureTarget::Tex2DMultisample:
			return TextureBinding::Tex2DMultisample;
		case TextureTarget::Tex2DMultisampleArray:
			return TextureBinding::Tex2DMultisampleArray;
		default:
			return static_cast<TextureBinding>(0);
	}
}

TextureTarget TextureBindingToTarget(TextureBinding binding)
{
	switch (binding) {
		case TextureBinding::Tex1D:
			return TextureTarget::Tex1D;
		case TextureBinding::Tex2D:
			return TextureTarget::Tex2D;
		case TextureBinding::Tex3D:
			return TextureTarget::Tex3D;
		case TextureBinding::Tex1DArray:
			return TextureTarget::Tex1DArray;
		case TextureBinding::Tex2DArray:
			return TextureTarget::Tex2DArray;
		case TextureBinding::TexRectangle:
			return TextureTarget::TexRectangle;
		case TextureBinding::TexCubeMap:
			return TextureTarget::TexCubeMap;
		case TextureBinding::TexCubeMapArray:
			return TextureTarget::TexCubeMapArray;
		case TextureBinding::TexBuffer:
			return TextureTarget::TexBuffer;
		case TextureBinding::Tex2DMultisample:
			return TextureTarget::Tex2DMultisample;
		case TextureBinding::Tex2DMultisampleArray:
			return TextureTarget::Tex2DMultisampleArray;
		default:
			return static_cast<TextureTarget>(0);
	}
}

uint32_t GetBoundTexture(TextureBinding binding)
{
	int32_t value = 0;
	GLUTIL_GL_CALL(glGetIntegerv(ENUM(binding), &value));
	return value;
}

uint32_t GetBoundTexture(TextureTarget target)
{
	return GetBoundTexture(TextureTargetToBinding(target));
}

uint32_t GetActiveTextureUnit()
{
	int32_t value = 0;
	GLUTIL_GL_CALL(glGetIntegerv(GL_ACTIVE_TEXTURE, &value));
	return value - GL_TEXTURE0;
}

void SetActiveTextureUnit(uint32_t unit)
{
	GLUTIL_GL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
}

Texture::Texture(TextureTarget target)
{
	GLUTIL_GL_CALL(glCreateTextures(ENUM(target), 1, GetIDPtr()));
}

Texture::Texture(const char* filename, bool genMipmap) :
	Texture(TextureTarget::Tex2D)
{
	LoadFile(filename, genMipmap);
}

Texture::Texture(uint32_t texture) :
	GLObject(texture)
{}

Texture::~Texture()
{
	if (*this) {
		GLUTIL_GL_CALL(glDeleteTextures(1, GetIDPtr()));
	}
}

bool Texture::LoadFile(const char* filename, bool genMipmap)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* pixels = stbi_load(filename, &width, &height, &channels, 0);
	if (!pixels)
		return false;

	TextureInternalFormat internalFormat;
	TextureBaseFormat format;
	switch (channels) {
		case STBI_grey:
			internalFormat = TextureInternalFormat::R8;
			format = TextureBaseFormat::R;
			SetSwizzleG(TextureSwizzle::Red);
			SetSwizzleB(TextureSwizzle::Red);
			SetSwizzleA(TextureSwizzle::One);
			break;
		case STBI_grey_alpha:
			internalFormat = TextureInternalFormat::RG8;
			format = TextureBaseFormat::RG;
			SetSwizzleG(TextureSwizzle::Red);
			SetSwizzleB(TextureSwizzle::Red);
			SetSwizzleA(TextureSwizzle::Green);
			break;
		case STBI_rgb:
			internalFormat = TextureInternalFormat::RGB8;
			format = TextureBaseFormat::RGB;
			SetSwizzleA(TextureSwizzle::One);
			break;
		case STBI_rgb_alpha:
			internalFormat = TextureInternalFormat::RGBA8;
			format = TextureBaseFormat::RGBA;
			break;
		default:
			stbi_image_free(pixels);
			return false;
	}

	int levels = 1;
	if (genMipmap) {
		levels = (int)std::max(log2(width), log2(height)) + 1;
		SetMinFilter(TextureFilter::LinearMipmapLinear);
		SetMagFilter(TextureFilter::Nearest);
	} else {
		SetMinFilter(TextureFilter::Linear);
		SetMagFilter(TextureFilter::Nearest);
	}

	Storage2D(levels, internalFormat, { width, height });
	SubImage2D(0, { 0, 0 }, { width, height }, format, DataType::UnsignedByte, pixels);
	stbi_image_free(pixels);
	if (genMipmap)
		GenerateMipmap();

	return true;
}

Texture& Texture::Storage1D(int32_t levels, TextureInternalFormat format, int32_t width)
{
	GLUTIL_GL_CALL(glTextureStorage1D(*this, levels, ENUM(format), width));
	return *this;
}

Texture& Texture::Storage2D(int32_t levels, TextureInternalFormat format, Vec2i size)
{
	GLUTIL_GL_CALL(glTextureStorage2D(*this, levels, ENUM(format), size.x, size.y));
	return *this;
}

Texture& Texture::Storage2DMultisample(int32_t samples, TextureInternalFormat format, Vec2i size, bool fixedSampleLocations)
{
	GLUTIL_GL_CALL(glTextureStorage2DMultisample(*this, samples, ENUM(format), size.x, size.y, fixedSampleLocations));
	return *this;
}

Texture& Texture::Storage3D(int32_t levels, TextureInternalFormat format, Vec3i size)
{
	GLUTIL_GL_CALL(glTextureStorage3D(*this, levels, ENUM(format), size.x, size.y, size.z));
	return *this;
}


Texture& Texture::Storage3DMultisample(int32_t samples, TextureInternalFormat format, Vec3i size, bool fixedSampleLocations)
{
	GLUTIL_GL_CALL(glTextureStorage3DMultisample(*this, samples, ENUM(format), size.x, size.y, size.z, fixedSampleLocations));
	return *this;
}

Texture& Texture::Image1D(int32_t level, TextureInternalFormat internalFormat, int32_t width, int32_t border, TextureBaseFormat format, DataType type, const void* data, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glTexImage1D(ENUM(target), level, ENUM(internalFormat), width, border, ENUM(format), ENUM(type), data));
	return *this;
}

Texture& Texture::CompressedImage1D(int32_t level, TextureInternalFormat format, int32_t width, int32_t border, int32_t imageSize, const void* data, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glCompressedTexImage1D(ENUM(target), level, ENUM(format), width, border, imageSize, data));
	return *this;
}


Texture& Texture::Image2D(int32_t level, TextureInternalFormat internalFormat, Vec2i size, int32_t border, TextureBaseFormat format, DataType type, const void* data, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glTexImage2D(ENUM(target), level, ENUM(internalFormat), size.x, size.y, border, ENUM(format), ENUM(type), data));
	return *this;
}

Texture& Texture::Image2DMultisample(int32_t samples, TextureInternalFormat format, Vec2i size, bool fixedSampleLocations, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glTexImage2DMultisample(ENUM(target), samples, ENUM(format), size.x, size.y, fixedSampleLocations));
	return *this;
}

Texture& Texture::CompressedImage2D(int32_t level, TextureInternalFormat format, Vec2i size, int32_t border, int32_t imageSize, const void* data, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glCompressedTexImage2D(ENUM(target), level, ENUM(format), size.x, size.y, border, imageSize, data));
	return *this;
}

Texture& Texture::Image3D(int32_t level, TextureInternalFormat internalFormat, Vec3i size, int32_t border, TextureBaseFormat format, DataType type, const void* data, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glTexImage3D(ENUM(target), level, ENUM(internalFormat), size.x, size.y, size.z, border, ENUM(format), ENUM(type), data));
	return *this;
}

Texture& Texture::Image3DMultisample(int32_t samples, TextureInternalFormat format, Vec3i size, bool fixedSampleLocations, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glTexImage3DMultisample(ENUM(target), samples, ENUM(format), size.x, size.y, size.z, fixedSampleLocations));
	return *this;
}

Texture& Texture::CompressedImage3D(int32_t level, TextureInternalFormat format, Vec3i size, int32_t border, int32_t imageSize, const void* data, TextureTarget target)
{
	TEXTURE_BIND;
	GLUTIL_GL_CALL(glCompressedTexImage3D(ENUM(target), level, ENUM(format), size.x, size.y, size.z, border, imageSize, data));
	return *this;
}

Texture& Texture::SubImage1D(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, const void* pixels)
{
	GLUTIL_GL_CALL(glTextureSubImage1D(*this, level, x, width, ENUM(format), ENUM(type), pixels));
	return *this;
}

Texture& Texture::CompressedSubImage1D(int32_t level, int32_t x, int32_t width, TextureInternalFormat format, int32_t imageSize, const void* data)
{
	GLUTIL_GL_CALL(glCompressedTextureSubImage1D(*this, level, x, width, ENUM(format), imageSize, data));
	return *this;
}

Texture& Texture::SubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, const void* pixels)
{
	GLUTIL_GL_CALL(glTextureSubImage2D(*this, level, offset.x, offset.y, size.x, size.y, ENUM(format), ENUM(type), pixels));
	return *this;
}

Texture& Texture::CompressedSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureInternalFormat format, int32_t imageSize, const void* data)
{
	GLUTIL_GL_CALL(glCompressedTextureSubImage2D(*this, level, offset.x, offset.y, size.x, size.y, ENUM(format), imageSize, data));
	return *this;
}

Texture& Texture::SubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, const void* pixels)
{
	GLUTIL_GL_CALL(glTextureSubImage3D(*this, level, offset.x, offset.y, offset.z, size.x, size.y, size.z, ENUM(format), ENUM(type), pixels));
	return *this;
}

Texture& Texture::CompressedSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureInternalFormat format, int32_t imageSize, const void* data)
{
	GLUTIL_GL_CALL(glCompressedTextureSubImage3D(*this, level, offset.x, offset.y, offset.z, size.x, size.y, size.z, ENUM(format), imageSize, data));
	return *this;
}

Texture& Texture::Buffer(TextureInternalFormat format, uint32_t buffer)
{
	GLUTIL_GL_CALL(glTextureBuffer(*this, ENUM(format), buffer));
	return *this;
}

Texture& Texture::BufferRange(TextureInternalFormat format, uint32_t buffer, intptr_t offset, int32_t size)
{
	GLUTIL_GL_CALL(glTextureBufferRange(*this, ENUM(format), buffer, offset, size));
	return *this;
}

Texture& Texture::View(TextureTarget target, uint32_t texture, TextureInternalFormat format, uint32_t minLevel, uint32_t levels, uint32_t minLayer, uint32_t layers)
{
	GLUTIL_GL_CALL(glTextureView(*this, ENUM(target), texture, ENUM(format), minLevel, levels, minLayer, layers));
	return *this;
}

Texture& Texture::ClearImage(int32_t level, TextureBaseFormat format, DataType type, const void* data)
{
	GLUTIL_GL_CALL(glClearTexImage(*this, level, ENUM(format), ENUM(type), data));
	return *this;
}

Texture& Texture::ClearSubImage1D(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, const void* data)
{
	return ClearSubImage3D(level, { x, 0, 0 }, { width, 1, 1 }, format, type, data);
}

Texture& Texture::ClearSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, const void* data)
{
	return ClearSubImage3D(level, { offset, 0 }, { size, 1 }, format, type, data);
}

Texture& Texture::ClearSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, const void* data)
{
	GLUTIL_GL_CALL(glClearTexSubImage(*this, level, offset.x, offset.y, offset.z, size.x, size.y, size.z, ENUM(format), ENUM(type), data));
	return *this;
}

Texture& Texture::CopyReadBufferImage1D(int32_t level, int32_t x, Vec2i srcOffset, int32_t width)
{
	GLUTIL_GL_CALL(glCopyTextureSubImage1D(*this, level, x, srcOffset.x, srcOffset.y, width));
	return *this;
}

Texture& Texture::CopyReadBufferImage2D(int32_t level, Vec2i offset, Vec2i srcOffset, Vec2i size)
{
	GLUTIL_GL_CALL(glCopyTextureSubImage2D(*this, level, offset.x, offset.y, srcOffset.x, srcOffset.y, size.x, size.y));
	return *this;
}

Texture& Texture::CopyReadBufferImage3D(int32_t level, Vec3i offset, Vec2i srcOffset, Vec2i size)
{
	GLUTIL_GL_CALL(glCopyTextureSubImage3D(*this, level, offset.x, offset.y, offset.z, srcOffset.x, srcOffset.y, size.x, size.y));
	return *this;
}

Texture& Texture::CopyImageSubData1D(uint32_t srcName, TextureTarget srcTarget, int32_t srcLevel, int32_t srcX, TextureTarget target, int32_t level, int32_t x, int32_t width)
{
	return CopyImageSubData3D(srcName, srcTarget, srcLevel, { srcX, 0, 0 }, target, level, { x, 0, 0 }, { width, 1, 1 });
}

Texture& Texture::CopyImageSubData2D(uint32_t srcName, TextureTarget srcTarget, int32_t srcLevel, Vec2i srcOffset, TextureTarget target, int32_t level, Vec2i offset, Vec2i size)
{
	return CopyImageSubData3D(srcName, srcTarget, srcLevel, { srcOffset, 0 }, target, level, { offset, 0 }, { size, 1 });
}

Texture& Texture::CopyImageSubData3D(uint32_t srcName, TextureTarget srcTarget, int32_t srcLevel, Vec3i srcOffset, TextureTarget target, int32_t level, Vec3i offset, Vec3i size)
{
	GLUTIL_GL_CALL(glCopyImageSubData(srcName, ENUM(srcTarget), srcLevel, srcOffset.x, srcOffset.y, srcOffset.z, *this, ENUM(target), level, offset.x, offset.y, offset.z, size.x, size.y, size.z));
	return *this;
}

Texture& Texture::GenerateMipmap()
{
	GLUTIL_GL_CALL(glGenerateTextureMipmap(*this));
	return *this;
}

Texture& Texture::InvalidateImage(int32_t level)
{
	GLUTIL_GL_CALL(glInvalidateTexImage(*this, level));
	return *this;
}

Texture& Texture::InvalidateSubImage1D(int32_t level, int32_t x, int32_t width)
{
	return InvalidateSubImage3D(level, { x, 0, 0 }, { width, 1, 1 });
}

Texture& Texture::InvalidateSubImage2D(int32_t level, Vec2i offset, Vec2i size)
{
	return InvalidateSubImage3D(level, { offset, 0 }, { size, 1 });
}

Texture& Texture::InvalidateSubImage3D(int32_t level, Vec3i offset, Vec3i size)
{
	GLUTIL_GL_CALL(glInvalidateTexSubImage(*this, level, offset.x, offset.y, offset.z, size.x, size.y, size.z));
	return *this;
}

void Texture::Bind(TextureTarget target) const
{
	GLUTIL_GL_CALL(glBindTexture(ENUM(target), *this));
}

void Texture::Bind(TextureTarget target, uint32_t unit) const
{
	ScopeActiveTexture activeTex(unit);
	GLUTIL_GL_CALL(glBindTexture(ENUM(target), *this));
}

void Texture::Bind(uint32_t unit) const
{
	GLUTIL_GL_CALL(glBindTextureUnit(unit, *this));
}

void Texture::BindImage(uint32_t unit, int32_t level, bool layered, int32_t layer, Access access, TextureInternalFormat format) const
{
	GLUTIL_GL_CALL(glBindImageTexture(unit, *this, level, layered, layer, ENUM(access), ENUM(format)));
}

void Texture::GetCompressedImage(int32_t level, int32_t bufSize, void* pixels) const
{
	GLUTIL_GL_CALL(glGetCompressedTextureImage(*this, level, bufSize, pixels));
}

void Texture::GetCompressedSubImage1D(int32_t level, int32_t x, int32_t width, int32_t bufSize, void* pixels) const
{
	GetCompressedSubImage3D(level, { x, 0, 0 }, { width, 1, 1 }, bufSize, pixels);
}

void Texture::GetCompressedSubImage2D(int32_t level, Vec2i offset, Vec2i size, int32_t bufSize, void* pixels) const
{
	GetCompressedSubImage3D(level, { offset, 0 }, { size, 1 }, bufSize, pixels);
}

void Texture::GetCompressedSubImage3D(int32_t level, Vec3i offset, Vec3i size, int32_t bufSize, void* pixels) const
{
	GLUTIL_GL_CALL(glGetCompressedTextureSubImage(*this, level, offset.x, offset.x, offset.z, size.x, size.y, size.z, bufSize, pixels));
}

void Texture::GetImage(int32_t level, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels) const
{
	GLUTIL_GL_CALL(glGetTextureImage(*this, level, ENUM(format), ENUM(type), bufSize, pixels));
}

void Texture::GetSubImage1D(int32_t level, int32_t x, int32_t width, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels)
{
	GetSubImage3D(level, { x, 0, 0 }, { width, 1, 1 }, format, type, bufSize, pixels);
}

void Texture::GetSubImage2D(int32_t level, Vec2i offset, Vec2i size, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels)
{
	GetSubImage3D(level, { offset, 0 }, { size, 1 }, format, type, bufSize, pixels);
}

void Texture::GetSubImage3D(int32_t level, Vec3i offset, Vec3i size, TextureBaseFormat format, DataType type, int32_t bufSize, void* pixels)
{
	GLUTIL_GL_CALL(glGetTextureSubImage(*this, level, offset.x, offset.y, offset.z, size.x, size.y, size.z, ENUM(format), ENUM(type), bufSize, pixels));
}

void Texture::GetLevelProp(int32_t level, TextureLevelProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetTextureLevelParameteriv(*this, level, ENUM(pname), value));
}

void Texture::GetLevelProp(int32_t level, TextureLevelProp pname, float* value) const
{
	GLUTIL_GL_CALL(glGetTextureLevelParameterfv(*this, level, ENUM(pname), value));
}

int32_t Texture::GetLevelPropI(int32_t level, TextureLevelProp pname) const
{
	int32_t value = 0;
	GetLevelProp(level, pname, &value);
	return value;
}

float Texture::GetLevelPropF(int32_t level, TextureLevelProp pname) const
{
	float value = 0;
	GetLevelProp(level, pname, &value);
	return value;
}

int32_t Texture::GetLevelWidth(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::Width);
}

int32_t Texture::GetLevelHeight(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::Height);
}

int32_t Texture::GetLevelDepth(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::Depth);
}

Vec2i Texture::GetLevelSize2D(int32_t level) const
{
	return Vec2i(GetLevelWidth(level), GetLevelHeight(level));
}

Vec3i Texture::GetLevelSize3D(int32_t level) const
{
	return Vec3i(GetLevelSize2D(level), GetLevelDepth(level));
}

TextureInternalFormat Texture::GetLevelInternalFormat(int32_t level) const
{
	return static_cast<TextureInternalFormat>(GetLevelPropI(level, TextureLevelProp::InternalFormat));
}

TextureComponentType Texture::GetLevelRedType(int32_t level) const
{
	return static_cast<TextureComponentType>(GetLevelPropI(level, TextureLevelProp::RedType));
}

TextureComponentType Texture::GetLevelGreenType(int32_t level) const
{
	return static_cast<TextureComponentType>(GetLevelPropI(level, TextureLevelProp::GreenType));
}

TextureComponentType Texture::GetLevelBlueType(int32_t level) const
{
	return static_cast<TextureComponentType>(GetLevelPropI(level, TextureLevelProp::BlueType));
}

TextureComponentType Texture::GetLevelAlphaType(int32_t level) const
{
	return static_cast<TextureComponentType>(GetLevelPropI(level, TextureLevelProp::AlphaType));
}

TextureComponentType Texture::GetLevelDepthType(int32_t level) const
{
	return static_cast<TextureComponentType>(GetLevelPropI(level, TextureLevelProp::DepthType));
}

int32_t Texture::GetLevelRedSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::RedSize);
}

int32_t Texture::GetLevelGreenSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::GreenSize);
}

int32_t Texture::GetLevelBlueSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::BlueSize);
}

int32_t Texture::GetLevelAlphaSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::AlphaSize);
}

int32_t Texture::GetLevelDepthSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::DepthSize);
}

int32_t Texture::GetLevelStencilSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::StencilSize);
}

bool Texture::IsLevelCompressed(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::IsCompressed) == GL_TRUE;
}

int32_t Texture::GetLevelCompressedImageSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::CompressedImageSize);
}

int32_t Texture::GetLevelBufferOffset(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::BufferOffset);
}

int32_t Texture::GetLevelBufferSize(int32_t level) const
{
	return GetLevelPropI(level, TextureLevelProp::BufferSize);
}

Texture& Texture::SetParamI(TextureParam pname, int32_t value)
{
	GLUTIL_GL_CALL(glTextureParameteri(*this, ENUM(pname), value));
	return *this;
}

Texture& Texture::SetParamF(TextureParam pname, float value)
{
	GLUTIL_GL_CALL(glTextureParameterf(*this, ENUM(pname), value));
	return *this;
}

Texture& Texture::SetParam(TextureParam pname, const int32_t* value)
{
	GLUTIL_GL_CALL(glTextureParameteriv(*this, ENUM(pname), value));
	return *this;
}

Texture& Texture::SetParam(TextureParam pname, const float* values)
{
	GLUTIL_GL_CALL(glTextureParameterfv(*this, ENUM(pname), values));
	return *this;
}

Texture& Texture::SetParamInteger(TextureParam pname, const int32_t* values)
{
	GLUTIL_GL_CALL(glTextureParameterIiv(*this, ENUM(pname), values));
	return *this;
}

Texture& Texture::SetParamInteger(TextureParam pname, const uint32_t* values)
{
	GLUTIL_GL_CALL(glTextureParameterIuiv(*this, ENUM(pname), values));
	return *this;
}

Texture& Texture::SetDepthStencilMode(TextureDepthStencilMode mode)
{
	return SetParamI(TextureParam::DepthStencilMode, ENUM(mode));
}

Texture& Texture::SetBaseLevel(int32_t baseLevel)
{
	return SetParamI(TextureParam::BaseLevel, baseLevel);
}

Texture& Texture::SetBorderColorF(Vec4f color)
{
	return SetParam(TextureParam::BorderColor, color.v);
}

Texture& Texture::SetBorderColorI(Vec4i color)
{
	return SetParam(TextureParam::BorderColor, color.v);
}

Texture& Texture::SetBorderColorIntegerI(Vec4i color)
{
	return SetParamInteger(TextureParam::BorderColor, color.v);
}

Texture& Texture::SetBorderColorIntegerUI(Vec4ui color)
{
	return SetParamInteger(TextureParam::BorderColor, color.v);
}

Texture& Texture::SetCompareFunc(CompareFunc func)
{
	return SetParamI(TextureParam::CompareFunc, ENUM(func));
}

Texture& Texture::SetCompareMode(TextureCompareMode mode)
{
	return SetParamI(TextureParam::CompareMode, ENUM(mode));
}

Texture& Texture::SetLodBias(float bias)
{
	return SetParamF(TextureParam::LodBias, bias);
}

Texture& Texture::SetMinFilter(TextureFilter filter)
{
	return SetParamI(TextureParam::MinFilter, ENUM(filter));
}

Texture& Texture::SetMagFilter(TextureFilter filter)
{
	return SetParamI(TextureParam::MagFilter, ENUM(filter));
}

Texture& Texture::SetMinLod(float minLod)
{
	return SetParamF(TextureParam::MinLod, minLod);
}

Texture& Texture::SetMaxLod(float maxLod)
{
	return SetParamF(TextureParam::MaxLod, maxLod);
}

Texture& Texture::SetMaxLevel(int32_t maxLevel)
{
	return SetParamI(TextureParam::MaxLevel, maxLevel);
}

Texture& Texture::SetSwizzleR(TextureSwizzle swizzle)
{
	return SetParamI(TextureParam::SwizzleR, ENUM(swizzle));
}

Texture& Texture::SetSwizzleG(TextureSwizzle swizzle)
{
	return SetParamI(TextureParam::SwizzleG, ENUM(swizzle));
}

Texture& Texture::SetSwizzleB(TextureSwizzle swizzle)
{
	return SetParamI(TextureParam::SwizzleB, ENUM(swizzle));
}

Texture& Texture::SetSwizzleA(TextureSwizzle swizzle)
{
	return SetParamI(TextureParam::SwizzleA, ENUM(swizzle));
}

Texture& Texture::SetSwizzleRGBA(TextureSwizzleRGBA swizzles)
{
	return SetParam(TextureParam::SwizzleRGBA, reinterpret_cast<int32_t*>(swizzles.swizzles));
}

Texture& Texture::SetWrapS(TextureWrap wrap)
{
	return SetParamI(TextureParam::WrapS, ENUM(wrap));
}

Texture& Texture::SetWrapT(TextureWrap wrap)
{
	return SetParamI(TextureParam::WrapT, ENUM(wrap));
}

Texture& Texture::SetWrapR(TextureWrap wrap)
{
	return SetParamI(TextureParam::WrapR, ENUM(wrap));
}

void Texture::GetProp(TextureProp pname, float* value) const
{
	GLUTIL_GL_CALL(glGetTextureParameterfv(*this, ENUM(pname), value));
}

void Texture::GetProp(TextureProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetTextureParameteriv(*this, ENUM(pname), value));
}

void Texture::GetPropInteger(TextureProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetTextureParameterIiv(*this, ENUM(pname), value));
}

void Texture::GetPropInteger(TextureProp pname, uint32_t* value) const
{
	GLUTIL_GL_CALL(glGetTextureParameterIuiv(*this, ENUM(pname), value));
}

float Texture::GetPropF(TextureProp pname) const
{
	float value = 0.0f;
	GetProp(pname, &value);
	return value;
}

int32_t Texture::GetPropI(TextureProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

TextureDepthStencilMode Texture::GetDepthStencilMode() const
{
	return static_cast<TextureDepthStencilMode>(GetPropI(TextureProp::DepthStencilMode));
}

TextureFilter Texture::GetMagFilter() const
{
	return static_cast<TextureFilter>(GetPropI(TextureProp::MagFilter));
}

TextureFilter Texture::GetMinFilter() const
{
	return static_cast<TextureFilter>(GetPropI(TextureProp::MinFilter));
}

float Texture::GetMinLod() const
{
	return GetPropF(TextureProp::MinLod);
}

float Texture::GetMaxLod() const
{
	return GetPropF(TextureProp::MaxLod);
}

int32_t Texture::GetBaseLevel() const
{
	return GetPropI(TextureProp::BaseLevel);
}

int32_t Texture::GetMaxLevel() const
{
	return GetPropI(TextureProp::MaxLevel);
}

TextureSwizzle Texture::GetSwizzleR() const
{
	return static_cast<TextureSwizzle>(GetPropI(TextureProp::SwizzleR));
}

TextureSwizzle Texture::GetSwizzleG() const
{
	return static_cast<TextureSwizzle>(GetPropI(TextureProp::SwizzleG));
}

TextureSwizzle Texture::GetSwizzleB() const
{
	return static_cast<TextureSwizzle>(GetPropI(TextureProp::SwizzleB));
}

TextureSwizzle Texture::GetSwizzleA() const
{
	return static_cast<TextureSwizzle>(GetPropI(TextureProp::SwizzleA));
}

TextureSwizzleRGBA Texture::GetSwizzleRGBA() const
{
	TextureSwizzleRGBA swizzles = { { TextureSwizzle::Red, TextureSwizzle::Green, TextureSwizzle::Blue, TextureSwizzle::Alpha } };
	GetProp(TextureProp::SwizzleRGBA, reinterpret_cast<int32_t*>(swizzles.swizzles));
	return swizzles;
}

TextureWrap Texture::GetWrapS() const
{
	return static_cast<TextureWrap>(GetPropI(TextureProp::WrapS));
}

TextureWrap Texture::GetWrapT() const
{
	return static_cast<TextureWrap>(GetPropI(TextureProp::WrapT));
}

TextureWrap Texture::GetWrapR() const
{
	return static_cast<TextureWrap>(GetPropI(TextureProp::WrapR));
}

Vec4f Texture::GetBorderColorF() const
{
	Vec4f r;
	GetProp(TextureProp::BorderColor, r.v);
	return r;
}

Vec4i Texture::GetBorderColorI() const
{
	Vec4i r;
	GetProp(TextureProp::BorderColor, r.v);
	return r;
}

Vec4i Texture::GetBorderColorIntegerI() const
{
	Vec4i r;
	GetPropInteger(TextureProp::BorderColor, r.v);
	return r;
}

Vec4ui Texture::GetBorderColorIntegerUI() const
{
	Vec4ui r;
	GetPropInteger(TextureProp::BorderColor, r.v);
	return r;
}

TextureCompareMode Texture::GetCompareMode() const
{
	return static_cast<TextureCompareMode>(GetPropI(TextureProp::CompareMode));
}

CompareFunc Texture::GetCompareFunc() const
{
	return static_cast<CompareFunc>(GetPropI(TextureProp::CompareFunc));
}

int32_t Texture::GetViewMinLevel() const
{
	return GetPropI(TextureProp::ViewMinLevel);
}

int32_t Texture::GetViewNumLevels() const
{
	return GetPropI(TextureProp::ViewNumLevels);
}

int32_t Texture::GetViewMinLayer() const
{
	return GetPropI(TextureProp::ViewMinLayer);
}

int32_t Texture::GetViewNumLayers() const
{
	return GetPropI(TextureProp::ViewNumLayers);
}

int32_t Texture::GetNumImmutableLevels() const
{
	return GetPropI(TextureProp::NumImmutableLevels);
}

ImageFormatCompatibilityType Texture::GetImageFormatCompatibilityType() const
{
	return static_cast<ImageFormatCompatibilityType>(GetPropI(TextureProp::ImageFormatCompatibilityType));
}

bool Texture::IsImmutableFormat() const
{
	return GetPropI(TextureProp::IsImmutableFormat) == GL_TRUE;
}

TextureTarget Texture::GetTarget() const
{
	return static_cast<TextureTarget>(GetPropI(TextureProp::Target));
}

} // namespace GLUtil