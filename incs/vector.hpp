#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <cstddef>
#include "VectorIterator.hpp"
#include <stdexcept>
#include <memory>
#include <limits>
#include <iostream>

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef ft::VectorIterator<T> iterator;
			typedef ft::ReverseVectorIterator<T> reverse_iterator;
			typedef ft::VectorIterator<const T> const_iterator;
			typedef ft::ReverseVectorIterator<const T> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		protected:
			allocator_type _allocator;
			pointer _elements;
			size_type _size;
			size_type _capacity;

		private:
			size_type get_new_capacity(size_type req)
			{
				size_type cap = 1;
				while (cap < req)
					cap = (cap << 1);
				return cap;
			}

			void realloc_vector(size_type new_capacity)
			{
				pointer new_arr = _allocator.allocate(new_capacity);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(&new_arr[i], _elements[i]);
					_allocator.destroy(&_elements[i]);
				}
				if (_capacity != 0)
					_allocator.deallocate(_elements, _capacity);
				_elements = new_arr;
				_capacity = new_capacity;
			}

			template<class Type>
			void swap_type(Type& t, Type& t2) const
			{
				Type t3 = t2;
				t2 = t;
				t = t3;
			}

		public:
			explicit vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _elements(NULL), _size(0), _capacity(0)
			{}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _allocator(alloc), _elements(NULL), _size(0), _capacity(0)
			{
				_elements = _allocator.allocate(n);
				_capacity = n;
				_size = n;
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_elements + i, val);
			}

			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc), _elements(NULL), _size(0), _capacity(0)
			{
				for (; first != last; first++)
					push_back(*first);
			}

			vector(const vector& other) : _allocator(other._allocator), _elements(NULL), _size(other._size), _capacity(other._capacity)
			{
				_elements = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _capacity; i++)
					_allocator.construct(&_elements[i], other._elements[i]);
			}

			vector& operator=(const vector& other)
			{
				_allocator.deallocate(_elements, _capacity);
				_size = other._size;
				_capacity = other._capacity;
				_allocator = other._allocator;
				_elements = NULL;
				_elements = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(&_elements[i], other._elements[i]);
				return *this;
			}

			void push_back(const value_type& val)
			{
				reserve(_size + 1);
				_allocator.construct(&_elements[_size++], val);
			}

			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(&_elements[i]);
				_allocator.deallocate(_elements, _capacity);
			}

			const_reference operator[](size_type i) const
			{
				return _elements[i];
			}

			reference operator[](size_type i)
			{
				return _elements[i];
			}

			reference at(size_type i)
			{
				if (i >= _size)
					throw std::out_of_range("index is out of vector range");
				return _elements[i];
			}

			const_reference at(size_type i) const
			{
				if (i >= _size)
					throw std::out_of_range("index is out of vector range");
				return _elements[i];
			}

			reference front()
			{
				return _elements[0];
			}

			const_reference front() const
			{
				return _elements[0];
			}

			reference back()
			{
				return _elements[_size - 1];
			}

			const_reference back() const
			{
				return _elements[_size - 1];
			}

			iterator begin()
			{
				return iterator(_elements);
			}

			const_iterator begin() const
			{
				return const_iterator(_elements);
			}

			const_iterator end() const
			{
				return const_iterator(_elements + _size);
			}

			iterator end()
			{
				return iterator(_elements + _size);
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(_elements + _size - 1);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(_elements + _size - 1);
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(_elements - 1);
			}

			reverse_iterator rend()
			{
				return reverse_iterator(_elements - 1);
			}

			size_type size() const
			{
				return _size;
			}

			size_type max_size() const
			{
				return std::numeric_limits<size_type>::max() / (sizeof(vector<value_type>) - sizeof(pointer));
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
					erase(begin() + n, end());
				else if (n > _size)
				{
					reserve(n);
					insert(begin() + _size, n - _size, val);
				}
			}

			void clear()
			{
				if (!empty())
					erase(begin(), end());
			}

			void pop_back()
			{
				_size--;
				_allocator.destroy(_elements + _size);
			}

			iterator insert(iterator position, const value_type& val)
			{
				difference_type gap = position - begin();
				insert(position, (size_type)1, (const value_type&)val);
				return &_elements[(size_type)gap];
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				difference_type gap = position - begin();
				reserve(_size + n);
				if (empty())
				{
					for (size_type i = 0; i < n; i++)
						_allocator.construct(_elements + i, val);
					_size += n;
					return;
				}

				for (size_type i2 = _size; i2 > (size_type)gap; i2--)
				{
					size_type i = i2 - 1;
					if (i + n >= _size)
						_allocator.construct(_elements + i + n, _elements[i]);
					else
						_elements[i + n] = _elements[i];
				}
				for (size_type i = (size_type)gap; i < n + gap; i++)
				{
					if (i >= _size)
						_allocator.construct(_elements + i, val);
					else
						_elements[i] = val;
				}
				_size += n;
			}

			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last)
			{
				difference_type gap = position - begin();
				for (; first != last; first++)
				{
					insert(begin() + gap, *first);
					gap++;
				}
			}

			iterator erase(iterator position)
			{
				if (empty())
					return position;
				iterator cpy = position;

				difference_type gap = position - begin();
				for (difference_type i = gap; i < (difference_type)_size - 1; i++)
					_elements[i] = _elements[i + 1];
				_allocator.destroy(_elements + _size - 1);
				_size--;
				return cpy;
			}

			iterator erase(iterator first, iterator last)
			{
				if (empty())
					return last;
				iterator ret = first;
				while (first != last--)
					ret = erase(first);
				return ret;
			}

			template<class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				clear();
				for (; first != last; first++)
					push_back(*first);
			}

			void assign(size_type n, const value_type& val)
			{
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			size_type capacity() const
			{
				return _capacity;
			}

			bool empty() const
			{
				return _size == 0;
			}

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("requested size is greater than max_size.");
				if (n <= _capacity)
					return;
				realloc_vector(get_new_capacity(n));
			}

			void swap(vector& x)
			{
				swap_type(x._capacity, _capacity);
				swap_type(x._size, _size);
				swap_type(x._elements, _elements);
				swap_type(x._allocator, _allocator);
			}
	};

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
		typename vector<T, Alloc>::const_iterator it2 = rhs.begin();

		for (; it1 != lhs.end() && it2 != rhs.end(); it1++, it2++)
		{
			if (*it1 < *it2) return true;
			if (*it2 < *it1) return false;
		}
		return it1 == lhs.end() && it2 != rhs.end();
	}

	template<class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}
}

#endif
