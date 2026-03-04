/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_input.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:31:26 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/03/03 23:15:16 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_move_input(t_game *g, double *fwd, double *right)
{
	*fwd = 0.0;
	*right = 0.0;
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		*fwd += 1.0;
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		*fwd -= 1.0;
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		*right += 1.0;
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		*right -= 1.0;
}

static void	game_bonus_input(t_app *app, double *speed)
{
	t_game	*g;

	g = app->game;
	if (is_bonus_mode() == false)
		return ;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
		*speed *= GAME_RUN_MULT;
	if (mlx_is_key_down(g->mlx, MLX_KEY_SPACE))
		game_jump_start(app);
}

void	game_handle_keys(t_app *app)
{
	t_game	*g;
	double	rot;
	double	fwd;
	double	right;
	double	speed;

	g = app->game;
	rot = g->rot_speed * g->dt;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		game_rotate(g, -rot);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		game_rotate(g, rot);
	speed = g->move_speed;
	game_move_input(g, &fwd, &right);
	game_bonus_input(app, &speed);
	game_apply_movement(app, fwd, right, speed);
}

static bool	game_mouse_delta_center(t_game *g, double *dx, double *dy)
{
	int32_t	mx;
	int32_t	my;
	double	cx;
	double	cy;
	double	max_dx;
	double	max_dy;

	mlx_get_mouse_pos(g->mlx, &mx, &my);
	cx = g->mlx->width / 2.0;
	cy = g->mlx->height / 2.0;
	*dx = (double)mx - cx;
	*dy = (double)my - cy;
	max_dx = (double)g->mlx->width * 0.45;
	max_dy = (double)g->mlx->height * 0.45;
	if (fabs(*dx) > max_dx || fabs(*dy) > max_dy)
		return (false);
	if (fabs(*dx) < 1.0)
		*dx = 0.0;
	if (fabs(*dy) < 1.0)
		*dy = 0.0;
	return (!(*dx == 0.0 && *dy == 0.0));
}

#ifdef __EMSCRIPTEN__
static bool	game_mouse_delta_relative(t_game *g, double *dx, double *dy)
{
	int32_t	mx;
	int32_t	my;

	mlx_get_mouse_pos(g->mlx, &mx, &my);
	*dx = (double)mx - g->mouse.last_x;
	*dy = (double)my - g->mouse.last_y;
	g->mouse.last_x = (double)mx;
	g->mouse.last_y = (double)my;
	if (fabs(*dx) > 300.0 || fabs(*dy) > 300.0)
		return (false);
	if (fabs(*dx) < 0.01)
		*dx = 0.0;
	if (fabs(*dy) < 0.01)
		*dy = 0.0;
	return (!(*dx == 0.0 && *dy == 0.0));
}
#endif

void	game_handle_mouse(t_app *app)
{
	t_game	*g;
	double	dx;
	double	dy;
	double	sens;
	int32_t	cx;
	int32_t	cy;

	g = app->game;
	cx = g->mlx->width / 2;
	cy = g->mlx->height / 2;
	sens = g->mouse_sens;
	if (g->mouse.active == false)
	{
#ifdef __EMSCRIPTEN__
		mlx_get_mouse_pos(g->mlx, &cx, &cy);
		g->mouse.last_x = (double)cx;
		g->mouse.last_y = (double)cy;
#else
		mlx_set_mouse_pos(g->mlx, cx, cy);
#endif
		g->mouse.active = true;
		return ;
	}
#ifdef __EMSCRIPTEN__
	if (game_mouse_delta_relative(g, &dx, &dy) == false)
		return ;
	sens *= 0.90;
#else
	if (game_mouse_delta_center(g, &dx, &dy) == false)
	{
		mlx_set_mouse_pos(g->mlx, cx, cy);
		return ;
	}
#endif
	g->player.dir += dx * sens;
	g->player.pitch -= dy * sens;
	game_wrap_angle(&g->player.dir);
	game_clamp_pitch(&g->player.pitch);
#ifndef __EMSCRIPTEN__
	mlx_set_mouse_pos(g->mlx, cx, cy);
#endif
}
