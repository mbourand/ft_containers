#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

namespace ft
{
	template<class T>
	class VectorIterator
	{
		public:
			typedef T value_type;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef ptrdiff_t difference_type;

		protected:
			pointer ptr;

		public:
			VectorIterator(pointer ptr = NULL) : ptr(ptr) {}
			VectorIterator(const VectorIterator& other) : ptr(other.ptr) {}
			~VectorIterator() {}

			VectorIterator& operator=(const VectorIterator& other)
			{
				ptr = other.ptr;
				return (*this);
			}

			VectorIterator operator++()
			{
				ptr++;
				return *this;
			}

			VectorIterator operator++(int)
			{
				VectorIterator cpy(*this);
				ptr++;
				return cpy;
			}

			VectorIterator operator--()
			{
				ptr--;
				return *this;
			}

			VectorIterator operator--(int)
			{
				VectorIterator cpy(*this);
				ptr--;
				return cpy;
			}

			VectorIterator operator+(int n) const
			{
				return ptr + n;
			}

			VectorIterator operator-(int n) const
			{
				return ptr - n;
			}

			difference_type operator-(const VectorIterator& other) const
			{
				return ptr - other.ptr;
			}

			VectorIterator operator+=(int n)
			{
				return ptr += n;
			}

			VectorIterator operator-=(int n)
			{
				return ptr -= n;
			}

			bool operator==(const VectorIterator& other)
			{
				return ptr == other.ptr;
			}

			bool operator!=(const VectorIterator& other)
			{
				return ptr != other.ptr;
			}

			bool operator<(const VectorIterator& other)
			{
				return ptr < other.ptr;
			}

			bool operator>(const VectorIterator& other)
			{
				return ptr > other.ptr;
			}

			bool operator<=(const VectorIterator& other)
			{
				return ptr <= other.ptr;
			}

			bool operator>=(const VectorIterator& other)
			{
				return ptr >= other.ptr;
			}

			reference operator*()
			{
				return *ptr;
			}

			const_reference operator*() const
			{
				return *ptr;
			}

			pointer operator->()
			{
				return ptr;
			}

			const_pointer operator->() const
			{
				return ptr;
			}

			reference operator[](size_t n)
			{
				return ptr[n];
			}
	};

	template<class T>
	class ReverseVectorIterator
	{
		public:
			typedef T value_type;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef T& reference;
			typedef const T& const_reference;
			typedef ptrdiff_t difference_type;

		protected:
			pointer ptr;

		public:
			ReverseVectorIterator(pointer ptr = NULL) : ptr(ptr) {}
			ReverseVectorIterator(const ReverseVectorIterator& other) : ptr(other.ptr) {}
			~ReverseVectorIterator() {}

			ReverseVectorIterator& operator=(const ReverseVectorIterator& other)
			{
				ptr = other.ptr;
				return *this;
			}

			ReverseVectorIterator operator++()
			{
				ptr--;
				return *this;
			}

			ReverseVectorIterator operator++(int)
			{
				ReverseVectorIterator cpy(*this);
				ptr--;
				return cpy;
			}

			ReverseVectorIterator operator--()
			{
				ptr++;
				return *this;
			}

			ReverseVectorIterator operator--(int)
			{
				ReverseVectorIterator cpy(*this);
				ptr++;
				return cpy;
			}

			ReverseVectorIterator operator+(int n) const
			{
				return ptr - n;
			}

			ReverseVectorIterator operator-(int n) const
			{
				return ptr + n;
			}

			difference_type operator-(const ReverseVectorIterator& other) const
			{
				return -(ptr - other.ptr);
			}

			ReverseVectorIterator operator+=(int n)
			{
				return ptr -= n;
			}

			ReverseVectorIterator operator-=(int n)
			{
				return ptr += n;
			}

			bool operator==(const ReverseVectorIterator& other)
			{
				return ptr == other.ptr;
			}

			bool operator!=(const ReverseVectorIterator& other)
			{
				return ptr != other.ptr;
			}

			bool operator<(const ReverseVectorIterator& other)
			{
				return ptr < other.ptr;
			}

			bool operator>(const ReverseVectorIterator& other)
			{
				return ptr > other.ptr;
			}

			bool operator<=(const ReverseVectorIterator& other)
			{
				return ptr <= other.ptr;
			}

			bool operator>=(const ReverseVectorIterator& other)
			{
				return ptr >= other.ptr;
			}

			reference operator*()
			{
				return *ptr;
			}

			const_reference operator*() const
			{
				return *ptr;
			}

			pointer operator->()
			{
				return ptr;
			}

			const_pointer operator->() const
			{
				return ptr;
			}

			reference operator[](size_t n)
			{
				return ptr[n];
			}

	};
}

#endif
