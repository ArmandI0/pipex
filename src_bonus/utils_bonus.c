/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:31:10 by aranger           #+#    #+#             */
/*   Updated: 2024/02/07 17:12:38 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_command	*struct_command(char *arg, char **envp, int heredoc)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->command = ft_split(arg, ' ');
	cmd->command_path = find_command_path(envp, arg);
	cmd->heredoc = heredoc;
	cmd->command_name = arg;
	return (cmd);
}

int	open_outfile(char *path, t_command *cmd)
{
	int	file_fd;

	if (cmd->heredoc == 1)
		file_fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		file_fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (file_fd);
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
