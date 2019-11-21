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

// char	bynary_pow_2(uint_fast8_t mod)
// {
// 	if (index < 4)
// 	{
// 		if (index == 0)
// 			return (1);
// 		else if (index == 1)
// 			return (2);
// 		else if (index == 2)
// 			return (4);
// 		return (8);
// 	}
// 	else if (index == 4)
// 		return (16);
// 	else if (index == 5)
// 		return (32);
// 	else if (index == 6)
// 		return (64);
// 	return (128);
// }

// uint_fast8_t	add_on(char *on, size_t to_add)
// {
// 	size_t	on_index;
// 	char	compare;

// 	on_index = to_add / 8;
// 	compare = binary_pow_2(to_add % 8);
// 	if (compare & on[on_index])
// 		return (0);
// 	on[on_index] += compare;
// 	return (1);
// }

t_path		*create_path(t_lem_in *s, size_t malloc_size)
{
	size_t	i;
	t_path	*new;

	i = 0;
	if (!(new = malloc(sizeof(t_path))))
		exit_failure(s, 2, "can't malloc path", 0);
	new->p_next = NULL;
	if (!(new->path = malloc(sizeof(size_t) * malloc_size)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	if (!(new->on_p = malloc(sizeof(uint8_t) * s->nb_room)))
		exit_failure(s, 123, "can't malloc on_queu", 0);
	return (new);
}

// t_path	*realloc_path(t_lem_in *s, t_path *path, size_t malloc_size)
// {
// 	t_path	*new;
// 	size_t	i;

// 	new = create_path(s, malloc_size);
// 	i = 0;
// 	new->path_size = path->path_size;
// 	while (i < path->path_size)
// 	{
// 		new->path[i] = path->path[i];
// 		new->on_p[i] = path->on_p[i];
// 		i++;
// 	}
// 	while (i < s->nb_room)
// 	{
// 		new->on_p[i] = path->on_p[i];
// 		i++;
// 	}
// 	free(path->path);
// 	free(path->on_p);
// 	free(path);
// 	return (new);
// }

void	realloc_path(t_lem_in *s, t_path *path, size_t malloc_size)
{
	size_t	*new;
	size_t	i;

	if (!(new = malloc(sizeof(size_t) * malloc_size)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	i = 0;
	while (i <= path->path_size)
	{
		new[i] = path->path[i];
		i++;
	}
	free(path->path);
	path->path = new;
}

void		duplicate_path(t_lem_in *s, size_t to_add, t_path *tmp, 
	size_t malloc_size)
{
	size_t	i;

	s->l_way->p_next = create_path(s, malloc_size);
	s->l_way = s->l_way->p_next;
	i = 0;
	while (i < tmp->path_size)
	{
		s->l_way->path[i] = tmp->path[i];
		s->l_way->on_p[i] = tmp->on_p[i];
		i++;
	}
	s->l_way->path[i] = to_add;
	while (i < s->nb_room)
	{
		s->l_way->on_p[i] = tmp->on_p[i];
		i++;
	}
	s->l_way->on_p[tmp->path[tmp->path_size]] = 0;
	s->l_way->on_p[to_add] = 1;
	s->l_way->path_size = tmp->path_size;
}

void		copy_path(t_lem_in *s, size_t to_add, t_path *tmp,
	size_t *malloc_size)
{
	 size_t	i;

	 i = 0;
	//if (!is_duplicate(tmp->path, tmp->path_size, to_add))

	ft_printf("add this %s\n to ", s->room_tab[to_add].name);
	while (i <= tmp->path_size)
	{
		ft_printf(" %s ", s->room_tab[tmp->path[i]].name);
		i++;
	}
	ft_printf("\n");
	if (!tmp->on_p[to_add])
	{
		ft_printf("is not on queu\n");
		//ft_printf("got here\n");
		if (s->queu[s->cur] == tmp->path[tmp->path_size])
		{
			if (tmp->path_size + 1 >= *malloc_size)
			{
				ft_printf("malloc : %d\n", *malloc_size);
				*malloc_size *= *malloc_size;
				ft_printf("realoc malloc : %d\n", *malloc_size);
				realloc_path(s, tmp, *malloc_size);
				ft_printf("after realoc\n");
			}
			//ft_printf("here : %d\n", tmp->path_size);
			tmp->path_size++;
			tmp->path[tmp->path_size] = to_add;
			tmp->on_p[to_add] = 1;
		}
		else
			duplicate_path(s, to_add, tmp, *malloc_size);
	}
	ft_printf("end coppy\n");

}

void		init_algo(t_lem_in *s)
{
	clear_map(s);
	s->way = create_path(s, PATH_SIZE);
	ft_bzero(s->way->on_p, s->nb_room);
	s->l_way = s->way;
	s->way->path_size = 0;
	s->way->path[0] = s->start;
	s->way->on_p[s->start] = 1;
	if (!(s->queu = malloc(sizeof(size_t) * s->nb_room)))
		exit_failure(s, 123, "can't malloc queu", 0);
	s->queu[0] = s->start;
	s->cur = 0;
	s->q_size = 0;
	if (!(s->on_q = malloc(sizeof(uint8_t) * s->nb_room)))
		exit_failure(s, 123, "can't malloc on_queu", 0);
	ft_bzero(s->on_q, s->nb_room);
	s->on_q[s->start] = 1;
}


void		find_path(t_lem_in *s, ssize_t *link, size_t nb_link)
{
	size_t	i;
	t_path	*tmp;
	size_t	malloc_size;

	ft_printf("|Recherche chemin qui finissent par curr|\n");
	tmp = s->way;
	while (tmp)
	{
		ft_printf("new chemin\n");
		if (tmp->path[tmp->path_size] == s->queu[s->cur])
		{
			ft_printf("finie par cur\n");
			malloc_size = PATH_SIZE;
			i = 0;
			while (i < nb_link && link[i] != -1)
			{
				copy_path(s, link[i], tmp, &malloc_size);
				i++;
			}
		}
		tmp = tmp->p_next;
	}
}

void		add_queu(t_lem_in *s, ssize_t *link, size_t nb_link)
{
	size_t	i;

	i = 0;
	while (i < nb_link && link[i] != -1)
	{
		// opti possible ? : spliter la condition
		if (link[i] != s->end && !s->on_q[link[i]])
		{
			s->on_q[link[i]] = 1;
			s->q_size++;
			s->queu[s->q_size] = link[i];
		}
		i++;
	}
}

// void		add_queu(t_lem_in *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < s->room_tab[s->queu[s->cur]].nb_link
// 		 && s->room_tab[s->queu[s->cur]].link[i] != -1)
// 	{
// 		// opti possible ? : spliter la condition
// 		if (s->room_tab[s->queu[s->cur]].link[i] != s->end
// 			&& !is_duplicate(s->queu, s->q_size, s->room_tab[s->queu[s->cur]].link[i]))
// 		{
// 			s->q_size++;
// 			s->on_q[s->room_tab[s->queu[s->cur]].link[i]] = 1;
// 			s->queu[s->q_size] = s->room_tab[s->queu[s->cur]].link[i];
// 		}
// 		i++;
// 	}
// }

void		algo(t_lem_in *s)
{
	size_t	nb_link;
	ssize_t	*link;

	//ft_printf("start algo\n");
	init_algo(s);
	//ft_printf("after init_algo\n");
	//ft_printf("queu size %d\n", s->q_size);
	while (s->cur <= s->q_size)
	{
	ft_printf("start boucle (current %d)\n", s->cur);
	//	ft_printf("queu size %d current %d\n", s->q_size, s->cur);
		nb_link = s->room_tab[s->queu[s->cur]].nb_link;
		link = s->room_tab[s->queu[s->cur]].link;
		add_queu(s, link, nb_link);
		//ft_printf("after add\n");
		find_path(s, link, nb_link);
		s->cur++;
	}
//	ft_printf("%d | %d\n", s->nb_room, s->q_size);
}
