/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:30 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/01/26 19:17:06 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* The map must be composed of only 6 possible characters: 
* 0 for an empty space,
* 1 for a wall, 
* and N,S,E or W for the player’s start position and spawning
* orientation.
*
*
* The map must be closed/surrounded by walls, if not the program must return
* an error.
*
*/

static bool	check_emty_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_is_emty_str(map[i]))
			return (fn_error(ERR_INVALID_MAP), false);
		i++;
	}
	return (true);
}

static bool	check_map_count(t_map *map)
{
	bool	flag;

	flag = map->invalid_char == false
		&& map->player_count == 1
		&& map->wall_count >= 4;
	if (flag == false)
		fn_error(ERR_INVALID_MAP);
	return (flag);
}

static bool	fn_map_validate(t_map *map)
{
	return (check_emty_line(map->map_2d)
		&& check_map_count(map)
		&& fn_map_wall_check(map->map_2d));
}

void	fn_map_set_start_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_2d[i])
	{
		j = 0;
		while (map->map_2d[i][j])
		{
			if (map->map_2d[i][j] == 'N' || map->map_2d[i][j] == 'S'
				|| map->map_2d[i][j] == 'W' || map->map_2d[i][j] == 'E')
			{
				map->start_pos.y = i;
				map->start_pos.x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

t_parser_state	fn_parser_map(t_config *config, t_map *map)
{
	bool	is_map_ready;

	is_map_ready = fn_map_prapare(config, map);
	if (is_map_ready == false)
		return (PARSER_ERROR);
	if (fn_map_validate(map) == false)
		return (PARSER_ERROR);
	fn_map_set_start_pos(map);
	return (PARSER_DONE);
}
