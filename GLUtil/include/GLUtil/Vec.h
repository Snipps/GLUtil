#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <type_traits>

namespace GLUtil {

template<unsigned N, typename T>
struct Vec
{
	T v[N];

	inline Vec(const Vec&) = default;
	inline Vec(Vec&&) noexcept = default;
	inline Vec& operator=(const Vec&) = default;
	inline Vec& operator=(Vec&&) noexcept = default;
	inline ~Vec() = default;

	Vec()
	{
		for (unsigned i = 0; i < N; i++)
			v[i] = static_cast<T>(0);
	}

	Vec(T all)
	{
		for (unsigned i = 0; i < N; i++)
			v[i] = all;
	}

	explicit Vec(const T* mem)
	{
		for (unsigned i = 0; i < N; i++)
			v[i] = mem[i];
	}

	Vec& operator=(T all)
	{
		for (unsigned i = 0; i < N; i++)
			v[i] = all;
		return *this;
	}

	Vec& operator=(const T* mem)
	{
		for (unsigned i = 0; i < N; i++)
			v[i] = mem[i];
		return *this;
	}

	inline const T& operator[](unsigned i) const { return v[i]; }
	inline T& operator[](unsigned i) const { return v[i]; }
	inline operator const T*() const { return v; }
	inline operator T*() { return v; }
};

template<typename T>
struct Vec<2, T>
{
	union
	{
		T v[2];
		struct { T x, y; };
	};

	inline Vec(const Vec&) = default;
	inline Vec(Vec&&) noexcept = default;
	inline Vec& operator=(const Vec&) = default;
	inline Vec& operator=(Vec&&) noexcept = default;
	inline ~Vec() = default;

	inline Vec() :
		x(0), y(0)
	{}

	inline Vec(T all) :
		x(all), y(all)
	{}

	inline Vec(const T* mem) :
		x(mem[0]), y(mem[1])
	{}

	inline Vec(T x, T y) :
		x(x), y(y)
	{}

	inline Vec& operator=(T all)
	{
		x = all;
		y = all;
		return *this;
	}

	inline Vec& operator=(const T* mem)
	{
		x = mem[0];
		y = mem[1];
		return *this;
	}

	inline const T& operator[](unsigned i) const { return v[i]; }
	inline T& operator[](unsigned i) { return v[i]; }
	inline operator const T* () const { return v; }
	inline operator T* () { return v; }
};

template<typename T>
struct Vec<3, T>
{
	union
	{
		T v[3];
		struct { T x, y, z; };
	};

	inline Vec(const Vec&) = default;
	inline Vec(Vec&&) noexcept = default;
	inline Vec& operator=(const Vec&) = default;
	inline Vec& operator=(Vec&&) noexcept = default;
	inline ~Vec() = default;

	inline Vec() :
		x(0), y(0), z(0)
	{}

	inline Vec(T all) :
		x(all), y(all), z(all)
	{}

	inline Vec(const T* mem) :
		x(mem[0]), y(mem[1]), z(mem[2])
	{}

	inline Vec(T x, T y, T z = 0) :
		x(x), y(y), z(z)
	{}

	inline Vec(const Vec<2, T>& xy, T z = 0) :
		x(xy.x), y(xy.y), z(z)
	{}

	inline Vec(T x, const Vec<2, T>& yz) :
		x(x), y(yz.x), z(yz.y)
	{}

	inline Vec& operator=(T all)
	{
		x = all;
		y = all;
		z = all;
		return *this;
	}

	inline Vec& operator=(const T* mem)
	{
		x = mem[0];
		y = mem[1];
		z = mem[2];
		return *this;
	}

	inline const T& operator[](unsigned i) const { return v[i]; }
	inline T& operator[](unsigned i) { return v[i]; }
	inline operator const T* () const { return v; }
	inline operator T* () { return v; }
};

template<typename T>
struct Vec<4, T>
{
	union
	{
		T v[4];
		struct { T x, y, z, w; };
	};

	inline Vec(const Vec&) = default;
	inline Vec(Vec&&) noexcept = default;
	inline Vec& operator=(const Vec&) = default;
	inline Vec& operator=(Vec&&) noexcept = default;
	inline ~Vec() = default;

	inline Vec() :
		x(0), y(0), z(0), w(0)
	{}

	inline Vec(T all) :
		x(all), y(all), z(all), w(all)
	{}

	inline Vec(const T* mem) :
		x(mem[0]), y(mem[1]), z(mem[2]), w(mem[3])
	{}

	inline Vec(T x, T y, T z = 0, T w = 0) :
		x(x), y(y), z(z), w(w)
	{}

	inline Vec(const Vec<3, T>& xyz, T w = 0) :
		x(xyz.x), y(xyz.y), z(xyz.z), w(w)
	{}

	inline Vec(T x, const Vec<3, T>& yzw) :
		x(x), y(yzw.x), z(yzw.y), w(yzw.z)
	{}

	inline Vec(const Vec<2, T>& xy, const Vec<2, T>& zw) :
		x(xy.x), y(xy.y), z(zw.x), w(zw.y)
	{}

	inline Vec(const Vec<2, T>& xy, T z = 0, T w = 0) :
		x(xy.x), y(xy.y), z(z), w(w)
	{}

	inline Vec(T x, const Vec<2, T>& yz, T w = 0) :
		x(x), y(yz.x), z(yz.y), w(w)
	{}

	inline Vec(T x, T y, const Vec<2, T>& zw) :
		x(x), y(y), z(zw.x), w(zw.y)
	{}

	inline Vec& operator=(T all)
	{
		x = all;
		y = all;
		z = all;
		w = all;
		return *this;
	}

	inline Vec& operator=(const T* mem)
	{
		x = mem[0];
		y = mem[1];
		z = mem[2];
		w = mem[3];
		return *this;
	}

	inline const T& operator[](unsigned i) const { return v[i]; }
	inline T& operator[](unsigned i) { return v[i]; }
	inline operator const T* () const { return v; }
	inline operator T* () { return v; }
};

template<typename T>
using Vec2 = Vec<2, T>;

using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int32_t>;
using Vec2ui = Vec2<uint32_t>;
using Vec2i64 = Vec2<int64_t>;
using Vec2ui64 = Vec2<uint64_t>;
using Vec2b = Vec2<bool>;

template<typename T>
using Vec3 = Vec<3, T>;

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int32_t>;
using Vec3ui = Vec3<uint32_t>;
using Vec3i64 = Vec3<int64_t>;
using Vec3ui64 = Vec3<uint64_t>;
using Vec3b = Vec3<bool>;

template<typename T>
using Vec4 = Vec<4, T>;

using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
using Vec4i = Vec4<int32_t>;
using Vec4ui = Vec4<uint32_t>;
using Vec4i64 = Vec4<int64_t>;
using Vec4ui64 = Vec4<uint64_t>;
using Vec4b = Vec4<bool>;

template<unsigned N, typename T>
Vec<N, T> operator+(const Vec<N, T>& a, const Vec<N, T>& b)
{
	Vec<N, T> r = a;
	for (unsigned i = 0; i < N; i++)
		r.v[i] += b.v[i];
	return r;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator+(const Vec<N, T>& a, U b)
{
	return a + Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator+(U a, const Vec<N, T>& b)
{
	return Vec<N, T>(static_cast<T>(a)) + b;
}

template<unsigned N, typename T>
Vec<N, T>& operator+=(Vec<N, T>& a, const Vec<N, T>& b)
{
	for (unsigned i = 0; i < N; i++)
		a.v[i] += b.v[i];
	return a;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>&>::type
operator+=(Vec<N, T>& a, U b)
{
	return a += Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T>
Vec<N, T> operator-(const Vec<N, T>& a, const Vec<N, T>& b)
{
	Vec<N, T> r = a;
	for (unsigned i = 0; i < N; i++)
		r.v[i] -= b.v[i];
	return r;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator-(const Vec<N, T>& a, U b)
{
	return a - Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator-(U a, const Vec<N, T>& b)
{
	return Vec<N, T>(static_cast<T>(a)) - b;
}

template<unsigned N, typename T>
Vec<N, T>& operator-=(Vec<N, T>& a, const Vec<N, T>& b)
{
	for (unsigned i = 0; i < N; i++)
		a.v[i] -= b.v[i];
	return a;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>&>::type
operator-=(Vec<N, T>& a, U b)
{
	return a -= Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T>
Vec<N, T> operator*(const Vec<N, T>& a, const Vec<N, T>& b)
{
	Vec<N, T> r = a;
	for (unsigned i = 0; i < N; i++)
		r.v[i] *= b.v[i];
	return r;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator*(const Vec<N, T>& a, U b)
{
	return a * Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator*(U a, const Vec<N, T>& b)
{
	return Vec<N, T>(static_cast<T>(a)) * b;
}

template<unsigned N, typename T>
Vec<N, T>& operator*=(Vec<N, T>& a, const Vec<N, T>& b)
{
	for (unsigned i = 0; i < N; i++)
		a.v[i] *= b.v[i];
	return a;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>&>::type
operator*=(Vec<N, T>& a, U b)
{
	return a *= Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T>
Vec<N, T> operator/(const Vec<N, T>& a, const Vec<N, T>& b)
{
	Vec<N, T> r = a;
	for (unsigned i = 0; i < N; i++)
		r.v[i] /= b.v[i];
	return r;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator/(const Vec<N, T>& a, U b)
{
	return a / Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>>::type
operator/(U a, const Vec<N, T>& b)
{
	return Vec<N, T>(static_cast<T>(a)) / b;
}

template<unsigned N, typename T>
Vec<N, T>& operator/=(Vec<N, T>& a, const Vec<N, T>& b)
{
	for (unsigned i = 0; i < N; i++)
		a.v[i] /= b.v[i];
	return a;
}

template<unsigned N, typename T, typename U>
typename std::enable_if<std::is_scalar<U>::value, Vec<N, T>&>::type
operator/=(Vec<N, T>& a, U b)
{
	return a /= Vec<N, T>(static_cast<T>(b));
}

template<unsigned N, typename T>
T Sum(const Vec<N, T>& v)
{
	T r = v.v[0];
	for (unsigned i = 1; i < N; i++)
		r += v.v[i];
	return r;
}

template<unsigned N, typename T>
T Norm(const Vec<N, T>& v)
{
	return Sum(v * v);
}

template<unsigned N, typename T>
T Length(const Vec<N, T>& v)
{
	return std::sqrt(Norm(v));
}

template<unsigned N, typename T>
Vec<N, T> Normalize(const Vec<N, T>& v)
{
	return v / Length(v);
}

template<unsigned N, typename T>
T Dot(const Vec<N, T>& a, const Vec<N, T>& b)
{
	return Sum(a * b);
}

template<typename T>
Vec<3, T> Cross(const Vec<3, T>& a, const Vec<3, T>& b)
{
	return (Vec<3, T>(a.y, a.z, a.x) * Vec<3, T>(b.z, b.x, b.y)) - (Vec<3, T>(a.z, a.x, a.y) * Vec<3, T>(b.y, b.z, b.x));
}

} // namespace GLUtil