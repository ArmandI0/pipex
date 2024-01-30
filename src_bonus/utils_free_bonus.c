/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:27:15 by aranger           #+#    #+#             */
/*   Updated: 2024/01/30 13:04:39 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	close_and_finish(t_command *cmd, t_pipe p_fd, char *arg)
{
	free_cmd_struct(cmd);
	close_pipe(p_fd.pipe_fd1);
	close_pipe(p_fd.pipe_fd2);
	file_error(arg);
	return (1);
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
	if (cmd->command != NULL)
		free_split(cmd->command);
	if (cmd->command != NULL)
		free(cmd->command_path);
	free(cmd);
	cmd = NULL;
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
