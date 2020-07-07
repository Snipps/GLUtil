#pragma once

#include "Common.h"

namespace GLUtil {

enum class Error : uint32_t
{
	NoError,
	InvalidEnum,
	InvalidValue,
	InvalidOperation,
	InvalidFramebufferOperation,
	OutOfMemory,
	StackUnderflow,
	StackOverflow
};

const char* GetErrorString(Error error);

} // namespace GLUtil