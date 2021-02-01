#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

namespace ft
{
	template<class T> class VectorIterator;
	template<class T> class ReverseVectorIterator;
	template<class T> class ConstVectorIterator;
	template<class T> class ReverseConstVectorIterator;

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

			operator ConstVectorIterator<T>() const { return ConstVectorIterator<T>(ptr); }
			operator VectorIterator<T>() const { return VectorIterator<T>(ptr); }
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

			operator ReverseConstVectorIterator<T>() const { return ReverseConstVectorIterator<T>(ptr); }
			operator VectorIterator<T>() const { return VectorIterator<T>(ptr); }
	};

	template<class T>
	class ReverseConstVectorIterator : public ReverseVectorIterator<T>
	{
		public:
			typedef T const & reference;
			typedef T const * pointer;

			ReverseConstVectorIterator(T* ptr)
			{
				this->ptr = ptr;
			}

			ReverseConstVectorIterator& operator=(const ReverseConstVectorIterator& other)
			{
				this->ptr = other.ptr;
				return *this;
			}

			ReverseConstVectorIterator operator++()
			{
				this->ptr--;
				return *this;
			}

			ReverseConstVectorIterator operator++(int)
			{
				ReverseConstVectorIterator cpy(*this);
				this->ptr--;
				return cpy;
			}

			ReverseConstVectorIterator operator--()
			{
				this->ptr++;
				return *this;
			}

			ReverseConstVectorIterator operator--(int)
			{
				ReverseConstVectorIterator cpy(*this);
				this->ptr++;
				return cpy;
			}

			ReverseConstVectorIterator operator+(int n) const
			{
				return this->ptr - n;
			}

			ReverseConstVectorIterator operator-(int n) const
			{
				return this->ptr + n;
			}

			ReverseConstVectorIterator operator+=(int n)
			{
				return this->ptr -= n;
			}

			ReverseConstVectorIterator operator-=(int n)
			{
				return this->ptr += n;
			}

			reference operator*() const
			{ return *(this->ptr); }

			pointer operator->() const
			{ return this->ptr; }

			operator ConstVectorIterator<T>() const { return ConstVectorIterator<T>(this->ptr); }
	};

	template<class T>
	class ConstVectorIterator : public VectorIterator<T>
	{
		public:
			typedef T const & reference;
			typedef T const * pointer;

			ConstVectorIterator(T* ptr)
			{
				this->ptr = ptr;
			}

			reference operator*() const
			{ return *(this->ptr); }

			pointer operator->() const
			{ return this->ptr; }

			ConstVectorIterator& operator=(const ConstVectorIterator& other)
			{
				this->ptr = other.ptr;
				return (*this);
			}

			ConstVectorIterator operator++()
			{
				this->ptr++;
				return *this;
			}

			ConstVectorIterator operator++(int)
			{
				ConstVectorIterator cpy(*this);
				this->ptr++;
				return cpy;
			}

			ConstVectorIterator operator--()
			{
				this->ptr--;
				return *this;
			}

			ConstVectorIterator operator--(int)
			{
				ConstVectorIterator cpy(*this);
				this->ptr--;
				return cpy;
			}

			ConstVectorIterator operator+(int n) const
			{
				return this->ptr + n;
			}

			ConstVectorIterator operator-(int n) const
			{
				return this->ptr - n;
			}

			ConstVectorIterator operator+=(int n)
			{
				return this->ptr += n;
			}

			ConstVectorIterator operator-=(int n)
			{
				return this->ptr -= n;
			}

			operator ReverseConstVectorIterator<T>() const { return ReverseConstVectorIterator<T>(this->ptr); }
	};
}

#endif
