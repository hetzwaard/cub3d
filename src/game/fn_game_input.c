/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_input.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:31:26 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:31:28 by mahkilic      ########   odam.nl         */
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

static bool	game_mouse_delta(t_game *g, double *dx, double *dy)
{
	int32_t	mx;
	int32_t	my;

	mlx_get_mouse_pos(g->mlx, &mx, &my);
	*dx = (double)mx - (g->win_w / 2.0);
	*dy = (double)my - (g->win_h / 2.0);
	return (!(*dx == 0.0 && *dy == 0.0));
}

void	game_handle_mouse(t_app *app)
{
	t_game	*g;
	double	dx;
	double	dy;

	g = app->game;
	if (g->mouse.active == false)
	{
		mlx_set_mouse_pos(g->mlx, g->win_w / 2, g->win_h / 2);
		g->mouse.active = true;
		return ;
	}
	if (game_mouse_delta(g, &dx, &dy) == false)
		return ;
	g->player.dir += dx * g->mouse_sens;
	g->player.pitch -= dy * g->mouse_sens;
	game_wrap_angle(&g->player.dir);
	game_clamp_pitch(&g->player.pitch);
	mlx_set_mouse_pos(g->mlx, g->win_w / 2, g->win_h / 2);
}
