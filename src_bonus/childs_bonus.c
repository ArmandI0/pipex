/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:54:56 by aranger           #+#    #+#             */
/*   Updated: 2024/02/06 18:23:43 by aranger          ###   ########.fr       */
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
			exit(exit_file_error(cmd, pipe_fd, f_path));
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd);
		if (cmd != NULL)
			execve(cmd->command_path, cmd->command, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
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
		if (cmd != NULL)
			execve(cmd->command_path, cmd->command, envp);
		exit(EXIT_FAILURE);
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
			exit(exit_file_error(cmd, p_fd, f_path));
		dup2(p_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		close_pipe(p_fd);
		close(file_fd);
		if (cmd != NULL)
			execve(cmd->command_path, cmd->command, envp);
		exit (EXIT_FAILURE);
	}
	close_pipe(p_fd);
	waitpid(pid, NULL, 0);
	free_cmd_struct(cmd);
	return (1);
}
