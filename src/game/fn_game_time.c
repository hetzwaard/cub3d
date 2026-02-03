/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_time.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:32:53 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:32:55 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_time_update(t_game *game)
{
	double	now;

	now = mlx_get_time();
	game->dt = now - game->last_time;
	if (game->dt < 0.0)
		game->dt = 0.0;
	if (game->dt > 0.2)
		game->dt = 0.2;
	game->last_time = now;
	game->accum += game->dt;
}

bool	game_frame_ready(t_game *game)
{
	if (game->accum < game->frame_time)
		return (false);
	game->accum -= game->frame_time;
	game->dt = game->frame_time;
	if (game->accum > game->frame_time * 4.0)
		game->accum = game->frame_time;
	return (true);
}
