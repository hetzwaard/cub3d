/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_render.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:29:11 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:29:30 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_bonus_render(t_app *app)
{
	if (app == NULL || app->game == NULL || app->game->img == NULL)
		return ;
	bonus_update_keys(app);
	bonus_render_sprites(app);
	bonus_render_minimap(app);
	bonus_render_hud(app);
}
