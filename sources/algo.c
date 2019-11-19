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

t_path		*create_path(t_lem_in *s)
{
	size_t	i;
	t_path	*new;

	i = 0;
	if (!(new = malloc(sizeof(t_path))))
		exit_failure(s, 2, "can't malloc path", 0);
	new->p_next = NULL;
	if (!(new->path = malloc(sizeof(size_t) * s->nb_room)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	return (new);
}

void		print_tab(size_t *tab, size_t size, char *msg)
{
	size_t i;

	i = 0;
	ft_printf("%s\n", msg);
	while (i < size)
		ft_printf("%d ", tab[i++]);
	ft_printf("\n");	
}

void		duplicate_path(t_lem_in *s, size_t to_add, t_path *tmp)
{
	size_t	i;

	s->l_way->p_next = create_path(s);
	s->l_way = s->l_way->p_next;
	i = 0;
	while (i < tmp->path_size)
	{
		s->l_way->path[i] = tmp->path[i];
		i++;
	}
	s->l_way->path[i] = to_add;
	s->l_way->path_size = i;
}

void		copy_path(t_lem_in *s, size_t to_add, t_path *tmp)
{
	size_t	i;

	i = 0;
	if (!is_duplicate(tmp->path, tmp->path_size, to_add))
	{
		if (s->queu[s->cur] == tmp->path[tmp->path_size])
		{
			tmp->path_size++;
			tmp->path[tmp->path_size] = to_add;
		}
		else
			duplicate_path(s, to_add, tmp);
	}
}

void		init_algo(t_lem_in *s)
{
	// ft_printf("before map\n");
	clear_map(s);
	// ft_printf("after map\n");
	s->way = create_path(s);
	s->l_way = s->way;
	s->way->path_size = 0;
	s->way->path[0] = s->start;
	if (!(s->queu = malloc(sizeof(sizeof(size_t)) * s->nb_room)))
		exit_failure(s, 123, "can't malloc queu", 0);
	s->queu[0] = s->start;
	s->cur = 0;
	s->q_size = 0;
}

uint_fast8_t	is_duplicate(size_t *tab, size_t tab_size, size_t to_add)
{
	size_t	i;

	i = 0;
	while (i <= tab_size)
	{
		if (tab[i] == to_add)
			return (1);
		i++;
	}
	return (0);
}

void		find_path(t_lem_in *s)
{
	size_t	i;
	t_path	*tmp;

	tmp = s->way;
	while (tmp)
	{
		if (tmp->path[tmp->path_size] == s->queu[s->cur])
		{
			i = 0;
			while (i < s->room_tab[s->queu[s->cur]].nb_link
				&& s->room_tab[s->queu[s->cur]].link[i] != -1)
			{
				copy_path(s, s->room_tab[s->queu[s->cur]].link[i], tmp);
				i++;
			}
		}
		tmp = tmp->p_next;
	}	
}

void		add_queu(t_lem_in *s)
{
	size_t	i;

	i = 0;
	while (i < s->room_tab[s->queu[s->cur]].nb_link
		&& s->room_tab[s->queu[s->cur]].link[i] != -1)
	{
		// opti possible ? : spliter la condition
		if (s->room_tab[s->queu[s->cur]].link[i] != s->end && !is_duplicate(s->queu, s->q_size, s->room_tab[s->queu[s->cur]].link[i]))
		{
			s->q_size++;
			s->queu[s->q_size] = s->room_tab[s->queu[s->cur]].link[i];
		}
		i++;
	}
}

void		algo(t_lem_in *s)
{
	init_algo(s);
	while (s->cur <= s->q_size)
	{
		add_queu(s);
		//ft_printf("After Add queue\n");
		find_path(s); // ici
		//ft_printf("After find path\n");
		s->cur++;
	}
}