/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 04:31:46 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:32:17 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_ray_ctx_init(t_game *g, t_ray_ctx *ctx)
{
	double	plane_len;

	ctx->dir_x = cos(g->player.dir);
	ctx->dir_y = sin(g->player.dir);
	plane_len = tan(g->fov_rad / 2.0);
	ctx->plane_x = -ctx->dir_y * plane_len;
	ctx->plane_y = ctx->dir_x * plane_len;
}

void	game_render(t_app *app)
{
	t_game		*g;
	t_ray		ray;
	int			x;
	t_ray_ctx	ctx;

	g = app->game;
	if (g == NULL || g->img == NULL)
		return ;
	game_ray_ctx_init(g, &ctx);
	x = 0;
	while (x < g->render_w)
	{
		game_ray_init(g, &ray, x, &ctx);
		game_ray_cast(app, &ray);
		game_draw_column(app, x, &ray);
		if (g->zbuffer)
			g->zbuffer[x] = ray.dist;
		x++;
	}
}
