/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_free.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/31 18:13:42 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/01/31 18:13:42 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	game_free(t_app *app)
{
	t_game	*g;

	if (app == NULL || app->game == NULL)
		return ;
	g = app->game;
	if (g->mlx && g->img)
		mlx_delete_image(g->mlx, g->img);
	if (g->mlx && g->wall)
		mlx_delete_image(g->mlx, g->wall);
	if (g->mlx)
		mlx_terminate(g->mlx);
	if (g->zbuffer)
		ft_free(g->zbuffer);
	if (g->prev_frame)
		ft_free(g->prev_frame);
	if (is_bonus_mode())
		game_bonus_free(app);
	g->mlx = NULL;
	g->img = NULL;
	g->wall = NULL;
	g->zbuffer = NULL;
	g->prev_frame = NULL;
}
