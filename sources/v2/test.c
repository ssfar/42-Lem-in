/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:30:49 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/10 14:43:36 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>

int main(int ac, char **av)
{
	char *line = NULL;
	get_next_line(0, &line);
	if (line)
		printf("|%s|", line);
}