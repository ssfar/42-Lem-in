/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:20:38 by vrobin            #+#    #+#             */
/*   Updated: 2019/12/18 16:29:03 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

uint_fast8_t	is_collision(t_lem_in *s, ssize_t *new_current,
					size_t to_add, size_t max_path)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < max_path)
	{
		j = 0;
		while (j < max_path && new_current[j] != -1)
		{
			if (is_on_path(s, s->way[new_current[j]].on_p, s->way[to_add]) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

size_t calculate_best_case(size_t path_size, size_t ant, size_t nb_path)
{
	ft_printf("size %d, ant %d, nb_path %d\n", path_size, ant, nb_path);
	return (path_size + ((ant - 1) / nb_path) - 1);
}

size_t calculate_case(size_t path_size1, size_t path_size2, size_t ant, size_t nb_path)
{
	ft_printf("path_size1 %d, path_size2 %d, ant %d, nb_path %d\n", path_size1, path_size2, ant, nb_path);
	return (path_size2 + ((ant + path_size1 - 1 - path_size2) / nb_path) - 1);
}

// void		sort_way(t_lem_in *s)
// {
// 	size_t	i;
// 	t_path	tmp;

// 	i = 0;
// 	while (i < path_size)
// 	{
// 		if (s->way[i].last_node > s->way[i + 1].last_node)
// 		{
// 			tmp = s->way[i];
// 			s->way[i] = s->way[i + 1];
// 			s->way[i + 1] = tmp;
// 			i = 0;
// 		}
// 		else
// 			i++;
// 	}
// }

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

void		print_possible_path(t_lem_in *s, ssize_t *current)
{
	size_t i;
	ssize_t j;

	i = 0;
	while (current[i] != -1)
	{
		j = 0;
		while (j <= s->way[current[i]].last_node)
			ft_printf("%s ", s->room_tab[s->way[current[i]].path[j]]);
		ft_printf("\n");
		i++;
	}
}

size_t		get_new_case(t_lem_in *s, size_t i, size_t max_path, size_t path_size)
{
	size_t	j;
	size_t	k;
	ssize_t	*new_current;

	k = 0;
	j = i + 1;
	if (!(new_current = malloc(sizeof(size_t) * max_path + 1)))
		return (0);
	new_current[k] = i;
	k++;
	while (k < max_path)
		new_current[k++] = -1;
	k = 1;
	while (j <= path_size && k < max_path)
	{
		if (is_collision(s, new_current, j, k) == 0)
		{
			new_current[k] = j;
			k++;
		}
		j++;
	}
	k = 0;
	while (k < max_path - 2 && new_current[k + 1] != -1)
		k++;
	print_stab(new_current, max_path, "new found");
	return (calculate_case(s->way[1].last_node, s->way[new_current[k]].last_node, s->ant, k + 1));
}

ssize_t		*get_way(t_lem_in *s, size_t path_size)
{
	size_t	i;
	ssize_t *current;
	size_t	max_path;
	size_t	best_case;
	size_t	new_case;
		
	i = 0;
	best_case = s->way[0].last_node + s->ant - 1;
	max_path = s->room_tab[s->start].link_rm > s->room_tab[s->end].link_rm ? s->room_tab[s->end].link_rm : s->room_tab[s->start].link_rm;
	ft_printf("\n[yellow]max path usable : %d\n", max_path);
	ft_printf("best case : %d\n\n[a_reset]", best_case);
	if (!(current = malloc(sizeof(size_t) * max_path + 1)))
		return (NULL);
	while (i < max_path)
		current[i++] = -1;
	i = 0;
	new_case = 0;
	while (i < path_size && new_case < best_case)
	{
		new_case = calculate_best_case(s->way[i].last_node, s->ant, max_path);
		if ((new_case = get_new_case(s, i, max_path, path_size)) < best_case)
		{
			best_case = new_case;
			new_case = 0;
		}
		ft_printf("\n[blue]best_case = %d | [red]new_case = %d\n[a_reset]\n", best_case, new_case);
		i++;
	}
	// write_case()
	return (NULL);
}