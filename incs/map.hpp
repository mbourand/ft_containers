#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "list.hpp"
#include <memory>
#include <stddef.h>
#include <limits>
#include <functional>

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef typename ft::list<value_type>::iterator iterator;
			typedef typename ft::list<value_type>::const_iterator const_iterator;
			typedef typename ft::list<value_type>::reverse_iterator reverse_iterator;
			typedef typename ft::list<value_type>::const_reverse_iterator const_reverse_iterator;

		private:
			ft::list<value_type> _elements;
			key_compare _compare;
			allocator_type _alloc;

			template<class Type>
			void swap_type(Type& t, Type& t2) const
			{
				Type t3 = t2;
				t2 = t;
				t = t3;
			}

		public:
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = Allocator())
			{
				_compare = comp;
				_alloc = alloc;
			}

			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = Allocator())
			{
				_compare = comp;
				_alloc = alloc;
				insert(first, last);
			}

			map(const map& x) : _elements(x._elements), _compare(x._compare), _alloc(x._alloc) {}

			iterator begin() { return _elements.begin(); }
			const_iterator begin() const { return _elements.begin(); }
			iterator end() { return _elements.end(); }
			const_iterator end() const { return _elements.end(); }
			reverse_iterator rbegin() { return _elements.rbegin(); }
			const_reverse_iterator rbegin() const { return _elements.rbegin(); }
			reverse_iterator rend() { return _elements.rend(); }
			const_reverse_iterator rend() const { return _elements.rend(); }

			bool empty() const { return _elements.empty(); }
			size_type size() const { return _elements.size(); }
			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

			void clear() { _elements.clear(); }

			ft::pair<iterator, bool> insert(const value_type& value)
			{
				iterator at;
				if ((at = find(value.first)) != end())
					return ft::pair<iterator, bool>(at, false);
				if (empty())
				{
					_elements.push_back(value);
					return ft::pair<iterator, bool>(begin(), true);
				}
				for (iterator it = begin(); it != end(); it++)
				{
					if (!_compare(it->first, value.first))
					{
						at = _elements.insert(it, value);
						break;
					}
				}
				if (at == end())
				{
					_elements.push_back(value);
					at = --end();
				}
				return ft::pair<iterator, bool>(at, true);
			}

			iterator insert(iterator position, const value_type& val)
			{
				iterator at;
				if ((at = find(val.first)) != end())
					return at;
				if (empty())
					return _elements.insert(begin(), val);
				if (position == end())
					position--;
				bool comp = _compare(position->first, val.first);
				if (!comp)
				{
					for (iterator it = position; it != begin(); it--)
						if (_compare(it->first, val.first) != comp)
							return _elements.insert(++it, val);
					if (_compare(begin()->first, val.first) != comp)
						return _elements.insert(++begin(), val);
					return _elements.insert(begin(), val);
				}
				for (iterator it = position; it != end(); it++)
					if (_compare(it->first, val.first) != comp)
						return _elements.insert(it, val);
				return _elements.insert(end(), val);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			}

			~map() {}

			map& operator=(const map& other)
			{
				_elements = other._elements;
				_compare = other._compare;
				_alloc = other._alloc;
				return *this;
			}

			void swap(map& x)
			{
				swap_type(_elements, x._elements);
				swap_type(_compare, x._compare);
			}

			mapped_type& operator[](const key_type& k)
			{
				return insert(ft::make_pair(k, mapped_type())).first->second;
			}

			iterator find(const key_type& k)
			{
				if (empty())
					return end();
				for (iterator it = begin(); it != end(); it++)
					if (!_compare(k, it->first) && !_compare(it->first, k))
						return it;
				return end();
			}

			const_iterator find(const key_type& k) const
			{
				if (empty())
					return end();
				for (const_iterator it = begin(); it != end(); it++)
					if (!_compare(k, it->first) && !_compare(it->first, k))
						return it;
				return end();
			}

			size_type count(const key_type& k) const
			{
				return find(k) == end() ? 0 : 1;
			}

			iterator lower_bound(const key_type& k)
			{
				if (empty())
					return begin();
				for (iterator it = begin(); it != end(); it++)
					if (!_compare(it->first, k))
						return it;
				return end();
			}

			const_iterator lower_bound(const key_type& k) const
			{
				if (empty())
					return begin();
				for (const_iterator it = begin(); it != end(); it++)
					if (!_compare(it->first, k))
						return it;
				return end();
			}

			iterator upper_bound(const key_type& k)
			{
				if (empty())
					return begin();
				for (iterator it = begin(); it != end(); it++)
					if (_compare(k, it->first))
						return it;
				return end();
			}

			const_iterator upper_bound(const key_type& k) const
			{
				if (empty())
					return begin();
				for (const_iterator it = begin(); it != end(); it++)
					if (_compare(k, it->first))
						return it;
				return end();
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			ft::pair<iterator, iterator> equal_range(const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			key_compare key_comp() const
			{
				return _compare;
			}

			value_compare value_comp() const
			{
				return value_compare(_compare);
			}

			void erase(iterator position)
			{
				_elements.erase(position);
			}

			size_type erase(const key_type& k)
			{
				iterator position = find(k);
				if (position == end())
					return 0;
				_elements.erase(position);
				return 1;
			}

			void erase(iterator first, iterator last)
			{
				for (; first != last; first++)
					erase(first);
			}

			bool operator==(const ft::map<key_type, mapped_type>& map) const
			{
				return _elements == map._elements;
			}

			bool operator>(const ft::map<key_type, mapped_type>& map) const
			{
				return _elements > map._elements;
			}

			bool operator<(const ft::map<key_type, mapped_type>& map) const
			{
				return _elements < map._elements;
			}

			bool operator>=(const ft::map<key_type, mapped_type>& map) const
			{
				return !(*this < map);
			}

			bool operator<=(const ft::map<key_type, mapped_type>& map) const
			{
				return !(map < *this);
			}

			bool operator!=(const ft::map<key_type, mapped_type>& map) const
			{
				return !(*this == map);
			}
	};

}

#endif
