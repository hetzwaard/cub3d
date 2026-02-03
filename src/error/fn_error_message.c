/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_error_message.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 17:47:14 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/02 20:12:50 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// If any misconfiguration of any kind is encountered in the file, the program
// must exit properly and return "Error\n" followed by an explicit error message
// of your choice.

static char	*get_error_message(t_error err_num)
{
	static char	*err[14];

	if (err[0] == NULL)
	{
		err[ERR_ARGC] = "invalid amount of arguments";
		err[ERR_F_EXTENTION] = "invalid file extension.";
		err[ERR_FILE_CONTENT] = "invalid file content, check the file";
		err[ERR_OPEN] = "could not open file";
		err[ERR_ALLOC] = "error allocating memory";
		err[ERR_INVALID_MAP] = "map is invalid";
		err[ERR_INVALID_WALL] = "map is invalid (open wall detected)";
		err[ERR_INVALID_START] = "start position is invalid";
		err[ERR_FILE_INEXISTS] = "texture does not exist";
		err[ERR_TEX_SIZE] = "texture must be 64x64";
		err[ERR_LOAD_MAP] = "could not load map (map select)";
		err[ERR_UNKNOWN_ELEM] = "unknown element present in .cub file";
		err[ERR_MLX] = "mlx error occured";
		err[ERR_SIZE] = "n/a";
	}
	return (err[err_num]);
}

void	fn_error(t_error err_num)
{
	ft_printf("Error\n%s\n", get_error_message(err_num));
}
