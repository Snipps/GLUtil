#pragma once

#include "Common.h"
#include "Object.h"
#include "Vec.h"

namespace GLUtil {

enum class SamplerParam : uint32_t
{
	MinFilter = 0x2801,
	MagFilter = 0x2800,
	MinLod = 0x813A,
	MaxLod = 0x813B,
	WrapS = 0x2802,
	WrapT = 0x2803,
	WrapR = 0x8072,
	BorderColor = 0x1004,
	CompareMode = 0x884C,
	CompareFunc = 0x884D
};

enum class TextureFilter : uint32_t
{
	Nearest  = 0x2600,
	Linear = 0x2601,
	NearestMipmapNearest = 0x2700,
	LinearMipmapNearest = 0x2701,
	NearestMipmapLinear = 0x2702,
	LinearMipmapLinear = 0x2703
};

enum class TextureWrap : uint32_t
{
	ClampToEdge = 0x812F,
	ClampToBorder = 0x812D,
	MirroredRepeat = 0x8370,
	Repeat = 0x2901,
	MirrorClampToEdge = 0x8743
};

enum class TextureCompareMode : uint32_t
{
	RefToTexture = 0x884E,
	None = 0
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