/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_lem_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:43:02 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/12 15:33:31 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	link_push_back(t_table *src, t_link *to_add)
{
	t_link *tmp;

	if (src->link == NULL)
		src->link = to_add;
	else
	{
		tmp = src->link;
		while (tmp->l_next != NULL)
			tmp = tmp->l_next;
		tmp->l_next = to_add;
	}
}

void	init_link(t_link *link, t_table *table)
{
	link->jump = table;
	link->l_next = NULL;
}

t_link	*create_link(t_table *table)
{
	t_link *new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	init_link(new, table);
	return (new);
}

void	info_push_back(t_lem_in *s, t_info *to_add)
{
	if (s->info == NULL)
	{
		s->info = to_add;
		s->i_current = to_add;
	}
	else
	{
		s->i_current->i_next = to_add;
		s->i_current = s->i_current->i_next;
	}
}

void	init_info(t_info *new, char *str)
{
	new->str = str;
	new->i_next = NULL;
}

t_info	*create_info(char *str)
{
	t_info	*new;

	if (!(new = (t_info*)malloc(sizeof(t_info))))
		return (NULL);
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
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			{
				free(line);
				exit_failure(s, 1, "\nNo/invalid ant nbr");
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
			exit_failure(s, 1, "\nNo/invalid ant nbr");
		}
	}
	exit_failure(s, 1, "\nNo/invalid ant nbr");
}

void	read_tip(uint_fast8_t *tip, t_lem_in *s)
{
	char	*line;

	if (*tip != 0)
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
			s->nb_room++;
			info_push_back(s, create_info(line));
			*tip = 1;
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

char	*read_room(t_lem_in *s)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (is_room(line))
		{
			info_push_back(s, create_info(line));
			s->nb_room++;
		}
		else if ('#' == *line)
			info_push_back(s, create_info(line));
			if (ft_strcmp("##start", line) == 0)
				read_tip(&s->st, s);
			else if (ft_strcmp("##end", line) == 0)
				read_tip(&s->en, s);
		}
		else
			return (line);
	}
	return (NULL);
}

t_table		*find_table(t_table *table, char *key, size_t index)
{
	t_table *tmp;

	tmp = table[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->t_next;
	}
	return (NULL);
}

t_table	*get_room_pipe(char *line, t_lem_in *s)
{
	char	*key;
	ssize_t	j;
	t_table *tmp;

	j = 0;
	if ((j = hash(line, s->nb_room)) == -1)
		return (NULL);
	tmp = find_table(s->table, key, j);
	return (tmp);
}

uint_fast8_t	is_pipe(t_lem_in *s, char *line)
{
	size_t	i;
	t_table	*tmp1;
	t_table	*tmp2;
	size_t	mid;

	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return	(0);
	if (line[0] != '#')
	{
		if (!line[0] || line[0] == 'L' || line[0] == ' ' || line[0] == '-')
			return (0);
		i = 1;
		while (line[i] && line[i] != ' ' && line[i] != '-')
			i++;
		i = mid;
		if (line[i] != '-')
			return (0);
		line[i] = '\0';
		if (!(tmp1 = get_room_pipe(line, s)))
			return (0);
		line[i] = '-';
		++i;
		while (line[i] && line[i] != ' ' && line[i] != '-')
			i++;
		if (line[i] == '-' || line[i] != '\0'
			|| !(tmp2 = get_room_pipe(line + mid, s)))
			return (0);
		link_push_back(table1, create_link(table2));
		link_push_back(table2, create_link(table1));
	}
	info_push_back(s, create_info(line));
	return (1);
}

t_table	*place_table(t_lem_in *s, char *key)
{
	t_table	*tmp;
	size_t	index;

	index = hash(key, s->nb_room);
	if (ft_strcmp(table[index]->key, key) == 0)
		return (NULL);
	tmp = table[index];
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->t_next;
	}
	return (NULL);
}

void	place_tip(t_lem_in *s, t_table **tip, t_info **tmp)
{
	if (*tip)
		exit_failure(s, 2, "Tip already exist");
	*tmp = *tmp->next;
	while (*tmp)
	{
		if (*tmp->str[0] == '#')
		{
			if (!ft_strcmp("##start") || !ft_strcmp("##end"))
				exit_failure(s, 2, "##start/end command followed by an other");
			*tmp = *tmp->next
		}
		else
		{
			if (!(*tip = place_table(s, *tmp->str))
				exit_failure(s, 2, "Tip room is a copy of a previous room");
			*tmp = *tmp->next;
			return ;
		}
	}
	exit_failure(s, 2, "No room after ##star/end command");
}

void	create_table(t_lem_in *s, char *line)
{
	t_info	*tmp;

	s->nb_room *= 3;
	if (!line || !(s->table = malloc(sizeof(t_table) * s->nb_room)))
	{
		free(line);
		exit_failure(s, 1, "No pipe or Malloc error");
	}
	tmp = s->info;
	while (tmp)
	{
		if (tmp->str[0] == '#')
		{
			if (!ft_strcmp(tmp->str, "##start"))
				place_tip(s, &s->start, &tmp);
			else if (!ft_strcmp(tmp->str, "##end"))
				place_tip(s, &s->end, &tmp);
			else
				tmp = tmp->next;
		}
		else
		{
			if (!place_room(s, *tmp->str))
				exit_failure(s, 1, "Duplicated room");
			tmp = tmp->next;
		}
	}
}

void	read_pipe(t_lem_in *s, char *line)
{
	create_table(s);
	if (is_pipe(s, line) == 0)
	{
		free(line);
		exit_failure(s, 1,  "Not enouth viable info");
	}
	while (get_next_line(0, &line)
	{
		if (is_pipe(s, line) == 0)
			return ;	
	}
}

void	init_struct(t_lem_in *s)
{
	s->info = NULL;
	s->i_current = NULL;
	s->start = NULL;
	s->end = NULL;
	s->st = 0;
	s->en = 0;
	s->nb_room = 0;
}

int	main(void)
{
	t_lem_in	s;

	init_struct(&s);
	read_ant_nb(&s);
	read_pipe(&s, read_room(&s))
}