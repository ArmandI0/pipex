/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:54:56 by aranger           #+#    #+#             */
/*   Updated: 2024/01/29 17:04:24 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

t_command	*struct_command(char *arg, char *envp[])
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

int	first_child(t_command *cmd, char *f_path, int pipe_fd[2], char *envp[])
{
	int	file_fd;
	int	pid;

	if ((pid = fork()) < 0)
			return (-1);
	if (pid == 0)
	{
		file_fd = open(f_path, O_RDONLY);
		if (file_fd == -1)
			return(0);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd); 
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		execve(cmd->command_path, cmd->command, envp);
		return (-1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		free_cmd_struct(cmd);
	}
	return (1);
}

int	last_child(t_command *cmd, char *f_path, int pipe_fd[2], char *envp[])
{
	int	file_fd;
	int	pid;
	
	if ((pid = fork()) < 0)
			return (-1);
	if (pid == 0)
	{
		file_fd = open(f_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			return (0);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		close_pipe(pipe_fd);
		close(file_fd);
		execve(cmd->command_path, cmd->command, envp);
		return (-1);
	}
	close_pipe(pipe_fd);
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
	return (1);
}
