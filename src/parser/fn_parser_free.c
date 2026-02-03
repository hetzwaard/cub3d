/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 21:26:35 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/01/31 18:25:12 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fn_config_free(t_config *config)
{
	ft_lstclear(&config->content_of_file, ft_free);
	if (config->north_texture)
		mlx_delete_xpm42(config->north_texture);
	if (config->south_texture)
		mlx_delete_xpm42(config->south_texture);
	if (config->east_texture)
		mlx_delete_xpm42(config->east_texture);
	if (config->west_texture)
		mlx_delete_xpm42(config->west_texture);
	ft_free(config->north_tex_path);
	ft_free(config->south_tex_path);
	ft_free(config->west_tex_path);
	ft_free(config->east_tex_path);
	ft_free(config->filename);
}

void	fn_map_free(t_map *map)
{
	ft_lstclear(&map->map, ft_free);
	ft_free_matrix(map->map_2d);
	ft_free(map->row_len);
}

void	fn_parser_free(t_config *config, t_map *map)
{
	fn_map_free(map);
	fn_config_free(config);
}
