/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_collision.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:30:45 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:30:47 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	game_bonus_cell(char cell)
{
	if (is_bonus_mode() == false)
		return (-1);
	if (cell == 'D')
		return (1);
	if (cell == 'd' || cell == '2' || cell == 'L' || cell == 'K')
		return (0);
	return (-1);
}

bool	game_is_wall(t_app *app, int mx, int my)
{
	char	**map;
	int		row_len;
	char	cell;
	int		bonus;

	map = app->map->map_2d;
	if (my < 0 || my >= app->game->map_h || mx < 0)
		return (true);
	if (map[my] == NULL)
		return (true);
	if (app->map->row_len)
		row_len = app->map->row_len[my];
	else
		row_len = (int)ft_strlen(map[my]);
	if (mx >= row_len || mx < 0)
		return (true);
	cell = map[my][mx];
	bonus = game_bonus_cell(cell);
	if (bonus == 1)
		return (true);
	if (bonus == 0)
		return (false);
	return (cell == '1' || cell == ' ');
}

static bool	game_can_move(t_app *app, double x, double y)
{
	double	r;

	r = COLLISION_RADIUS;
	if (game_is_wall(app, (int)(x - r), (int)(y - r)))
		return (false);
	if (game_is_wall(app, (int)(x + r), (int)(y - r)))
		return (false);
	if (game_is_wall(app, (int)(x - r), (int)(y + r)))
		return (false);
	if (game_is_wall(app, (int)(x + r), (int)(y + r)))
		return (false);
	return (true);
}

void	game_try_move(t_app *app, double nx, double ny)
{
	t_player	*p;

	p = &app->game->player;
	if (game_can_move(app, nx, p->y))
		p->x = nx;
	else
		p->vx = 0.0;
	if (game_can_move(app, p->x, ny))
		p->y = ny;
	else
		p->vy = 0.0;
}
