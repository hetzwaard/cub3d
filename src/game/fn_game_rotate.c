/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_rotate.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 05:37:51 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:32:28 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_wrap_angle(double *angle)
{
	while (*angle < 0.0)
		*angle += 2.0 * GAME_PI;
	while (*angle >= 2.0 * GAME_PI)
		*angle -= 2.0 * GAME_PI;
}

void	game_clamp_pitch(double *pitch)
{
	if (*pitch > GAME_PITCH_MAX)
		*pitch = GAME_PITCH_MAX;
	if (*pitch < -GAME_PITCH_MAX)
		*pitch = -GAME_PITCH_MAX;
}

void	game_rotate(t_game *game, double rot)
{
	game->player.dir += rot;
	game_wrap_angle(&game->player.dir);
}
