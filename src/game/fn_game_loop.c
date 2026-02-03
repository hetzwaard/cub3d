/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_loop.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:31:33 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:31:35 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_loop_bonus(t_app *app)
{
	t_game	*g;

	g = app->game;
	game_handle_mouse(app);
	game_handle_keys(app);
	game_jump_update(app);
	game_render(app);
	game_post_blur(g);
	game_bonus_render(app);
	game_draw_crosshair(g);
}

void	game_loop(void *param)
{
	t_app	*app;
	t_game	*g;

	app = param;
	if (app == NULL || app->game == NULL || app->game->mlx == NULL)
		return ;
	g = app->game;
	game_time_update(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	if (game_frame_ready(g) == false)
		return ;
	if (is_bonus_mode())
		game_loop_bonus(app);
	else
	{
		game_handle_keys(app);
		game_render(app);
	}
}
