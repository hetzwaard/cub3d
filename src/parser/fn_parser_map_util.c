/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_parser_map_util.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 20:16:34 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/01/26 19:17:25 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*skip_to_map(t_list *file, int start_index)
{
	int		i;

	i = 0;
	while (i < start_index)
	{
		i++;
		file = file->next;
	}
	while (ft_is_emty_str(file->content) == true)
		file = file->next;
	return (file);
}

void	fn_map_copy(t_config *config, t_map *map)
{
	t_list	*file;
	t_list	*new;
	char	*trimmed;

	file = skip_to_map(config->content_of_file, map->start_index);
	while (file)
	{
		if (ft_is_emty_str(file->content))
			trimmed = ft_strdup(" ");
		else
			trimmed = ft_strtrim(file->content, "\n");
		if (trimmed == NULL)
			return (fn_error(ERR_ALLOC));
		new = ft_lstnew(trimmed);
		if (new == NULL)
			return (fn_error(ERR_ALLOC), ft_free(trimmed));
		ft_lstadd_back(&map->map, new);
		file = file->next;
	}
}

static int	get_trimmed_index(char **map)
{
	int	last_index;

	last_index = 0;
	while (map[last_index])
		last_index++;
	last_index--;
	while (last_index >= 0)
	{
		if (ft_is_emty_str(map[last_index]))
			last_index--;
		else
			break ;
	}
	return (last_index);
}

char	**fn_map_trimmed(char **map)
{
	int		size;
	char	**new_map;
	int		i;

	size = get_trimmed_index(map);
	new_map = ft_calloc(size + 2, sizeof(char *));
	if (new_map == NULL)
		return (ft_free_matrix(map), NULL);
	i = 0;
	while (i < size + 1)
	{
		new_map[i] = ft_strdup(map[i]);
		if (map[i] == NULL)
			return (ft_free_matrix(new_map), ft_free_matrix(map), NULL);
		i++;
	}
	ft_free_matrix(map);
	return (new_map);
}

char	**fn_map_to_array(t_list *map)
{
	int		i;
	int		size;
	char	**map_2d;

	size = ft_lstsize(map);
	map_2d = ft_calloc(size + 1, sizeof(char *));
	if (map_2d == NULL)
		return (NULL);
	i = 0;
	while (map)
	{
		map_2d[i] = ft_strdup(map->content);
		if (map_2d[i] == NULL)
			return (ft_free_matrix(map_2d), NULL);
		map = map->next;
		i++;
	}
	return (map_2d);
}
