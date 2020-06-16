#pragma once

#include "Common.h"
#include "Object.h"

namespace GLUtil {

enum class BufferTarget : uint32_t
{
	Array = 0x8892,
	AtomicCounter = 0x92C0,
	CopyRead = 0x8F36,
	CopyWrite = 0x8F37,
	DispatchIndirect = 0x90EE,
	DrawIndirect = 0x8F3F,
	ElementArray = 0x8893,
	PixelPack = 0x88EB,
	PixelUnpack = 0x88EC,
	Query = 0x9192,
	ShaderStorage = 0x90D2,
	Texture = 0x8C2A,
	TransformFeedback = 0x8C8E,
	Uniform = 0x8A11
};

enum class BufferBinding : uint32_t
{
	Array = 0x8894,
	AtomicCounter = 0x92C1,
	CopyRead = 0x8F36,
	CopyWrite = 0x8F37,
	DispatchIndirect = 0x90EF,
	DrawIndirect = 0x8F43,
	ElementArray = 0x8895,
	PixelPack = 0x88ED,
	PixelUnpack = 0x88EF,
	Query = 0x9193,
	ShaderStorage = 0x90D3,
	Texture = 0x8C2A,
	TransformFeedback = 0x8C8F,
	Uniform = 0x8A28
};

enum class BufferStorageFlags : uint32_t
{
	DynamicStorage = 0x0100,
	MapRead = 0x0001,
	MapWrite = 0x0002,
	MapPersistent = 0x0040,
	MapCoherent = 0x0080,
	ClientStorage = 0x0200
};

enum class BufferUsage : uint32_t
{
	StreamDraw = 0x88E0,
	StreamRead = 0x88E1,
	StreamCopy = 0x88E2,
	StaticDraw = 0x88E4,
	StaticRead = 0x88E5,
	StaticCopy = 0x88E6,
	DynamicDraw = 0x88E8,
	DynamicRead = 0x88E9,
	DynamicCopy = 0x88EA
};

enum class BufferAccess : uint32_t
{
	ReadOnly = 0x88B8,
	WriteOnly = 0x88B9,
	ReadWrite = 0x88BA
};

enum class BufferAccessFlags : uint32_t
{
	Read = 0x0001,
	Write = 0x0002,
	Persistent = 0x0040,
	Coherent = 0x0080,
	InvalidateRange = 0x0004,
	InvalidateBuffer = 0x0008,
	FlushExplicit = 0x0010,
	Unsynchronized = 0x0020
};

enum class BufferParam : uint32_t
{
	Access = 0x88BB,
	AccessFlags = 0x911F,
	ImmutableStorage = 0x821F,
	Mapped = 0x88BC,
	MapLength = 0x9120,
	MapOffset = 0x9121,
	Size = 0x8764,
	StorageFlags = 0x8220,
	Usage = 0x8765

};

enum class BufferPointer : uint32_t
{
	Map = 0x88BD
};

BufferBinding BufferTargetToBinding(BufferTarget target);
BufferTarget BufferBindingToTarget(BufferBinding binding);
uint32_t GetBoundBuffer(BufferBinding binding);
uint32_t GetBoundBuffer(BufferTarget target);

void BindBuffer(BufferTarget target, uint32_t buffer);
void BindBufferBase(BufferTarget target, uint32_t index, uint32_t buffer);
void BindBufferRange(BufferTarget target, uint32_t index, uint32_t buffer, intptr_t offset, intptr_t size);

class BufferBind
{
private:
	BufferTarget mTarget;
	uint32_t mPrev;
public:
	BufferBind() = delete;
	BufferBind(const BufferBind&) = delete;
	BufferBind(BufferBind&&) = delete;
	BufferBind& operator=(const BufferBind&) = delete;
	BufferBind& operator=(BufferBind&&) = delete;

	BufferBind(BufferTarget target, uint32_t buffer);
	~BufferBind();
};

class Buffer : public GLObject
{
public:
	Buffer(const Buffer&) = delete;
	Buffer(Buffer&&) noexcept = default;
	Buffer& operator=(const Buffer&) = delete;
	Buffer& operator=(Buffer&&) noexcept = default;

	Buffer(BufferTarget target = BufferTarget::CopyWrite);
	Buffer(uint32_t buffer);
	Buffer(intptr_t size, const void* data, Flags<BufferStorageFlags> flags, BufferTarget target = BufferTarget::CopyWrite);
	Buffer(intptr_t size, const void* data, BufferUsage usage, BufferTarget target = BufferTarget::CopyWrite);
	virtual ~Buffer();

	Buffer& Storage(intptr_t size, const void* data, Flags<BufferStorageFlags> flags, BufferTarget target = BufferTarget::CopyWrite);
	Buffer& Data(intptr_t size, const void* data, BufferUsage usage, BufferTarget target = BufferTarget::CopyWrite);
	Buffer& SubData(intptr_t offset, intptr_t size, const void* data, BufferTarget target = BufferTarget::CopyWrite);

	void* Map(BufferAccess access, BufferTarget target = BufferTarget::CopyWrite);
	void* MapRange(intptr_t offset, intptr_t length, Flags<BufferAccessFlags> accessFLags, BufferTarget target = BufferTarget::CopyWrite);
	void Unmap(BufferTarget target = BufferTarget::CopyWrite);

	void Bind(BufferTarget target) const;
	void BindBase(BufferTarget target, uint32_t index) const;
	void BindRange(BufferTarget target, uint32_t index, intptr_t offset, intptr_t size) const;

	void GetParam(BufferParam pname, int32_t* value, BufferTarget target = BufferTarget::CopyWrite) const;
	void GetParam(BufferParam pname, int64_t* value, BufferTarget target = BufferTarget::CopyWrite) const;
	void GetPointer(BufferPointer pname, void** ptr, BufferTarget target = BufferTarget::CopyWrite) const;

	int32_t GetParamI(BufferParam pname, BufferTarget target = BufferTarget::CopyWrite) const;
	int64_t GetParamI64(BufferParam pname, BufferTarget target = BufferTarget::CopyWrite) const;
	void* GetPointer(BufferPointer pname, BufferTarget target = BufferTarget::CopyWrite) const;

	BufferAccess GetAccess(BufferTarget target = BufferTarget::CopyWrite) const;
	Flags<BufferAccessFlags> GetAccessFlags(BufferTarget target = BufferTarget::CopyWrite) const;
	bool IsImmutableStorage(BufferTarget target = BufferTarget::CopyWrite) const;
	bool IsMapped(BufferTarget target = BufferTarget::CopyWrite) const;
	int64_t GetMapLength(BufferTarget target = BufferTarget::CopyWrite) const;
	int64_t GetMapOffset(BufferTarget target = BufferTarget::CopyWrite) const;
	int64_t GetSize(BufferTarget target = BufferTarget::CopyWrite) const;
	Flags<BufferStorageFlags> GetStorageFlags(BufferTarget target = BufferTarget::CopyWrite) const;
	BufferUsage GetUsage(BufferTarget target = BufferTarget::CopyWrite) const;
	void* GetMapPointer(BufferTarget target = BufferTarget::CopyWrite) const;
};

namespace DSA {

class Buffer : public GLObject
{
public:
	Buffer(const Buffer&) = delete;
	Buffer(Buffer&&) noexcept = default;
	Buffer& operator=(const Buffer&) = delete;
	Buffer& operator=(Buffer&&) noexcept = default;

	Buffer();
	Buffer(uint32_t buffer);
	Buffer(intptr_t size, const void* data, Flags<BufferStorageFlags> flags);
	Buffer(intptr_t size, const void* data, BufferUsage usage);
	virtual ~Buffer();

	Buffer& Storage(intptr_t size, const void* data, Flags<BufferStorageFlags> flags);
	Buffer& Data(intptr_t size, const void* data, BufferUsage usage);
	Buffer& SubData(intptr_t offset, intptr_t size, const void* data);

	void* Map(BufferAccess access);
	void* MapRange(intptr_t offset, intptr_t length, Flags<BufferAccessFlags> accessFLags);
	void Unmap();

	void Bind(BufferTarget target) const;
	void BindBase(BufferTarget target, uint32_t index) const;
	void BindRange(BufferTarget target, uint32_t index, intptr_t offset, intptr_t size) const;

	void GetParam(BufferParam pname, int32_t* value) const;
	void GetParam(BufferParam pname, int64_t* value) const;
	void GetPointer(BufferPointer pname, void** ptr) const;

	int32_t GetParamI(BufferParam pname) const;
	int64_t GetParamI64(BufferParam pname) const;
	void* GetPointer(BufferPointer pname) const;

	BufferAccess GetAccess() const;
	Flags<BufferAccessFlags> GetAccessFlags() const;
	bool IsImmutableStorage() const;
	bool IsMapped() const;
	int64_t GetMapLength() const;
	int64_t GetMapOffset() const;
	int64_t GetSize() const;
	Flags<BufferStorageFlags> GetStorageFlags() const;
	BufferUsage GetUsage() const;
	void* GetMapPointer() const;
};

} // namespace DSA

} // namespace GLUtil