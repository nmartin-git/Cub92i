/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:20:44 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/13 18:40:03 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define N_DIR 2
# define S_DIR 3
# define E_DIR 4
# define W_DIR 5

typedef struct s_data	t_data;

typedef struct s_map
{
	int					**map;
	char				*n_t;
	char				*s_t;
	char				*e_t;
	char				*w_t;
	int					f_rgb;
	int					c_rgb;
	int					row;
	int					col;
	int					x_spawn;
	int					y_spawn;
}						t_map;

/* check_map */

int						check_neighbors(t_map *map, int x, int y);
int						check_map(t_map *map);
int						check_av(char *av, int *fd);
int						check_infos(t_map *map);
int						check_colors(char **str);

/* free_map */

void					free_infos(t_map *map);
void					ft_free_tab_int(int **tab);
void					close_void(int fd);
void					free_map(t_map *map);

/* texture */

int						fill_t(char *line, t_map *map, char c1, char c2);
int						fill_colors(char *line, t_map *map, char c, char *tmp);
int						fill_textures(char *line, t_map *map, int *count,
							char *tmp);
int						fill_ec(char *line, t_map *map, int *count, char *tmp);
int						gateway_textures(char *line, t_map *map, int *count);

/* map_utils */

int						start_of_map(int fd, char **line);
int						count_size(int fd, int *col);
int						ctoi(char c, int *count);
int						encode_rgb(int r, int g, int b);
void					fill_rgb(char **str, t_map *map, char c);

/* map */

int						fill_row(int **row, char *line, int col,
							int *count_spawn);
int						init_map(t_map *map, int fd, char *av);
int						last_row(int **row, int col);
int						fill_tabmap(int fd, t_map *map, int *count_spawn);
void					set_pos_spawn(t_map *map);

/* resize_map.c */

int						is_col_empty(int **map, int i);
int						count_pre_col(int **map);
int						count_post_col(int **map, int size);
int						resize_line(int *map, int **newmap, int start,
							int size);

/* parsing */

int						fill_infos(int fd, t_map *map);
int						fill_map(int fd, t_map *map, char *av);
void					pre_init(t_map *map);
int						resize_map(t_map *map);
int						parsing(char *av, t_map *map);

/*	load textures */

int						load_texutres(t_data *data);
void					free_textures(t_data *data);

#endif
