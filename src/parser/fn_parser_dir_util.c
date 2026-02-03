/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_dir_util.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:24 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 20:14:23 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_direction(char *str)
{
	if (!ft_strncmp(str, "NO", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "SO", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "EA", ft_strlen(str)))
		return (true);
	else if (!ft_strncmp(str, "WE", ft_strlen(str)))
		return (true);
	return (false);
}

bool	add_direction(t_config *config, char **line)
{
	char	*texture_path;

	if (line[1] == NULL)
		return (false);
	texture_path = ft_strdup(line[1]);
	if (texture_path == NULL)
		return (false);
	if (!ft_strncmp(line[0], "NO", 2) && config->north_tex_path == NULL)
		config->north_tex_path = texture_path;
	else if (!ft_strncmp(line[0], "SO", 2) && config->south_tex_path == NULL)
		config->south_tex_path = texture_path;
	else if (!ft_strncmp(line[0], "EA", 2) && config->east_tex_path == NULL)
		config->east_tex_path = texture_path;
	else if (!ft_strncmp(line[0], "WE", 2) && config->west_tex_path == NULL)
		config->west_tex_path = texture_path;
	else
		return (ft_free(texture_path), false);
	return (true);
}
