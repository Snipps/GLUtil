#include <GLUtil/Sampler.h>

#include <glad/gl.h>

#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

Sampler::Sampler(uint32_t sampler) :
	GLObject(sampler)
{}

Sampler::~Sampler()
{
	if (*this) {
		GLUTIL_GL_CALL(glDeleteSamplers(1, GetIDPtr()));
	}
}

Sampler Sampler::Create()
{
	uint32_t sampler = 0;
	GLUTIL_GL_CALL(glCreateSamplers(1, &sampler));
	return Sampler(sampler);
}

Sampler Sampler::Gen()
{
	uint32_t sampler = 0;
	GLUTIL_GL_CALL(glGenSamplers(1, &sampler));
	return Sampler(sampler);
}

void Sampler::Bind(uint32_t unit) const
{
	GLUTIL_GL_CALL(glBindSampler(unit, *this));
}

Sampler& Sampler::SetParamF(SamplerParam pname, float value)
{
	GLUTIL_GL_CALL(glSamplerParameterf(*this, ENUM(pname), value));
	return *this;
}

Sampler& Sampler::SetParamI(SamplerParam pname, int32_t value)
{
	GLUTIL_GL_CALL(glSamplerParameteri(*this, ENUM(pname), value));
	return *this;
}

Sampler& Sampler::SetParam(SamplerParam pname, const float* values)
{
	GLUTIL_GL_CALL(glSamplerParameterfv(*this, ENUM(pname), values));
	return *this;
}

Sampler& Sampler::SetParam(SamplerParam pname, const int32_t* values)
{
	GLUTIL_GL_CALL(glSamplerParameteriv(*this, ENUM(pname), values));
	return *this;
}

Sampler& Sampler::SetParamInteger(SamplerParam pname, const int32_t* values)
{
	GLUTIL_GL_CALL(glSamplerParameterIiv(*this, ENUM(pname), values));
	return *this;
}

Sampler& Sampler::SetParamInteger(SamplerParam pname, const uint32_t* values)
{
	GLUTIL_GL_CALL(glSamplerParameterIuiv(*this, ENUM(pname), values));
	return *this;
}

Sampler& Sampler::SetMinFilter(TextureFilter filter)
{
	return SetParamI(SamplerParam::MinFilter, ENUM(filter));
}

Sampler& Sampler::SetMagFilter(TextureFilter filter)
{
	return SetParamI(SamplerParam::MagFilter, ENUM(filter));
}

Sampler& Sampler::SetMinLod(float minLod)
{
	return SetParamF(SamplerParam::MinLod, minLod);
}

Sampler& Sampler::SetMaxLod(float maxLod)
{
	return SetParamF(SamplerParam::MaxLod, maxLod);
}

Sampler& Sampler::SetWrapS(TextureWrap wrap)
{
	return SetParamI(SamplerParam::WrapS, ENUM(wrap));
}

Sampler& Sampler::SetWrapT(TextureWrap wrap)
{
	return SetParamI(SamplerParam::WrapT, ENUM(wrap));
}

Sampler& Sampler::SetWrapR(TextureWrap wrap)
{
	return SetParamI(SamplerParam::WrapR, ENUM(wrap));
}

Sampler& Sampler::SetBorderColorF(Vec4f color)
{
	return SetParam(SamplerParam::BorderColor, color.v);
}

Sampler& Sampler::SetBorderColorI(Vec4i color)
{
	return SetParam(SamplerParam::BorderColor, color.v);
}

Sampler& Sampler::SetBorderColorIntegerI(Vec4i color)
{
	return SetParamInteger(SamplerParam::BorderColor, color.v);
}

Sampler& Sampler::SetBorderColorIntegerUI(Vec4ui color)
{
	return SetParamInteger(SamplerParam::BorderColor, color.v);
}

Sampler& Sampler::SetCompareMode(TextureCompareMode mode)
{
	return SetParamI(SamplerParam::CompareMode, ENUM(mode));
}

Sampler& Sampler::SetCompareFunc(CompareFunc func)
{
	return SetParamI(SamplerParam::CompareFunc, ENUM(func));
}

void Sampler::GetParam(SamplerParam pname, float* value) const
{
	GLUTIL_GL_CALL(glGetSamplerParameterfv(*this, ENUM(pname), value));
}

void Sampler::GetParam(SamplerParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetSamplerParameteriv(*this, ENUM(pname), value));
}

void Sampler::GetParamInteger(SamplerParam pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetSamplerParameterIiv(*this, ENUM(pname), value));
}

void Sampler::GetParamInteger(SamplerParam pname, uint32_t* value) const
{
	GLUTIL_GL_CALL(glGetSamplerParameterIuiv(*this, ENUM(pname), value));
}

float Sampler::GetParamF(SamplerParam pname) const
{
	float value = 0;
	GetParam(pname, &value);
	return value;
}

int32_t Sampler::GetParamI(SamplerParam pname) const
{
	int32_t value = 0;
	GetParam(pname, &value);
	return value;
}

TextureFilter Sampler::GetMinFilter() const
{
	return static_cast<TextureFilter>(GetParamI(SamplerParam::MinFilter));
}

TextureFilter Sampler::GetMagFilter() const
{
	return static_cast<TextureFilter>(GetParamI(SamplerParam::MagFilter));
}

float Sampler::GetMinLod() const
{
	return GetParamF(SamplerParam::MinLod);
}

float Sampler::GetMaxLod() const
{
	return GetParamF(SamplerParam::MaxLod);
}

TextureWrap Sampler::GetWrapS() const
{
	return static_cast<TextureWrap>(GetParamI(SamplerParam::WrapS));
}

TextureWrap Sampler::GetWrapT() const
{
	return static_cast<TextureWrap>(GetParamI(SamplerParam::WrapT));
}

TextureWrap Sampler::GetWrapR() const
{
	return static_cast<TextureWrap>(GetParamI(SamplerParam::WrapR));
}

Vec4f Sampler::GetBorderColorF() const
{
	Vec4f r;
	GetParam(SamplerParam::BorderColor, r.v);
	return r;
}

Vec4i Sampler::GetBorderColorI() const
{
	Vec4i r;
	GetParam(SamplerParam::BorderColor, r.v);
	return r;
}

Vec4i Sampler::GetBorderColorIntegerI() const
{
	Vec4i r;
	GetParamInteger(SamplerParam::BorderColor, r.v);
	return r;
}

Vec4ui Sampler::GetBorderColorIntegerUI() const
{
	Vec4ui r;
	GetParamInteger(SamplerParam::BorderColor, r.v);
	return r;
}

TextureCompareMode Sampler::GetCompareMode() const
{
	return static_cast<TextureCompareMode>(GetParamI(SamplerParam::CompareMode));
}

CompareFunc Sampler::GetCompareFunc() const
{
	return static_cast<CompareFunc>(GetParamI(SamplerParam::CompareFunc));
}

} // namespace GLUtil