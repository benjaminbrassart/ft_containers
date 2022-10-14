/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullptr.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:52:41 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/14 10:08:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// if using a version older than c++11
#if __cplusplus < 201103L

// https://stackoverflow.com/a/44517878
const class nullptr_t
{
	public:
	template< class T >
	operator T*() const { return 0; };

	template< class C, class T >
	operator T* C::*() const { return 0; };

	private:
	void operator&() const;
} nullptr = {};

#endif
