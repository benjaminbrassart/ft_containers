/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:45:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/25 13:34:09 by bbrassar         ###   ########.fr       */
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
		class Compare = std::less< Key >,
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
		typedef std::allocator< value_type > allocator_type; // TODO revert to Alloc
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef value_type* iterator; // TODO implement bidirectional iterator
		typedef value_type const* const_iterator; // TODO implement bidirectional iterator
		typedef ft::reverse_iterator< iterator > reverse_iterator;
		typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
		typedef typename ft::iterator_traits< iterator >::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		private:
		struct node_type
		{
			public:
			node_type* left;
			node_type* right;
			value_type value;
			int height;

			public:
			node_type(T const& value) :
				value(value),
				left(NULL),
				right(NULL),
				height(1)
			{
			}
		}; // struct node_type

		class map_iterator : public ft::iterator< ft::bidirectional_iterator_tag, value_type >
		{
			private:

			public:
			map_iterator();

			private:
			map_iterator(node_type* node);

			public:
			map_iterator(map_iterator const& x);

			map_iterator& operator=(map_iterator const& rhs);

			~map_iterator();

			public:
			bool operator==(map_iterator const& rhs);
			bool operator!=(map_iterator const& rhs);
			reference operator*();
			const_reference operator*() const;
			pointer operator->();
			map_iterator& operator++(); // pre
			map_iterator operator++(int); // post
			map_iterator& operator--(); // pre
			map_iterator operator--(int); // post
		}; // class map_iterator

		private:
		node_type* _root;
		size_type _size;
		key_compare _kcomp;
		value_compare _vcomp;
		allocator_type _alloc;

		public:
		explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_size(0),
			_kcomp(comp),
			_alloc(alloc)
		{
		}

		template< class InputIterator >
		map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_size(0),
			_kcomp(comp),
			_alloc(alloc)
		{
			for (InputIterator it = first; it != last; ++it)
				this->insert(*it);
		}

		map(map const& x) :
			_root(NULL),
			_size(0),
			_kcomp(x._kcomp),
			_alloc(x._alloc)
		{
			for (iterator it = x.begin(); it != x.end(), ++it)
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
				for (iterator it = x.begin(); it != x.end(), ++it)
					this->insert(*it);
			}
			return *this;
		}

		public:
		// TODO provide implementation
		iterator begin()
		{
			return iterator(this->_root);
		}

		// TODO provide implementation
		const_iterator begin() const
		{
			return iterator(this->_root);
		}

		// TODO provide implementation
		iterator end();

		// TODO provide implementation
		const_iterator end() const;

		// TODO provide implementation
		reverse_iterator rbegin();

		// TODO provide implementation
		const_reverse_iterator rbegin() const;

		// TODO provide implementation
		reverse_iterator rend();

		// TODO provide implementation
		const_reverse_iterator rend() const;

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
		// never throws exception,
		mapped_type& operator[](key_type const& key);

		// TODO provide implementation
		mapped_type& at(key_type const& key)
		{
			throw std::out_of_range(__PRETTY_FUNCTION__);
		}

		// TODO provide implementation
		const mapped_type& at(key_type const& key) const
		{
			throw std::out_of_range(__PRETTY_FUNCTION__);
		}

		public:
		// TODO provide implementation
		ft::pair< iterator, bool > insert(value_type const& val);

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
		void erase(iterator first, iterator last);

		// TODO test implementation
		void swap(map& x)
		{
			// swap root nodes
			node_type* x_root = x._root;

			x._root = this->_root;
			this->_root = x_root;

			// swap sizes
			this->_size ^= x._size;
			x._size ^= thi->._size;
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
		// TODO provide implementation
		iterator find(key_type const& k);

		// TODO provide implementation
		const_iterator find(key_type const& k) const;

		// TODO provide implementation
		size_type count(key_type const& k) const;

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
		node_type* insert(T const& value, node_type* node)
		{
			if (node == NULL)
				return this->get_allocator().construct(this->get_allocator().allocate(1), value);
			return NULL; // TODO insert
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

		void update_height(node_type* node)
		{
			int h_left = get_height(node->left);
			int h_right = get_height(node->right);
			int h_max = (h_left > h_right) ? h_left : h_right;

			node->height = h_max + 1;
		}

		node_type* rebalance(node_type* node)
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

		node_type* rotate_right(node_type* node)
		{
			node_type* left = node->left;
			node_type* center = left->right;

			left->right = node;
			node->left = center;
			update_height(node);
			update_height(left);
			return left;
		}

		node_type* rotate_left(node_type* node)
		{
			node_type* right = node->right;
			node_type* center = right->left;

			right->left = node;
			node->right = center;
			avltree::update_height(node);
			avltree::update_height(right);
			return right;
		}

		int get_balance(node_type* node)
		{
			if (node == NULL)
				return 0;
			return get_height(node->left) - get_height(node->right);
		}

		int get_height(node_type* node)
		{
			if (node == NULL)
				return 0;
			return node->height;
		}

		void release(node_type* node)
		{
			if (node == NULL)
				return ;
			release(node->left);
			release(node->right);
			this->get_allocator().destroy(node);
			this->get_allocator().deallocate(node, 1);
		}

		value_type& get_max(node_type* node)
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
