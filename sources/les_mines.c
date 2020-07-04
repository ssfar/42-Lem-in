/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_mines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:39:11 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 18:17:58 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void			hash_data(void *dest, const size_t size, const char *key)
{
	size_t			j;
	unsigned char	*d;

	j = 0;
	d = ft_bzero(dest, size);
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

void			hunt_deadend(t_lem_in *s, ssize_t start, ssize_t end,
			t_room *room_tab)
{
	ssize_t	i;
	ssize_t	nb_room;

	i = 0;
	nb_room = s->nb_room;
	while (i < nb_room)
	{
		if (room_tab[i].link_rm == 1 && i != start && i != end)
			delete_link(s, room_tab, room_tab[i].link, i);
		i++;
	}
}

void			bubble_sort_node(size_t *arr, ssize_t *node, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				u_swap(&arr[j], &arr[j + 1]);
				swap(&node[j], &node[j + 1]);
			}
			j++;
		}
		i++;
	}
}

int				main(void)
{
	t_lem_in	s;
	size_t		check;

	if (MAP_SIZE < 1 || MAP_SIZE >= SSIZE_T_MAX)
		return (EXIT_FAILURE);
	init_struct(&s);
	read_ant_nb(&s);
	read_link(&s, read_room(&s));
	write_room(&s);
	write_link(&s);
	print_start_to_end(&s);
	init_algo(&s);
	check = algo_base(&s);
	full_reset(&s);
	algo(&s, check);
	ft_bzero(s.on_q, s.on_size);
	print_info(&s);
	print_ant(&s);
}
