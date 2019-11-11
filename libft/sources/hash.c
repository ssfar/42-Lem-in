/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:29:11 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/11 15:43:36 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	hash(char *key, ssize_t tab_size)
{
	if (key && key[0] && tab_size > 0)
		return ((key[0] + key[ft_strlen(key)]) % tab_size);
	return (-1);
}