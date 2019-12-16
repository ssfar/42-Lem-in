/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:20:38 by vrobin            #+#    #+#             */
/*   Updated: 2019/12/16 18:16:30 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

uint_fast8_t	is_collision(t_lem_in *s, size_t *queue, size_t current)
{
	ssize_t i;
	ssize_t j;

	i = 1;
	while (i < way1.last_node)
	{
		j = 1;
		while (j < way2.last_node)
		{
			if (way1.path[i] == way2.path[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void		sort_way(t_lem_in *s)
{
	size_t i;
	t_path tmp;

	i = 0;
	while (i < s->p_last)
	{
		if (s->way[i].last_node > s->way[i + 1].last_node)
		{
			tmp = s->way[i];
			s->way[i] = s->way[i + 1];
			s->way[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

/*

recup link to start et end
recup le best_case actuel (le plus court (chemin[0]) + nb_fourmis)
tant que le prochain meilleur cas possible peut etre mieux que lancien
tenter de mettre nv chemin tant que on a pas atteint max_path:
> collision = next chemin
> pas collision = assigner 
calculer le coups
si meilleur -> changer, si pire continuer

*/

ssize_t		*get_way(t_lem_in *s)
{
	size_t	i; // current path
	size_t	j; // other path to add
	size_t	max_path; // room link to start && end
	ssize_t	*current; // return tab (with indexs of all path who will be used)
	size_t	best_case; // best case found
	// size_t	act_ant; // ant left to use
	size_t	act_path; // index of current number of path
	// size_t	act_case; // current case 

	i = 0;
	max_path = s->room_tab[s->start].link_rm;
	current = NULL;
	if (max_path > s->room_tab[s->end].link_rm)
		max_path = s->room_tab[s->start].link_rm;
	if (!(current = malloc(sizeof(ssize_t) * max_path + 1)))
		exit_failure(s, 123, "can't malloc current", 0);
	ft_printf("max_path %d\n", max_path);
	while (i <= max_path)
		current[i++] = -1;
	i = 0;
	best_case = s->way[0].last_node + s->ant - 1;
	max_path -= 1;
	while (i < s->p_last)
	{
		if (is_collision(s, current, j) == 0) 
			act_path++;
	}
	return (current);
}