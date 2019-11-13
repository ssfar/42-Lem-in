/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V3_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:51:48 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/13 18:37:20 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

//			 \ / 		 //
// 			\(")/		 //
// 			-( )-		 // 
// 			/( )\		 //

void			add_link(t_lem_in *s, ssize_t index1, ssize_t index2)
{
	size_t	i;

	if (index1 == index2)
		return ;
	i = 0;
	while (s->room_tab[index1].link[i] != -1)
	{
		if (s->room_tab[index1].link[i] == index2)
			return ;
		i++;
	}
	s->room_tab[index1].link[i] = index2;
	i = 0;
	while (s->room_tab[index2].link[i] != -1)
		i++;
	s->room_tab[index2].link[i] = index1;	
}

void			write_link(t_lem_in *s)
{
	ssize_t	index1;
	ssize_t	index2;
	size_t	i;
	t_room	*tmp;

	while (s->pipe != NULL)
	{
		i = 0;
		while (s->pipe->str[0] == '#')
			s->pipe = s->pipe->i_next;
		while (s->pipe->str[i] != '-')
			i++;
		s->pipe->str[i] = '\0';
		tmp = find_room(s, s->pipe->str, hash_to_int(s->pipe->str));
		index1 = tmp->index;
		s->pipe->str[i] = '-';
		i += 1;
		tmp = find_room(s, s->pipe->str + i, hash_to_int(s->pipe->str + i));
		index2 = tmp->index;
		add_link(s, index1, index2);
		s->pipe = s->pipe->i_next;
	}
}

void	write_room(t_lem_in *s)
{
	size_t	i;
	size_t	j;
	size_t k;
	t_table	*tmp;

	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
		exit_failure(s, 123, "Malloc error room_tab");
	i = 0;
	while (i < MAP_SIZE)
	{
		tmp = s->map[i];
		while (tmp)
		{
			j = tmp->room->index;
			s->room_tab[j] = *(tmp->room);
			free(tmp->room);
			if (!(s->room_tab[j].link = malloc(sizeof(ssize_t) * s->room_tab[j].nb_link)))
				exit_failure(s, 123, "Malloc error room_tab");
			k = 0;
			while(k < s->room_tab[j].nb_link)
				s->room_tab[j].link[k++] = -1;
			tmp->room = &s->room_tab[j];
			tmp = tmp->t_next;
		}
		i++;
	}
}

void	exit_failure(t_lem_in *s, size_t id, char *message)
{
	// if (id >= 1)
	// {
	// 	info_clear(s->info)
	// 	room_clear(s->first);
	// }
	// if (id >= 2)
	// 	tube_clear(s->tube);
	(void)s;
	(void)id;
	ft_printf("[red]%s[a_reset]\n", message);
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
}

uint_fast8_t	is_link2(t_lem_in *s, char *line, int i)
{
	size_t	mid;
	t_room	*tmp;

	mid = i;
	line[mid] = '-';
	++i;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] != '\0')
		return (0);
	if (!(tmp = find_room(s, line + mid + 1 , hash_to_int(line + mid + 1))))
		return (0);
	tmp->nb_link++;
	return (1);
}

uint_fast8_t	is_link(t_lem_in *s, char *line)
{
	size_t	i;
	t_room	*tmp;

	if (!line || !ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return (0);
	if (line[0] != '#')
	{
		if (!line[0] || line[0] == 'L' || line[0] == ' ' || line[0] == '-')
			return (0);
		i = 1;
		while (line[i] && line[i] != ' ' && line[i] != '-')
			i++;
		if (line[i] != '-')
			return (0);
		line[i] = '\0';
		if (!(tmp = find_room(s, line, hash_to_int(line))))
		{
			line[i] = '-';
			return (0);
		}
		tmp->nb_link++;
		if (!is_link2(s, line, i))
		{
			line[i] = '-';
			return (0);
		}
	}
	info_push_back(s, create_info(line));
	return (1);
}

void			read_link(t_lem_in *s, char *line)
{
	if (!s->start || !s->end || is_link(s, line) == 0)
	{
		free(line);
		exit_failure(s, 123, "Not enought viable info");
	}
	s->pipe = s->i_current;
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
				free(line);
				exit_failure(s, 1, "Two ##star/end command for the same room");
			}
			info_push_back(s, create_info(line));
		}
		else if (is_room(line))
		{
			*tip = place_room(s, line, hash_to_int(line));
			info_push_back(s, create_info(line));
			s->nb_room++;
			break;
		}
		else
		{
			free(line);
			exit_failure(s, 1, "Invalid/already exist room after ##start/end command");
		}
	}
}

t_room	*init_room(t_lem_in *s, t_table *tmp, char *name)
{
	tmp->room = malloc(sizeof(t_room));
	tmp->room->name = name;
	tmp->room->index = s->nb_room;
	tmp->room->nb_link = 0;
	tmp->room->link = NULL;
	return	(tmp->room);
}

t_room	*place_room(t_lem_in *s, char *key, size_t index)
{
	t_table	*tmp;

	if (!(s->map[index]))
	{
		if (!(s->map[index] = malloc(sizeof(t_room))))
			exit_failure(s, 123, "Can't malloc s->map");
		s->map[index]->t_next = NULL;
		return (init_room(s, s->map[index], key));
	}
	tmp = s->map[index];
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
	if (ft_strcmp(key, tmp->room->name) == 0)
	{
		key[ft_strlen(key)] = ' ';
		free(key);
		exit_failure(s, 123, "Room already exist");
	}
	tmp->t_next = malloc(sizeof(t_table));
	tmp = tmp->t_next;
	tmp->t_next = NULL;
	return (init_room(s, tmp, key));
}

uint_fast8_t	is_room(char *line)
{
	size_t	i;

	if (!line[0] || line[0] == ' ' || line[0] == '-' || line[0] == 'L' || line[0] == '#')
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
				if (!*line)
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
				read_tip(s, &s->start);
			else if (ft_strcmp("##end", line) == 0)
				read_tip(s, &s->end);
		}
		else if (is_room(line))
		{
			place_room(s, line, hash_to_int(line));
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

void			init_struct(t_lem_in *s)
{
	s->info = NULL;
	s->i_current = NULL;
	s->start = NULL;
	s->end = NULL;
	s->nb_room = 0;
	s->room_tab = NULL;
	init_map(s);
}

void	print_ant(size_t ant)
{
	ft_printf("\n [black]  \\ /\n");//
	ft_printf(" [242;231;191]\\[150;0;0]([white]\[green]'[red]U[green]'[150;0;0])[242;231;191]/\n");//
	ft_printf("  -[150;0;0]( )[242;231;191]-[a_bold][red] = %zd\n", ant);//
	ft_printf(" [a_reset][242;231;191]/[150;0;0]([black] _ [150;0;0])[242;231;191]\\\n[a_reset]");//
}

void	print_datatab(t_lem_in *s)
{
	size_t i;
	size_t	j;

	i = 0;
	while (i < s->nb_room)
	{
		ft_printf("Name : %s\t", s->room_tab[i].name);
		ft_printf("Index : %d\t", s->room_tab[i].index);
		ft_printf("Nb_link : %d\t", s->room_tab[i].nb_link);
		ft_printf("links : ", s->room_tab[i].nb_link);
		j = 0;
		// while (j < s->room_tab[i].nb_link && s->room_tab[i].link[j] != -1)
		while (j < s->room_tab[i].nb_link)
			ft_printf("%zd\t", s->room_tab[i].link[j++]);
		ft_printf("\n");
		i++;
	}
}

int				main(void)
{
	t_lem_in	s;

	init_struct(&s);
	read_ant_nb(&s);
	read_link(&s, read_room(&s));
	write_room(&s);
	write_link(&s);
	//print_datatab(&s);


	//print_ant(s.ant);
	// print_map(&s);
	//if (!(s.room_tab = (t_room*)malloc(sizeof(t_room) * s.nb_room)))
	//	return (EXIT_FAILURE);
	//write_room(&s);
	//write_link(s);
}