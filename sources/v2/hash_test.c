/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:43:09 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/12 18:06:34 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE	1024
	

// void	map_to_tab(void)
// {
// 	t_node nodes[NODE_COUNT];
// 	t_list	map[MAP_SIZE];
// 	t_list *tmp;
// 	int 	i;

// 	//map[0]->node = &{0, "TITI", 0, NULL};
// 	i = 0;
// 	while (i < MAP_SIZE)
// 	{
// 		tmp = map[i++];
// 		while (tmp)
// 		{
// 			int j = tmp->node->id;
// 			nodes[j] = *(tmp->node);
// 			free(tmp->node);
// 			tmp->node = &nodes[j];
// 			tmp = tmp->next;
// 		}
// 	}
// }
//	\ /  //
// \(")/ //
// -( )- // 
// /( )\ //




void	hash_data(void *dest, const size_t size, const char *key)
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

int main(void)
{
	unsigned int	v;
	char			*key;

	key = "0123456";
	printf("key '%s' -> %u\n", key, hash_to_int(key));

	key = "01234";
	printf("key '%s' -> %u\n", key, hash_to_int(key));

	key = "012345";
	printf("key '%s' -> %u\n", key, hash_to_int(key));

	key = "012345678";
	printf("key '%s' -> %u\n", key, hash_to_int(key));
	return (0);
}