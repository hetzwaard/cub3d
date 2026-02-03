/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:37 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 19:06:52 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	fn_parser_init_config(t_config *config, char **av)
{
	config->ceil_rgb = RGBA_DEF;
	config->floor_rgb = RGBA_DEF;
	config->east_tex_path = NULL;
	config->north_tex_path = NULL;
	config->south_tex_path = NULL;
	config->west_tex_path = NULL;
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->east_texture = NULL;
	config->west_texture = NULL;
	config->filename = ft_strdup(av[1]);
	if (!config->filename)
		return (fn_error(ERR_ALLOC), false);
	config->content_of_file = NULL;
	return (true);
}

static void	fn_parser_init_map(t_map *map)
{
	map->height = -1;
	map->width = -1;
	map->wall_count = 0;
	map->player_count = 0;
	map->space_count = 0;
	map->invalid_char = false;
	map->has_lava = false;
	map->map = NULL;
	map->map_2d = NULL;
	map->row_len = NULL;
	map->start_pos.x = -1;
	map->start_pos.y = -1;
}

static void	fn_parser_init_state(t_parser_fn *parser_state_map)
{
	parser_state_map[PARSER_FILE] = fn_parser_file;
	parser_state_map[PARSER_IDENTIFIER] = fn_parser_identifiers;
	parser_state_map[PARSER_MAP] = fn_parser_map;
}

static int	fn_parser_run(t_config *config, t_map *map)
{
	t_parser_fn		parser_state_map[PARSER_DONE];
	t_parser_state	state;

	fn_parser_init_state(parser_state_map);
	state = fn_parser_start(config, map);
	while (state != PARSER_DONE && state != PARSER_ERROR)
	{
		state = parser_state_map[state](config, map);
	}
	if (state == PARSER_ERROR)
		return (PARSER_EXIT_FAILURE);
	return (PARSER_EXIT_SUCCESS);
}

int	fn_parser(t_config *config, t_map *map, char **av)
{
	int	ret;

	fn_parser_init_map(map);
	ret = fn_parser_init_config(config, av);
	if (!ret)
		return (1);
	ret = fn_parser_run(config, map);
	if (ret == PARSER_EXIT_SUCCESS)
		return (0);
	fn_parser_free(config, map);
	return (1);
}
