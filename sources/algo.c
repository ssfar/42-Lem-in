/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:57:22 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 18:40:29 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

size_t		algo(t_lem_in *s, char on)
{
	size_t	new_nb_turn;
	size_t	nb_turn;

	nb_turn = SIZE_T_MAX;
	while (1)
	{
		bfs(s, on);
		ft_bzero(s->on_q, s->on_size);
		if (check_ledit(s) == 0)
			break ;
		edit_link(s);
		if ((new_nb_turn = count_path(s, 0, 0, 0)) >= nb_turn)
		{
			return_to_the_future(s);
			break ;
		}
		nb_turn = new_nb_turn;
		reset_map(s);
	}
	return (count_path(s, 0, 0, 0));
}

size_t		algo_base_2(t_lem_in *s, size_t nb_turn, size_t check)
{
	size_t	new_turn;

	if (nb_turn > (new_turn = algo(s, 3)))
	{
		nb_turn = new_turn;
		check = 3;
	}
	full_reset(s);
	if (nb_turn > (new_turn = algo(s, 4)))
	{
		nb_turn = new_turn;
		check = 4;
	}
	return (check);
}

size_t		algo_base(t_lem_in *s)
{
	size_t	nb_turn;
	size_t	new_turn;
	size_t	check;

	nb_turn = SSIZE_T_MAX;
	if (nb_turn > (new_turn = algo(s, 1)))
	{
		nb_turn = new_turn;
		check = 1;
	}
	full_reset(s);
	if (nb_turn > (new_turn = algo(s, 2)))
	{
		nb_turn = new_turn;
		check = 2;
	}
	full_reset(s);
	return (algo_base_2(s, nb_turn, check));
}
