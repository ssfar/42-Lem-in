/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:30:49 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/08 18:06:41 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>



uint_fast8_t	is_room(char *line)
{
	int i;

	if (!line || *line == 'L' || *line == '#')
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (i != 0 && line[i++] == ' ')
	{
		if (line[i] == '-')
			i++;
		if (line[i] >= '0' && line[i++] <= '9')
		{
			while (line[i] >= '0' && line[i] <= '9')
				i++;
			if (line[i++] == ' ')
			{
				if (line[i] == '-')
					i++;
				if (line[i++] >= '0' && line[i] <= '9')
				{
					while (line[i] >= '0' && line[i] <= '9')
						i++;
					if (line[i] == '\0')
						return (1);
				}
			}
		}
	}
	return (0);
}

uint_fast8_t	is_tube(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '-')
	{
		if (line[0] == 'L' || line[0] == '#' || line[i] == ' ')
			return (0);
		i++;
	}
	if (line[i] != '-')
		return (0);
	i++;
	if (line[i] == '#' || line[i] == 'L' || line[i] == ' ')
		return (0);
	while (line[i] && line[i] != '-' && line[i] != ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	printf("%d\n", is_tube(av[1]));
}