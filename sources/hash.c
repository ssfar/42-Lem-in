/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:01:50 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/14 22:52:57 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

// void			hash_data(void *dest, const size_t size, const char *key)
// {
// 	size_t			i;
// 	int				j;
// 	unsigned char	*d;

// 	j = strlen(key);
// 	bzero(dest, size);
// 	d = dest;

// 	while (*key)
// 	{
// 		i = 0;
// 		while (i < size)
// 		{
// 			//  if (!key[i % j])
// 			//  	return ;
// 			d[i] ^= key[i % j];
// 			++i;
// 		}
// 		key += size;
// 		j -= size;
// 	}
// }


void			hash_data(void *dest, const size_t size, const char *key)
{
	size_t			j;
	unsigned char	*d;

	j = 0;
	d = bzero(dest, size);
	while (*key)
	{
		if (j == size)
			j = 0;
		d[j++] ^= *key++;
	}
}

unsigned int	hash_to_int(const char *key)
{
	unsigned int	v;

	hash_data(&v, sizeof(v), key);
	return (v % MAP_SIZE);
}

t_room		*find_room(t_lem_in *s, char *key, size_t index)
{
	t_table	*tmp;

	if (!s->map[index])
		return (NULL);
	tmp = s->map[index];
	while (tmp->room != NULL)
	{
		if (ft_strcmp(tmp->room->name, key) == 0)
			return (tmp->room);
		tmp = tmp->t_next;
	}
	return (NULL);
}