/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:57:42 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/09 17:28:56 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_failure(t_lem_in *l, size_t id, char *message)
{
	if (id >= 1)
	room_clear(l->first);
	if (id >= 2)
		tube_clear(l->tube);
	ft_printf("%s\n", message);
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
}

// connexion possible ici si les deux room sont trouve

uint_fast8_t	is_tube(char *line, t_lem_in *l)
{
	size_t i;
	size_t mid;
	t_room *tmp1;
	t_room *tmp2;

	i = 0;
	if (line[0] == '#')
		return (1);
	if (line[0] == 'L' || line[0] == ' ' || line[0] == '-')
		return (0);
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] != '-' || !(tmp1 = get_room(line, l)))
		return (0);
	i++;
	mid = i;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] != '\0' || !(tmp2 = get_room(line + mid, l)))
		return (0);
	link_push_back(tmp1, create_link(tmp2));
	link_push_back(tmp2, create_link(tmp1));
	return (1);
}

void	read_tube(t_lem_in *l, char *line)
{
	if (is_tube(line, l) == 0)
	{
		free(line);
		return ;
	}
	l->tube = create_tube(line);
	while (get_next_line(0, &line) > 0)
	{
		if (is_tube(line, l) == 0)
			return (free(line));
		tube_push_back(l->tube, create_tube(line));
	}
	return ;
}

uint_fast8_t	is_room2(char *line, size_t	i)
{
	if (i != 0 && line[i++] == ' ')
	{
		if (line[i] == '-')
			i++;
		if (ft_isdigit(line[i++]))
		{
			while (ft_isdigit(line[i]))
				i++;
			if (line[i++] == ' ')
			{
				if (line[i] == '-')
					i++;
				if (ft_isdigit(line[i++]))
				{
					while (ft_isdigit(line[i]))
						i++;
					return (line[i] ? 0 : 1);
				}
			}
		}
	}
	return (0);
}

uint_fast8_t	is_room(char *line)
{
	size_t	i;

	if (!line || *line == 'L' || *line == '#')
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-')
			return (0);
		i++;
	}
	return (is_room2(line, i));
}

void	init_struct(t_lem_in *l)
{
	l->start = NULL;
	l->end = NULL;
	l->first = NULL;
	l->current = NULL;
}

void	get_tip(t_room **tip, t_lem_in *l)
{
	char	*line;

	line = NULL;
	if (*tip != NULL || get_next_line(0, &line) < 1 || *line == '#')
	{
		free(line);
		exit_failure(l, 1 , "Get tip");
	}
	room_push_back(l, create_room(line));
	*tip = l->current;
}

ssize_t	read_ant_nb(void)
{
	char	*line;
	ssize_t	ant;

	line = NULL;
	ant = 0;
	if (get_next_line(0, &line) <= 0)
		exit_failure(NULL, 0, "Ant nbr doens't exist");
	if (!str_is_numeric(line) || (ant = ft_atoi(line)) <= 0)
	{
		free(line);
		exit_failure(NULL, 0, "Ant nbr no valid");
	}
	free(line);
	return (ant);
}

char	*read_room(t_lem_in *l)
{
	char		*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (is_room(line))
		{
			if (get_room(line, l))
			{
				ft_printf(" line of error : %s\n", line);
				free(line);
				exit_failure(l, 1, "room already exist");
			}
			room_push_back(l, create_room(line));
		}
		else if ('#' == *line)
		{
			room_push_back(l, create_room(line));
			if (ft_strcmp("##start", line))
				get_tip(&l->start, l);
			else if (ft_strcmp("##end", line))
				get_tip(&l->end, l);
		}
		else
			break;
	}
	
	return (line);
}

uint_fast16_t	strcmp_before_charset(const char *s1, const char *s2, char *charset)
{
	size_t	i;
	size_t	y;

	if (s1 && s2 && charset)
	{
		i = 0;
		while (s1[i] && s2[i] && s1[i] == s2[i])
		{
			y = 0;
			while (charset[y])
			{
				if (s1[i] == charset[y])
					return (i ? s1[i - 1] - s2[i - 1] : s1[i] - s2[i]);
				y++;
			}
			i++;
		}
		return (s1[i] == '-' 
		? s1[i - 1] - s2[i - 1] : s1[i] - s2[i]);
	}
	if (s1)
		return (*s1);
	else if (s2)
		return (-(*s2));
	return (0);
}

uint_fast16_t	room_compare(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] && s2[i] && s1[i] == s2[i]
			&& (s1[i] != ' ' || s1[i] != '-'))
			i++;
		if ((s1[i] == '-' && s2[i] == ' ') || (s1[i] == ' ' && s2[i] == ' '))
			return (0);
		return (1);
	}
	return (1);
}

int	main(void)
{
	ft_printf("debut du prog\n");//
	t_lem_in	l;
	t_room *current;

	l.ant = read_ant_nb();
	ft_printf("ant %zd\n", l.ant);//
	read_tube(&l, read_room(&l));
	current = l.first; 
	print_room(current, "room");//
	current = l.first;
	print_tube(l.tube, "tube");
	print_link(current, "link");
}