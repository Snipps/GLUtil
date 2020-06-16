#pragma once

#include <cstdint>

namespace GLUtil {

class GLObject
{
private:
	uint32_t mObject;
protected:
	uint32_t* GetIDPtr();
	GLObject& operator=(uint32_t id);
	GLObject& SetID(uint32_t id);
public:
	GLObject(const GLObject&) = delete;
	GLObject& operator=(const GLObject&) = delete;
	virtual ~GLObject() = default;

	GLObject();
	GLObject(GLObject&& other) noexcept;
	explicit GLObject(uint32_t id);
	GLObject& operator=(GLObject&& other) noexcept;

	const uint32_t* GetIDPtr() const;

	uint32_t GetID() const;
	operator uint32_t() const;

	operator bool() const;
};

} // namespace GLUtil