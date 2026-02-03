/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_file_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/31 18:03:43 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 18:11:33 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_file_perm_valid(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (fn_error(ERR_OPEN), false);
	close(fd);
	return (true);
}

static bool	is_file_name_valid(char *file, char *f_extention)
{
	char	*end;

	if (file == NULL)
		return (fn_error(ERR_F_EXTENTION), false);
	end = ft_strnstr(file, f_extention, ft_strlen(file));
	if (end == NULL)
		return (fn_error(ERR_F_EXTENTION), false);
	if (ft_strncmp(end, f_extention, ft_strlen(end)) == 0)
		return (true);
	return (fn_error(ERR_F_EXTENTION), false);
}

bool	is_valid_file(char *file, char *f_extention)
{
	if (!is_file_name_valid(file, f_extention))
		return (false);
	else if (!is_file_perm_valid(file))
		return (false);
	return (true);
}

bool	is_valid_texture_file(t_config *config)
{
	return (is_valid_file(config->east_tex_path, ".xpm42")
		&& is_valid_file(config->north_tex_path, ".xpm42")
		&& is_valid_file(config->west_tex_path, ".xpm42")
		&& is_valid_file(config->south_tex_path, ".xpm42"));
}
