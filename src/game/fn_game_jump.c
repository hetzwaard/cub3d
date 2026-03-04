/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_jump.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:31:30 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:31:32 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	game_is_lava(t_app *app)
{
	t_player	*p;
	int			mx;
	int			my;

	if (is_bonus_mode() == false)
		return (false);
	p = &app->game->player;
	if (p->z > GAME_LAVA_Z || p->x < 0.0 || p->y < 0.0)
		return (false);
	mx = (int)p->x;
	my = (int)p->y;
	if (my < 0 || my >= app->map->height || mx < 0)
		return (false);
	if (app->map->row_len && mx >= app->map->row_len[my])
		return (false);
	if (app->map->map_2d[my] && app->map->map_2d[my][mx] == 'L')
		return (true);
	return (false);
}

static void	game_lava_reset(t_app *app)
{
	t_game	*game;
	double	respawn_x;
	double	respawn_y;
	double	last_dir;
	double	last_pitch;
	bool	checkpoint_armed;

	if (game_is_lava(app))
	{
		game = app->game;
		respawn_x = game->respawn_x;
		respawn_y = game->respawn_y;
		last_dir = game->player.dir;
		last_pitch = game->player.pitch;
		checkpoint_armed = game->checkpoint_armed;
		game_init_player(app);
		game->respawn_x = respawn_x;
		game->respawn_y = respawn_y;
		game->checkpoint_armed = checkpoint_armed;
		game->player.x = game->respawn_x;
		game->player.y = game->respawn_y;
		game->player.dir = last_dir;
		game->player.pitch = last_pitch;
		game_wrap_angle(&game->player.dir);
		game_clamp_pitch(&game->player.pitch);
	}
}

void	game_jump_start(t_app *app)
{
	double	ground;
	t_game	*game;

	game = app->game;
	ground = 0.0;
	if (game->player.z > ground || game->player.vz > 0.0)
		return ;
	game->player.vz = GAME_JUMP_VEL;
}

void	game_jump_update(t_app *app)
{
	double	ground;
	t_game	*game;

	game = app->game;
	ground = 0.0;
	if (game->player.z <= ground && game->player.vz <= 0.0)
	{
		game->player.z = ground;
		game->player.vz = 0.0;
	}
	else
	{
		game->player.vz -= GAME_JUMP_GRAVITY * game->dt;
		game->player.z += game->player.vz * game->dt;
		if (game->player.z <= ground)
		{
			game->player.z = ground;
			game->player.vz = 0.0;
		}
	}
	game_lava_reset(app);
}
