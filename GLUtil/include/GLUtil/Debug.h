#pragma once

#include "Common.h"

namespace GLUtil {

enum class Error : uint32_t
{
	NoError = 0,
	InvalidEnum  = 0x0500,
	InvalidValue = 0x0501,
	InvalidOperation = 0x0502,
	InvalidFramebufferOperation = 0x0506,
	OutOfMemory = 0x0505,
	StackUnderflow = 0x0504,
	StackOverflow = 0x0503
};

Error GetError();
const char* GetErrorString(Error error);

} // namespace GLUtil