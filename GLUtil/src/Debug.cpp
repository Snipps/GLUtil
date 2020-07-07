#include <GLUtil/Debug.h>

namespace GLUtil {

const char* GetErrorString(Error error)
{
	switch (error) {
		case Error::NoError:
			return "no error";
		case Error::InvalidEnum:
			return "invalid enum";
		case Error::InvalidValue:
			return "invalid value";
		case Error::InvalidOperation:
			return "invalid operation";
		case Error::InvalidFramebufferOperation:
			return "invalid framebuffer operation";
		case Error::OutOfMemory:
			return "out of memory";
		case Error::StackUnderflow:
			return "stack underflow";
		case Error::StackOverflow:
			return "stack overflow";
		default:
			return "unreckognized error";
	}
}

} // namespace GLUtil