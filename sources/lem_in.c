/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:57:42 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/11 15:24:36 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_failure(t_lem_in *s, size_t id, char *message)
{
	if (id >= 1)
	room_clear(s->first);
	if (id >= 2)
		tube_clear(s->tube);
	ft_printf("[red]%s[a_reset]\n", message);
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
}

void	init_struct(t_lem_in *s)
{
	s->start = NULL;
	s->end = NULL;
	s->first = NULL;
	s->current = NULL;
}

void	read_tip(t_room **tip, t_lem_in *s)
{
	char	*line;

	if (*tip != NULL)
		exit_failure(s, 1, "Tip already read");
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			{
				ft_printf("error line : |%s|\n", line);
				free(line);
				exit_failure(s, 1, "Two ##star/end command for the same room");
			}
			room_push_back(s, create_room(line));
		}
		else if (is_room(line) && !get_room(line, s))
		{
			room_push_back(s, create_room(line));
			*tip = s->current;
			return ;
		}
		else
		{
			ft_printf("error line : |%s|\n", line);
			free(line);
			exit_failure(s, 1, "Invalid/already exist room after ##start/end command");
		}
	}
	exit_failure(s, 1, "No room after ##star/end command");
}

void	read_ant_nb(t_lem_in *s)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			{
				free(line);
				exit_failure(s, 1, "\nNo/invalid ant nbr");
			}
			room_push_back(s, create_room(line));
		}
		else if (str_is_numeric_no_symbol(line) && *line != '0')
		{
			s->ant = atou(line);
			return (free(line));
		}
		else
		{
			free(line);
			exit_failure(s, 1, "\nNo/invalid ant nbr");
		}
	}
	exit_failure(s, 1, "\nNo/invalid ant nbr");
}

int	main(void)
{
	t_lem_in	s;
	t_room		*current;//

	read_ant_nb(&s);
	ft_printf("\n[black] \\ /\n");//
	ft_printf("\\[red]([white]\"[red])[black]/\n");//
	ft_printf("-[red]( )[black]-[a_bold][red] = %zd\n", s.ant);//
	ft_printf("[a_reset][black]/[red](_)[black]\\\n[a_reset]");//
	read_tube(&s, read_room(&s));
	if (!s.start->link || !s.end->link)
		exit_failure(&s, 2, "No valid path");
	current = s.first;//
	print_room(current, "|room|");//
	current = s.first;//
	print_tube(s.tube, "|tube|");//
	print_link(current, "|link|");//
}