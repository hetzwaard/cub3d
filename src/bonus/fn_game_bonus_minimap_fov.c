/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_minimap_fov.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/29 09:24:15 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:27:10 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	bonus_fov_blocked(t_app *app, double x, double y)
{
	char	c;

	c = bonus_cell_at(app, (int)floor(x), (int)floor(y));
	if (c == '1' || c == ' ' || c == 'D' || c == 'd')
		return (true);
	return (false);
}

static int	bonus_fov_max(t_app *app, double ca, double sa)
{
	int		len;
	int		i;
	double	dist;
	int		limit;

	len = MINI_RADIUS * MINI_TILE;
	i = 0;
	while (i <= len)
	{
		dist = (double)i / (double)MINI_TILE;
		if (bonus_fov_blocked(app, app->game->player.x + ca * dist,
				app->game->player.y + sa * dist))
		{
			limit = i - MINI_FOV_STAMP - 1;
			if (limit < 0)
				limit = 0;
			return (limit);
		}
		i++;
	}
	return (len);
}

static void	bonus_fov_stamp(t_game *g, int x, int y, uint32_t color)
{
	int	dx;
	int	dy;

	dy = -MINI_FOV_STAMP;
	while (dy <= MINI_FOV_STAMP)
	{
		dx = -MINI_FOV_STAMP;
		while (dx <= MINI_FOV_STAMP)
		{
			bonus_put_pixel(g, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	bonus_draw_fov_ray(t_app *app, t_point center, double ca,
		double sa)
{
	int			max;
	int			i;
	int			step;

	max = bonus_fov_max(app, ca, sa);
	if (max <= 0)
		return ;
	step = MINI_FOV_STEP;
	if (step < 1)
		step = 1;
	i = 0;
	while (i <= max)
	{
		bonus_fov_stamp(app->game, center.x + (int)(ca * i),
			center.y + (int)(sa * i),
			MINI_FOV | (uint32_t)((max - i) * MINI_FOV_ALPHA / max));
		i += step;
	}
}

void	bonus_draw_fov(t_app *app)
{
	t_point			center;
	t_fov_state		s;
	double			tmp;
	int				i;

	center.x = MINI_MARGIN + MINI_RADIUS * MINI_TILE + MINI_TILE / 2;
	center.y = MINI_MARGIN + MINI_RADIUS * MINI_TILE + MINI_TILE / 2;
	if (MINI_FOV_RAYS < 1)
		return ;
	s.half = app->game->fov_rad * 0.5;
	s.step = (s.half * 2.0) / (double)MINI_FOV_RAYS;
	s.ca = cos(app->game->player.dir - s.half);
	s.sa = sin(app->game->player.dir - s.half);
	s.cs = cos(s.step);
	s.ss = sin(s.step);
	i = 0;
	while (i <= MINI_FOV_RAYS)
	{
		bonus_draw_fov_ray(app, center, s.ca, s.sa);
		tmp = s.ca;
		s.ca = s.ca * s.cs - s.sa * s.ss;
		s.sa = s.sa * s.cs + tmp * s.ss;
		i++;
	}
}
