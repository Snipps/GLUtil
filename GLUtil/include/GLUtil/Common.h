#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <initializer_list>

#define GLUTIL_GL_CALL(call) call

namespace GLUtil {

enum class DataType : uint32_t
{
	Float,
	FloatVec2,
	FloatVec3,
	FloatVec4,
	Double,
	DoubleVec2,
	DoubleVec3,
	DoubleVec4,
	Int,
	IntVec2,
	IntVec3,
	IntVec4,
	UnsignedInt,
	UnsignedIntVec2,
	UnsignedIntVec3,
	UnsignedIntVec4,
	Bool,
	BoolVec2,
	BoolVec3,
	BoolVec4,
	FloatMat2,
	FloatMat3,
	FloatMat4,
	FloatMat2x3,
	FloatMat2x4,
	FloatMat3x2,
	FloatMat3x4,
	FloatMat4x2,
	FloatMat4x3,
	DoubleMat2,
	DoubleMat3,
	DoubleMat4,
	DoubleMat2x3,
	DoubleMat2x4,
	DoubleMat3x2,
	DoubleMat3x4,
	DoubleMat4x2,
	DoubleMat4x3,
	Sampler1D,
	Sampler2D,
	Sampler3D,
	SamplerCube,
	Sampler1DShadow,
	Sampler2DShadow,
	Sampler1DArray,
	Sampler2DArray,
	Sampler1DArrayShadow,
	Sampler2DArrayShadow,
	Sampler2DMultisample,
	Sampler2DMultisampleArray,
	SamplerCubeShadow,
	SamplerBuffer,
	Sampler2DRect,
	Sampler2DRectShadow,
	IntSampler1D,
	IntSampler2D,
	IntSampler3D,
	IntSamplerCube,
	IntSampler1DArray,
	IntSampler2DArray,
	IntSampler2DMultisample,
	IntSampler2DMultisampleArray,
	IntSamplerBuffer,
	IntSampler2DRect,
	UnsignedIntSampler1D,
	UnsignedIntSampler2D,
	UnsignedIntSampler3D,
	UnsignedIntSamplerCube,
	UnsignedIntSampler1DArray,
	UnsignedIntSampler2DArray,
	UnsignedIntSampler2DMultisample,
	UnsignedIntSampler2DMultisampleArray,
	UnsignedIntSamplerBuffer,
	UnsignedIntSampler2DRect
};

uint32_t GetDataTypeSize(DataType type);

template<typename E, typename I = typename std::underlying_type<E>::type>
class Flags
{
private:
	union
	{
		E mEnum;
		I mInt;
	};
public:
	inline constexpr Flags(const Flags&) = default;
	inline constexpr Flags(Flags&&) noexcept = default;
	inline Flags& operator=(const Flags&) = default;
	inline Flags& operator=(Flags&&) noexcept = default;
	inline ~Flags() = default;

	inline constexpr Flags() :
		mInt(0)
	{}

	inline constexpr Flags(I i) :
		mInt(i)
	{}

	inline constexpr Flags(E e) :
		mEnum(e)
	{}

	constexpr Flags(std::initializer_list<E> init) :
		mInt(0)
	{
		for (auto it = init.begin(); it != init.end(); it++)
			mInt |= static_cast<I>(*it);
	}

	inline Flags& operator=(I other) { mInt = other; return *this; }
	inline Flags& operator=(E other) { mEnum = other; return *this; }
	
	Flags& operator=(std::initializer_list<E> init)
	{
		mInt = 0;
		for (auto it = init.begin(); it != init.end(); it++)
			mInt |= static_cast<I>(*it);
		return *this;
	}

	inline constexpr bool operator==(Flags other) const { return mInt == other.mInt; }
	inline constexpr bool operator==(I other) const { return mInt == other; }
	inline constexpr bool operator==(E other) const { return mEnum == other; }

	inline constexpr bool operator!=(Flags other) const { return mInt != other.mInt; }
	inline constexpr bool operator!=(I other) const { return mInt != other; }
	inline constexpr bool operator!=(E other) const { return mEnum != other; }

	inline constexpr operator bool() const { return mInt != 0; }

	inline constexpr Flags operator|(Flags other) const { return mInt | other.mInt; }
	inline constexpr Flags operator|(I other) const { return mInt | other; }
	inline constexpr Flags operator|(E other) const { return mInt | static_cast<I>(other); }

	inline Flags& operator|=(Flags other) { return *this = (mInt | other.mInt); }
	inline Flags& operator|=(I other) { return *this = (mInt | other); }
	inline Flags& operator|=(E other) { return *this = (mInt | static_cast<I>(other)); }
	
	inline constexpr Flags operator&(Flags other) const { return mInt & other.mInt; }
	inline constexpr Flags operator&(I other) const { return mInt & other; }
	inline constexpr Flags operator&(E other) const { return mInt & static_cast<I>(other); }
	
	template<typename T>
	inline constexpr T AsInt() const { return static_cast<T>(mInt); }

	inline constexpr E AsEnum() const { return mEnum; }
	inline constexpr I AsInt() const { return mInt; }
	inline constexpr operator E() const { return mEnum; }
	inline constexpr operator I() const { return mInt; }
};

}