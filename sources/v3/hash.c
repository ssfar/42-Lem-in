/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:01:50 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/12 18:00:07 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void			hash_data(void *dest, const size_t size, const char *key)
{
	int				i;
	int				j;
	unsigned char	*d;

	j = strlen(key);
	bzero(dest, size);
	d = dest;

	while (*key)
	{
		i = 0;
		while (i < size)
		{
			d[i] ^= key[i % j];
			++i;
		}
		key += size;
		j -= size;
	}
}

unsigned int	hash_to_int(const char *key)
{
	unsigned int	v;

	hash_data(&v, sizeof(v), key);
	return (v % MAP_SIZE);
}

t_table			*find_table(t_table *table, char *key, size_t index)
{
	t_table *tmp;

	tmp = table[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->t_next;
	}
	return (NULL);
}