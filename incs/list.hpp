#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <stddef.h>
#include "ListIterator.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class list
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::reference const_reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;
			typedef ListIterator<T> iterator;
			typedef ListIterator<const T> const_iterator;
			typedef ReverseListIterator<T> reverse_iterator;
			typedef ReverseListIterator<const T> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		protected:
			Node<value_type>* _elements;
			Node<value_type>* _back;
			size_type _size;

		public:
			explicit list(const allocator_type& alloc = allocator_type()) : _elements(NULL), _back(NULL) { (void)alloc; }

			explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				(void)alloc;
				_elements = NULL;
				_back = NULL;
				_size = 0;
				if (n == 0)
					return;
				for (size_type i = 1; i < n; i++)
					push_back(val);
			}

			template<class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			{
				(void)alloc;
				_elements = NULL;
				_back = NULL;
				_size = 0;
				for (; first != last; first++)
					push_back(*first);
			}

			list(const list& x)
			{
				const_iterator first = x.begin();
				const_iterator last = x.end();

				_elements = NULL;
				_back = NULL;
				_size = 0;
				for (; first != last; first++)
					push_back(*first);
			}

			iterator begin() { return iterator(_elements); }
			iterator end() { return iterator(_back->next); }
			const_iterator begin() const { return const_iterator(_elements); }
			const_iterator end() const { return const_iterator(_back->next); }
			reverse_iterator rbegin() { return reverse_iterator(_back); }
			reverse_iterator rend() { return reverse_iterator(_elements->prev); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_back); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_elements->prev); }

			reference front() { return _elements->val; }
			const_reference front() const { return _elements->val; }
			reference back() { return _back->val; }
			const_reference back() const { return _back->val; }

			void push_back(const value_type& val)
			{
				if (!_elements)
				{
					_elements = new Node<T>(val);
					_back = _elements;
					return;
				}
				_back->next = new Node<T>(val);
				_back = _back->next;
				_size++;
			}

			size_type size() const
			{
				return _size;
			}

	};
}

#endif
