/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_map_wall_check.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 20:49:58 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 21:33:56 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'W'
		|| c == 'N' || c == 'E' || c == 'S')
		return (true);
	if (is_bonus_mode() && (c == 'D' || c == 'd'
			|| c == 'L' || c == 'K' || c == 'C'))
		return (true);
	return (false);
}

static bool	is_invalid_cell(char **map, int i, int j)
{
	if (i < 0 || j < 0 || map[i] == NULL || map[i][j] == '\0')
		return (true);
	if (is_valid_char(map[i][j]) == false)
		return (true);
	return (false);
}

static int	check_neighbor(char **map, int i, int j)
{
	if (is_invalid_cell(map, i, j + 1))
		return (1);
	if (is_invalid_cell(map, i, j - 1))
		return (1);
	if (is_invalid_cell(map, i + 1, j))
		return (1);
	if (is_invalid_cell(map, i - 1, j))
		return (1);
	return (0);
}

bool	fn_map_wall_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'W'
				|| (is_bonus_mode()
					&& (map[i][j] == 'd'
						|| map[i][j] == 'L'
						|| map[i][j] == 'K'
						|| map[i][j] == 'C')))
			{
				if (check_neighbor(map, i, j))
					return (fn_error(ERR_INVALID_WALL), false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
