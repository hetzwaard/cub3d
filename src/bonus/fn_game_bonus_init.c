/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_init.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 13:01:46 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 21:37:13 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	bonus_load_key_xpm(t_game *g)
{
	g->key_xpm = mlx_load_xpm42("assets/key.xpm42");
	if (g->key_xpm == NULL)
		return (fn_error(ERR_MLX), false);
	return (true);
}

static bool	bonus_init_doors(t_game *g)
{
	int	size;

	size = g->map_w * g->map_h;
	if (size <= 0)
		return (fn_error(ERR_LOAD_MAP), false);
	g->door_unlocked = ft_calloc(size, sizeof(bool));
	if (!g->door_unlocked)
		return (fn_error(ERR_ALLOC), false);
	return (true);
}

void	game_bonus_init(t_app *app)
{
	t_game	*g;
	int		count;

	g = app->game;
	bonus_load_key_xpm(g);
	bonus_init_doors(g);
	count = bonus_count_sprites(app);
	if (count < 0)
		return (fn_error(ERR_INVALID_MAP));
	g->sprites = ft_calloc(count, sizeof(t_sprite));
	if (g->sprites == NULL)
		return (fn_error(ERR_ALLOC));
	g->sprite_count = count;
	bonus_store_sprites(app, g->sprites);
}

void	game_bonus_free(t_app *app)
{
	if (app->game->sprites)
		ft_free(app->game->sprites);
	if (app->game->key_xpm)
		mlx_delete_xpm42(app->game->key_xpm);
	if (app->game->door_unlocked)
		ft_free(app->game->door_unlocked);
	app->game->sprites = NULL;
	app->game->sprite_count = 0;
	app->game->key_xpm = NULL;
	app->game->door_unlocked = NULL;
}
