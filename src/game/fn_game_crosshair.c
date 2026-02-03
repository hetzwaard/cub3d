/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_crosshair.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:30:50 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:30:52 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_put_pixel(t_game *g, int x, int y, uint32_t color)
{
	uint32_t	*buf;

	if (x < 0 || y < 0 || x >= g->render_w || y >= g->render_h)
		return ;
	buf = (uint32_t *)g->img->pixels;
	buf[y * g->render_w + x] = color;
}

static void	game_draw_hline(t_game *g, int cx, int cy, int thick)
{
	int	i;
	int	t;

	i = -CROSS_SIZE;
	while (i <= CROSS_SIZE)
	{
		t = 0;
		while (t < thick)
		{
			game_put_pixel(g, cx + i, cy - t, CROSS_COLOR);
			t++;
		}
		i++;
	}
}

static void	game_draw_vline(t_game *g, int cx, int cy, int thick)
{
	int	i;
	int	t;

	i = -CROSS_SIZE;
	while (i <= CROSS_SIZE)
	{
		t = 0;
		while (t < thick)
		{
			game_put_pixel(g, cx - t, cy + i, CROSS_COLOR);
			t++;
		}
		i++;
	}
}

void	game_draw_crosshair(t_game *g)
{
	int	cx;
	int	cy;
	int	thick_x;
	int	thick_y;

	if (g == NULL || g->img == NULL)
		return ;
	cx = g->render_w / 2;
	cy = g->render_h / 2;
	thick_x = 1 + (g->render_w % 2 == 0);
	thick_y = 1 + (g->render_h % 2 == 0);
	game_draw_hline(g, cx, cy, thick_y);
	game_draw_vline(g, cx, cy, thick_x);
}
