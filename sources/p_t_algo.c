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

uint_fast8_t	is_on(unsigned char *on, size_t to_check)
{
	size_t			on_index;
	unsigned char	compare;

	on_index = to_check / 8;
	compare = binary_pow_2(to_check % 8);
	if (compare & on[on_index])
		return (1);
	return (0);
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

uint_fast8_t	is_on_path(t_lem_in *s, unsigned char *on, t_path to_add)
{
	ssize_t	index;
	size_t	on_index;
	size_t	compare;

	index = 0;
	while (index <= to_add.n_last)
	{
	if (to_add.node[index] != s->start && to_add.node[index] != s->end)
	{
	on_index = to_add.node[index] / 8;
	compare = binary_pow_2(to_add.node[index] % 8);
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
	if (!(new->node = malloc(sizeof(ssize_t) * malloc_size)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	new->n_size = malloc_size - 1;
}

void	realloc_path(t_lem_in *s, t_path *path, size_t malloc_size)
{
	ssize_t	*new;
	ssize_t	i;

	if (!(new = malloc(sizeof(ssize_t) * malloc_size)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	i = 0;
	while (i <= path->n_last)
	{
		new[i] = path->node[i];
		i++;
	}
	free(path->node);
	path->node = new;
	path->n_size = malloc_size - 1;
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
		realloc_path_tab(s, s->way, s->p_last * s->p_last + 2);
	create_path(s, &s->way[s->p_last], tmp->n_size + 2);
	i = 0;
	while (i < tmp->n_last)
	{
		s->way[s->p_last].node[i] = tmp->node[i];
		if ((size_t)i < s->on_size)
			s->way[s->p_last].on_p[i] = tmp->on_p[i];
		i++;
	}
	s->way[s->p_last].node[i] = to_add;
	while ((size_t)i < s->on_size)
	{
		s->way[s->p_last].on_p[i] = tmp->on_p[i];
		i++;
	}
	remove_on(s->way[s->p_last].on_p, tmp->node[tmp->n_last]);
	remove_on(tmp->on_p, to_add);
	s->way[s->p_last].n_last = tmp->n_last;
}

void		copy_path(t_lem_in *s, size_t to_add, t_path *tmp, size_t cur)
{
	if (add_on(tmp->on_p, to_add))
	{
		if (s->queu[cur] == tmp->node[tmp->n_last])
		{
			if (tmp->n_last == tmp->n_size)
				realloc_path(s, tmp, tmp->n_size * 2 + 2);
			tmp->n_last++;
			tmp->node[tmp->n_last] = to_add;
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
	s->way[0].n_last = 0;
	s->way[0].node[0] = s->start;
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

int		find_path(t_lem_in *s, ssize_t *link, size_t nb_link, ssize_t cur)
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
		if (tmp[i].node[tmp[i].n_last] == s->queu[cur])
		{
			j = 0;
			while (j < nb_link)
			{
				if (link[j] != -2)
					copy_path(s, link[j], &tmp[i], cur);
				if (tmp[i].node[tmp[i].n_last] == s->end)
					return (i);
				j++;
			}
		}
		i++;
	}
	return (-1);
}

void		add_queu(t_lem_in *s, ssize_t *link, ssize_t *prio, size_t nb_link)
{
	size_t	i;

	i = 0;
	while (i < nb_link)
	{
		if (prio[i] != -2 && prio[i] != -1 && link[i] != s->end && add_on(s->on_q, link[i]))
		{
			s->q_last++;
			s->queu[s->q_last] = link[i];
		}
		i++;
	}
}

uint_fast8_t	valid_path(t_path *way, size_t p_last, ssize_t end)
{
	size_t	i;
	i = 0;
	while (i <= p_last)
	{
		if (way[i].node[way[i].n_last] == end)
			return (1);
		i++;
	}
	return (0);
}
void	duply(t_lem_in *s, size_t tmp_path_last, t_path *way_i, t_path *way_j)
{
	size_t	k;
	size_t	l;
	size_t	pos;
	k = 0;
	while (way_j->node[k] != way_i->node[way_i->n_last])
		k++;
	k++;
	pos = k;
	while (k < (size_t)way_j->n_last)
	{
		if (is_on(way_i->on_p, way_j->node[k]))
			return ;
		k++;
	}
	while (tmp_path_last <= s->p_last)
	{
		k = pos;
		l = way_i->n_last + 1;
		while (l < (size_t)s->way[tmp_path_last].n_last && way_j->node[k] == s->way[tmp_path_last].node[l])
		{
			k++;
			l++;
		}
		if (way_j->node[k] == s->way[tmp_path_last].node[l])
			return ;
		tmp_path_last++;
	}
	s->p_last++;
	if (s->p_last >= s->p_size)
		realloc_path_tab(s, s->way, s->p_size * s->p_size + 2);
	create_path(s, &s->way[s->p_last], way_i->n_last + 1 + way_j->n_last - pos + 1);
	k = 0;
	while (k <= (size_t)way_i->n_last)
	{
		s->way[s->p_last].node[k] = way_i->node[k];
		if (k < s->on_size)
			s->way[s->p_last].on_p[k] = way_i->on_p[k];
		k++;
	}
	l = k;
	while (k < s->on_size)
	{
		s->way[s->p_last].on_p[k] = way_i->on_p[k];
		k++;
	}
	while (pos <= (size_t)way_j->n_last)
	{
		s->way[s->p_last].node[l++] = way_j->node[pos];
		add_on(s->way[s->p_last].on_p, way_j->node[pos++]);
	}
	s->way[s->p_last].n_last = l - 1;
}
void	complete_path(t_lem_in *s, t_path *way, size_t p_last, ssize_t end)
{
	size_t	i;
	size_t	j;
	ssize_t	i_last;
	size_t tmp_last_path;
	i = 0;
	while (i <= p_last)
	{
		if (way[i].node[way[i].n_last] != end)
		{
			i_last = way[i].node[way[i].n_last];
			j = 0;
			tmp_last_path = s->p_last;
			while (j <= p_last)
			{
				if (way[j].node[way[j].n_last] == end && is_on(way[j].on_p, i_last))
					duply(s, tmp_last_path, &way[i], &way[j]);
				j++;
			}
		}
		i++;
	}
}
	
uint_fast8_t	sort_way(t_lem_in *s, t_path *way, size_t path_size)
{
	size_t i;
	t_path tmp;

	i = 0;
	while (i <= path_size)
	{
		if (way[i].node[way[i].n_last] != s->end)
		{
			tmp = s->way[i];
			s->way[i] = s->way[path_size];
			s->way[path_size] = tmp;
			path_size--;
		}
		else
			i++;
	}
	return (path_size);
}

void		clear_link(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = 0;
	while (i < s->nb_room)
	{
		if (s->room_tab[i].link[0] == -2 || s->room_tab[i].link[s->room_tab[i].nb_link - 1] == -2)
		{
			if (s->room_tab[i].link[0] == -2)
				s->room_tab[i].link++;
			s->room_tab[i].nb_link--;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (i < s->nb_room)
	{
		if (!(s->room_tab[i].prio = malloc(sizeof(ssize_t) * s->room_tab[i].nb_link + 1)))
			exit_failure(s, 123, "can't malloc prio", 1);
		j = 0;
		while (j < s->room_tab[i].nb_link)
		{
			s->room_tab[i].prio[j] = ALL;
			j++;
		}
		i++;
	}
}

void		edit_link(t_lem_in *s, size_t find, size_t i, size_t j)
{
	size_t	k;

	k = 0;
	while (k < s->room_tab[j].nb_link)
	{
		if (i > 0 && s->room_tab[j].link[k] == s->way[find].node[i - 1])
		{
			if (s->room_tab[j].prio[k] == 1)
				s->room_tab[j].prio[k] = 0;
			else
				s->room_tab[j].prio[k] = -2;
			
		}
		if (i < find && s->room_tab[j].link[k] == s->way[find].node[i + 1])
		{
			if (s->room_tab[j].prio[k] == 1)
				s->room_tab[j].prio[k] = -1;
			else
				s->room_tab[j].prio[k] = -2;
		}
		k++;
	}
}

void		bhandari(t_lem_in *s, t_room *data_tab, ssize_t find)
{
	ssize_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < s->way[find].n_last)
	{
		ft_printf("%s\n", s->room_tab[i].name);
		j = 0;
		while (data_tab[j].index != s->way[find].node[i])
			j++;
		edit_link(s, find, i, j);
		i++;
	}
}

size_t		calcul_turn(t_lem_in s)
{
	size_t	act_case;

	act_case = 0;
	(void)(s);
	return (act_case);
}

void		algo(t_lem_in *s)
{
	t_room	*data_tab;
	ssize_t	cur;
	ssize_t	find;
	ssize_t	i;
	// size_t	act_case;

	clear_link(s);
	init_algo(s);
	cur = 0;
	data_tab = s->room_tab;
	find = -1;
	i = 0;
	print_datatab(s);
	/*
	while (cur <= s->q_last)
	{
		add_queu(s, data_tab[s->queu[cur]].link, data_tab[s->queu[cur]].prio, data_tab[s->queu[cur]].nb_link); // envoyer en + les prio
		i = find_path(s, data_tab[s->queu[cur]].link, data_tab[s->queu[cur]].nb_link, cur); // pareil
		// bhandari(s, data_tab, i);
		cur++;
	}
	*/
	// if (!valid_path(s->way, s->p_last, s->end))
	// print_info(s);
	// complete_path(s, s->way, s->p_last, s->end);
	// new_p_last = sort_way(s, s->way, s->p_last);
	// sort_path(s, s->p_last);
	// s->p_last = sort_way(s, s->way, s->p_last);
	// ft_printf("\nafter completion \n\n");
	// get_way(s, s->p_last);
	// throw_ant(s, get_way(s, s->p_last));
}
