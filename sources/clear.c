/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:51:35 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 18:42:27 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	exit_success(t_lem_in *s)
{
	free_struct(s, 1);
	exit(EXIT_SUCCESS);
}

void	exit_failure(t_lem_in *s, void *to_free,
	char mode, char print_error)
{
	free(to_free);
	free_struct(s, mode);
	if (print_error)
		ft_printf("ERROR\n");
	exit(EXIT_FAILURE);
}

void	clear_the_mess(t_lem_in *s, size_t i, t_hashmap *unlinked)
{
	clean_before_unlinked(s, i, unlinked);
	free(s->room_tab);
	clean_after_unlinked(s, i, unlinked->collision_next);
	free(unlinked);
	free_info(s);
	exit(EXIT_FAILURE);
}

void	clean_after_unlinked(t_lem_in *s, size_t i, t_hashmap *tmp)
{
	size_t		j;
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
	size_t		j;

	j = 0;
	while (j < i)
	{
		tmp = s->hmap[j];
		while (tmp)
		{
			free_room(tmp->room, 0);
			tmp2 = tmp->collision_next;
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
	tmp = s->hmap[i];
	while (tmp && tmp != unliked)
	{
		free_room(tmp->room, 0);
		tmp2 = tmp->collision_next;
		free(tmp);
		tmp = tmp2;
	}
}
