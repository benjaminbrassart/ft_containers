/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:45:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/23 06:19:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		class Alloc = std::allocator< ft::pair< const Key, T > >
	>
	class map
	{
		private:
		struct _Node;

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
		struct _Node
		{
			_Node* parent;
			_Node* left;
			_Node* right;
			value_type value;
		}; // struct _Node

		private:
		_Node* _root;
		size_type _size;
		key_compare _comp;
		allocator_type _alloc;

		public:
		explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_size(0),
			_comp(comp),
			_alloc(alloc)
		{
		}

		template< class InputIterator >
		map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_size(0),
			_comp(comp),
			_alloc(alloc)
		{
			for (InputIterator it = first; it != last; ++it)
				this->insert(*it);
		}

		map(map const& x) :
			_root(NULL),
			_size(0),
			_comp(x._comp),
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
		iterator begin();

		// TODO provide implementation
		const_iterator begin() const;

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
			_Node* x_root = x._root;

			x._root = this->_root;
			this->_root = x_root;

			// swap sizes
			this->_size ^= x._size;
			x._size ^= thi->._size;
			this->_size ^= x._size;
		}

		// TODO provide implementation
		void clear()
		{
			this->_size = 0;
		}

		public:
		// TODO provide implementation
		key_compare key_comp() const;

		// TODO provide implementation
		value_compare value_comp() const;

		public:
		// TODO provide implementation
		iterator find(key_type const& k);

		// TODO provide implementation
		const_iterator find(key_type const& k) const;

		// TODO provide implementation
		size_type count(key_type const& k) const;

		// TODO provide implementation
		iterator lower_bound(key_type const&k);

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
