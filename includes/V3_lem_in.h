
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V3_lem_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:52:28 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/22 16:10:00 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# define MAP_SIZE	100000
# define PATH_SIZE	2

typedef	struct s_path
{
	uint8_t			*on_p;
	size_t			*path;
	size_t			last_node;
	size_t			max_pos;
	struct s_path	*p_next;
}				t_path;

typedef	struct	s_table
{
	struct s_room	*room;
	struct s_table	*t_next;
}				t_table;

typedef struct	s_lem_in
{
	size_t			*queu;
	// size_t			cur;
	size_t			q_size;
	uint8_t			*on_q;
	size_t			ant;
	struct	s_info	*info;
	struct	s_info	*i_current;
	struct	s_info	*pipe;
	ssize_t			start;
	ssize_t			end;
	struct	s_room	*room_tab;
	size_t			nb_room;
	size_t			on_size;
	struct	s_table	*map[MAP_SIZE];
	struct	s_path	*way;
	struct	s_path	*l_way;
}				t_lem_in;

typedef	struct	s_info
{
	char			*str;
	struct	s_info	*i_next;
}				t_info;

typedef	struct	s_room
{
	size_t	index;
	char	*name;
	size_t	nb_link;
	ssize_t	*link;
}				t_room;

void			hash_data(void *dest, const size_t size, const char *key);
unsigned int	hash_to_int(const char *key);
void			hash_data(void *dest, const size_t size, const char *key);
void			init_struct(t_lem_in *s);
void			init_map(t_lem_in *s);
void			init_info(t_info *new, char *str);
t_info			*create_info(t_lem_in *s, char *str);
void			info_push_back(t_lem_in *s, t_info *to_add);
void			clear_info(t_info *to_clear);
void			clear_the_mess(t_lem_in *s, size_t i, t_table *unlinked);
void			clean_before_unlinked(t_lem_in *s, size_t i, t_table *unliked);
void			clean_after_unlinked(t_lem_in *s, size_t i, t_table *tmp);
void			read_ant_nb(t_lem_in *s);
uint_fast8_t	is_room2(char *line);
uint_fast8_t	is_room(char *line);
void			clear_room_tab(t_lem_in *s);
void			clear_map(t_lem_in *s);
void			clear_map_room(t_lem_in *s);
char			*read_room(t_lem_in *s);
uint_fast8_t	is_link2(t_lem_in *s, char *line);
uint_fast8_t	is_link(t_lem_in *s, char *line);
void			read_link(t_lem_in *s, char *line);
t_room			*place_room(t_lem_in *s, char *key, size_t index);
t_room			*find_room(t_lem_in *s, char *key, size_t index);
void			read_tip(t_lem_in *s, ssize_t *tip);
t_room			*place_room(t_lem_in *s, char *key, size_t index);
void			exit_failure(t_lem_in *s, size_t id, char *message, uint_fast8_t error);
void			print_map(t_lem_in *s);
void			print_datatab(t_lem_in *s);
void			print_info(t_lem_in *s);
void			print_ant(size_t ant);
void			print_way(t_lem_in *s);
void			write_room(t_lem_in *s);
void			write_link(t_lem_in *s);
void			write_room2(t_lem_in *s, t_table *tmp, size_t i);
void			algo(t_lem_in *s);
void			print_tab(size_t *tab, size_t size, char *msg);
void			print_stab(ssize_t *tab, size_t size, char *msg);
void			print_max_way(t_lem_in *s);