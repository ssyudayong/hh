///
/// @brief	memory_pool类是从github上面cacay的MemoryPool类修改而来。
///			源地址为：https://github.com/cacay/MemoryPool
///			
///

#pragma once

#include <climits>
#include <cstddef>


namespace hh
{
	template <typename T, size_t BlockSize = 4096>
	class memory_pool
	{
	public:
		/* Member types */
		typedef T               value_type;
		typedef T*              pointer;
		typedef T&              reference;
		typedef const T*        const_pointer;
		typedef const T&        const_reference;
		typedef size_t          size_type;
		typedef ptrdiff_t       difference_type;
		typedef std::false_type propagate_on_container_copy_assignment;
		typedef std::true_type  propagate_on_container_move_assignment;
		typedef std::true_type  propagate_on_container_swap;

		template <typename U> struct rebind {
			typedef memory_pool<U> other;
		};
	public:
		/* Member functions */
		memory_pool() noexcept;
		memory_pool(const memory_pool& memoryPool) noexcept;
		memory_pool(memory_pool&& memoryPool) noexcept;
		template <class U> memory_pool(const memory_pool<U>& memoryPool) noexcept;

		virtual ~memory_pool() noexcept;

		memory_pool& operator=(const memory_pool& memoryPool) = delete;
		memory_pool& operator=(memory_pool&& memoryPool) noexcept;

		pointer address(reference x) const noexcept;
		const_pointer address(const_reference x) const noexcept;

		// Can only allocate one object at a time. n and hint are ignored
		pointer allocate(size_type n = 1, const_pointer hint = 0);
		void deallocate(pointer p, size_type n = 1);

		size_type max_size() const noexcept;

		template <class U, class... Args> void construct(U* p, Args&&... args);
		template <class U> void destroy(U* p);

		template <class... Args> pointer newElement(Args&&... args);
		void deleteElement(pointer p);

	private:
		union Slot_ {
			value_type element;
			Slot_* next;
		};

		typedef char* data_pointer_;
		typedef Slot_ slot_type_;
		typedef Slot_* slot_pointer_;

		slot_pointer_ currentBlock_;
		slot_pointer_ currentSlot_;
		slot_pointer_ lastSlot_;
		slot_pointer_ freeSlots_;

		size_type padPointer(data_pointer_ p, size_type align) const noexcept;
		void allocateBlock();

		static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
	};

}

#include "memory_pool.ipp"
