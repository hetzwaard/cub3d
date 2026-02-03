/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_wall_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:33:01 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:33:03 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	wall_tex_y(double tex_pos, int tex_h)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_h)
		tex_y = tex_h - 1;
	return (tex_y);
}

static uint32_t	wall_pixel_color(uint8_t *p, int shade_i)
{
	uint32_t	color;

	color = ((uint32_t)(p[0] * shade_i) >> 8) << 24;
	color |= ((uint32_t)(p[1] * shade_i) >> 8) << 16;
	color |= ((uint32_t)(p[2] * shade_i) >> 8) << 8;
	color |= p[3];
	return (color);
}

static void	wall_loop_setup(t_wall_loop *l, t_wall_draw *w, xpm_t *xpm)
{
	l->tex_w = (int)xpm->texture.width;
	l->tex_h = (int)xpm->texture.height;
	l->raw_start = (double)(-w->wb.line_h / 2 + w->wb.center);
	l->step = (double)l->tex_h / (double)w->wb.line_h;
	l->tex_pos = ((double)w->wb.b.start - l->raw_start) * l->step;
	l->y = w->wb.b.start;
}

void	game_draw_wall_loop(t_wall_draw *w, xpm_t *xpm, int tex_x, int shade_i)
{
	t_wall_loop	l;
	int			tex_y;
	uint8_t		*p;

	wall_loop_setup(&l, w, xpm);
	while (l.y <= w->wb.b.end)
	{
		tex_y = wall_tex_y(l.tex_pos, l.tex_h);
		p = &xpm->texture.pixels[(tex_y * l.tex_w + tex_x) * 4];
		w->col.buf[l.y * w->col.w + w->col.x]
			= wall_pixel_color(p, shade_i);
		l.tex_pos += l.step;
		l.y++;
	}
}
