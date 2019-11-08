/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_numeric.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:13:04 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/08 18:07:09 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Check if the string (str) only contain numeric characters and signs at start,
** if so the function return 1 otherwise 0.
*/

uint_fast8_t	str_is_numeric(char *str)
{
	uint_fast8_t	numeric;

	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	numeric = ft_isdigit(*str++);
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0' && numeric);
}
