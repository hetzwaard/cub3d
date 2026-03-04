/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 00:34:41 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 19:33:41 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#ifdef __EMSCRIPTEN__
# include <emscripten/emscripten.h>
#endif

static int	game_setup_mlx(t_game *g)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	g->mlx = mlx_init(g->render_w, g->render_h, "GO!", true);
	if (g->mlx == NULL)
		return (1);
	mlx_set_window_size(g->mlx, g->win_w, g->win_h);
	return (0);
}

static int	game_setup_buffers(t_game *g)
{
	g->img = mlx_new_image(g->mlx, g->render_w, g->render_h);
	if (g->img == NULL)
		return (1);
	g->zbuffer = ft_calloc(g->render_w, sizeof(double));
	if (g->zbuffer == NULL)
		return (fn_error(ERR_ALLOC), 1);
	g->prev_frame = ft_calloc(g->render_w * g->render_h, sizeof(uint32_t));
	if (g->prev_frame == NULL)
		return (fn_error(ERR_ALLOC), 1);
	mlx_image_to_window(g->mlx, g->img, 0, 0);
	return (0);
}

static void	game_setup_input(t_app *app)
{
	t_game	*g;
	int32_t	cx;
	int32_t	cy;

	g = app->game;
	g->last_time = mlx_get_time();
	if (is_bonus_mode() == false)
		return ;
	cx = g->mlx->width / 2;
	cy = g->mlx->height / 2;
	mlx_set_cursor_mode(g->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(g->mlx, cx, cy);
	mlx_key_hook(g->mlx, game_bonus_keyhook, app);
}

int	game_start(t_app *app)
{
	t_game	*g;

	if (app == NULL || app->game == NULL || app->map == NULL)
		return (1);
	g = app->game;
	game_init_defaults(g);
	game_init_map(app);
	game_init_player(app);
	game_init_textures(app);
	if (is_bonus_mode())
		game_bonus_init(app);
	if (game_setup_mlx(g) != 0)
		return (1);
	if (game_setup_buffers(g) != 0)
		return (game_free(app), 1);
	game_setup_input(app);
	mlx_loop_hook(g->mlx, game_loop, app);
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg((em_arg_callback_func)mlx_loop, g->mlx, 0, 1);
#else
	mlx_loop(g->mlx);
	game_free(app);
#endif
	return (0);
}
