/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:45:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/09/22 03:33:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "utils.hpp"

#include <functional>
#include <memory>
#include <stdexcept>

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = less< Key >,
		class Alloc = std::allocator< ft::pair< const Key, T > > //! cannot use this to allocate nodes because
	>
	class map
	{
		private:
		struct node_type;
		class map_iterator;

		public:
		/** The first template parameter */
		typedef Key key_type;
		/** The second template parameter */
		typedef T mapped_type;
		typedef ft::pair< key_type const, mapped_type > value_type;
		typedef Compare key_compare;
		typedef void *value_compare; // TODO
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef map_iterator iterator;
		typedef map_iterator const const_iterator;
		typedef ft::reverse_iterator< iterator > reverse_iterator;
		typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
		typedef typename ft::iterator_traits< iterator >::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		private:
		struct node_type
		{
			public:
			node_type* parent;
			node_type* left;
			node_type* right;
			value_type value;
			int height;

			public:
			node_type(node_type* parent, T const& value) :
				parent(parent),
				left(NULL),
				right(NULL),
				value(value),
				height(1)
			{
			}
		}; // struct node_type

		class map_iterator : public ft::iterator< ft::bidirectional_iterator_tag, value_type >
		{
			private:
			node_type* _node;

			public:
			map_iterator() :
				_node(NULL)
			{
			}

			private:
			map_iterator(node_type* node) :
				_node(node)
			{
			}

			public:
			map_iterator(map_iterator const& x) :
				_node(x.node)
			{
			}

			map_iterator& operator=(map_iterator const& rhs)
			{
				if (&rhs != this)
				{
					this->_node = rhs._node;
				}
				return *this;
			}

			~map_iterator()
			{
			}

			public:
			bool operator==(map_iterator const& rhs)
			{
				return this->_node == rhs.node;
			}

			bool operator!=(map_iterator const& rhs)
			{
				return !(*this == rhs);
			}

			// TODO test implementation
			reference operator*()
			{
				return this->_node.value;
			}

			// TODO test implementation
			const_reference operator*() const
			{
				return this->_node.value;
			}

			// TODO test implementation
			pointer operator->()
			{
				return &this->_node.value;
			}

			// TODO test implementation
			map_iterator& operator++() // pre
			{
				if (this->_node != NULL)
				{
					if (this->_node->right != NULL)
						this->_node = this->_node->right;
					else if (this->_node->parent != NULL)
						this->_node = this->_node->parent;
				}
				return *this;
			}

			map_iterator operator++(int)
			{
				return map_iterator(); // TODO
			}

			// TODO test implementation
			map_iterator& operator--() // pre
			{
				if (this->_node != NULL)
				{
					if (this->_node->left != NULL)
						this->_node = this->_node->rileftght;
					else if (this->_node->parent != NULL)
						this->_node = this->_node->parent;
				}
				return *this;
			}

			map_iterator operator--(int)
			{
				return map_iterator(); // TODO
			}
		}; // class map_iterator

		private:
		node_type* _root;
		node_type* _min;
		node_type* _max;
		size_type _size;
		key_compare _kcomp;
		value_compare _vcomp;
		allocator_type _alloc;

		public:
		explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_min(NULL),
			_max(NULL),
			_size(0),
			_kcomp(comp),
			_alloc(alloc)
		{
		}

		template< class InputIterator >
		map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_min(NULL),
			_max(NULL),
			_size(0),
			_kcomp(comp),
			_alloc(alloc)
		{
			for (InputIterator it = first; it != last; ++it)
				this->insert(*it);
		}

		map(map const& x) :
			_root(NULL),
			_min(NULL),
			_max(NULL),
			_size(0),
			_kcomp(x._kcomp),
			_alloc(x._alloc)
		{
			for (iterator it = x.begin(); it != x.end(); ++it)
				this->insert(*it);
		}

		~map()
		{
			this->clear();
		}

		map& operator=(map const& rhs)
		{
			if (this != &rhs)
			{
				this->clear();
				for (iterator it = rhs.begin(); it != rhs.end(); ++it)
					this->insert(*it);
			}
			return *this;
		}

		public:
		iterator begin()
		{
			return iterator(this->_min);
		}

		const_iterator begin() const
		{
			return iterator(this->_min);
		}

		// TODO test implementation
		iterator end()
		{
			return iterator(NULL);
		}

		// TODO test implementation
		const_iterator end() const
		{
			return iterator(NULL);
		}

		reverse_iterator rbegin()
		{
			return iterator(this->_max);
		}

		const_reverse_iterator rbegin() const
		{
			return iterator(this->_max);
		}

		// TODO test implementation
		reverse_iterator rend()
		{
			return reverse_iterator(NULL);
		}

		// TODO test implementation
		const_reverse_iterator rend() const
		{
			return reverse_iterator(NULL);
		}

		public:
		bool empty() const
		{
			return this->size() == 0;
		}

		size_type size() const
		{
			return this->_size;
		}

		size_type max_size() const
		{
			return this->get_allocator().max_size();
		}

		public:
		// TODO provide implementation
		// never throws exception, always add element
		mapped_type& operator[](key_type const& key);

		// TODO provide implementation
		mapped_type& at(key_type const& key)
		{
			const_iterator it = this->find(key);

			if (it == this->end())
				throw std::out_of_range(__PRETTY_FUNCTION__);
			return it->;
		}

		// TODO provide implementation
		const mapped_type& at(key_type const& key) const
		{
			throw std::out_of_range(__PRETTY_FUNCTION__);
		}

		public:
		// TODO provide implementation
		ft::pair< iterator, bool > insert(value_type const& val)
		{
			node_type* node = this->_root;

			while (node != NULL)
			{
				if (!this->key_comp()(k, node->_value))
					node = node->right;
				else if (!this->key_comp()(node->_value, k))
					node = node->left;
				else
				{
					node->value.second = val.second;
					return ft::pair<iterator, bool>(iterator(node), false);
				}
			}
			return iterator(node);
		}

		// TODO provide implementation
		iterator insert(iterator position, value_type const& val);

		// TODO provide implementation
		template< class InputIterator >
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
				this->insert(*it);
		}

		// TODO provide implementation
		void erase(iterator position);

		// TODO provide implementation
		size_type erase(key_type const& k);

		// TODO provide implementation
		void erase(iterator first, iterator last)
		{
			for (iterator it = first; first != last; ++first)
				this->erase(it);
		}

		// TODO test implementation
		void swap(map& x)
		{
			// swap root nodes
			node_type* x_root = x._root;

			x._root = this->_root;
			this->_root = x_root;

			// swap sizes
			this->_size ^= x._size;
			x._size ^= this->_size;
			this->_size ^= x._size;
		}

		// TODO test implementation
		void clear()
		{
			this->_size = 0;
			this->release(this->_root);
		}

		public:
		// TODO test implementation
		key_compare key_comp() const
		{
			return this->_kcomp;
		}

		// TODO test implementation
		value_compare value_comp() const
		{
			return this->_vcomp;
		}

		public:
		// TODO test implementation
		iterator find(key_type const& k)
		{
			node_type* node = this->_root;

			while (node != NULL)
			{
				if (!this->key_comp()(k, node->_value))
					node = node->right;
				else if (!this->key_comp()(node->_value, k))
					node = node->left;
				else
					break;
			}
			return iterator(node);
		}

		// TODO test implementation
		const_iterator find(key_type const& k) const
		{
			node_type* node = this->_root;

			while (node != NULL)
			{
				if (!this->key_comp()(k, node->_value))
					node = node->right;
				else if (!this->key_comp()(node->_value, k))
					node = node->left;
				else
					break;
			}
			return iterator(node);
		}

		// TODO test implementation
		size_type count(key_type const& k) const
		{
			if (this->find(k) == NULL)
				return 0;
			return 1;
		}

		// TODO provide implementation
		iterator lower_bound(key_type const& k);

		// TODO provide implementation
		const_iterator lower_bound(key_type const& k) const;

		// TODO provide implementation
		iterator upper_bound(key_type const& k);

		// TODO provide implementation
		const_iterator upper_bound(key_type const& k) const;

		// TODO provide implementation
		ft::pair< const_iterator, const_iterator > equal_range(key_type const& k) const;

		// TODO provide implementation
		ft::pair< iterator, iterator > equal_range(key_type const& k);

		public:
		allocator_type get_allocator() const
		{
			return this->_alloc;
		}

		private:
		template< class _Alloc >
		static node_type* insert(T const& value, node_type* node, _Alloc const& alloc)
		{
			if (node == NULL)
				return alloc.construct(alloc.allocate(1), value);
			if (value < node->value) // TODO use key_compare
				node->left = insert(value, node->left, alloc);
			else if (value > node->value) // TODO use key_compare
				node->right = insert(value, node->right, alloc);
			else
				return node;
			update_height(node);
			return rebalance(node);
		}

		static node_type* remove(T const& value, node_type* node)
		{
		}

		static node_type* search(T const& value, node_type* node)
		{
			if (node == NULL)
				return NULL;
			if (value > node->value) // TODO use key_compare
				return search(value, node->right);
			if (value < node->value) // TODO use key_compare
				return search(value, node->left);
			return node;
		}

		static void update_height(node_type* node)
		{
			int h_left = get_height(node->left);
			int h_right = get_height(node->right);
			int h_max = (h_left > h_right) ? h_left : h_right;

			node->height = h_max + 1;
		}

		static node_type* rebalance(node_type* node)
		{
			int balance = get_balance(node);
			int balance_sub; // TODO remove

			if (balance > 1)
			{
				balance_sub = get_balance(node->left);
				if (balance_sub < 0)
					node->left = rotate_left(node->left);
				return rotate_right(node);
			}
			else if (balance < -1)
			{
				balance_sub = get_balance(node->right);
				if (balance_sub < 0)
					node->right = rotate_left(node->right);
				return rotate_left(node);
			}
			return node;
		}

		static node_type* rotate_right(node_type* node)
		{
			node_type* left = node->left;
			node_type* center = left->right;

			left->right = node;
			node->left = center;
			update_height(node);
			update_height(left);
			return left;
		}

		static node_type* rotate_left(node_type* node)
		{
			node_type* right = node->right;
			node_type* center = right->left;

			right->left = node;
			node->right = center;
			update_height(node);
			update_height(right);
			return right;
		}

		static int get_balance(node_type* node)
		{
			if (node == NULL)
				return 0;
			return get_height(node->left) - get_height(node->right);
		}

		static int get_height(node_type* node)
		{
			if (node == NULL)
				return 0;
			return node->height;
		}

		template< class _Alloc >
		static void release(node_type* node, _Alloc const& alloc)
		{
			if (node == NULL)
				return ;
			release(node->left);
			release(node->right);
			alloc.destroy(node);
			alloc.deallocate(node, 1);
		}

		static value_type& get_max(node_type* node)
		{
			if (node->right != NULL)
				return get_max(node->right);
			return node->value;
		}
	}; // class map

	// TODO provide implementation
	template< class Key, class T, class Compare, class Alloc >
	bool operator==(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	// TODO provide implementation
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	// TODO provide implementation
	template< class Key, class T, class Compare, class Alloc >
	bool operator<(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	// TODO provide implementation
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	// TODO provide implementation
	template< class Key, class T, class Compare, class Alloc >
	bool operator>(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	// TODO provide implementation
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	// TODO provide implementation
	template< class Key, class T, class Compare, class Alloc >
	void swap(map< Key, T, Compare, Alloc >& lhs, map< Key, T, Compare, Alloc >& rhs);
} // namespace ft
