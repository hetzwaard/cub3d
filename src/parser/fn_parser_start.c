/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_start.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:33 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/01/26 18:29:04 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	fn_list_copy_file_content(t_config *config)
{
	t_list	*new;
	char	*line;
	int		fd;

	fd = open(config->filename, O_RDONLY);
	if (fd == -1)
		return (fn_error(ERR_OPEN), false);
	new = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		return (fn_error(ERR_FILE_CONTENT), false);
	while (line)
	{
		new = ft_lstnew(line);
		if (new == NULL)
			return (fn_error(ERR_ALLOC), close(fd), ft_free(line), false);
		ft_lstadd_back(&config->content_of_file, new);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}

t_parser_state	fn_parser_start(t_config *config, t_map *map)
{
	bool	is_copied;

	(void)map;
	is_copied = fn_list_copy_file_content(config);
	if (is_copied == false)
		return (PARSER_ERROR);
	return (PARSER_FILE);
}
