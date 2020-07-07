#pragma once

#include "Vec.h"

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <initializer_list>

#define GLUTIL_GL_CALL(call) call

namespace GLUtil {

enum class DataType : uint32_t
{
	Byte = 0x1400,
	UnsignedByte = 0x1401,
	Short = 0x1402,
	UnsignedShort = 0x1403,
	Float = 0x1406,
	FloatVec2 = 0x8B50,
	FloatVec3 = 0x8B51,
	FloatVec4 = 0x8B52,
	Double = 0x140A,
	DoubleVec2 = 0x8FFC,
	DoubleVec3 = 0x8FFD,
	DoubleVec4 = 0x8FFE,
	Int = 0x1404,
	IntVec2 = 0x8B53,
	IntVec3 = 0x8B54,
	IntVec4 = 0x8B55,
	UnsignedInt = 0x1405,
	UnsignedIntVec2 = 0x8DC6,
	UnsignedIntVec3 = 0x8DC7,
	UnsignedIntVec4 = 0x8DC8,
	Bool = 0x8B56,
	BoolVec2 = 0x8B57,
	BoolVec3 = 0x8B58,
	BoolVec4 = 0x8B59,
	FloatMat2 = 0x8B5A,
	FloatMat3 = 0x8B5B,
	FloatMat4 = 0x8B5C,
	FloatMat2x3 = 0x8B65,
	FloatMat2x4 = 0x8B66,
	FloatMat3x2 = 0x8B67,
	FloatMat3x4 = 0x8B68,
	FloatMat4x2 = 0x8B69,
	FloatMat4x3 = 0x8B6A,
	DoubleMat2 = 0x8F46,
	DoubleMat3 = 0x8F47,
	DoubleMat4 = 0x8F48,
	DoubleMat2x3 = 0x8F49,
	DoubleMat2x4 = 0x8F4A,
	DoubleMat3x2 = 0x8F4B,
	DoubleMat3x4 = 0x8F4C,
	DoubleMat4x2 = 0x8F4D,
	DoubleMat4x3 = 0x8F4E,
	Sampler1D = 0x8B5D,
	Sampler2D = 0x8B5E,
	Sampler3D = 0x8B5F,
	SamplerCube = 0x8B60,
	Sampler1DShadow = 0x8B61,
	Sampler2DShadow = 0x8B62,
	Sampler1DArray = 0x8DC0,
	Sampler2DArray = 0x8DC1,
	Sampler1DArrayShadow = 0x8DC3,
	Sampler2DArrayShadow = 0x8DC4,
	Sampler2DMultisample = 0x9108,
	Sampler2DMultisampleArray = 0x910B,
	SamplerCubeShadow = 0x8DC5,
	SamplerBuffer = 0x8DC2,
	Sampler2DRect = 0x8B63,
	Sampler2DRectShadow = 0x8B64,
	IntSampler1D = 0x8DC9,
	IntSampler2D = 0x8DCA,
	IntSampler3D = 0x8DCB,
	IntSamplerCube = 0x8DCC,
	IntSampler1DArray = 0x8DCE,
	IntSampler2DArray = 0x8DCF,
	IntSampler2DMultisample = 0x9109,
	IntSampler2DMultisampleArray = 0x910C,
	IntSamplerBuffer = 0x8DD0,
	IntSampler2DRect = 0x8DCD,
	UnsignedIntSampler1D = 0x8DD1,
	UnsignedIntSampler2D = 0x8DD2,
	UnsignedIntSampler3D = 0x8DD3,
	UnsignedIntSamplerCube = 0x8DD4,
	UnsignedIntSampler1DArray = 0x8DD6,
	UnsignedIntSampler2DArray = 0x8DD7,
	UnsignedIntSampler2DMultisample = 0x910A,
	UnsignedIntSampler2DMultisampleArray = 0x910D,
	UnsignedIntSamplerBuffer = 0x8DD8,
	UnsignedIntSampler2DRect = 0x8DD5
};

enum class CompareFunc : uint32_t
{
	LessEqual,
	GreaterEqual,
	Less,
	Greater,
	Equal,
	NotEqual,
	Always,
	Never
};

enum class Access : uint32_t
{
	ReadOnly,
	WriteOnly,
	ReadWrite
};

uint32_t GetDataTypeSize(DataType type);

struct Box
{
	Vec2i offset, size;
};

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

} // namespace GLUtil