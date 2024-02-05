/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:54:56 by aranger           #+#    #+#             */
/*   Updated: 2024/01/31 18:56:46 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
			return (close_and_finish(cmd, pipe_fd, f_path));
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

int	pipe_to_pipe_child(t_command *cmd, int p_fd[2], int new_p_fd[2], char **envp)
{
	int	pid;

	pid = fork();
	
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(p_fd[0], STDIN_FILENO);
		dup2(new_p_fd[1], STDOUT_FILENO);
		close_pipe(p_fd);
		close_pipe(new_p_fd);
		execve(cmd->command_path, cmd->command, envp);
		return (-1);
	}
	close_pipe(p_fd);
	waitpid(pid, NULL, 0);
	p_fd[0] = new_p_fd[0];
	p_fd[1] = new_p_fd[1];
	free_cmd_struct(cmd);
	return (1);
}

int	last_child(t_command *cmd, char *f_path, int p_fd[2], char **envp)
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
			return (close_and_finish(cmd, p_fd, f_path));
		dup2(p_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		close_pipe(p_fd);
		close(file_fd);
		execve(cmd->command_path, cmd->command, envp);
		return (-1);
	}
	close_pipe(p_fd);
	//close(p_fd[0]);
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
	return (1);
}
