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
			typedef ft::pair<const Key, T> value_type;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef Allocator::reference reference;
			typedef Allocator::const_reference const_reference;
			typedef Allocator::pointer pointer;
			typedef Allocator::const_pointer pointer;

		private:
			ft::list<value_type> _elements;

		public:
			map();
			map(const map& other);
			virtual ~map();
			map& operator=(const map& other);
	};
}

#endif
