#pragma once

#include "Common.h"
#include "Object.h"
#include "Vec.h"

namespace GLUtil {

enum class SamplerParam : uint32_t
{
	MinFilter,
	MagFilter,
	MinLod,
	MaxLod,
	WrapS,
	WrapT,
	WrapR,
	BorderColor,
	CompareMode,
	CompareFunc
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

enum class TextureCompareMode : uint32_t
{
	RefToTexture,
	None
};

class Sampler : GLObject
{
public:
	Sampler() = delete;
	Sampler(const Sampler&) = delete;
	Sampler(Sampler&&) noexcept = default;
	Sampler& operator=(const Sampler&) = delete;
	Sampler& operator=(Sampler&&) noexcept = default;

	Sampler(uint32_t sampler);
	virtual ~Sampler();

	static Sampler Create();
	static Sampler Gen();

	void Bind(uint32_t unit) const;

	Sampler& SetParamF(SamplerParam pname, float value);
	Sampler& SetParamI(SamplerParam pname, int32_t value);
	Sampler& SetParam(SamplerParam pname, const float* values);
	Sampler& SetParam(SamplerParam pname, const int32_t* values);
	Sampler& SetParamInteger(SamplerParam pname, const int32_t* values);
	Sampler& SetParamInteger(SamplerParam pname, const uint32_t* values);

	Sampler& SetMinFilter(TextureFilter filter);
	Sampler& SetMagFilter(TextureFilter filter);
	Sampler& SetMinLod(float minLod);
	Sampler& SetMaxLod(float maxLod);
	Sampler& SetWrapS(TextureWrap wrap);
	Sampler& SetWrapT(TextureWrap wrap);
	Sampler& SetWrapR(TextureWrap wrap);
	Sampler& SetBorderColorF(Vec4f color);
	Sampler& SetBorderColorI(Vec4i color);
	Sampler& SetBorderColorIntegerI(Vec4i color);
	Sampler& SetBorderColorIntegerUI(Vec4ui color);
	Sampler& SetCompareMode(TextureCompareMode mode);
	Sampler& SetCompareFunc(CompareFunc func);

	void GetParam(SamplerParam pname, float* value) const;
	void GetParam(SamplerParam pname, int32_t* value) const;
	void GetParamInteger(SamplerParam pname, int32_t* value) const;
	void GetParamInteger(SamplerParam pname, uint32_t* value) const;

	float GetParamF(SamplerParam pname) const;
	int32_t GetParamI(SamplerParam pname) const;

	TextureFilter GetMinFilter() const;
	TextureFilter GetMagFilter() const;
	float GetMinLod() const;
	float GetMaxLod() const;
	TextureWrap GetWrapS() const;
	TextureWrap GetWrapT() const;
	TextureWrap GetWrapR() const;
	Vec4f GetBorderColorF() const;
	Vec4i GetBorderColorI() const;
	Vec4i GetBorderColorIntegerI() const;
	Vec4ui GetBorderColorIntegerUI() const;
	TextureCompareMode GetCompareMode() const;
	CompareFunc GetCompareFunc() const;
};

} // namespace GLUtil