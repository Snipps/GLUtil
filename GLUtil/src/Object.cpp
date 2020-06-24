#include <GLUtil/Object.h>

namespace GLUtil {

GLObject::GLObject() :
	mObject(0)
{}

GLObject::GLObject(GLObject&& other) noexcept
{
	mObject = other.mObject;
	other.mObject = 0;
}

GLObject::GLObject(uint32_t id) :
	mObject(id)
{}

GLObject& GLObject::operator=(GLObject&& other) noexcept
{
	uint32_t temp = mObject;
	mObject = other.mObject;
	other.mObject = temp;
	return *this;
}

GLObject& GLObject::operator=(uint32_t id)
{
	mObject = id;
	return *this;
}

GLObject& GLObject::SetID(uint32_t id)
{
	mObject = id;
	return *this;
}

const uint32_t* GLObject::GetIDPtr() const
{
	return &mObject;
}

uint32_t* GLObject::GetIDPtr()
{
	return &mObject;
}

uint32_t GLObject::GetID() const
{
	return mObject;
}

GLObject::operator uint32_t() const
{
	return mObject;
}

GLObject::operator bool() const
{
	return mObject != 0;
}

} // namespace GLUtil