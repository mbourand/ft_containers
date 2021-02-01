#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <stddef.h>
#include <limits>
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
			typedef ConstListIterator<T> const_iterator;
			typedef ReverseListIterator<T> reverse_iterator;
			typedef ReverseConstListIterator<T> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		protected:
			Node<value_type>* _elements;
			Node<value_type>* _back;
			Node<value_type>* _end;
			Node<value_type>* _rend;
			size_type _size;
			allocator_type _alloc;

		public:
			explicit list(const allocator_type& alloc = allocator_type())
				: _elements(NULL), _back(NULL), _end(new Node<T>(T(), _back)), _rend(new Node<T>(T(), NULL, _elements)), _size(0), _alloc(alloc)
			{}

			explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _elements(NULL), _back(NULL), _end(new Node<T>(T(), _back)), _rend(new Node<T>(T(), NULL, _elements)), _size(0), _alloc(alloc)
			{
				if (n == 0)
					return;
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			template<class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_elements = NULL;
				_back = NULL;
				_size = 0;
				_end = new Node<T>(T(), _back);
				_rend = new Node<T>(T(), NULL, _elements);
				for (; first != last; first++)
					push_back(*first);
			}

			list(const list& x)
			{
				const_iterator first = x.begin();
				const_iterator last = x.end();

				_alloc = x._alloc;
				_elements = NULL;
				_back = NULL;
				_size = 0;
				_end = new Node<T>(T(), _back);
				_rend = new Node<T>(T(), NULL, _elements);
				for (; first != last; first++)
					push_back(*first);
			}

			list& operator= (const list& x)
			{
				if (!empty())
				{
					for (Node<value_type>* node = _elements; node != _end;)
					{
						Node<value_type>* tmp = node;
						node = node->next;
						delete tmp;
					}
				}
				delete _end;
				delete _rend;

				const_iterator first = x.begin();
				const_iterator last = x.end();

				_elements = NULL;
				_back = NULL;
				_size = 0;
				_end = new Node<T>(T(), _back);
				_rend = new Node<T>(T(), NULL, _elements);
				_alloc = x._alloc;
				for (; first != last; first++)
					push_back(*first);
				return *this;
			}

			~list()
			{
				if (!empty())
				{
					for (Node<value_type>* node = _elements; node != _end;)
					{
						Node<value_type>* tmp = node;
						node = node->next;
						delete tmp;
					}
				}
				delete _end;
				delete _rend;
			}

			iterator begin() { return !empty() ? iterator(_elements) : iterator(_end); }
			iterator end() { return iterator(_end); }
			const_iterator begin() const { return !empty() ? const_iterator(_elements) : const_iterator(_end); }
			const_iterator end() const { return const_iterator(_end); }
			reverse_iterator rbegin() { return !empty() ? reverse_iterator(_back) : reverse_iterator(_rend); }
			reverse_iterator rend() { return reverse_iterator(_rend); }
			const_reverse_iterator rbegin() const { return !empty() ? const_reverse_iterator(_back) : const_reverse_iterator(_rend); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_rend); }

			reference front() { return _elements->val; }
			const_reference front() const { return _elements->val; }
			reference back() { return _back->val; }
			const_reference back() const { return _back->val; }

			void push_back(const value_type& val)
			{
				if (!_elements)
				{
					_elements = new Node<value_type>(val);
					_elements->next = NULL;
					_elements->prev = NULL;
					_back = _elements;
					_size = 1;
					update_end();
					return;
				}
				Node<value_type>* tmp = new Node<value_type>(val);
				tmp->next = NULL;
				tmp->prev = _back;
				tmp->prev->next = tmp;
				_back = tmp;
				_size++;
				update_end();
			}

			void push_front(const value_type& val)
			{
				if (!_elements)
				{
					push_back(val);
					return;
				}
				Node<value_type>* elem = new Node<value_type>(val);
				elem->next = _elements;
				_elements->prev = elem;
				_elements = elem;
				_size++;
				update_end();
			}

			iterator insert(iterator pos, const T& value)
			{
				if (pos == begin())
				{
					push_front(value);
					return begin();
				}
				if (pos == end())
				{
					push_back(value);
					return iterator(rbegin().getNode());
				}

				Node<value_type>* pos_node = pos.getNode();

				Node<value_type>* prev = pos_node->prev;
				Node<value_type>* new_elem = new Node<value_type>(value, prev, pos_node);

				prev->next = new_elem;
				pos_node->prev = new_elem;
				_size++;
				update_end();
				return iterator(new_elem);
			}

			template<class InputIt>
			void insert(iterator pos, InputIt first, InputIt last)
			{
				for (; first != last; first++)
				{
					pos = insert(pos, *first);
					pos++;
				}
			}

			void insert(iterator pos, size_type count, const T& value)
			{
				for (size_type i = 0; i < count; i++)
					insert(pos, value);
			}

			iterator erase(iterator pos)
			{
				if (pos == begin())
				{
					pop_front();
					return begin();
				}
				if (pos == --end())
				{
					pop_back();
					return end();
				}

				Node<T>* node = pos.getNode();
				pos++;
				node->prev->next = node->next;
				node->next->prev = node->prev;
				_size--;
				delete node;
				return pos;
			}

			iterator erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
				return last;
			}

			size_type size() const
			{
				return _size;
			}

			bool empty() const
			{
				return _size == 0;
			}

			size_type max_size() const
			{
				return size_type(-1) / sizeof(Node<value_type>);
			}

			void pop_front()
			{
				if (empty())
					return;
				Node<value_type>* tmp = _elements;
				_elements = _elements->next;
				if (_size == 1)
				{
					_elements = NULL;
					_back = NULL;
				}
				_size--;
				update_end();
				delete tmp;
			}

			void clear()
			{
				while (!empty())
					pop_back();
			}

			void pop_back()
			{
				if (empty())
					return;
				Node<value_type>* tmp = _back;
				_back = _back->prev;
				if (_size == 1)
				{
					_back = NULL;
					_elements = NULL;
				}
				_size--;
				update_end();
				delete tmp;
			}

			void sort()
			{
				sort(is_less());
			}

			template<class Compare>
			void sort(Compare comp)
			{
				if (_size < 2)
					return;
				for (size_t i = 0; i < _size - 1; i++)
				{
					bool sorted = true;
					iterator it = begin();
					iterator it_next = begin();
					it_next++;
					for (size_t j = 0; j < _size - i - 1; j++)
					{
						if (!comp(*it, *it_next))
						{
							value_type tmp = *it;
							*it = *it_next;
							*it_next = tmp;
							sorted = false;
						}
						it++;
						it_next++;
					}
					if (sorted)
						return;
				}
			}

			void swap(list& other)
			{
				swap(_size, other._size);
				swap(_elements, other._elements);
				swap(_back, other._back);
				swap(_end, other._end);
				swap(_rend, other._rend);
			}

			void resize(size_type count, T value = T())
			{
				if (count < _size)
				{
					while (count < _size)
						pop_back();
				}
				else if (count > _size)
				{
					while (count > _size)
						push_back(value);
				}
			}

			void assign(size_type count, const T& value)
			{
				clear();
				insert(begin(), count, value);
			}

			template<class InputIt>
			void assign(InputIt first, InputIt last)
			{
				clear();
				insert(begin(), first, last);
			}

			void splice(iterator position, list& x)
			{
				insert(position, x.begin(), x.end());
				x.clear();
			}

			void splice(iterator position, list& x, iterator i)
			{
				insert(position, *i);
				x.erase(i);
			}

			void splice(iterator position, list& x, iterator first, iterator last)
			{
				insert(position, first, last);
				x.erase(first, last);
			}

			void remove(const value_type& val)
			{
				for (iterator it = begin(); it != end(); )
				{
					if (*it == val)
						erase(it++);
					else
						it++;
				}
			}

			template<class Predicate>
			void remove_if(Predicate pred)
			{
				for (iterator it = begin(); it != end(); )
				{
					if (pred(*it))
						erase(it++);
					else
						it++;
				}
			}

			void unique()
			{
				if (size() < 2)
					return;
				iterator last = begin();

				for (iterator it = ++begin(); it != end();)
				{
					if (*it == *last)
					{
						erase(it++);
						continue;
					}
					last = it++;
				}
			}

			template<class BinaryPredicate>
			void unique(BinaryPredicate binary_pred)
			{
				if (size() < 2)
					return;
				iterator last = begin();

				for (iterator it = ++begin(); it != end();)
				{
					if (binary_pred(*last, *it))
					{
						erase(it++);
						continue;
					}
					last = it++;
				}
			}

			void merge(list& x)
			{
				merge(x, is_less());
			}

			template<class Compare>
			void merge(list& x, Compare compare)
			{
				if (&x == this || x.empty())
					return;
				insert(begin(), x.begin(), x.end());
				x.clear();
				sort(compare);
			}

			void reverse()
			{
				for (iterator it = begin(); it != end(); it--)
					swap(it.getNode()->next, it.getNode()->prev);
				swap(_back, _elements);
				update_end();
			}

			private:
				class is_less
				{
					public:
						bool operator()(const value_type& a, const value_type& b)
						{
							return a < b;
						}
				};

				void update_end()
				{
					_end->prev = _back;
					if (_back)
						_back->next = _end;
					if (_elements)
						_elements->prev = _rend;
					_rend->next = _elements;
					_rend->prev = _back;
				}

				template<class Type>
				void swap(Type& t1, Type& t2)
				{
					Type tmp = t2;
					t2 = t1;
					t1 = tmp;
				}
	};

	template< class T, class Alloc >
	bool operator==(const list<T,Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (typename list<T, Alloc>::iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end() && it2 != rhs.end(); it++, it2++)
			if (*it != *it2)
				return false;
		return true;
	}

	template<class T, class Alloc>
	bool operator!=(const list<T,Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		typename list<T, Alloc>::const_iterator it1 = lhs.begin();
		typename list<T, Alloc>::const_iterator it2 = rhs.begin();

		for (; it1 != lhs.end() && it2 != rhs.end(); it1++, it2++)
		{
			if (*it1 < *it2) return true;
			if (*it2 < *it1) return false;
		}
		return it1 == lhs.end() && it2 != rhs.end();
	}

	template<class T, class Alloc>
	bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class T, class Alloc>
	bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template<class T, class Alloc>
	void swap(list<T,Alloc>& lhs, list<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
