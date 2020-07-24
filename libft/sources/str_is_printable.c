/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_printable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <samisfar.dev@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:33:15 by ssfar             #+#    #+#             */
/*   Updated: 2020/07/24 11:08:54 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Check if the string (str) only contain non whitespace characters,
** if so the function return 1 otherwise 0.
*/

uint_fast8_t	str_is_printable(char *str)
{
	uint_fast8_t	printable;

	if (!str)
		return (0);
	printable = ft_isprint(*str++);
	while (ft_isprint(*str))
		str++;
	return (*str == '\0' && printable);
}
