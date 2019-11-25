/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V3_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:51:48 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/25 15:52:30 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

//			 \ / 		 //
// 			\(")/		 //
// 			-( )-		 // 
// 			/( )\		 //



void	exit_failure(t_lem_in *s, size_t id, char *message, uint_fast8_t error)
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
	init_map(s);
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
	// print_info(&s);
	// print_datatab(&s);
	// print_map(&s);
	algo(&s);
	//if (!(s.room_tab = (t_room*)malloc(sizeof(t_room) * s.nb_room)))
	//	return (EXIT_FAILURE);
	//print_way(&s);
	//print_max_way(&s);
}