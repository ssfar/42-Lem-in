/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 11:08:33 by ssfar             #+#    #+#             */
/*   Updated: 2019/08/15 14:38:54 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Writes (len) bytes of value (c) to the string (b).
*/

void	*ft_memset(void *b, int_fast8_t c, size_t len)
{
	if (b)
		while (len)
			((uint8_t*)b)[--len] = (uint8_t)c;
	return (b);
}
