/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:27:15 by aranger           #+#    #+#             */
/*   Updated: 2024/02/05 15:35:31 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	exit_file_error(t_command *cmd, int p_fd[2], char *arg)
{
	free_cmd_struct(cmd);
	close_pipe(p_fd);
	file_error(arg);
	return (EXIT_FAILURE);
}

int	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

void	free_cmd_struct(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd != NULL)
	{
		if (cmd->command != NULL)
			free_split(cmd->command);
		if (cmd->command != NULL)
			free(cmd->command_path);
		free(cmd);
		cmd = NULL;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}
