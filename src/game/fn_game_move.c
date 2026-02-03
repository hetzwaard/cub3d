/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_move.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 02:14:57 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:31:49 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_get_wish(t_game *g, t_move *m)
{
	double	dx;
	double	dy;
	double	rx;
	double	ry;
	double	len;

	dx = cos(g->player.dir);
	dy = sin(g->player.dir);
	rx = -dy;
	ry = dx;
	m->wx = dx * m->fwd + rx * m->right;
	m->wy = dy * m->fwd + ry * m->right;
	len = sqrt(m->wx * m->wx + m->wy * m->wy);
	if (len > 0.0)
	{
		m->wx /= len;
		m->wy /= len;
	}
	if (len > 1.0)
		len = 1.0;
	m->ws = m->speed * len;
}

static void	game_apply_friction(t_game *g)
{
	double	speed;
	double	new_speed;

	speed = sqrt(g->player.vx * g->player.vx
			+ g->player.vy * g->player.vy);
	if (speed < 0.0001)
		return ;
	new_speed = speed - speed * GAME_FRICTION * g->dt;
	if (new_speed < 0.0)
		new_speed = 0.0;
	g->player.vx *= new_speed / speed;
	g->player.vy *= new_speed / speed;
}

static void	game_accelerate(t_game *g, t_move *m, double accel)
{
	double	cur;
	double	add;
	double	accel_speed;

	if (m->ws <= 0.0)
		return ;
	cur = g->player.vx * m->wx + g->player.vy * m->wy;
	add = m->ws - cur;
	if (add <= 0.0)
		return ;
	accel_speed = accel * g->dt * m->ws;
	if (accel_speed > add)
		accel_speed = add;
	g->player.vx += accel_speed * m->wx;
	g->player.vy += accel_speed * m->wy;
}

void	game_apply_movement(t_app *app, double fwd, double right,
		double speed)
{
	t_game	*g;
	t_move	move;
	bool	grounded;
	double	ground;

	g = app->game;
	move.fwd = fwd;
	move.right = right;
	move.speed = speed;
	game_get_wish(g, &move);
	ground = 0.0;
	grounded = (g->player.z <= ground && g->player.vz <= 0.0);
	if (grounded)
		game_apply_friction(g);
	if (grounded)
		game_accelerate(g, &move, GAME_ACCEL_GROUND);
	else
		game_accelerate(g, &move, GAME_ACCEL_AIR);
	game_try_move(app, g->player.x + g->player.vx * g->dt,
		g->player.y + g->player.vy * g->dt);
}
