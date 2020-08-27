#include <GLUtil/Buffer.h>

#include <GLUtil/Common.h>

#include <glad/gl.h>

#define BUFFER_BIND BufferBind _bind(target, *this)
#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

BufferBinding BufferTargetToBinding(BufferTarget target)
{
	switch (target) {
		case BufferTarget::Array:
			return BufferBinding::Array;
		case BufferTarget::AtomicCounter:
			return BufferBinding::AtomicCounter;
		case BufferTarget::CopyRead:
			return BufferBinding::CopyRead;
		case BufferTarget::CopyWrite:
			return BufferBinding::CopyWrite;
		case BufferTarget::DispatchIndirect:
			return BufferBinding::DispatchIndirect;
		case BufferTarget::DrawIndirect:
			return BufferBinding::DrawIndirect;
		case BufferTarget::ElementArray:
			return BufferBinding::ElementArray;
		case BufferTarget::PixelPack:
			return BufferBinding::PixelPack;
		case BufferTarget::PixelUnpack:
			return BufferBinding::PixelUnpack;
		case BufferTarget::Query:
			return BufferBinding::Query;
		case BufferTarget::ShaderStorage:
			return BufferBinding::ShaderStorage;
		case BufferTarget::Texture:
			return BufferBinding::Texture;
		case BufferTarget::TransformFeedback:
			return BufferBinding::TransformFeedback;
		case BufferTarget::Uniform:
			return BufferBinding::Uniform;
		default:
			return static_cast<BufferBinding>(0);
	}
}

BufferTarget BufferBindingToTarget(BufferBinding binding)
{
	switch (binding) {
		case BufferBinding::Array:
			return BufferTarget::Array;
		case BufferBinding::AtomicCounter:
			return BufferTarget::AtomicCounter;
		case BufferBinding::CopyRead:
			return BufferTarget::CopyRead;
		case BufferBinding::CopyWrite:
			return BufferTarget::CopyWrite;
		case BufferBinding::DispatchIndirect:
			return BufferTarget::DispatchIndirect;
		case BufferBinding::DrawIndirect:
			return BufferTarget::DrawIndirect;
		case BufferBinding::ElementArray:
			return BufferTarget::ElementArray;
		case BufferBinding::PixelPack:
			return BufferTarget::PixelPack;
		case BufferBinding::PixelUnpack:
			return BufferTarget::PixelUnpack;
		case BufferBinding::Query:
			return BufferTarget::Query;
		case BufferBinding::ShaderStorage:
			return BufferTarget::ShaderStorage;
		case BufferBinding::Texture:
			return BufferTarget::Texture;
		case BufferBinding::TransformFeedback:
			return BufferTarget::TransformFeedback;
		case BufferBinding::Uniform:
			return BufferTarget::Uniform;
		default:
			return static_cast<BufferTarget>(0);
	}
}

uint32_t GetBoundBuffer(BufferBinding binding)
{
	uint32_t buffer = 0;
	GLUTIL_GL_CALL(glGetIntegerv(ENUM(binding), reinterpret_cast<GLint*>(&buffer)));
	return buffer;
}

uint32_t GetBoundBuffer(BufferTarget target)
{
	return GetBoundBuffer(BufferTargetToBinding(target));
}

void BindBuffer(BufferTarget target, uint32_t buffer)
{
	GLUTIL_GL_CALL(glBindBuffer(ENUM(target), buffer));
}

void BindBufferBase(BufferTarget target, uint32_t index, uint32_t buffer)
{
	GLUTIL_GL_CALL(glBindBufferBase(ENUM(target), index, buffer));
}

void BindBufferRange(BufferTarget target, uint32_t index, uint32_t buffer, intptr_t offset, intptr_t size)
{
	GLUTIL_GL_CALL(glBindBufferRange(ENUM(target), index, buffer, offset, size));
}

BufferBind::BufferBind(BufferTarget target, uint32_t buffer) :
	mTarget(target), mPrev(GetBoundBuffer(target))
{
	BindBuffer(target, buffer);
}

BufferBind::~BufferBind()
{
	BindBuffer(mTarget, mPrev);
}

Buffer::Buffer()
{
	GLUTIL_GL_CALL(glCreateBuffers(1, GetIDPtr()));
}

Buffer::Buffer(uint32_t buffer) :
	GLObject(buffer)
{}

Buffer::Buffer(intptr_t size, const void* data, Flags<BufferStorageFlags> flags) : 
	Buffer()
{
	Storage(size, data, flags);
}

Buffer::Buffer(intptr_t size, const void* data, BufferUsage usage) :
	Buffer()
{
	Data(size, data, usage);
}

Buffer::~Buffer()
{
	if (*this) {
		GLUTIL_GL_CALL(glDeleteBuffers(1, GetIDPtr()));
	}
}

Buffer& Buffer::Storage(intptr_t size, const void* data, Flags<BufferStorageFlags> flags)
{
	GLUTIL_GL_CALL(glNamedBufferStorage(*this, size, data, flags));
	return *this;
}

Buffer& Buffer::Data(intptr_t size, const void* data, BufferUsage usage)
{
	GLUTIL_GL_CALL(glNamedBufferData(*this, size, data, ENUM(usage)));
	return *this;
}

Buffer& Buffer::SubData(intptr_t offset, intptr_t size, const void* data)
{
	GLUTIL_GL_CALL(glNamedBufferSubData(*this, offset, size, data));
	return *this;
}

void* Buffer::Map(BufferAccess access)
{
	GLUTIL_GL_CALL(void* ptr = glMapNamedBuffer(*this, ENUM(access)));
	return ptr;
}

void* Buffer::MapRange(intptr_t offset, intptr_t length, Flags<BufferAccessFlags> accessFlags)
{
	GLUTIL_GL_CALL(void* ptr = glMapNamedBufferRange(*this, offset, length, accessFlags));
	return ptr;
}

void Buffer::Unmap()
{
	GLUTIL_GL_CALL(glUnmapNamedBuffer(*this));
}

void Buffer::Bind(BufferTarget target) const
{
	BindBuffer(target, *this);
}

void Buffer::BindBase(BufferTarget target, uint32_t index) const
{
	BindBufferBase(target, index, *this);
}

void Buffer::BindRange(BufferTarget target, uint32_t index, intptr_t offset, intptr_t size) const
{
	BindBufferRange(target, index, *this, offset, size);
}

void Buffer::GetProp(BufferProp pname, int32_t* value) const
{
	GLUTIL_GL_CALL(glGetNamedBufferParameteriv(*this, ENUM(pname), value));
}

void Buffer::GetProp(BufferProp pname, int64_t* value) const
{
	GLUTIL_GL_CALL(glGetNamedBufferParameteri64v(*this, ENUM(pname), value));
}

void Buffer::GetPointer(BufferPointer pname, void** ptr) const
{
	GLUTIL_GL_CALL(glGetNamedBufferPointerv(*this, ENUM(pname), ptr));
}

int32_t Buffer::GetPropI(BufferProp pname) const
{
	int32_t value = 0;
	GetProp(pname, &value);
	return value;
}

int64_t Buffer::GetPropI64(BufferProp pname) const
{
	int64_t value = 0;
	GetProp(pname, &value);
	return value;
}

void* Buffer::GetPointer(BufferPointer pname) const
{
	void* ptr = nullptr;
	GetPointer(pname, &ptr);
	return ptr;
}

BufferAccess Buffer::GetAccess() const
{
	return static_cast<BufferAccess>(GetPropI(BufferProp::Access));
}

Flags<BufferAccessFlags> Buffer::GetAccessFlags() const
{
	return GetPropI(BufferProp::AccessFlags);
}

bool Buffer::IsImmutableStorage() const
{
	return GetPropI(BufferProp::ImmutableStorage) == GL_TRUE;
}

bool Buffer::IsMapped() const
{
	return GetPropI(BufferProp::Mapped) == GL_TRUE;
}

int64_t Buffer::GetMapLength() const
{
	return GetPropI64(BufferProp::MapLength);
}

int64_t Buffer::GetMapOffset() const
{
	return GetPropI64(BufferProp::MapOffset);
}

int64_t Buffer::GetSize() const
{
	return GetPropI64(BufferProp::Size);
}

Flags<BufferStorageFlags> Buffer::GetStorageFlags() const
{
	return GetPropI(BufferProp::StorageFlags);
}

BufferUsage Buffer::GetUsage() const
{
	return static_cast<BufferUsage>(GetPropI(BufferProp::Usage));
}

void* Buffer::GetMapPointer() const
{
	return GetPointer(BufferPointer::Map);
}

} // namespace GLUtil