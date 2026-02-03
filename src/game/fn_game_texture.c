/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_texture.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/31 18:21:01 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 19:32:18 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static uint32_t	game_sample_texture(xpm_t *xpm, double tex_x, double tex_y)
{
	int		x;
	int		y;
	uint8_t	*p;

	if (!xpm)
		return (0);
	x = (int)(tex_x * (double)xpm->texture.width);
	y = (int)(tex_y * (double)xpm->texture.height);
	if (x < 0)
		x = 0;
	if (x >= (int)xpm->texture.width)
		x = (int)xpm->texture.width - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)xpm->texture.height)
		y = (int)xpm->texture.height - 1;
	p = &xpm->texture.pixels[(y * xpm->texture.width + x) * 4];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static uint32_t	game_fallback_color(t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0)
		return (WALL_W);
	if (ray->side == 0)
		return (WALL_E);
	if (ray->dir_y > 0)
		return (WALL_N);
	return (WALL_S);
}

static xpm_t	*game_get_wall_texture(t_app *app, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0)
		return (app->config->west_texture);
	if (ray->side == 0)
		return (app->config->east_texture);
	if (ray->dir_y > 0)
		return (app->config->north_texture);
	return (app->config->south_texture);
}

uint32_t	game_wall_color(t_app *app, t_ray *ray, double tex_y)
{
	xpm_t	*xpm;
	double	tex_x;

	xpm = game_get_wall_texture(app, ray);
	if (xpm == NULL)
		return (game_fallback_color(ray));
	tex_x = ray->wall_x;
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = 1.0 - tex_x;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = 1.0 - tex_x;
	return (game_sample_texture(xpm, tex_x, tex_y));
}

int	game_init_textures(t_app *app)
{
	t_config	*cfg;

	cfg = app->config;
	if (cfg->north_tex_path)
		cfg->north_texture = mlx_load_xpm42(cfg->north_tex_path);
	if (cfg->south_tex_path)
		cfg->south_texture = mlx_load_xpm42(cfg->south_tex_path);
	if (cfg->east_tex_path)
		cfg->east_texture = mlx_load_xpm42(cfg->east_tex_path);
	if (cfg->west_tex_path)
		cfg->west_texture = mlx_load_xpm42(cfg->west_tex_path);
	return (!cfg->north_texture || !cfg->south_texture
		|| !cfg->east_texture || !cfg->west_texture);
}
