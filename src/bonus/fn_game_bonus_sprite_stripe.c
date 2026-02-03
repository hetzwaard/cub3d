/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_sprite_stripe.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:29:56 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:29:58 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_draw_sprite_stripe(t_game *g, t_sprite_line *line,
		uint32_t color)
{
	int	y;

	if (line->x < 0 || line->x >= g->render_w)
		return ;
	if (line->y_start < 0)
		line->y_start = 0;
	if (line->y_end >= g->render_h)
		line->y_end = g->render_h - 1;
	y = line->y_start;
	while (y <= line->y_end)
	{
		bonus_put_pixel(g, line->x, y, color);
		y++;
	}
}
