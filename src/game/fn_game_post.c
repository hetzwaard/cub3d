/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_post.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/27 04:36:11 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:31:59 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	game_blend_pixel(uint32_t cur, uint32_t prev)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
	uint32_t	w_prev;

	w_prev = GAME_BLUR_DEN - GAME_BLUR_NUM;
	r = (((cur >> 24) & 0xFF) * GAME_BLUR_NUM
			+ ((prev >> 24) & 0xFF) * w_prev) / GAME_BLUR_DEN;
	g = (((cur >> 16) & 0xFF) * GAME_BLUR_NUM
			+ ((prev >> 16) & 0xFF) * w_prev) / GAME_BLUR_DEN;
	b = (((cur >> 8) & 0xFF) * GAME_BLUR_NUM
			+ ((prev >> 8) & 0xFF) * w_prev) / GAME_BLUR_DEN;
	a = cur & 0xFF;
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	game_blend_at(uint32_t *buf, uint32_t *prev, size_t i)
{
	uint32_t	cur;
	uint32_t	blend;

	cur = buf[i];
	blend = game_blend_pixel(cur, prev[i]);
	buf[i] = blend;
	prev[i] = blend;
}

void	game_post_blur(t_game *game)
{
	uint32_t	*buf;
	uint32_t	*prev;
	size_t		i;
	size_t		len;

	if (game->blur_enabled == false || game->prev_frame == NULL)
		return ;
	buf = (uint32_t *)game->img->pixels;
	prev = game->prev_frame;
	len = (size_t)game->render_w * (size_t)game->render_h;
	i = 0;
	while (i < len)
	{
		game_blend_at(buf, prev, i);
		i++;
	}
}
