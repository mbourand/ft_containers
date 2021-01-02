#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include "Node.hpp"
#include <stddef.h>

namespace ft
{
	template<class T>
	class ListIterator
	{
		public:
			typedef T value_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef ptrdiff_t difference_type;

		protected:
			Node<value_type>* node;

		public:
			ListIterator() : node(NULL) {}
			ListIterator(const ListIterator& other) : node(other.node) {}
			ListIterator(Node<value_type>* node) : node(node) {}
			~ListIterator() {}
			ListIterator& operator=(const ListIterator& other)
			{
				node = other.node;
				return *this;
			}

			bool operator==(const ListIterator& other) const
			{ return node == other.node; }

			bool operator!=(const ListIterator& other) const
			{ return node != other.node; }

			reference operator*() const
			{ return node->val; }

			ListIterator operator++()
			{
				node = node->next;
				return *this;
			}

			ListIterator operator++(int)
			{
				ListIterator cpy(*this);
				node = node->next;
				return cpy;
			}

			ListIterator operator--()
			{
				node = node->prev;
				return *this;
			}

			ListIterator operator--(int)
			{
				ListIterator cpy(*this);
				node = node->prev;
				return cpy;
			}
	};

	template<class T>
	class ReverseListIterator
	{
		public:
			typedef T value_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef ptrdiff_t difference_type;

		protected:
			Node<T>* node;

		public:
			ReverseListIterator() : node(NULL) {}
			ReverseListIterator(const ReverseListIterator& other) : node(other.node) {}
			ReverseListIterator(Node<value_type>* node) : node(node) {}
			~ReverseListIterator() {}
			ReverseListIterator& operator=(const ReverseListIterator& other)
			{
				node = other.node;
				return *this;
			}

			bool operator==(const ReverseListIterator& other) const
			{ return node == other.node; }

			bool operator!=(const ReverseListIterator& other) const
			{ return node != other.node; }

			reference operator*() const
			{ return node->val; }

			ReverseListIterator operator++()
			{
				node = node->prev;
				return *this;
			}

			ReverseListIterator operator++(int)
			{
				ReverseListIterator cpy(*this);
				node = node->prev;
				return cpy;
			}

			ReverseListIterator operator--()
			{
				node = node->next;
				return *this;
			}

			ReverseListIterator operator--(int)
			{
				ReverseListIterator cpy(*this);
				node = node->next;
				return cpy;
			}
	};
}

#endif
