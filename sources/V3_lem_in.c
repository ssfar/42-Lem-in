/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V3_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:51:48 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/14 17:44:17 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

//			 \ / 		 //
// 			\(")/		 //
// 			-( )-		 // 
// 			/( )\		 //

void	clear_data_tab(t_lem_in *s)
{
	size_t i;

	i = 0;
	while (i < MAP_SIZE)
	{
		free(s->room_tab[i].link);
		i++;
	}
	free(s->room_tab);
}

void	clear_map_room(t_lem_in *s)
{
	t_table *tmp;
	size_t	i;

	i = 0;
	while (i < s->nb_room)
	{
		while (s->map[i] != NULL)
		{
			tmp = s->map[i];
			free(tmp->room);
			free(tmp);
			s->map[i] = s->map[i]->t_next;
		}
		i++;
	}
}

void	clear_map(t_lem_in *s)
{
	size_t	i;
	t_table	*tmp;

	i = 0;
	while (i < s->nb_room)
	{
		while (s->map[i] != NULL)
		{
			tmp = s->map[i];
			free(tmp);
			s->map[i] = s->map[i]->t_next;
		}
		i++;
	}
}

void	exit_failure(t_lem_in *s, size_t id, char *message)
{
	if (id >= 0)
		clear_info(s->info);
	if (id == 1)
		clear_map_room(s);
	if (id == 2 || id == 3)
		clear_data_tab(s);
	if (id == 3)
		clear_map(s);
	ft_printf("[red]%s[a_reset]\n", message);
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
}

void			read_tip(t_lem_in *s, ssize_t *tip)
{
	char	*line;

	if (*tip != -1) 
		exit_failure(s, 1, "Tip already read");
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			{
				free(line);
				exit_failure(s, 1, "Two ##star/end command for the same room"); 
			}
			info_push_back(s, create_info(line));
		}
		else if (is_room(line))
		{
			place_room(s, line, hash_to_int(line));
			info_push_back(s, create_info(line));
			*tip = s->nb_room++;
			break;
		}
		else
		{
			free(line);
			exit_failure(s, 1, "Invalid/already exist room after ##start/end command");
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
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			{
				free(line);
				exit_failure(s, 0, "\nNo/invalid ant nbr");
			}
			info_push_back(s, create_info(line));
		}
		else if (str_is_numeric_no_symbol(line) && *line != '0')
		{
			s->ant = atou(line);
			return (free(line));
		}
		else
		{
			free(line);
			exit_failure(s, 0, "\nNo/invalid ant nbr");
		}
	}
	exit_failure(s, 0, "\nNo/invalid ant nbr");
}

void			init_struct(t_lem_in *s)
{
	s->info = NULL;
	s->i_current = NULL;
	s->start = -1;
	s->end = -1;
	s->nb_room = 0;
	s->room_tab = NULL;
	init_map(s);
}

int				main(void)
{
	t_lem_in	s;

	if (MAP_SIZE < 1)
		return (EXIT_FAILURE);
	init_struct(&s);
	read_ant_nb(&s);
	read_link(&s, read_room(&s));
	clear_map(&s);
	write_room(&s);
	write_link(&s);
	

	// print_info(&s);
	// print_ant(s.ant);
	// print_datatab(&s);
	// print_map(&s);
	//if (!(s.room_tab = (t_room*)malloc(sizeof(t_room) * s.nb_room)))
	//	return (EXIT_FAILURE);
	//write_room(&s);
	//write_link(s);
}