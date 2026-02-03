/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_map_prapare.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 20:14:36 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/01/26 18:30:10 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	line_bonus_setup(t_map *map, char c)
{
	if (c == 'L')
		map->has_lava = true;
	map->space_count++;
}

void	line_setup(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			return ;
		if (line[i] == '1')
			map->wall_count++;
		else if (line[i] == '0')
			map->space_count++;
		else if (ft_strchr("NSWE", line[i]) != NULL)
			map->player_count++;
		else if (is_bonus_mode()
			&& ft_strchr("DdLK", line[i]) != NULL)
			line_bonus_setup(map, line[i]);
		else
			map->invalid_char = true;
		i++;
	}
}

static void	fn_map_count_setup(t_map *map)
{
	int		i;
	char	**map_2d;

	map_2d = map->map_2d;
	i = 0;
	while (map_2d[i])
	{
		line_setup(map, map_2d[i]);
		i++;
	}
}

static bool	fn_map_size_setup(t_map *map)
{
	char	**map_2d;
	int		i;
	int		max_w;

	map_2d = map->map_2d;
	i = 0;
	max_w = 0;
	while (map_2d[i])
	{
		if ((int)ft_strlen(map_2d[i]) > max_w)
			max_w = (int)ft_strlen(map_2d[i]);
		i++;
	}
	map->height = i;
	map->width = max_w;
	map->row_len = ft_calloc(i, sizeof(int));
	if (map->row_len == NULL)
		return (false);
	while (--i >= 0)
		map->row_len[i] = (int)ft_strlen(map_2d[i]);
	return (true);
}

bool	fn_map_prapare(t_config *config, t_map *map)
{
	char	**map_2d;

	fn_map_copy(config, map);
	map_2d = fn_map_to_array(map->map);
	if (map_2d == NULL)
		return (fn_error(ERR_ALLOC), false);
	map->map_2d = fn_map_trimmed(map_2d);
	if (map->map_2d == NULL)
		return (fn_error(ERR_ALLOC), false);
	if (fn_map_size_setup(map) == false)
		return (fn_error(ERR_ALLOC), false);
	fn_map_count_setup(map);
	return (true);
}
