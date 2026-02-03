/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_identifiers.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:16 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 21:28:11 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Rules:
* Each element (except the map) firsts information 
* is the type identifier (composed by one or two character(s)), 
* followed by all specific informations for each
* object in a strict order.
*/

static bool	is_identifier(char **split, t_config *config)
{
	bool	flag;

	flag = false;
	if (is_direction(split[0]))
	{
		if (ft_get_split_size(split) != 1)
			flag = add_direction(config, split);
		else
			flag = false;
	}
	else if (is_color(split[0]))
	{
		if (ft_get_split_size(split) == 2)
			flag = add_color(config, split);
		else
			flag = false;
	}
	else
		flag = false;
	return (flag);
}

static bool	fill_line(char *line, t_config *config)
{
	char	*trimmed_str;
	char	**split;
	bool	flag;

	flag = false;
	trimmed_str = ft_strtrim(line, WHITESPACES);
	if (trimmed_str == NULL)
		return (fn_error(ERR_ALLOC), false);
	split = ft_split(trimmed_str, ' ');
	ft_free(trimmed_str);
	if (split == NULL)
		return (fn_error(ERR_ALLOC), false);
	flag = is_identifier(split, config);
	if (flag == false)
		fn_error(ERR_FILE_CONTENT);
	ft_free_matrix(split);
	return (flag);
}

static bool	is_done(t_config *config)
{
	return (config->east_tex_path != NULL
		&& config->west_tex_path != NULL
		&& config->north_tex_path != NULL
		&& config->south_tex_path != NULL
		&& config->ceil_rgb != RGBA_DEF
		&& config->floor_rgb != RGBA_DEF);
}

static int	parse_config(t_config *config, t_map *map)
{
	bool	flag;
	t_list	*file_content;
	int		map_start_index;

	flag = true;
	file_content = config->content_of_file;
	map_start_index = 0;
	while (file_content && flag)
	{
		map_start_index++;
		if (ft_is_emty_str((char *)file_content->content) == false)
			flag = fill_line((char *)file_content->content, config);
		if (is_done(config))
		{
			map->start_index = map_start_index;
			break ;
		}
		file_content = file_content->next;
	}
	return (flag);
}

t_parser_state	fn_parser_identifiers(t_config *config, t_map *map)
{
	bool	is_valid_parsing;
	bool	is_valid_texture;

	is_valid_parsing = parse_config(config, map);
	if (is_valid_parsing == false)
		return (PARSER_ERROR);
	is_valid_texture = is_valid_texture_file(config);
	if (is_valid_texture == false)
		return (PARSER_ERROR);
	return (PARSER_MAP);
}
