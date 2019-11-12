/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_numeric_no_symbol.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 10:13:37 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/10 15:04:03 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Check if the string (str) contain and only contain numeric characters,
** if so the function return 1 otherwise 0.
*/

uint_fast8_t	str_is_numeric_no_symbol(char *str)
{
	if (!str)
		return (0);
	if (ft_isdigit(*str++))
	{
		while (ft_isdigit(*str))
			str++;
		return (*str == '\0');
	}
	return (0);
}