/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_settings.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/31 20:10:06 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:32:37 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_set_render_scale(t_game *game)
{
	if (game->win_w >= GAME_RENDER_CUTOFF_W
		|| game->win_h >= GAME_RENDER_CUTOFF_H)
		game->render_scale = GAME_RENDER_SCALE_HI;
	else
		game->render_scale = GAME_RENDER_SCALE_LO;
	game->render_w = (int32_t)(game->win_w * game->render_scale);
	game->render_h = (int32_t)(game->win_h * game->render_scale);
	if (game->render_w < 1)
		game->render_w = 1;
	if (game->render_h < 1)
		game->render_h = 1;
}

void	game_set_fov(t_game *game, double fov_deg)
{
	if (fov_deg < GAME_FOV_MIN)
		fov_deg = GAME_FOV_MIN;
	if (fov_deg > GAME_FOV_MAX)
		fov_deg = GAME_FOV_MAX;
	game->fov_deg = fov_deg;
	game->fov_rad = (fov_deg * GAME_PI) / 180.0;
}
