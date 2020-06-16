#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#define GLUTIL_GL_CALL(call) call

namespace GLUtil {

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