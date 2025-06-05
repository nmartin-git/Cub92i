/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:20:44 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/05 16:06:00 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct s_map
{
	int		**map;
	char	*n_t;
	char	*s_t;
	char	*e_t;
	char	*w_t;
	int		f_rgb;
	int		c_rgb;
	int		row;
	int		col;
}			t_map;

/* check_map */

int			check_neighbors(t_map *map, int x, int y);
int			check_map(t_map *map);
int			check_av(char *av, int *fd);
int			check_infos(t_map *map);

/* free_map */

void		free_infos(t_map *map);
void		ft_free_tab_int(int **tab);
void		close_void(int fd);
void		free_map(t_map *map);

/* texture */

int			fill_t(char *line, t_map *map, char c1, char c2);
int			fill_colors(char *line, t_map *map, char c);
int			fill_textures(char *line, t_map *map, int *count);
int			fill_ec(char *line, t_map *map, int *count);
int			gateway_textures(char *line, t_map *map, int *count);

/* map_utils */

int			start_of_map(int fd, char **line);
int			count_size(int fd, int *col);
int			ctoi(char c, int *count);
int			encode_rgb(int r, int g, int b);

/* map */

int			fill_row(int **row, char *line, int col, int *count_spawn);
int			init_map(t_map *map, int fd, char *av);
int			last_row(int **row, int col);
int			fill_tabmap(int fd, t_map *map, int *count_spawn);

/* resize_map.c */

int			is_col_empty(int **map, int i);
int			count_pre_col(int **map);
int			count_post_col(int **map, int size);
int			resize_line(int *map, int **newmap, int start, int size);

/* parsing */

int			fill_infos(int fd, t_map *map);
int			fill_map(int fd, t_map *map, char *av);
void		pre_init(t_map *map);
int			resize_map(t_map *map);
int			parsing(char *av, t_map *map);

#endif
