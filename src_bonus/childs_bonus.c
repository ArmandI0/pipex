/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:54:56 by aranger           #+#    #+#             */
/*   Updated: 2024/01/30 13:41:17 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	dup_pipe(t_pipe p_fd, int file_fd)
{
	if (file_fd == -1)
	{
		if (p_fd.status == 0)
		{
			dup2(p_fd.pipe_fd1[0], STDIN_FILENO);
			dup2(p_fd.pipe_fd2[1], STDOUT_FILENO);
		}
		else if (p_fd.status == 1)
		{
			dup2(p_fd.pipe_fd2[0], STDIN_FILENO);
			dup2(p_fd.pipe_fd1[1], STDOUT_FILENO);
		}
	}
	else
	{
		if (p_fd.status == 0)
		{
			dup2(p_fd.pipe_fd1[0], STDIN_FILENO);
			dup2(file_fd, STDOUT_FILENO);
		}
		else if (p_fd.status == 1)
		{
			dup2(p_fd.pipe_fd2[0], STDIN_FILENO);
			dup2(file_fd, STDOUT_FILENO);
		}
	}
}

int	first_child(t_command *cmd, char *f_path, int pipe_fd[2], char **envp)
{
	int	file_fd;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		file_fd = open(f_path, O_RDONLY);
		if (file_fd == -1)
			return (0);
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

int	pipe_to_pipe_child(t_command *cmd, t_pipe p_fd, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup_pipe(p_fd, -1);
		close_pipe(p_fd.pipe_fd1);
		close_pipe(p_fd.pipe_fd2);
		execve(cmd->command_path, cmd->command, envp);
		return (-1);
	}
	if (p_fd.status)
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
	return (0);
}

int	last_child(t_command *cmd, char *f_path, t_pipe p_fd, char **envp)
{
	int	file_fd;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		file_fd = open(f_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			return (0);
		dup_pipe(p_fd, file_fd);
		close_pipe(p_fd.pipe_fd1);
		close_pipe(p_fd.pipe_fd2);
		close(file_fd);
		execve(cmd->command_path, cmd->command, envp);
		return (-1);
	}
	close_pipe(p_fd.pipe_fd1);
	close_pipe(p_fd.pipe_fd2);
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
	return (1);
}
