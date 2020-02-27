/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V3_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:51:48 by ssfar             #+#    #+#             */
/*   Updated: 2020/02/27 18:28:36 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

//			 \ / 		 //
// 			\(")/		 //
// 			-( )-		 // 
// 			/( )\		 //



void	exit_failure(t_lem_in *s, uint_fast8_t id, char *message, uint_fast8_t error)
{
	ft_printf("[red]%s[a_reset]\n", message);
	clear_info(s->info);
	if (id == 1)
		clear_map_room(s);
	if (id == 2)
		clear_room_tab(s);
	if (error)
		ft_printf("ERROR");
	exit(EXIT_FAILURE);
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
			info_push_back(s, create_info(s, line));
			place_room(s, line, hash_to_int(line));
			*tip = s->nb_room++;
			if (s->nb_room < 1)
				exit_failure(s, 123, "Too many rooms", 0);
			break;
		}
		else
		{
			free(line);
			exit_failure(s, 1, "Invalid/already exist room after ##start/end command", 1);
		}
	}
}

void			read_ant_nb(t_lem_in *s)
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
			s->ant = atou(line);
			return (free(line));
		}
		else
		{
			free(line);
			exit_failure(s, 0, "\nNo/invalid ant nbr", 1);
		}
	}
	exit_failure(s, 0, "\nNo/invalid ant nbr", 1);
}

void			init_struct(t_lem_in *s)
{
	s->info = NULL;
	s->i_current = NULL;
	s->start = -1;
	s->end = -1;
	s->nb_room = 0;
	s->room_tab = NULL;
	s->res = NULL;
	init_map(s);
}

int		check_visited(ssize_t *visited, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (visited[i] != -1)
			return (0);
		i++;
	}
	return (1);
}

void	edit_cost(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;
	ssize_t	*visited;

	i = 0;
	visited = malloc(sizeof(ssize_t) * s->nb_room + 1);
	while (i < s->nb_room)
	{
		visited[i] = s->room_tab[i].index;
		i++;
	}
	i = s->start;
	j = 0;
	while (check_visited(visited, s->nb_room) != -1 && i < s->nb_room)
	{
		j = 0;
		while (j < s->room_tab[i].nb_link)
		{
			if (s->room_tab[i].cost + 1 < s->room_tab[s->room_tab[i].link[j]].cost)
				s->room_tab[s->room_tab[i].link[j]].cost = s->room_tab[i].cost + 1;
			j++;
		}
		i++;
	}
	visited[i] = -1;
}

int				main(void)
{
	t_lem_in	s;

	if (MAP_SIZE < 1 || PATH_SIZE < 1)
		return (EXIT_FAILURE);
	init_struct(&s);
	read_ant_nb(&s);
	read_link(&s, read_room(&s));
	write_room(&s);	
	write_link(&s);
	// print_ant(s.ant);
	// print_datatab(&s);
	// print_map(&s);
	s.room_tab[s.start].cost = 0;
	edit_cost(&s);
	algo(&s);
}