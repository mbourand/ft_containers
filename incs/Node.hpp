#ifndef NODE_HPP
#define NODE_HPP

namespace ft
{
	template<typename T>
	struct Node
	{
		Node<T>* prev;
		Node<T>* next;
		T val;

		Node(const T& val = T(), Node<T>* prev = NULL, Node<T>* next = NULL) : prev(prev), next(next), val(val) {}
		Node(const Node<T>& other) { *this = other; }
		~Node() {}
		Node& operator=(const Node<T>& other)
		{
			prev = other.prev;
			next = other.next;
			val = other.val;
			return *this;
		}
	};
}

#endif
