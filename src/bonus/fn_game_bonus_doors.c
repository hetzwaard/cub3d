/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_doors.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 13:46:55 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:20:16 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	bonus_door_unlocked(t_game *g, int x, int y)
{
	int	idx;

	if (g->door_unlocked == NULL)
		return (false);
	idx = y * g->map_w + x;
	return (g->door_unlocked[idx]);
}

static void	bonus_unlock_door(t_game *g, int x, int y)
{
	int	idx;

	if (g->door_unlocked == NULL)
		return ;
	idx = y * g->map_w + x;
	g->door_unlocked[idx] = true;
}

static void	bonus_toggle_at(t_game *g, char *row, int x, int y)
{
	bool	unlocked;

	if (row[x] != 'D' && row[x] != 'd')
		return ;
	unlocked = bonus_door_unlocked(g, x, y);
	if (row[x] == 'd' && unlocked == false)
		bonus_unlock_door(g, x, y);
	if (row[x] == 'D' && unlocked == false)
	{
		if (g->keys <= 0)
			return ;
		g->keys--;
		bonus_unlock_door(g, x, y);
	}
	if (row[x] == 'D')
		row[x] = 'd';
	else
		row[x] = 'D';
}

static void	bonus_toggle_door(t_app *app)
{
	t_game	*g;
	int		x;
	int		y;
	char	*row;

	g = app->game;
	x = (int)(g->player.x + cos(g->player.dir) * DOOR_REACH);
	y = (int)(g->player.y + sin(g->player.dir) * DOOR_REACH);
	if (y < 0 || y >= g->map_h || x < 0)
		return ;
	row = app->map->map_2d[y];
	if (row == NULL || x >= (int)ft_strlen(row))
		return ;
	bonus_toggle_at(g, row, x, y);
}

void	game_bonus_keyhook(mlx_key_data_t key, void *param)
{
	t_app	*app;

	app = param;
	if (key.action != MLX_PRESS)
		return ;
	if (key.key == MLX_KEY_E)
		bonus_toggle_door(app);
	if (key.key == MLX_KEY_M)
		app->game->minimap_enabled = !app->game->minimap_enabled;
}
