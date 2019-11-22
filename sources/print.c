/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:33:28 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/21 17:38:32 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void			print_map(t_lem_in *s)
{
	int	i;

	i = 0;
	while (i < MAP_SIZE)
	{
		if (s->map[i])
			ft_printf("map[%d]->index = %d, ->name = |%s|\n", i, s->map[i]->room->index, s->map[i]->room->name);
		i++;
	}
}

void	print_info(t_lem_in *s)
{
	while (s->info != NULL)
	{
		ft_printf("[a_reset]%s\n", s->info->str);
		s->info = s->info->i_next;
	}
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
	size_t	i;
	size_t	j;

	ft_printf("\n##start\tname : |%s|\n##end\tname : |%s|\n", s->room_tab[s->start].name, s->room_tab[s->end].name);
	i = 0;
	while (i < s->nb_room)
	{
		ft_printf("[red]Name : %s\t", s->room_tab[i].name);
		ft_printf("[blue]Index : %d\t", s->room_tab[i].index);
		ft_printf("[green]Nb_link : %d\t", s->room_tab[i].nb_link);
		ft_printf("[yellow]links : ", s->room_tab[i].nb_link);
		j = 0;
		// while (j < s->room_tab[i].nb_link && s->room_tab[i].link[j] != -1)
		while (j < s->room_tab[i].nb_link)
			ft_printf("|%zd|\t", s->room_tab[i].link[j++]);
		ft_printf("[a_reset]\n");
		i++;
	}
}

void	print_max_way(t_lem_in *s)
{
	size_t i;

	i = 0;
	while (s->way != NULL)
	{
		if (s->way->path_size > i)
			i = s->way->path_size;
		s->way = s->way->p_next; 
	}
	ft_printf("Size max : %d\n", i);
}

void	print_way(t_lem_in *s)
{
	size_t	i;

	while (s->way != NULL)
	{
		i = 0;
		ft_printf("[blue]Path : ");
		while (i <= s->way->path_size)
			ft_printf("%s ", s->room_tab[s->way->path[i++]].name);
		ft_printf("\n");
		s->way = s->way->p_next;
	}
}

void		print_tab(size_t *tab, size_t size, char *msg)
{
	size_t i;

	i = 0;
	ft_printf("%s\n", msg);
	while (i < size)
		ft_printf("%d ", tab[i++]);
	ft_printf("\n");	
}

void		print_stab(ssize_t *tab, size_t size, char *msg)
{
	size_t i;

	i = 0;
	ft_printf("%s\n", msg);
	while (i < size)
		ft_printf("%d ", tab[i++]);
	ft_printf("\n");	
}