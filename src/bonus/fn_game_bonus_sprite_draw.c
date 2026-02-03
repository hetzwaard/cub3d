/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_sprite_draw.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:29:43 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:29:45 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	bonus_tex_color(xpm_t *xpm, int x, int y)
{
	uint8_t	*p;

	if (x < 0 || y < 0 || x >= (int)xpm->texture.width
		|| y >= (int)xpm->texture.height)
		return (0);
	p = &xpm->texture.pixels[(y * xpm->texture.width + x) * 4];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static int	bonus_tex_x(t_sprite_draw *d, int x)
{
	int	tex_x;

	tex_x = (x - d->cast->start_x) * (int)d->xpm->texture.width / d->cast->w;
	if (tex_x < 0 || tex_x >= (int)d->xpm->texture.width)
		return (-1);
	return (tex_x);
}

static void	bonus_tex_limits(t_sprite_draw *d, t_tex_state *t)
{
	t->y = d->cast->start_y;
	t->y_end = d->cast->end_y;
	if (t->y < 0)
		t->y = 0;
	if (t->y_end >= d->g->render_h)
		t->y_end = d->g->render_h - 1;
	t->step = (double)d->xpm->texture.height / d->cast->h;
	t->tex_pos = (t->y - d->cast->start_y) * t->step;
}

static void	bonus_draw_tex_stripe(t_sprite_draw *d, int x)
{
	t_tex_state	t;
	uint32_t	color;

	t.tex_x = bonus_tex_x(d, x);
	if (t.tex_x < 0)
		return ;
	bonus_tex_limits(d, &t);
	while (t.y <= t.y_end)
	{
		color = bonus_tex_color(d->xpm, t.tex_x, (int)t.tex_pos);
		if ((color & 0xFF) != 0)
			bonus_put_pixel(d->g, x, t.y,
				bonus_shade_color(color, d->shade));
		t.tex_pos += t.step;
		t.y++;
	}
}

void	bonus_sprite_draw(t_sprite_draw *d)
{
	t_sprite_line	line;
	int				x;

	x = d->cast->start_x;
	while (x <= d->cast->end_x)
	{
		if (x >= 0 && x < d->g->render_w && d->cast->ty < d->g->zbuffer[x])
		{
			if (d->xpm)
				bonus_draw_tex_stripe(d, x);
			else
			{
				line.x = x;
				line.y_start = d->cast->start_y;
				line.y_end = d->cast->end_y;
				bonus_draw_sprite_stripe(d->g, &line,
					bonus_shade_color(d->color, d->shade));
			}
		}
		x++;
	}
}
