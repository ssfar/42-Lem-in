/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:42:21 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/09 15:49:14 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	store_ant_movement(t_visu *v)
{
	size_t	i;
	t_info	*tmp;

	i = 0;
	while (i < v->ant_nb)
	{
		if (!(v->ant[i].path = malloc(sizeof(t_room*) * v->ant[i].nb_move)))
			exit_fail(v, "Malloc error", NULL);
		i++;
	}
	while (v->info != NULL)
	{
		tmp = v->info->next;
		i = 0;
		while (v->info->str[i])
		{
			while (v->info->str[i] != 'L')
				i++;
			i++;
			i = store_ant_path(v, v->info->str, i);
		}
		free(v->info->str);
		free(v->info);
		v->info = tmp;
	}
}

size_t	store_ant_path(t_visu *v, char *line, size_t i)
{
	size_t	ant_id;
	size_t	j;
	size_t	k;

	ant_id = atou(&line[i]) - 1;
	while (line[i] != '-')
		i++;
	i++;
	j = i;
	while (line[j] != ' ' && line[j] != '\0')
		j++;
	k = 0;
	while (k < v->nb_room)
	{
		if (ft_strlen(v->room[k].name) == j - i
			&& !ft_strncmp(v->room[k].name, &line[i], j - i))
		{
			v->ant[ant_id].path[v->ant[ant_id].goal] = &v->room[k];
			v->ant[ant_id].goal++;
			return (j);
		}
		k++;
	}
	invalid_map(v, NULL);
	return (0);
}

void	store_link(t_visu *v, char *to_free)
{
	size_t	a;
	size_t	b;
	t_info	*tmp;

	if (!(v->link = malloc(sizeof(t_link) * v->nb_total_link)))
		exit_fail(v, "Malloc error", to_free);
	v->nb_valid_link = 0;
	while (v->info != NULL && find_link(v, v->info->str, &a)
		&& find_link(v, &v->info->str[ft_strlen(v->info->str) + 1], &b))
	{
		if (a != b)
		{
			v->link[v->nb_valid_link].a = &v->room[a];
			v->link[v->nb_valid_link].b = &v->room[b];
			v->nb_valid_link++;
		}
		tmp = v->info;
		v->info = v->info->next;
		free(tmp->str);
		free(tmp);
	}
}

void	store_room(t_visu *v)
{
	size_t	i;
	size_t	y;
	t_info	*tmp;

	if (!(v->room = malloc(sizeof(t_room) * v->nb_room)))
		exit_fail(v, "Malloc error", NULL);
	i = 0;
	while (v->info != v->cur_info)
	{
		v->room[i].name = v->info->str;
		y = ft_strlen(v->info->str) + 1;
		v->room[i].x = ft_atoi(&v->info->str[y]);
		while (v->info->str[y] != ' ')
			y++;
		v->room[i].y = ft_atoi(&v->info->str[y]);
		i++;
		tmp = v->info;
		v->info = v->info->next;
		free(tmp);
	}
}
