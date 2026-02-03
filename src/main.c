/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:39 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 19:03:03 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_config	config;
	t_map		map;
	t_game		game;
	t_app		app;
	int			ret;

	if (ac != 2)
		return (fn_error(ERR_ARGC), 1);
	ret = fn_parser(&config, &map, av);
	if (ret != 0)
		return (1);
	app.game = &game;
	app.config = &config;
	app.map = &map;
	if (game_start(&app) != 0)
		return (fn_parser_free(&config, &map), 1);
	fn_parser_free(&config, &map);
	return (0);
}
