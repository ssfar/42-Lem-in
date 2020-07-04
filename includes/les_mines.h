/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_mines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:39:07 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/11 14:14:30 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LES_MINES_H
# define LES_MINES_H
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# define MAP_SIZE	100000
# define SSIZE_T_MAX	9223372036854775807L
# define SIZE_T_MAX	18446744073709551615UL
# define ROOM_OVERFLOW	10000000000
# define DEL -2
# define LOCK -1
# define PRIO 1
# define ALL 0

typedef struct			s_lem_in
{
	size_t				nb_ant;
	ssize_t				nb_room;
	ssize_t				start;
	ssize_t				end;
	struct s_info		*info;
	struct s_info		*i_curr;
	struct s_info		*i_pipe;
	struct s_hashmap	*hmap[MAP_SIZE];
	struct s_room		*room_tab;
	size_t				on_size;
	size_t				*queu;
	size_t				q_last;
	unsigned char		*on_q;
	size_t				nb_turn;
	size_t				ant;
	char				run;
}						t_lem_in;

typedef struct			s_info
{
	char				*str;
	struct s_info		*i_next;
}						t_info;

typedef struct			s_room
{
	ssize_t				index;
	char				*name;
	size_t				nb_link;
	size_t				link_rm;
	ssize_t				*link;
	size_t				cost;
	signed char			*prio;
	char				ascend;
	ssize_t				prev;
	size_t				ant;
}						t_room;

typedef struct			s_hashmap
{
	struct s_room		*room;
	struct s_hashmap	*collision_next;
}						t_hashmap;

size_t					algo(t_lem_in *s, char on);
size_t					algo_base_2(t_lem_in *s, size_t nb_turn, size_t check);
size_t					algo_base(t_lem_in *s);
void					print_ant(t_lem_in *s);
void					move_ant(t_lem_in *s, size_t *path, ssize_t *node,
	size_t size);
void					get_ant_out(t_lem_in *s, size_t *path, ssize_t *node,
	size_t size);
void					update_ant_pos(t_lem_in *s);
void					print_start_to_end(t_lem_in *s);
void					bfs(t_lem_in *s, unsigned char on);
void					normal_case(t_lem_in *s, t_room *room, t_room *tab,
	unsigned char on);
void					ascend_case(t_lem_in *s, t_room *room, t_room *tab,
	unsigned char on);
char					search_for_all(t_lem_in *s, t_room *room, t_room *tab,
	unsigned char on);
void					exit_success(t_lem_in *s);
void					exit_failure(t_lem_in *s, void *to_free,
	char mode, char print_error);
void					clear_the_mess(t_lem_in *s, size_t i,
	t_hashmap *unlinked);
void					clean_after_unlinked(t_lem_in *s, size_t i,
	t_hashmap *tmp);
void					clean_before_unlinked(t_lem_in *s, size_t i,
	t_hashmap *unliked);
void					free_info(t_lem_in *s);
void					free_room(t_room *room, char mode);
void					free_hash_map(t_lem_in *s, char mode);
void					free_struct(t_lem_in *s, char mode);
void					get_prev_ant(t_lem_in *s, ssize_t cur);
size_t					*get_ant2(size_t nb_ant, size_t *ant_tab, size_t size);
void					init_ant_tab(size_t *ant_tab, size_t size);
size_t					*get_ant(t_lem_in *s, size_t nb_ant, size_t *path,
	size_t size);
void					info_push_back(t_lem_in *s, t_info *to_add);
void					init_info(t_info *new, char *str);
t_info					*create_info(t_lem_in *s, char *str);
void					print_info(t_lem_in *s);
t_room					*init_room(t_lem_in *s, t_hashmap *new, char *name);
void					init_info(t_info *new, char *str);
void					init_struct(t_lem_in *s);
void					init_algo(t_lem_in *s);
void					init_hmap(t_lem_in *s);
char					is_room_name_format(char *line, size_t *i);
char					is_link2(t_lem_in *s, char *line, t_room *room1);
char					is_link(t_lem_in *s, char *line);
char					is_room(char *line);
char					is_room2(char *line);
void					hash_data(void *dest, const size_t size,
	const char *key);
unsigned int			hash_to_int(const char *key);
void					hunt_deadend(t_lem_in *s, ssize_t start, ssize_t end,
	t_room *room_tab);
void					bubble_sort_node(size_t *arr, ssize_t *node, size_t n);
int						main(void);
void					delete_link(t_lem_in *s, t_room *room_tab,
	ssize_t *link, ssize_t i);
void					set_link_to_all(t_lem_in *s, ssize_t i, size_t j);
void					edit_link(t_lem_in *s);
size_t					check_ledit(t_lem_in *s);
void					retrace_path(t_lem_in *s, size_t node,
	size_t *path_size);
size_t					get_size_path(t_lem_in *s, size_t act_path);
size_t					get_size_path_prev(t_lem_in *s, size_t act_path);
size_t					count_path(t_lem_in *s, size_t i, size_t j,
	size_t size);
size_t					count_nb_path(t_lem_in *s);
unsigned char			binary_pow_2(unsigned char index);
unsigned char			add_on(unsigned char *on, size_t to_add);
void					add_queu(t_lem_in *s, ssize_t *link, size_t nb_link);
unsigned char			remove_on(unsigned char *on, size_t to_remove);
void					read_link(t_lem_in *s, char *line);
void					read_ant_nb(t_lem_in *s);
void					read_tip(t_lem_in *s, ssize_t *tip);
char					*read_room(t_lem_in *s);
void					reset_map(t_lem_in *s);
void					full_reset(t_lem_in *s);
size_t					count_turn(t_lem_in *s, size_t nb_ant, size_t *path,
	size_t size);
void					return_to_the_future(t_lem_in *s);
t_room					*place_room(t_lem_in *s, char *key, size_t index);
void					add_room(t_lem_in *s, char *line);
t_room					*find_room(t_lem_in *s, char *key, size_t index);
void					write_room(t_lem_in *s);
void					write_room_alloc(t_lem_in *s, ssize_t j, size_t i,
	t_hashmap *tmp);
void					write_room2(t_lem_in *s, t_hashmap *tmp, size_t i);
void					write_link(t_lem_in *s);
void					add_link(t_lem_in *s, ssize_t index1, ssize_t index2);

#endif
