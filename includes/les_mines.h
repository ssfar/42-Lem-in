/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_mines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:39:07 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/03 15:38:49 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# define MAP_SIZE	100000
# define SSIZE_T_MAX	9223372036854775807L
# define SIZE_T_MAX	18446744073709551615UL
# define DEL -2
# define LOCK -1
# define PRIO 1
# define ALL 0

typedef struct	s_lem_in
{
	size_t			nb_ant;
	ssize_t			nb_room;
	ssize_t			start;
	ssize_t			end;
	struct s_info	*info;
	struct s_info	*i_curr; /* info_current */
	struct s_info	*i_pipe;
	struct s_hashmap	*hmap[MAP_SIZE];
	struct s_room		*room_tab;
	size_t	on_size;
	struct s_path	*way; /* tab that contains all the paths struct*/
	size_t			w_size; /* way_size */
	size_t			w_last;
	size_t			*queu;
	size_t			q_last;
	unsigned char	*on_q;
	// char			q_overflow;
	size_t			nb_turn;
}				t_lem_in;

typedef	struct s_path
{
	unsigned char	*on_p;
	ssize_t			*node; /* tab of nodes that make a path */
	ssize_t			n_size;
}				t_path;

/* a simple linked list that contains the strings read from the map file */
typedef	struct	s_info
{
	char			*str;
	struct s_info	*i_next;
}				t_info;

typedef	struct	s_room
{
	size_t	index;
	char	*name;
	size_t	nb_link;
	size_t	link_rm;
	ssize_t	*link;
	char	link_to_end;
	size_t	cost;	// distance de start  
	signed char	*prio;	// priorite des links
	char	ascend;	// remonte ? (0 / 1)
	ssize_t	prev; 	// introduced by
	size_t	ant; /* identite de la fourmi */
}				t_room;

typedef	struct	s_hashmap
{
	struct s_room		*room;
	struct s_hashmap	*collision_next;
}				t_hashmap;

char	is_room_name_format(char *line, size_t *i);
char	is_link2(t_lem_in *s, char *line, t_room *tmp1);
char	is_link(t_lem_in *s, char *line);
char	is_room(char *line);
char	is_room2(char *line);
void			hash_data(void *dest, const size_t size, const char *key);
unsigned int	hash_to_int(const char *key);
void			init_hmap(t_lem_in *s);
t_room	*init_room(t_lem_in *s, t_hashmap *tmp, char *name);
t_room	*place_room(t_lem_in *s, char *key, size_t index);
void	add_room(t_lem_in *s, char *line);
void			read_tip(t_lem_in *s, ssize_t *tip);
t_room		*find_room(t_lem_in *s, char *key, size_t index);
void			read_link(t_lem_in *s, char *line);
char			*read_room(t_lem_in *s);
void	info_push_back(t_lem_in *s, t_info *to_add);
void	init_info(t_info *new, char *str);
t_info	*create_info(t_lem_in *s, char *str);
void	read_ant_nb(t_lem_in *s);
void	init_struct(t_lem_in *s);
void		copy_path(t_lem_in *s, size_t to_add, t_path *way, ssize_t node_in_queu);
