/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:28:27 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/25 15:13:04 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

int	set_color(int *color, char *line, int *flag)
{
	int i;
	int comma_count;
	char **sep_str;

	i = 0;
	line += 2;
	comma_count = count_comma(line);
	if (comma_count != 2)
		return (print_err("Error\nInvalid Color!\n"), 0);
	while(*line == ' ')
		line++;
	if (*flag == 0)
	{
		(*flag)++;
		sep_str = ft_split(line, ',');
		if (!sep_str)
			return (perror("Error\n"), 0);
		if (count_2d_len(sep_str) != 3 || !translate_rgb(sep_str, color))
			return (free_2d_array(sep_str), print_err("Error\nInvalid Color!\n"), 0);
		return (1);
	}
	else
		return (print_err("Error\nDuplicated Color!\n"), 0);
}
int	skip_lines(int n, int fd)
{
	int i;
	char *line;

	i = 0;
	while (i < n)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		free(line);
		i++;
	}
	return (1);
}

int	count_height(char *map_path, int *map_height, int *map_width, int skip_n)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (fd == -1 || !line) 
	{
		free(line);
		return (0);
	}
	skip_lines(skip_n, fd);
	while (line)
	{
		width = ft_strlen(line);
		if (width > *map_width)
			*map_width = width;
		free(line);
		(*map_height)++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	fill_gaps(char **line, int width)
{
	char *tmp;

	while ((int)ft_strlen(*line) < width)
	{
		tmp = *line;
		*line = ft_strjoin(tmp, " ");
		if (!*line)
			return (free(tmp), 0);
		free(tmp);
	}
	return (1);
}

char	**store_2d_array(t_player *player, char *map_path, int *map_height, int *map_width)
{
	int		fd;
	char	**d_map;
	int		i = 0;
	int		skip_n;

	skip_n = get_textures(player, map_path);
	if (skip_n == -1)
		return (NULL);
	if (count_height(map_path, map_height, map_width, skip_n) == 0)
		return (print_err("Error\nInvalid Map!\n"), NULL);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (print_err("Error\nInvalid Map!\n"), NULL);
	skip_lines(skip_n, fd);
	d_map = malloc(sizeof(char *) * (*map_height + 1));
	if (!d_map)
		return (perror("Error\nMap"), NULL);
	while (i < *map_height)
	{
		d_map[i] = get_next_line(fd);
		if (!d_map[i] || !fill_gaps(&d_map[i], *map_width))
			return (free_memory(d_map, i), perror("Error\nMap"), NULL);
		i++;
	}
	d_map[i] = NULL;
	close(fd);
	if (check_map_valid(d_map ,player) == 0)
		return (free_2d_array(d_map), NULL);
	return (d_map);
}
