/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:34:44 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/16 13:34:44 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

unsigned char	binary_pow_2(uint_fast8_t index)
{
	if (index < 4)
	{
		if (index == 0)
			return (1);
		else if (index == 1)
			return (2);
		else if (index == 2)
			return (4);
		return (8);
	}
	else if (index == 4)
		return (16);
	else if (index == 5)
		return (32);
	else if (index == 6)
		return (64);
	return (128);
}

uint_fast8_t	remove_on(unsigned char *on, size_t to_add)
{
	size_t			on_index;
	unsigned char	compare;

	on_index = to_add / 8;
	compare = binary_pow_2(to_add % 8);
	on[on_index] -= compare;
	return (1);
}

uint_fast8_t	add_on(unsigned char *on, size_t to_add)
{
	size_t			on_index;
	unsigned char	compare;

	on_index = to_add / 8;
	compare = binary_pow_2(to_add % 8);
	if (compare & on[on_index])
		return (0);
	on[on_index] += compare;
	return (1);
}

uint_fast8_t	is_on(t_lem_in *s, unsigned char *on, t_path to_add)
{
	ssize_t			index;
	size_t			on_index;
	size_t			compare;

	index = 0;
	while (index <= to_add.last_node)
	{
		if (to_add.path[index] != s->start && to_add.path[index] != s->end)
		{
			on_index = to_add.path[index] / 8;
			compare = binary_pow_2(to_add.path[index] % 8);
			if (compare & on[on_index])
				return (1);
		}
		index++;
	}
	return (0);
}

void		create_path(t_lem_in *s, t_path *new, size_t malloc_size)
{
	if (!(new->on_p = malloc(sizeof(uint8_t) * s->on_size)))
		exit_failure(s, 123, "can't malloc on_p", 0);
	if (!(new->path = malloc(sizeof(ssize_t) * malloc_size)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	new->max_pos = malloc_size - 1;
}

void	realloc_path(t_lem_in *s, t_path *path, size_t malloc_size)
{
	ssize_t	*new;
	ssize_t	i;

	if (!(new = malloc(sizeof(ssize_t) * malloc_size)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	i = 0;
	while (i <= path->last_node)
	{
		new[i] = path->path[i];
		i++;
	}
	free(path->path);
	path->path = new;
	path->max_pos = malloc_size - 1;
}

void		realloc_path_tab(t_lem_in *s, t_path *path, size_t size)
{
	t_path	*new;
	size_t	i;

	if (!(new = malloc(sizeof(t_path) * size)))
		exit_failure(s, 2, "can't malloc *way", 0);
	i = 0;
	while (i < s->p_last)
	{
		new[i] = path[i];
		i++;
	}
	free(s->way);
	s->way = new;
	s->p_size = size;
}

void		duplicate_path(t_lem_in *s, size_t to_add, t_path *tmp)
{
	ssize_t	i;

	s->p_last++;
	if (s->p_last >= s->p_size)
		realloc_path_tab(s, s->way, s->p_size * s->p_size + 2);
	create_path(s, &s->way[s->p_last], tmp->max_pos + 1);
	i = 0;
	while (i < tmp->last_node)
	{
		s->way[s->p_last].path[i] = tmp->path[i];
		if ((size_t)i < s->on_size)
			s->way[s->p_last].on_p[i] = tmp->on_p[i];
		i++;
	}
	s->way[s->p_last].path[i] = to_add;
	while ((size_t)i < s->on_size)
	{
		s->way[s->p_last].on_p[i] = tmp->on_p[i];
		i++;
	}
	remove_on(s->way[s->p_last].on_p, tmp->path[tmp->last_node]);
	remove_on(tmp->on_p, to_add);
	s->way[s->p_last].last_node = tmp->last_node;
}

void		copy_path(t_lem_in *s, size_t to_add, t_path *tmp, size_t cur)
{
	if (add_on(tmp->on_p, to_add))
	{
		if (s->queu[cur] == tmp->path[tmp->last_node])
		{
			if (tmp->last_node == tmp->max_pos)
				realloc_path(s, tmp, tmp->max_pos * 2 + 2);
			tmp->last_node++;
			tmp->path[tmp->last_node] = to_add;
		}
		else		
			duplicate_path(s, to_add, tmp);
	}
}

void		init_algo(t_lem_in *s)
{
	clear_map(s);
	s->on_size = (s->nb_room / 8) + 1;
	//path init ...
	s->p_size = s->nb_room * 25;
	if (!(s->way = malloc(sizeof(t_path) * s->p_size)))
		exit_failure(s, 123, "can't malloc s->way", 0);
	create_path(s, &s->way[0], PATH_SIZE);
	s->p_last = 0;
	s->way[0].last_node = 0;
	s->way[0].path[0] = s->start;
	ft_bzero(s->way[0].on_p, s->on_size);
	add_on(s->way[0].on_p, s->start);
	//queu init ...	
	if (!(s->queu = malloc(sizeof(ssize_t) * s->nb_room)))
		exit_failure(s, 123, "can't malloc queu", 0);
	s->queu[0] = s->start;
	s->q_last = 0;
	if (!(s->on_q = malloc(sizeof(uint8_t) * s->on_size)))
		exit_failure(s, 123, "can't malloc on_queu", 0);
	ft_bzero(s->on_q, s->on_size);
	add_on(s->on_q, s->start);
	update_link(s, s->start, s->end, s->room_tab);
	if (s->room_tab[s->start].link_rm < 1 || s->room_tab[s->end].link_rm < 1)
		exit_failure(s, 123, "No path from start to end", 1);
}

void		find_path(t_lem_in *s, ssize_t *link, size_t nb_link, ssize_t cur)
{
	size_t	i;
	size_t	j;
	size_t	p_last;
	t_path	*tmp;

	p_last = s->p_last;
	tmp = s->way;
	i = 0;
	while (i <= p_last)
	{
		if (tmp[i].path[tmp[i].last_node] == s->queu[cur])
		{
			j = 0;
			while (j < nb_link)
			{
				if (link[j] != -2)
					copy_path(s, link[j], &tmp[i], cur);
				j++;
			}
		}
		i++;
	}
}

void		add_queu(t_lem_in *s, ssize_t *link, size_t nb_link)
{
	size_t	i;

	i = 0;
	while (i < nb_link)
	{
		if (link[i] != -2 && link[i] != s->end && add_on(s->on_q, link[i]))
		{
			s->q_last++;
			s->queu[s->q_last] = link[i];
		}
		i++;
	}
}

void		algo(t_lem_in *s)
{
	t_room	*data_tab;
	ssize_t	cur;

	cur = 0;
	data_tab = s->room_tab;
	init_algo(s);
	//print_way_plus_bit(s);
	//ft_printf("sizeof path_tab : %d, path_last : %d\n", s->p_size, s->p_last);
	while (cur <= s->q_last)
	{
		add_queu(s, data_tab[s->queu[cur]].link, data_tab[s->queu[cur]].nb_link);
		find_path(s, data_tab[s->queu[cur]].link, data_tab[s->queu[cur]].nb_link, cur);	
		cur++;
	}
	//print_way(s);
}