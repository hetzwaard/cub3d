/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_wall_draw.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:32:57 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:32:58 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	wall_fallback_color(t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0.0)
		return (WALL_W);
	if (ray->side == 0)
		return (WALL_E);
	if (ray->dir_y > 0.0)
		return (WALL_N);
	return (WALL_S);
}

static xpm_t	*wall_texture(t_app *app, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0.0)
		return (app->config->west_texture);
	if (ray->side == 0)
		return (app->config->east_texture);
	if (ray->dir_y > 0.0)
		return (app->config->north_texture);
	return (app->config->south_texture);
}

static int	wall_tex_x(t_ray *ray, int tex_w)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)tex_w);
	if (ray->side == 0 && ray->dir_x > 0.0)
		tex_x = tex_w - 1 - tex_x;
	if (ray->side == 1 && ray->dir_y < 0.0)
		tex_x = tex_w - 1 - tex_x;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_w)
		tex_x = tex_w - 1;
	return (tex_x);
}

static int	wall_shade_i(t_ray *ray)
{
	int	shade_i;

	shade_i = (int)(game_shade_factor(ray) * 256.0);
	if (shade_i < 0)
		shade_i = 0;
	if (shade_i > 256)
		shade_i = 256;
	return (shade_i);
}

void	game_draw_wall(t_wall_draw *w, t_app *app, t_ray *ray)
{
	xpm_t	*xpm;
	int		tex_x;
	int		tex_w;
	int		shade_i;

	xpm = wall_texture(app, ray);
	if (xpm == NULL)
	{
		game_fill_column(&w->col, w->wb.b.start, w->wb.b.end,
			wall_fallback_color(ray));
		return ;
	}
	tex_w = (int)xpm->texture.width;
	tex_x = wall_tex_x(ray, tex_w);
	shade_i = wall_shade_i(ray);
	game_draw_wall_loop(w, xpm, tex_x, shade_i);
}
