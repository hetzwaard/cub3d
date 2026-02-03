/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_sprite_render.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:29:52 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:29:54 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bonus_sprite_bounds(t_sprite_cast *cast);

static bool	bonus_sprite_transform(t_game *g, t_sprite *s,
		t_sprite_ctx *ctx, t_sprite_cast *cast)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	trans_x;
	double	trans_y;

	sprite_x = s->x - g->player.x;
	sprite_y = s->y - g->player.y;
	inv_det = 1.0 / ctx->det;
	trans_x = inv_det * (ctx->dir_y * sprite_x - ctx->dir_x * sprite_y);
	trans_y = inv_det * (-ctx->plane_y * sprite_x + ctx->plane_x * sprite_y);
	if (trans_y <= 0.01)
		return (false);
	cast->ty = trans_y;
	cast->screen_x = (int)((g->render_w / 2.0)
			* (1.0 + trans_x / trans_y));
	cast->h = (int)fabs(g->render_h / trans_y);
	cast->w = cast->h;
	cast->start_y = -cast->h / 2 + g->render_h / 2 + ctx->pitch;
	cast->end_y = cast->h / 2 + g->render_h / 2 + ctx->pitch;
	bonus_sprite_bounds(cast);
	return (true);
}

static void	bonus_sprite_bounds(t_sprite_cast *cast)
{
	cast->start_x = -cast->w / 2 + cast->screen_x;
	cast->end_x = cast->w / 2 + cast->screen_x;
}

static void	bonus_sprite_draw_ctx(t_game *g, t_sprite_cast *cast,
		double shade, char type)
{
	t_sprite_draw	draw;

	if (cast->h <= 0 || cast->w <= 0)
		return ;
	draw.g = g;
	draw.cast = cast;
	draw.xpm = NULL;
	if (type == 'K')
		draw.xpm = g->key_xpm;
	draw.color = bonus_sprite_color(g, type);
	draw.shade = shade;
	bonus_sprite_draw(&draw);
}

static void	bonus_render_one(t_app *app, t_game *g, t_sprite_ctx *ctx,
		t_sprite *s)
{
	t_sprite_cast	cast;
	double			shade;
	char			type;

	type = bonus_cell_at(app, (int)s->x, (int)s->y);
	if (type != 'K')
		return ;
	if (bonus_sprite_transform(g, s, ctx, &cast) == false)
		return ;
	if (type == 'K')
	{
		shade = fabs(cos(mlx_get_time() * 4.0));
		cast.w = (int)(cast.w * (0.4 + shade * 0.6));
		if (cast.w < 1)
			cast.w = 1;
		bonus_sprite_bounds(&cast);
	}
	shade = 1.0 / (1.0 + cast.ty * 0.15);
	if (shade < 0.2)
		shade = 0.2;
	bonus_sprite_draw_ctx(g, &cast, shade, type);
}

void	bonus_render_sprites(t_app *app)
{
	t_game			*g;
	t_sprite_ctx	ctx;
	int				i;

	g = app->game;
	if (g->sprite_count == 0 || g->zbuffer == NULL)
		return ;
	ctx.dir_x = cos(g->player.dir);
	ctx.dir_y = sin(g->player.dir);
	ctx.plane_x = -ctx.dir_y * tan(g->fov_rad / 2.0);
	ctx.plane_y = ctx.dir_x * tan(g->fov_rad / 2.0);
	ctx.det = ctx.plane_x * ctx.dir_y - ctx.dir_x * ctx.plane_y;
	if (ctx.det == 0.0)
		return ;
	ctx.pitch = bonus_pitch_offset(g);
	i = 0;
	while (i < g->sprite_count)
	{
		bonus_render_one(app, g, &ctx, &g->sprites[i]);
		i++;
	}
}
