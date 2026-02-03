/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_ray.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 03:32:58 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:32:06 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	game_delta(double dir)
{
	if (dir == 0.0)
		return (HUGE_DIST);
	return (fabs(1.0 / dir));
}

void	game_ray_init(t_game *g, t_ray *ray, int x, t_ray_ctx *ctx)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)g->render_w - 1.0;
	ray->dir_x = ctx->dir_x + ctx->plane_x * camera_x;
	ray->dir_y = ctx->dir_y + ctx->plane_y * camera_x;
	ray->map_x = (int)g->player.x;
	ray->map_y = (int)g->player.y;
	ray->delta_dist_x = game_delta(ray->dir_x);
	ray->delta_dist_y = game_delta(ray->dir_y);
	ray->side = 0;
}

static void	game_ray_step_init(t_app *app, t_ray *ray)
{
	t_player	*p;

	p = &app->game->player;
	if (ray->dir_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->y) * ray->delta_dist_y;
	}
}

static void	game_ray_finish(t_app *app, t_ray *ray)
{
	if (ray->side == 0)
		ray->dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->dist < 0.0001)
		ray->dist = 0.0001;
	if (ray->side == 0)
		ray->wall_x = app->game->player.y + ray->dist * ray->dir_y;
	else
		ray->wall_x = app->game->player.x + ray->dist * ray->dir_x;
	ray->wall_x = ray->wall_x - (int)(ray->wall_x);
	if (ray->wall_x < 0.0)
		ray->wall_x += 1.0;
}

void	game_ray_cast(t_app *app, t_ray *ray)
{
	game_ray_step_init(app, ray);
	while (game_is_wall(app, ray->map_x, ray->map_y) == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
	game_ray_finish(app, ray);
}
