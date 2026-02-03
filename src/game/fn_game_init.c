/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 13:37:52 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 19:32:12 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_init_player(t_app *app)
{
	t_game	*game;
	char	start;

	game = app->game;
	game->player.x = app->map->start_pos.x + 0.5;
	game->player.y = app->map->start_pos.y + 0.5;
	start = app->map->map_2d[app->map->start_pos.y][app->map->start_pos.x];
	if (start == 'N')
		game->player.dir = GAME_PI * 1.5;
	else if (start == 'S')
		game->player.dir = GAME_PI / 2.0;
	else if (start == 'W')
		game->player.dir = GAME_PI;
	else
		game->player.dir = 0;
	game->player.pitch = 0;
	if (is_bonus_mode() && app->map->has_lava)
		game->player.pitch = GAME_LAVA_PITCH;
	game->player.vx = 0;
	game->player.vy = 0;
	game->player.z = 0;
	game->player.vz = 0;
}

void	game_init_map(t_app *app)
{
	app->game->map_h = app->map->height;
	app->game->map_w = app->map->width;
}

static void	game_init_base(t_game *game)
{
	game->win_w = GAME_WIN_W;
	game->win_h = GAME_WIN_H;
	game->move_speed = GAME_MOVE_SPEED;
	game->rot_speed = GAME_ROT_SPEED;
	game->mouse_sens = GAME_MOUSE_SENS;
	game->frame_time = 1.0 / GAME_TARGET_FPS;
	game->accum = 0;
	game_set_fov(game, GAME_FOV_DEFAULT);
	game_set_render_scale(game);
	game->mouse.active = false;
	game->img = NULL;
	game->wall = NULL;
	game->mlx = NULL;
}

static void	game_init_state(t_game *game)
{
	game->last_time = 0;
	game->dt = 0;
	game->zbuffer = NULL;
	game->prev_frame = NULL;
	game->sprites = NULL;
	game->sprite_count = 0;
	game->minimap_enabled = is_bonus_mode() && GAME_ENABLE_MINIMAP;
	game->blur_enabled = is_bonus_mode() && GAME_ENABLE_BLUR;
	game->keys = 0;
	game->door_unlocked = NULL;
	game->key_xpm = NULL;
}

void	game_init_defaults(t_game *game)
{
	game_init_base(game);
	game_init_state(game);
}
