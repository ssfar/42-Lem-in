/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:57:52 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/11 14:11:57 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	info_push_back(t_lem_in *s, t_info *to_add)
{
	if (s->info == NULL)
	{
		s->info = to_add;
		s->i_curr = to_add;
	}
	else
	{
		s->i_curr->i_next = to_add;
		s->i_curr = s->i_curr->i_next;
	}
}

void	init_info(t_info *new, char *str)
{
	new->str = str;
	new->i_next = NULL;
}

t_info	*create_info(t_lem_in *s, char *str)
{
	t_info	*new;

	if (!(new = malloc(sizeof(*new))))
		exit_failure(s, str, 0, 0);
	init_info(new, str);
	return (new);
}

void	print_info(t_lem_in *s)
{
	char	pipe;

	pipe = 0;
	ft_printf("%zu\n", s->nb_ant);
	s->i_curr = s->info;
	while (s->i_curr)
	{
		if (s->i_curr->str[0] != '#')
		{
			if (pipe)
				ft_printf("%s-", s->i_curr->str);
			else
				ft_printf("%s ", s->i_curr->str);
			ft_printf("%s\n", &s->i_curr->str[ft_strlen(s->i_curr->str) + 1]);
		}
		else
			ft_printf("%s\n", s->i_curr->str);
		s->i_curr = s->i_curr->i_next;
		if (s->i_curr == s->i_pipe)
			pipe = 1;
	}
	ft_printf("\n");
}
