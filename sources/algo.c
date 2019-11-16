/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:34:44 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/16 13:34:44 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

t_path		*create_path(t_lem_in *s)
{
	size_t	i;
	t_path *new;

	i = 0;
	if (!(new = malloc(sizeof(t_path))))
		exit_failure(s, 2, "can't malloc path", 0);
	s->path->p_next = NULL;
	if (!(new->tab = malloc(sizeof(ssize_t) * s->nb_room)))
		exit_failure(s, 2, "can't malloc path tab", 0);
	s->path->tab_size = 0;
}

void		*add_path(t_lem_in *s, t_path *to_add)
{
	s->path->p_next = to_add;
}

void		algo(t_lem_in *s)
{
	clear_map(s);
		   [w]
			|
	[s]-[c = a]-[b]-[d]-[e]-[]-[]-[]
	s	 |
		[y]
	s->path = create_path(s);
	// compter le nombre de link a start
	// malloc le nombre de link en s->path 
	// commencer a fill
	// si nouveau chemin creer un nouveau s->path
	
}