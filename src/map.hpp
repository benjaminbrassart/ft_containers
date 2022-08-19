/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:45:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/19 22:47:43 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include "utils.hpp"

#include <memory>
#include <functional>

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less< Key >,
		class Alloc = std::allocator< ft::pair< const Key, T> >
	>
	class map
	{
		public:
		/** The first template parameter */
		typedef Key key_type;
		/** The second template parameter */
		typedef T mapped_type;
		typedef pair< key_type const, mapped_type > value_type;
		typedef Compare key_compare;
		typedef void* value_compare; // TODO
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef void* iterator; // TODO
		typedef void* const_iterator; // TODO
		typedef ft::reverse_iterator< iterator > reverse_iterator;
		typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
		typedef ptrdiff_t difference_type; // TODO
		typedef size_t size_type; // TODO

		private:
		struct node
		{
			map& map;
			node* left;
			node* right;
			value_type value;
		}; // struct node

		private:
		node* root;

		public:
		explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type());

		template< class InputIterator >
		map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type());

		map(map const& x);

		~map();

		map& operator=(map const& x);

		public:
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		public:
		bool empty() const;

		size_type size() const;
		size_type max_size() const;

		public:
		mapped_type& operator[](key_type const& key);
		mapped_type& at(key_type const& key);
		const mapped_type& at(key_type const& key) const;

		public:
		pair< iterator, bool > insert(value_type const& val);

		iterator insert(iterator position, value_type const& val);

		template< class InputIterator >
		void insert(InputIterator first, InputIterator last);

		void erase(iterator position);

		size_type erase(key_type const& k);

		void erase(iterator first, iterator last);

		void swap(map& x);

		void clear();

		public:
		key_compare key_comp() const;
		value_compare value_comp() const;

		public:
		iterator find(key_type const& k);
		const_iterator find(key_type const& k) const;

		size_type count(key_type const& k) const;

		iterator lower_bound(key_type const&k);
		const_iterator lower_bound(key_type const& k) const;

		iterator upper_bound(key_type const& k);
		const_iterator upper_bound(key_type const& k) const;

		pair< const_iterator, const_iterator > equal_range(key_type const& k) const;
		pair< iterator, iterator > equal_range(key_type const& k);

		public:
		allocator_type get_allocator() const;
	}; // class map

	template< class Key, class T, class Compare, class Alloc >
	bool operator==(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator<(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs);

	template< class Key, class T, class Compare, class Alloc >
	void swap(map< Key, T, Compare, Alloc >& lhs, map< Key, T, Compare, Alloc >& rhs);
} // namespace ft
