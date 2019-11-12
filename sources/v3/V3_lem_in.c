/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V3_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:51:48 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/12 19:04:41 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

//			 \ / 		 //
// 			\(")/		 //
// 			-( )-		 // 
// 			/( )\		 //

void			write_link(t_lem_in *s) // pas finit
{
	size_t	i;
	size_t	j;
	ssize_t	index1;
	ssize_t	index2
	t_table	*tmp;

	index1 = 0;
	index2 = 0;
	while (s->pipe != NULL)
	{
		i = 0;
		while (s->pipe->str[0] = '#')
			s->pipe = s->pipe->next;
		while (s->pipe->str[i] != '-')
			i++;
		str[i] = '\0';
		tmp = find_table(s->map, str, hash_to_int(str));
		index1 = tmp->room->index;
		str[i] = '-';
		tmp = find_table(s->map, str + i, hash_to_int(str + i));
		index2 = tmp->room->index;
		// check les doublons && index1 != index2		
		// assigner les index dans le tab,
	}
}

void			write_room(t_lem_in *s)
{
	size_t	i;
	size_t	j;
	t_room	*tmp;

	i = 0;
	j = 0;
	while (i < MAP_SIZE)
	{
		tmp = map[i];
		while (tmp)
		{
			j = tmp->room->index;
			s->room_tab[j] = *(tmp->room);
			if (!(s->room_tab[j]->link 
				= malloc(sizeof(size_t) * s->room_tab[j]->nb_link)))
				return ;
			tmp->room = &room_tab[j];
			// free tmp->room ?
			tmp = tmp->next;
		}
		i++;
	}
}

uint_fast8_t	is_link2(t_lem_in *s, char *line, int i)
{
	size_t	mid;
	t_table	*tmp;
	
	mid = i;
	line[mid] = '-';
	++i;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] != '\0')
		return (0);
	if (!(tmp = find_table(s->map, line + mid, hash_to_int(line))))
		return (0);
	tmp.nb_link++;
	return (1);
}

uint_fast8_t	is_link(t_lem_in *s, char *line)
{
	size_t	i;
	t_table	*tmp;

	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return	(0);
	if (line[0] != '#')
	{
		if (!line[0] || line[0] == 'L' || line[0] == ' ' || line[0] == '-')
			return (0);
		i = 1;
		while (line[i] && line[i] != ' ' && line[i] != '-')
			i++;
		mid = i;
		if (line[i] != '-')
			return (0);
		line[i] = '\0';
		if (!(tmp = find_table(s->map, line, hash_to_int(line))))
			return (0);
		tmp.nb_link++;
		if (!is_link2(s, line, i))
			return (0);
	}
	info_push_back(s, create_info(line));
	return (1);
}

void			read_link(t_lem_in *s, char *line)
{
	if (is_link(s, line) == 0)
	{
		free(line);
		exit_failure(s, 123, "Not enought viable info");
	}
	s->pipe = s->current;
	while (get_next_line(0, &line))
	{
		if (is_link(s, line) == 0)
		{
			free(line);
			return ;
		}
	}
}

void			read_tip(t_lem_in *s, t_room **tip)
{
	char	*line;

	if (*tip)
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
			info_push_back(s, create_info(line));
		}
		else if (is_room(line))
		{
			*tip = place_room(s, line);
			info_push_back(s, create_info(line));
			s->nb_room++;
		}
		else
		{
			ft_printf("error line : |%s|\n", line);
			free(line);
			exit_failure(s, 1, "Invalid/already exist room after ##start/end command");
		}
	}
}

void	init_room(t_lem_in *s, t_table **tmp, char *name)
{
	(*tmp)->room = malloc(sizeof(t_room));
	(*tmp)->room->name = name;
	(*tmp)->room->index = s->nb_room;
	(*tmp)->room->nb_link = 0;
	(*tmp)->room->link = NULL;
}

t_room	*place_room(t_lem_in *s, char *key)
{
	size_t	index;
	t_table	*tmp;

	index = hash_to_int(key);
	tmp = &s->map[index];
	while (tmp->t_next)
	{
		if (ft_strcmp(key, tmp->room->name) == 0)
		{
			key[ft_strlen(key)] = ' ';
			free(key);
			exit_failure(s, 123, "Room already exist");
		}
		tmp = tmp->t_next;
	}
	if (tmp->room)
	{
		if (ft_strcmp(key, tmp->room->name) == 0)
		{
			key[ft_strlen(key)] = ' ';
			free(key);
			exit_failure(s, 123, "Room already exist");
		}
		tmp->t_next = malloc(sizeof(t_table));
		tmp->t_next = NULL;
		tmp = tmp->t_next;
	}
	init_room(s, &tmp, key);
	return (tmp->room);
}

uint_fast8_t	is_room(char *line)
{
	size_t	i;

	if (!line[0] || line[0] == ' ' || line[0] == 'L' || line[0] == '#')
		return (0);
	i = 1;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-')
			return (0);
		i++;
	}
	if (i == 0 || line[i] != ' ')
		return (0);
	if (is_room2(&line[i + 1]))
	{
		line[i] = '\0';
		return (1);
	}
	return (0);
}

uint_fast8_t	is_room2(char *line)
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
				if (*line)
					return (1);
			}
		}
	}
	return (0);
}

char			*read_room(t_lem_in *s)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if ('#' == *line)
		{
			info_push_back(s, create_info(line));
			if (ft_strcmp("##start", line) == 0)
				read_tip(&s->start, s);
			else if (ft_strcmp("##end", line) == 0)
				read_tip(&s->end, s);
		}
		else if (is_room(line))
		{
			place_room(s, line);
			info_push_back(s, create_info(line));
			s->nb_room++;
		}
		else
			return (line);
	}
	return (NULL);
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

void			init_map(t_lem_in *s)
{
	size_t	i;

	i = 0;
	while (i < MAP_SIZE)
	{
		s->map[i].room = NULL;
		s->map[i].t_next = NULL;
		i++;
	}
}

void			init_struct(t_lem_in *s)
{
	s->info = NULL;
	s->current = NULL;
	s->start = NULL;
	s->end = NULL;
	s->nb_room = 0;
	s->room_tab = NULL;
	init_map(s->map);
}

int				main(void)
{
	t_lem_in	s;

	init_struct(&s);
	read_ant_nb(&s);
	read_link(&s, read_room(&s));
	if (!(s.room_tab = (t_room*)malloc(sizeof(t_room) * s.nb_room)))
		return (EXIT_FAILURE);
	write_room(&s);
	//write_link(s);
}