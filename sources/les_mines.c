/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_mines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:39:11 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/05 19:46:45 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

// check the top functions

void		print_tab(size_t *tab, size_t size, char *msg)
{
	size_t i;

	i = 0;
	ft_printf("%s\n", msg);
	while (i < size)
		ft_printf("%d ", tab[i++]);
	ft_printf("\n");	
}

void	print_datatab(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	ft_printf("\n##start\tname : |%s|\n##end\tname : |%s|\n", s->room_tab[s->start].name, s->room_tab[s->end].name);
	i = 0;
	while (i < s->nb_room)
	{
		ft_printf("[red]Name : %s\t", s->room_tab[i].name);
		ft_printf("[blue]Index : %d\t", s->room_tab[i].index);
		ft_printf("[green]Nb_link : %d\t", s->room_tab[i].nb_link);
		ft_printf("[green]link_rm : %d\t", s->room_tab[i].link_rm);
		ft_printf("[white]cost : %lu\t", s->room_tab[i].cost);
		ft_printf("[white]prev : %d\t", s->room_tab[i].prev);
		ft_printf("\n[yellow]links : ");
		j = 0;
		while (j < s->room_tab[i].nb_link)
			ft_printf("|%s|\t", s->room_tab[s->room_tab[i].link[j++]].name);
		j = 0;
		ft_printf("\n[yellow]prios : ");
		while (j < s->room_tab[i].nb_link)
		{
			if (s->room_tab[i].prio[j] == ALL)
				ft_printf("|%s|\t", "ALL");
			else if (s->room_tab[i].prio[j] == LOCK)
				ft_printf("|%s|\t", "LOCK");
			else if (s->room_tab[i].prio[j] == PRIO)
				ft_printf("|%s|\t", "PRIO");
			else if (s->room_tab[i].prio[j] == DEL)
				ft_printf("|%s|\t", "DEL");
			else
				ft_printf("|%s|%d|\t", "WTF", s->room_tab[i].prio[j]);
			j++;
		}
		ft_printf("\n[a_reset]\n");
		i++;
	}
}

void	exit_failure(t_lem_in *s, char i, char *line, char j)
{
	s->nb_room++;
	ft_printf("%s", line);
	j++;
	i++;
	exit(0);
}

void	clean_after_unlinked(t_lem_in *s, size_t i, t_hashmap *tmp)
{
	size_t	j;
	t_hashmap	*tmp2;

	while (tmp)
	{
		tmp2 = tmp->collision_next;
		free(tmp->room);
		free(tmp);
		tmp = tmp2;
	}
	j = i + 1;
	while (j < MAP_SIZE)
	{
		tmp = s->hmap[j];
		while (tmp)
		{
			tmp2 = tmp->collision_next;
			free(tmp->room);
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
}

void	clean_before_unlinked(t_lem_in *s, size_t i, t_hashmap *unliked)
{
	t_hashmap	*tmp;
	t_hashmap	*tmp2;
	size_t	j;

	j = 0;
	while (j < i)
	{
		tmp = s->hmap[j];
		while (tmp)
		{
			free(s->room_tab[tmp->room->index].link);
			tmp2 = tmp->collision_next;
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
	tmp = s->hmap[i];
	while (tmp && tmp != unliked)
	{
		free(s->room_tab[tmp->room->index].link);
		tmp2 = tmp->collision_next;
		free(tmp);
		tmp = tmp2;
	}
}

void	clear_the_mess(t_lem_in *s, size_t i, t_hashmap *unlinked)
{
	clean_before_unlinked(s, i, unlinked);
	free(s->room_tab);
	clean_after_unlinked(s, i, unlinked->collision_next);
	free(unlinked);
	exit_failure(s, 0, "Malloc error room_tab", 0);
}

// until here

char	is_room_name_format(char *line, size_t *i)
{
	size_t	j;

	j = *i;
	if (line[j] == '#' || line[j] == 'L' || line[j] == ' ' || line[j] == '-')
		return (0);
	while (line[j] != ' ' && line[j] != '-' && line[j] > 32 && line[j] < 127)
		j++;
	if (j == *i)
		return (0);
	*i = j;
	return (1);
}

char	is_link2(t_lem_in *s, char *line, t_room *room1)
{
	t_room	*room2;
	size_t	i;

	i = 0;
	if (!is_room_name_format(line, &i) || line[i] != '\0')
		return (0);
	if (!(room2 = find_room(s, line, hash_to_int(line))))
		return (0);
	if (room1->index == room2->index)
		return (1);
	room1->nb_link++;
	room2->nb_link++;
	if (room1->nb_link == SIZE_T_MAX || room2->nb_link == SIZE_T_MAX)
	{
		free(line);
		exit_failure(s, 1, "too many links", 0);
	}
	return (1);
}

char	is_link(t_lem_in *s, char *line)
{
	size_t	i;
	t_room	*room1;

	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return (0);
	i = 0;
	if (line[0] != '#')
	{
		if (!is_room_name_format(line, &i) || line[i] != '-')
			return (0);
		line[i] = '\0';
		if (!(room1 = find_room(s, line, hash_to_int(line))))
			return (0);
		if (!is_link2(s, &line[i + 1], room1))
			return (0);
	}
	info_push_back(s, create_info(s, line));
	return (1);
}

char	is_room(char *line)
{
	size_t	i;

	i = 0;
	if (is_room_name_format(line, &i) && line[i] == ' '
		&& is_room2(&line[i + 1]))
	{
		line[i] = '\0';
		return (1);
	}
	return (0);
}

char	is_room2(char *line)
{
	if (!*line)
		return (0);
	if (*line == '-')
		line++;
	if (ft_isdigit(*line))
	{
		line++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ' ')
		{
			line++;
			if (*line == '-')
				line++;
			if (ft_isdigit(*line))
			{
				line++;
				while (ft_isdigit(*line))
					line++;
				if (!*line)
					return (1);
			}
		}
	}
	return (0);
}

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

void			init_hmap(t_lem_in *s)
{
	size_t	i;

	i = 0;
	while (i < MAP_SIZE)
	{
		s->hmap[i] = NULL;
		i++;
	}
}

t_room	*init_room(t_lem_in *s, t_hashmap *new, char *name)
{
	if (!(new->room = malloc(sizeof(t_room))))
		exit_failure(s, 1, "Can't malloc tmp->room", 0);
	new->room->name = name;
	new->room->index = s->nb_room;
	new->room->nb_link = 0;
	new->room->link = NULL;
	new->room->link_to_end = 0;
	new->room->cost = SIZE_T_MAX;
	new->room->prio = NULL;
	new->room->ascend = 0;
	new->room->prev = -1;
	return	(new->room);
}

t_room	*place_room(t_lem_in *s, char *key, size_t index)
{
	t_hashmap	*tmp;

	if (!(s->hmap[index]))
	{
		if (!(s->hmap[index] = malloc(sizeof(t_hashmap))))
			exit_failure(s, 1, "Can't malloc s->hmap[i]", 0);
		s->hmap[index]->collision_next = NULL;
		return (init_room(s, s->hmap[index], key));
	}
	tmp = s->hmap[index];
	while (tmp->collision_next)
	{
		if (ft_strcmp(key, tmp->room->name) == 0)
			exit_failure(s, 1, "Room already exist", 1);
		tmp = tmp->collision_next;
	}
	if (ft_strcmp(key, tmp->room->name) == 0)
		exit_failure(s, 1, "Room already exist", 1);
	if (!(tmp->collision_next = malloc(sizeof(t_hashmap))))
		exit_failure(s, 1, "Can't malloc tmp->collision_next", 0);
	tmp = tmp->collision_next;
	tmp->collision_next = NULL;
	return (init_room(s, tmp, key));
}

void	add_room(t_lem_in *s, char *line)
{
	info_push_back(s, create_info(s, line));
	place_room(s, line, hash_to_int(line));
	s->nb_room++;
	if (s->nb_room >= SSIZE_T_MAX - 2)
		exit_failure(s, 123, "Too many rooms", 0);
}

void			read_tip(t_lem_in *s, ssize_t *tip)
{
	char	*line;

	if (*tip != -1)
		exit_failure(s, 1, "Tip already read", 1);
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			info_push_back(s, create_info(s, line));
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
				exit_failure(s, 1, "Two ##star/end command for the same room", 1); 
		}
		else if (is_room(line))
		{
			*tip = s->nb_room;
			add_room(s, line);
			break;
		}
		else
		{
			free(line);
			exit_failure(s, 1, "Invalid/already exist room after ##start/end command", 1);
		}
	}
}

t_room		*find_room(t_lem_in *s, char *key, size_t index)
{
	t_hashmap	*tmp;

	if (!s->hmap[index])
		return (NULL);
	tmp = s->hmap[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->room->name, key) == 0)
			return (tmp->room);
		tmp = tmp->collision_next;
	}
	return (NULL);
}

void			read_link(t_lem_in *s, char *line)
{
	if (!line || s->start == -1 || s->end == -1 || is_link(s, line) == 0)
	{
		ft_printf("line ; %s\n", line);
		free(line);
		exit_failure(s, 1, "Not enought viable info", 1);
	}
	s->i_pipe = s->i_curr;
	while (get_next_line(0, &line) > 0)
	{
		if (is_link(s, line) == 0)
		{
			free(line);
			return ;
		}
	}
}

char			*read_room(t_lem_in *s)
{
	char	*line;

	s->nb_room = 0;
	s->start = -1;
	s->end = -1;
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			info_push_back(s, create_info(s, line));
			if (ft_strcmp("##start", line) == 0)
				read_tip(s, &s->start);
			else if (ft_strcmp("##end", line) == 0)
				read_tip(s, &s->end);
		}
		else if (is_room(line))
			add_room(s, line);
		else
			return (line);
	}
	return (NULL);
}

void	info_push_back(t_lem_in *s, t_info *to_add)
{
	if (s->info == NULL)
	{
		s->info = to_add;
		s->i_curr = to_add;
	}
	else
	{
		s->i_curr->i_next = to_add;
		s->i_curr = s->i_curr->i_next;
	}
}

void	init_info(t_info *new, char *str)
{
	new->str = str;
	new->i_next = NULL;
}

t_info	*create_info(t_lem_in *s, char *str)
{
	t_info	*new;

	if (!(new = malloc(sizeof(t_info))))
	{
		free(str);
		exit_failure(s, 1, "Can't malloc t_info new", 0);
	}
	init_info(new, str);
	return (new);
}

void	read_ant_nb(t_lem_in *s)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			info_push_back(s, create_info(s, line));
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
				exit_failure(s, 0, "\nNo/invalid ant nbr", 1);
		}
		else if (str_is_numeric_no_symbol(line) && *line != '0')
		{
			s->nb_ant = atou(line);
			free(line);
			if (s->nb_ant == 0)
				exit_failure(s, 0, "\nToo many ants (overflow)", 1);
			return ;
		}
		else
		{
			free(line);
			exit_failure(s, 0, "\nNo/invalid ant nbr", 1);
		}
	}
	exit_failure(s, 0, "\nNo ant nbr", 1);
}

void	init_struct(t_lem_in *s)
{
	s->info = NULL;
	init_hmap(s);
}

void		print_stab(ssize_t *tab, size_t size, char *msg)
{
	size_t i;

	i = 0;
	ft_printf("%s\n", msg);
	while (i < size)
		ft_printf("%d ", tab[i++]);
	ft_printf("\n");	
}

void			add_link(t_lem_in *s, ssize_t index1, ssize_t index2)
{
	size_t	i;

	if (index1 == index2)
		return ;
	i = 0;
	while (s->room_tab[index1].link[i] != -1 && i < s->room_tab[index1].nb_link )
	{
		if (s->room_tab[index1].link[i] == index2)
		{
			s->room_tab[index1].nb_link--;
			s->room_tab[index2].nb_link--;
			return ;
		}
		i++;
	}
	s->room_tab[index1].link_rm = s->room_tab[index1].nb_link; //peut être un peu trop répétitif
	s->room_tab[index2].link_rm = s->room_tab[index2].nb_link; 
	s->room_tab[index1].link[i] = index2;
	s->room_tab[index1].prio[i] = ALL;
	i = 0;
	while (s->room_tab[index2].link[i] != -1 && i < s->room_tab[index2].nb_link)
		i++;
	s->room_tab[index2].link[i] = index1;
	s->room_tab[index2].prio[i] = ALL;
}

void			write_link(t_lem_in *s)
{
	ssize_t	index1;
	ssize_t	index2;
	size_t	i;
	t_room	*tmp;

	s->i_curr = s->i_pipe;
	while (s->i_curr != NULL)
	{
		i = 0;
		while (s->i_curr->str[0] == '#')
		{
			if (s->i_curr->i_next == NULL)
				return;
			s->i_curr = s->i_curr->i_next;
		}
		while (s->i_curr->str[i] != '\0')
			i++;
		tmp = find_room(s, s->i_curr->str, hash_to_int(s->i_curr->str));
		index1 = tmp->index;
		i += 1;
		tmp = find_room(s, s->i_curr->str + i, hash_to_int(s->i_curr->str + i));
		index2 = tmp->index;
		add_link(s, index1, index2);
		s->i_curr = s->i_curr->i_next;
	}
}

void	write_room2(t_lem_in *s, t_hashmap *tmp, size_t i)
{
	ssize_t	j;
	size_t	k;

	while (tmp)
	{
		j = tmp->room->index;
		s->room_tab[j] = *(tmp->room); /* copy of the room from hmap to tab */
		free(tmp->room);
		if (s->room_tab[j].nb_link > 0)
		{
			if (!(s->room_tab[j].link
				= malloc(sizeof(ssize_t) * s->room_tab[j].nb_link)))
				clear_the_mess(s, i, tmp);
			if (!(s->room_tab[j].prio 
				= malloc(sizeof(signed char) * s->room_tab[j].nb_link)))
				clear_the_mess(s, i, tmp);
			k = 0;
			while (k < s->room_tab[j].nb_link)
			{
				s->room_tab[j].prio[k] = DEL;
				s->room_tab[j].link[k] = -1;
				k++;
			}
		}
		tmp->room = &s->room_tab[j]; /* relink of the room to the hmap */
		tmp = tmp->collision_next;
	}
}

void	write_room(t_lem_in *s)
{
	size_t	i;

	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
		exit_failure(s, 1, "Malloc error room_tab", 0);
	i = 0;
	while (i < MAP_SIZE)
	{
		write_room2(s, s->hmap[i], i);
		i++;
	}
}

void	clear_map(t_lem_in *s)
{
	size_t	i;
	t_hashmap	*tmp;
	t_hashmap	*tmp1;

	i = 0;
	while (i < MAP_SIZE)
	{
		tmp = s->hmap[i];
		while (tmp)
		{
			tmp1 = tmp->collision_next;
			free(tmp);
			tmp = tmp1;
		}
		i++;
	}
}

// void		create_path(t_lem_in *s, t_path *new, size_t malloc_size)
// {
// 	if (!(new->on_p = malloc(sizeof(unsigned char) * s->on_size)))
// 		exit_failure(s, 123, "can't malloc on_p", 0);
// 	if (!(new->node = malloc(sizeof(ssize_t) * malloc_size)))
// 		exit_failure(s, 2, "can't malloc path tab", 0);
// 	new->max_pos = malloc_size - 1;
// }

unsigned char	binary_pow_2(unsigned char index)
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

/* return 1 if added, 0 if already there */
unsigned char	add_on(unsigned char *on, size_t to_add)
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

void	delete_link(t_lem_in *s, t_room *room_tab, ssize_t *link, ssize_t i)
{
	ssize_t	j;
	ssize_t	k;

	room_tab[i].link_rm = 0;
	j = 0;
	while (link[j] == -2)
		j++;
	j = link[j];
	room_tab[j].link_rm--;	
	if (room_tab[j].link_rm > 0)
	{
		k = 0;
		while (room_tab[j].link[k] != i)
			k++;
		room_tab[j].link[k] = -2;
		room_tab[j].prio[k] = DEL;
		if (room_tab[j].link_rm == 1 && j != s->start && j != s->end)
			return (delete_link(s, room_tab, room_tab[j].link, j));
	}
}

void	hunt_deadend(t_lem_in *s, ssize_t start, ssize_t end, t_room *room_tab)
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

void		mark_linked_to_end(t_lem_in *s)
{
	size_t	i;

	i = 0;
	while (i < s->room_tab[s->end].nb_link)
	{
		if (s->room_tab[s->end].link[i] != -2
			&& s->room_tab[s->end].link[i] != s->start)
			s->room_tab[s->room_tab[s->end].link[i]].link_to_end = 1;
		i++;
	}
}

void		init_algo(t_lem_in *s)
{
	clear_map(s);
	s->on_size = (s->nb_room / 8) + 1;
	//queu init ...
	if (!(s->queu = malloc(sizeof(size_t) * s->nb_room * s->nb_room)))
		exit_failure(s, 123, "can't malloc queu", 0);
	s->room_tab[s->start].cost = 0;
	if (!(s->on_q = malloc(sizeof(unsigned char) * s->on_size)))
		exit_failure(s, 123, "can't malloc on_queu", 0);
	ft_bzero(s->on_q, s->on_size);
	hunt_deadend(s, s->start, s->end, s->room_tab);
	if (s->room_tab[s->start].link_rm < 1 || s->room_tab[s->end].link_rm < 1)
		exit_failure(s, 123, "No path from start to end", 1);
	mark_linked_to_end(s);
}

// void		find_path(t_lem_in *s, ssize_t *link, size_t nb_link, ssize_t node_in_queu)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	w_last;
// 	t_path	*tmp;

// 	w_last = s->w_last;
// 	tmp = s->way;
// 	i = 0;
// 	while (i <= w_last)
// 	{
// 		if (tmp[i].node[tmp[i].n_last] == node_in_queu)
// 		{
// 			j = 0;
// 			while (j < nb_link)
// 			{
// 				if (link[j] != -2)
// 					copy_path(s, link[j], &tmp[i], node_in_queu);
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// }

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

void		realloc_path_tab(t_lem_in *s, t_path *path, size_t size)
{
	t_path	*new;
	size_t	i;

	if (!(new = malloc(sizeof(t_path) * size)))
		exit_failure(s, 2, "can't malloc *way", 0);
	i = 0;
	while (i < s->w_last)
	{
		new[i] = path[i];
		i++;
	}
	free(s->way);
	s->way = new;
	s->w_size = size;
}

unsigned char	remove_on(unsigned char *on, size_t to_remove)
{
	size_t			on_index;
	unsigned char	compare;

	on_index = to_remove / 8;
	compare = binary_pow_2(to_remove % 8);
	on[on_index] -= compare;
	return (1);
}

// void		duplicate_path(t_lem_in *s, size_t to_add, t_path *tmp)
// {
// 	ssize_t	i;

// 	s->w_last++;
// 	if (s->w_last >= s->w_size)
// 		realloc_path_tab(s, s->way, s->w_last * s->w_last + 2);
// 	create_path(s, &s->way[s->w_last], tmp->max_pos + 2);
// 	i = 0;
// 	while (i < tmp->n_last)
// 	{
// 		s->way[s->w_last].node[i] = tmp->node[i];
// 		if ((size_t)i < s->on_size)
// 			s->way[s->w_last].on_p[i] = tmp->on_p[i];
// 		i++;
// 	}
// 	s->way[s->w_last].node[i] = to_add;
// 	while ((size_t)i < s->on_size)
// 	{
// 		s->way[s->w_last].on_p[i] = tmp->on_p[i];
// 		i++;
// 	}
// 	remove_on(s->way[s->w_last].on_p, tmp->node[tmp->n_last]);
// 	remove_on(tmp->on_p, to_add);
// 	s->way[s->w_last].n_last = tmp->n_last;
// }

// void	realloc_path(t_lem_in *s, t_path *path, size_t malloc_size)
// {
// 	ssize_t	*new;
// 	ssize_t	i;

// 	if (!(new = malloc(sizeof(ssize_t) * malloc_size)))
// 		exit_failure(s, 2, "can't malloc path tab", 0);
// 	i = 0;
// 	while (i <= path->n_last)
// 	{
// 		new[i] = path->node[i];
// 		i++;
// 	}
// 	free(path->node);
// 	path->node = new;
// 	path->max_pos = malloc_size - 1;
// }

// void		copy_path(t_lem_in *s, size_t to_add, t_path *way, ssize_t node_in_queu)
// {
// 	if (add_on(way->on_p, to_add))
// 	{
// 		if (node_in_queu == way->node[way->n_last])
// 		{
// 			if (way->n_last == way->max_pos)
// 				realloc_path(s, way, way->max_pos * 2 + 2);
// 			way->n_last++;
// 			way->node[way->n_last] = to_add;
// 		}
// 		else		
// 			duplicate_path(s, to_add, way);
// 	}
// }

// void		find_path_to_add_end(t_lem_in *s, ssize_t node_in_queu)
// {
// 	size_t	i;
// 	size_t	w_last;
// 	t_path	*way;

// 	w_last = s->w_last;
// 	way = s->way;
// 	i = 0;
// 	while (i <= w_last)
// 	{
// 		if (way[i].node[way[i].n_last] == node_in_queu)
// 			copy_path(s, s->end, &way[i], node_in_queu);
// 		i++;
// 	}
// }

// void	print_way(t_lem_in *s)
// {
// 	ssize_t	i;
// 	size_t	j;
// 	size_t	total;

// 	total = 0;
// 	j = 0;
// 	while (j <= s->w_last)
// 	{
// 		i = 0;
// 		ft_printf("[blue]path[%d] = ", j);
// 		while (i <= s->way[j].n_last)
// 			ft_printf("%s ", s->room_tab[s->way[j].node[i++]].name);
// 		total++;
// 		ft_printf("\n");
// 		j++;
// 	}
// 	ft_printf("Total way = %d[a_reset]\n", total);
// 	ft_printf("End room = %s\n", s->room_tab[s->end].name);
// }

void	u_swap(size_t *a, size_t *b)
{
	size_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	bubble_sort_node(size_t *arr, ssize_t *node, size_t n) 
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

void	get_prev_ant(t_lem_in *s, ssize_t cur, char *run)
{
	if (s->room_tab[cur].prev != -1)
	{
		s->room_tab[cur].ant = s->room_tab[s->room_tab[cur].prev].ant;
		if (s->room_tab[cur].ant != 0)
		{
			if (*run)
				ft_printf(" ");
			ft_printf("L%zu-%s", s->room_tab[cur].ant, s->room_tab[cur].name);
			*run = 1;
		}
		return (get_prev_ant(s, s->room_tab[cur].prev, run));
	}
}

void	move_ant(t_lem_in *s, size_t *path, ssize_t *node, size_t size)
{
	size_t	i;
	char	run;
	size_t	ant;

	run = 1;
	ant = 1;
	while (run)
	{
		run = 0;
		i = 0;
		while (i < s->room_tab[s->end].nb_link)
		{
			if (s->room_tab[s->end].prio[i] == PRIO)
			{
				if (s->room_tab[s->room_tab[s->end].link[i]].ant != 0)
				{
					if (run)
						ft_printf(" ");
					run = 1;
					ft_printf("L%zu-%s", s->room_tab[s->room_tab[s->end].link[i]].ant, s->room_tab[s->end].name);
				}
				get_prev_ant(s, s->room_tab[s->end].link[i], &run);
			}
			i++;
		}
		i = 0;
		while (i < size)
		{
			if (path[i] > 0)
			{
				if (run)
					ft_printf(" ");
				path[i]--;
				s->room_tab[node[i]].ant = ant;
				ft_printf("L%zu-%s", ant, s->room_tab[node[i]].name);
				ant++;
				run = 1;
			}
			else
				s->room_tab[node[i]].ant = 0;
			i++;
		}
		if (run)
			ft_printf("\n");
	}
	free(path);
	free(node);
}

size_t	get_size_path_prev(t_lem_in *s, size_t act_path)
{
	ssize_t	i;
	size_t	j;
	size_t	ret;

	i = s->room_tab[act_path].index;
	ret = 1;
	while (i != s->end)
	{
		j = 0;
		while (s->room_tab[i].prio[j] != LOCK)
			j++;
		s->room_tab[s->room_tab[i].link[j]].prev = s->room_tab[i].index;
		ret++;
		i = s->room_tab[i].link[j];
	}
	return (ret);
}

size_t	*get_ant(size_t nb_ant, size_t *path, size_t size)
{
	size_t i;
	size_t ret;
	size_t	j;
	size_t *ant_tab;

	i = 0;
	ret = 0;
	if (!(ant_tab = malloc(sizeof(size_t) * size)))
		return (NULL);
	while (i < size)
	{
		ant_tab[i] = 0;
		i++;
	}
	i = 0;
	while (i < size - 1 && nb_ant > ret && nb_ant > 0)
	{
		j = 0;
		ret = path[i + 1] - path[i];
		while (ret > nb_ant)
			ret--;
		while (j < i + 1 && nb_ant > 0 && nb_ant > ret)
		{
			ant_tab[j] += ret;
			nb_ant -= ret;
			j++;
		}
		i++;
	}
	while (nb_ant > 0)
	{
		i = 0;
		while (i < size && nb_ant > 0)
		{
			ant_tab[i]++;
			nb_ant--;
			i++;
		}
	}
	if (ant_tab[size - 1] == 0)
		return(NULL);
	return (ant_tab);
}

void	print_ant(t_lem_in *s)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	*path;
	ssize_t	*node;

	i = 0;
	size = 0;
	while (i < s->room_tab[s->start].nb_link)
	{
		if (s->room_tab[s->start].prio[i] == LOCK)
			size++;
		i++;
	}
	if (!(path = malloc(sizeof(size_t) * size)))
		exit_failure(s, 123, "cant malloc path_turn", 123);
	if (!(node = malloc(sizeof(size_t) * size)))
		exit_failure(s, 123, "cant malloc path_turn", 123);
	i = 0;
	j = 0;
	while (i < size)
	{
		while (s->room_tab[s->start].prio[j] != LOCK)
			j++;
		node[i] = s->room_tab[s->start].link[j];
		path[i] = get_size_path_prev(s, s->room_tab[s->start].link[j]);
		j++;
		i++;
	}
	bubble_sort_node(path, node, size);
	move_ant(s, get_ant(s->nb_ant, path, size), node, size);
	free(path);
}

char	search_for_all(t_lem_in *s, t_room *room, t_room *tab)
{
	size_t	i;
	char	all_found;

	i = 0;
	all_found = 0;
	while (i < room->nb_link)
	{
		if (room->prio[i] == ALL) 
		{
			if (room->cost + 1 < tab[room->link[i]].cost)
			{
				all_found = 1;
				if (room->link[i] != s->end)
				{
					s->q_last++;
					s->queu[s->q_last] = room->link[i];
				}
				tab[room->link[i]].cost = room->cost + 1;
				tab[room->link[i]].prev = room->index;
			}
		}
		i++;
	}
	return (all_found);
}

void	ascend_case(t_lem_in *s, t_room *room, t_room *tab)
{
	size_t	i;

	i = 0;
	room->ascend = 0;
	if (!search_for_all(s, room, tab))
		while (i < room->nb_link)
		{
			if (room->prio[i] == PRIO)
			{
				if (room->cost + 1 < tab[room->link[i]].cost)
				{
					if (room->link[i] != s->end)
					{
						s->q_last++;
						s->queu[s->q_last] = room->link[i];
					}
					tab[room->link[i]].cost = room->cost + 1;
					tab[room->link[i]].prev = room->index;
					tab[room->link[i]].ascend = 1;
				}
				return;
			}
			i++;
		}
}

void	normal_case(t_lem_in *s, t_room *room, t_room *tab)
{
	size_t	i;

	i = 0;
	while (i < room->nb_link)
	{
		if (room->prio[i] == PRIO)
		{
			if (room->cost + 1 < tab[room->link[i]].cost)
			{
				if (room->link[i] != s->end)
				{
					s->q_last++;
					s->queu[s->q_last] = room->link[i];
				}
				tab[room->link[i]].cost = room->cost + 1;
				tab[room->link[i]].prev = room->index;
				tab[room->link[i]].ascend = 1;
			}
			return;
		}
		i++;
	}
	search_for_all(s, room, tab);
}

void	reset_map(t_lem_in *s)
{
	ssize_t	i;

	i = 0;
	while (i < s->nb_room)
	{
		s->room_tab[i].ascend = 0;
		s->room_tab[i].cost = SIZE_T_MAX;
		s->room_tab[i].prev = -1;
		i++;
	}
	s->room_tab[s->start].cost = 0;
}

void	edit_link(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = s->end;
	while (i != s->start)
	{
		j = 0;
		while (s->room_tab[i].prev != s->room_tab[i].link[j])
			j++;
		if (s->room_tab[i].prio[j] == ALL)
		{
			s->room_tab[i].prio[j] = PRIO;
			j = 0;
			while (s->room_tab[s->room_tab[i].prev].link[j] != i)
				j++;
			s->room_tab[s->room_tab[i].prev].prio[j] = LOCK;
		}
		else
		{
			s->room_tab[i].prio[j] = ALL;
			j = 0;
			while (s->room_tab[s->room_tab[i].prev].link[j] != i)
				j++;
			s->room_tab[s->room_tab[i].prev].prio[j] = ALL;
		}
		i = s->room_tab[i].prev;
	}
}

size_t	check_ledit(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = s->end;
	while (i != s->start)
	{
		j = 0;
		if (s->room_tab[i].prev == -1)
		{
			ft_printf("leave -1\n");
			return (0);
		}
		while (s->room_tab[i].prev != s->room_tab[i].link[j])
			j++;
		if (add_on(s->on_q, s->room_tab[i].link[j]) == 0)
		{
			ft_printf("leave boucle\n");
			return (0);
		}
		i = s->room_tab[i].prev;
	}
	return (1);
}

size_t	get_size_path(t_lem_in *s, size_t act_path)
{
	ssize_t	i;
	size_t	j;
	size_t	ret;

	i = s->room_tab[act_path].index;
	ret = 1;
	while (i != s->end)
	{
		j = 0;
		while (s->room_tab[i].prio[j] != LOCK)
			j++;
		ret++;
		i = s->room_tab[i].link[j];
	}
	return (ret);
}


size_t	count_turn(size_t nb_ant, size_t *path, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ret;
	size_t	*ant_tab;

	i = 0;
	j = 0;
	ret = 0;
	if ((ant_tab = get_ant(nb_ant, path, size)) == NULL)
		return(INT32_MAX);
	while (i < size)
	{
		path[i] += ant_tab[i] - 1;
		i++;
	}
	i = 0;
	ret = 0;
	while (i < size) /* chercher + grand nbr de tours parmis les paths */
	{
		if (path[i] > ret)
			ret = path[i];
		i++;
	}
	free(path);
	return (ret);
}

void	bubbleSort(size_t *arr, size_t n) 
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
				u_swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

size_t	count_path(t_lem_in *s)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	*path;

	i = 0;
	size = 0;
	while (i < s->room_tab[s->start].nb_link)
	{
		if (s->room_tab[s->start].prio[i] == LOCK)
			size++;
		i++;
	}
	if (!(path = malloc(sizeof(size_t) * size)))
		exit_failure(s, 123, "cant malloc path_turn", 123);
	i = 0;
	j = 0;
	while (i < size)
	{
		while (s->room_tab[s->start].prio[j] != LOCK)
			j++;
		path[i] = get_size_path(s, s->room_tab[s->start].link[j]);
		j++;
		i++;
	}
	bubbleSort(path, size);
	return (count_turn(s->nb_ant, path, size));
}

void		bfs(t_lem_in *s)
{
	t_room	*tab;
	size_t	cur;

	cur = 0;
	s->queu[0] = s->start;
	s->q_last = 0;
	// s->q_overflow = 0;
	tab = s->room_tab;
	while (cur <= s->q_last /*|| s->q_overflow == 1*/)
	{
		if (tab[s->queu[cur]].ascend)
			ascend_case(s, &tab[s->queu[cur]], tab);
		else
			normal_case(s, &tab[s->queu[cur]], tab);
		cur++;
	}
		// if (s->q_overflow == 1 && cur == s->nb_room)
		// {
		// 	s->q_overflow = 0;
		// 	cur = 0;
		// }
	//}
}

void	return_to_the_future(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = s->end;
	while (i != s->start)
	{
		j = 0;
		while (s->room_tab[i].prev != s->room_tab[i].link[j])
			j++;
		if (s->room_tab[i].prio[j] == PRIO)
		{
			s->room_tab[i].prio[j] = ALL;
			j = 0;
			while (s->room_tab[s->room_tab[i].prev].link[j] != i)
				j++;
			s->room_tab[s->room_tab[i].prev].prio[j] = ALL;
		}
		else
		{
			s->room_tab[i].prio[j] = LOCK;
			j = 0;
			while (s->room_tab[s->room_tab[i].prev].link[j] != i)
				j++;
			s->room_tab[s->room_tab[i].prev].prio[j] = PRIO;
		}
		i = s->room_tab[i].prev;
	}
}

void	retrace_path(t_lem_in *s, size_t node, size_t *path_size)
{
	size_t i;

	i = 0;
	(*path_size)++;
	while (i < s->room_tab[node].nb_link)
	{
		if (s->room_tab[node].prio[i] == LOCK)
			return (retrace_path(s, s->room_tab[node].link[i], path_size));
		i++;
	}
}

void	print_path(t_lem_in *s)
{
	size_t i;
	size_t	path_size;

	i = 0;
	while (i < s->room_tab[s->start].nb_link)
	{
		path_size = 1;
		if (s->room_tab[s->start].prio[i] == LOCK)
		{
			ft_printf("%s ", s->room_tab[s->start].name);
			retrace_path(s, s->room_tab[s->start].link[i], &path_size);
			ft_printf("   %zu \n", path_size);
		}
		i++;
	}
}

void		algo(t_lem_in *s)
{
	size_t	new_nb_turn;
	size_t	nb_turn;

	nb_turn = SIZE_T_MAX;
	init_algo(s);
	while(1)
	{
		bfs(s);
		if (check_ledit(s) == 0)
			break;
		edit_link(s);
		ft_bzero(s->on_q, s->on_size);
		if ((new_nb_turn = count_path(s)) >= nb_turn) /* > || >= ? */
		{
			return_to_the_future(s);
			break;
		}
		nb_turn = new_nb_turn;
		reset_map(s);
	}
	ft_bzero(s->on_q, s->on_size);
	print_ant(s);
}

int	main(void)
{
	t_lem_in	s;

	if (MAP_SIZE < 1 || MAP_SIZE >= SSIZE_T_MAX)
		return (EXIT_FAILURE);
	init_struct(&s);
	read_ant_nb(&s);
	read_link(&s, read_room(&s));
	write_room(&s);
	write_link(&s);
	algo(&s);
}