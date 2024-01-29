/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/01/29 10:55:04 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include "unistd.h"
#include <sys/wait.h>


int	main(int argc, char *argv[], char *envp[])
{
	char	*path;
	char	**command;
	int		file_fd;
	int		pipe_fd[2];
	int		pid;
	argc++;

	command = ft_split(argv[2], ' ');
	path = find_command_path(envp, argv[2]);

	//open infile

	file_fd = open(argv[1], O_RDONLY);
	if (file_fd == -1)
		return(0);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	if (pipe(pipe_fd) < 0)
		return (0);

	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execve(path, command, envp);
	}
	free_split(command);
	free(path);
	if ((pid = fork()) < 0)
		return (0);
	command = ft_split(argv[3], ' ');
	path = find_command_path(envp, argv[3]);
	file_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
	if (file_fd == -1)
		return(0);
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
        close(file_fd);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(file_fd);
		execve(path, command, envp);
	}
	else
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(file_fd);
		wait(0);
	}
	free_split(command);
	free(path);
}