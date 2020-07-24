/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <samisfar.dev@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 18:55:05 by ssfar             #+#    #+#             */
/*   Updated: 2020/07/24 11:08:31 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return a copy of the string (s) without the whitspace character
** '\t', ' ', '\n'.
** <i> The output string is malloced.
*/

char	*ft_strtrim(char const *s)
{
	size_t	len;

	if (!s)
		return (NULL);
	while ((*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	if (*s == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s) - 1;
	while ((s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
		len--;
	return (ft_strsub(s, 0, len + 1));
}
