/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:31:10 by aranger           #+#    #+#             */
/*   Updated: 2024/01/30 11:11:06 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_command	*struct_command(char *arg, char **envp)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->command = ft_split(arg, ' ');
	cmd->command_path = find_command_path(envp, arg);
	if (cmd->command == NULL || cmd->command_path == NULL)
	{
		if (cmd->command != NULL)
			free_split(cmd->command);
		if (cmd->command != NULL)
			free(cmd->command_path);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int	check_file_exist(char *path)
{
	int	a;

	a = access(path, F_OK);
	if (a == -1)
		return (0);
	a = access(path, W_OK);
	if (a == -1)
		return (-1);
	return (1);
}

t_bool	check_path_acces(char *path)
{
	int	a;

	a = access(path, F_OK | R_OK);
	if (a == -1)
		return (FALSE);
	return (TRUE);
}
