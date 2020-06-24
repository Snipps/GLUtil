#pragma once

#include "Vec.h"

namespace GLUtil {

template<unsigned N, unsigned M, typename T>
struct Mat
{
	union
	{
		Vec<M, T> rows[N];
		T v[N * M];
		T m[N][M];
	};

	Mat()
	{
		for (unsigned i = 0; i < N; i++)
			rows[i] = static_cast<T>(0);
	}
};

template<typename T>
using Mat2 = Mat<2, 2, T>;
using Mat2f = Mat2<float>;
using Mat2d = Mat2<double>;

template<typename T>
using Mat3 = Mat<3, 3, T>;
using Mat3f = Mat3<float>;
using Mat3d = Mat3<double>;

template<typename T>
using Mat4 = Mat<4, 4, T>;
using Mat4f = Mat4<float>;
using Mat4d = Mat4<double>;

template<typename T>
using Mat2x3 = Mat<2, 3, T>;
using Mat2x3f = Mat2x3<float>;
using Mat2x3d = Mat2x3<double>;

template<typename T>
using Mat2x4 = Mat<2, 4, T>;
using Mat2x4f = Mat2x4<float>;
using Mat2x4d = Mat2x4<double>;

template<typename T>
using Mat3x2 = Mat<3, 2, T>;
using Mat3x2f = Mat3x2<float>;
using Mat3x2d = Mat3x2<double>;

template<typename T>
using Mat3x4 = Mat<3, 4, T>;
using Mat3x4f = Mat3x4<float>;
using Mat3x4d = Mat3x4<double>;

template<typename T>
using Mat4x2 = Mat<4, 2, T>;
using Mat4x2f = Mat4x2<float>;
using Mat4x2d = Mat4x2<double>;

template<typename T>
using Mat4x3 = Mat<4, 3, T>;
using Mat4x3f = Mat4x3<float>;
using Mat4x3d = Mat4x3<double>;

} // namespace GLUtil