/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_color_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:20 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 20:46:58 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_rgb(uint32_t r, uint32_t g, uint32_t b)
{
	return (255 << 24 | b << 16 | g << 8 | r);
}

static bool	is_valid_rgb(char *color)
{
	int	i;

	i = 0;
	while (ft_isdigit(color[i]))
		i++;
	return (color[i] == '\0' && (ft_atoi(color) <= 255 && ft_atoi(color) >= 0));
}

static bool	set_rgb(uint32_t *rgb_to_set, char *rgb)
{
	char	**split;

	split = ft_split(rgb, ',');
	if (split == NULL)
		return (false);
	if (ft_get_split_size(split) != 3)
		return (ft_free_matrix(split), false);
	if (is_valid_rgb(split[0]) && is_valid_rgb(split[1])
		&& is_valid_rgb(split[2]))
		*rgb_to_set = get_rgb((uint32_t)ft_atoi(split[0]),
				(uint32_t)ft_atoi(split[1]), (uint32_t)ft_atoi(split[2]));
	ft_free_matrix(split);
	return (true);
}

bool	add_color(t_config *config, char **split)
{
	bool	status;

	if (ft_get_split_size(split) != 2)
		return (false);
	status = false;
	if (!ft_strncmp(split[0], "F", 1) && config->floor_rgb == RGBA_DEF)
	{
		status = set_rgb((uint32_t *)&config->floor_rgb, split[1]);
	}
	else if (!ft_strncmp(split[0], "C", 1) && config->ceil_rgb == RGBA_DEF)
	{
		status = set_rgb((uint32_t *)&config->ceil_rgb, split[1]);
	}
	else
		return (false);
	return (status);
}

bool	is_color(char *str)
{
	if (ft_strncmp(str, "F", ft_strlen(str)) == 0)
		return (true);
	else if (ft_strncmp(str, "C", ft_strlen(str)) == 0)
		return (true);
	return (false);
}
