/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:34:48 by cdudzik           #+#    #+#             */
/*   Updated: 2023/01/15 19:40:01 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define BUFFER_SIZE 1024

# include "cub3d.h"

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

typedef struct s_map_line
{
	int	*line;
	int	size;
}	t_map_line;

char		*read_next_line(int fd);
t_pair		*read_config_line(char *line);
int			parsing_error(const char *s1, const char *s2);
void		*parsing_error_null(const char *s1, const char *s2);
int			point_error(const char *s1, int x, int y);
void		*perr_null(void);
int			ft_null_or_empty(const char *str);
int			free_pair(t_pair *pair);
int			ft_strcmp(const char *s1, const char *s2);
int			free_textures(t_textures *textures);
int			is_valid_int(char *str);
int			str_ends_with(const char *str, const char *suffix);
t_map		*parse_map(int fd);
char		*trim_end(char *s);
int			free_map_line(t_map_line *line);
void		free_ml(void *ml);
int			max(int a, int b);
void		dump_map_line(void *line);
void		dump_map(t_map *map);
t_cell_type	get_cell_type(char c);
char		*read_until_not_empty(int fd);
int			validate_map(t_map **map, t_textures *textures);

#endif
