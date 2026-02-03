/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_file.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:26 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/01/26 18:21:46 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parser_state	fn_parser_file(t_config *config, t_map *map)
{
	(void)map;
	if (is_valid_file(config->filename, ".cub") == false)
		return (PARSER_ERROR);
	return (PARSER_IDENTIFIER);
}
