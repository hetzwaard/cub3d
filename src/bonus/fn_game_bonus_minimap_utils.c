/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_minimap_utils.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:29:08 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:29:32 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	bonus_cell_at(t_app *app, int x, int y)
{
	char	**map;
	int		len;

	map = app->map->map_2d;
	if (y < 0 || y >= app->game->map_h || x < 0)
		return (' ');
	if (map[y] == NULL)
		return (' ');
	if (app->map->row_len)
		len = app->map->row_len[y];
	else
		len = (int)ft_strlen(map[y]);
	if (x >= len)
		return (' ');
	return (map[y][x]);
}

uint32_t	bonus_minimap_color(char c)
{
	if (c == '1')
		return (MINI_WALL);
	if (c == ' ')
		return (MINI_VOID);
	if (c == 'D')
		return (MINI_DOOR);
	if (c == 'd')
		return (MINI_OPEN);
	if (c == '2')
		return (MINI_SPRITE);
	if (c == 'L')
		return (MINI_LAVA);
	if (c == 'K')
		return (MINI_KEY);
	return (MINI_EMPTY);
}

void	bonus_put_pixel(t_game *g, int x, int y, uint32_t color)
{
	uint32_t	*buf;

	if (x < 0 || y < 0 || x >= g->render_w || y >= g->render_h)
		return ;
	buf = (uint32_t *)g->img->pixels;
	buf[y * g->render_w + x] = color;
}

void	bonus_fill_rect_color(t_game *g, t_rect rect, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.h)
	{
		j = 0;
		while (j < rect.w)
		{
			bonus_put_pixel(g, rect.x + j, rect.y + i, color);
			j++;
		}
		i++;
	}
}

void	bonus_fill_rect_clipped(t_game *g, t_rect rect, t_rect box,
		uint32_t color)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = rect.x;
	y1 = rect.y;
	x2 = rect.x + rect.w;
	y2 = rect.y + rect.h;
	if (x1 < box.x)
		x1 = box.x;
	if (y1 < box.y)
		y1 = box.y;
	if (x2 > box.x + box.w)
		x2 = box.x + box.w;
	if (y2 > box.y + box.h)
		y2 = box.y + box.h;
	if (x1 >= x2 || y1 >= y2)
		return ;
	rect.x = x1;
	rect.y = y1;
	rect.w = x2 - x1;
	rect.h = y2 - y1;
	bonus_fill_rect_color(g, rect, color);
}
