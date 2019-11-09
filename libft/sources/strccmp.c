/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strccmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:23:24 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/08 20:02:08 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Lexicographically compare the characters of the strings (s1) and
** (s2) until the first difference, occurency of (c) or the end of a string.
** Return an integer greater than, equal to, or less than 0, according as the
** string (s1) is greater than, equal to, or less than (s2).
*/

int_fast16_t	strccmp(const char *s1, const char *s2, char c)
{
	if (s1 && s2)
	{
		while (*s1 && *s2 && *s1 == *s2 && *s1 != c)
		{
			s1++;
			s2++;
		}
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	if (s1)
		return ((unsigned char)*s1);
	else if (s2)
		return (-((unsigned char)*s2));
	return (0);
}

