/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:09:28 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 18:20:05 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

unsigned char	binary_pow_2(unsigned char index)
{
	if (index < 4)
	{
		if (index == 0)
			return (1);
		else if (index == 1)
			return (2);
		else if (index == 2)
			return (4);
		return (8);
	}
	else if (index == 4)
		return (16);
	else if (index == 5)
		return (32);
	else if (index == 6)
		return (64);
	return (128);
}

unsigned char	add_on(unsigned char *on, size_t to_add)
{
	size_t			on_index;
	unsigned char	compare;

	on_index = to_add / 8;
	compare = binary_pow_2(to_add % 8);
	if (compare & on[on_index])
		return (0);
	on[on_index] += compare;
	return (1);
}

void			add_queu(t_lem_in *s, ssize_t *link, size_t nb_link)
{
	size_t	i;

	i = 0;
	while (i < nb_link)
	{
		if (link[i] != -2 && link[i] != s->end && add_on(s->on_q, link[i]))
		{
			s->q_last++;
			s->queu[s->q_last] = link[i];
		}
		i++;
	}
}

unsigned char	remove_on(unsigned char *on, size_t to_remove)
{
	size_t			on_index;
	unsigned char	compare;

	on_index = to_remove / 8;
	compare = binary_pow_2(to_remove % 8);
	on[on_index] -= compare;
	return (1);
}
