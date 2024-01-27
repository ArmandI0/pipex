/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/01/27 18:03:11 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include "unistd.h"
#include <sys/wait.h>

// void	write_out(char *path, char *buffer)
// {
// 	int	fd;

// 	fd = open(path, O_RDWR | O_CREAT | O_TRUNC);
// 	if (fd == -1)
// 		return;
// 	write(fd, buffer, ft_strlen(buffer));
// 	close(fd);
// }

void	read_pipe(int fd[2])
{
	char	*read;

	read = ft_calloc(1, sizeof(char));
	close(fd[1]);
	//open(fd[0], O_RDONLY);
	while (read != NULL)
	{
		free(read);
		read = get_next_line(fd[0]);
		ft_putstr_fd(read, 2);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*path;
	char	**command;
	char	*path2;
	char	**command2;
	int		file_fd;
	int		pid;
	int		pipe_fd[2];
	argc++;

	command = ft_split(argv[2], ' ');
	path = find_command_path(envp, argv[2]);

	command2 = ft_split(argv[3], ' ');
	path2 = find_command_path(envp, argv[3]);
	
	//open infile
	// dup2(oldfd, newfd)
	file_fd = open(argv[1], O_RDONLY);
	if (file_fd == -1)
		return(0);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);

	//open pipe

	if (pipe(pipe_fd) == -1)
 		return (0);

	//fork cmd 1
	file_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
	if (file_fd == -1)
		return(0);
	
	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(path, command, envp);
	}
	else
	{
		wait(NULL);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
		close(pipe_fd[1]);
		execve(path2, command2, envp);
	}

	//read_pipe(pipe_fd);
	free_split(command);
	free(path);
	
	//fork cmd 2
	
	// command2 = ft_split(argv[3], ' ');
	// path2 = find_command_path(envp, argv[3]);
	
	// file_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
	// if (file_fd == -1)
	// 	return(0);

	// if ((pid = fork()) < 0)
	// 	return (0);

	// if (pid == 0)
	// {
	// 	close(pipe_fd[1]);
	// 	dup2(pipe_fd[0], STDIN_FILENO);
	// 	close(pipe_fd[0]);
	// 	//dup2(file_fd, STDOUT_FILENO);
	// 	execve(path2, command2, envp);
	// }
	// else
	// {	
	// 	close(pipe_fd[1]);
	// }
	// dup2(file_fd, STDOUT_FILENO);
    // close(pipe_fd[1]);
    // close(file_fd);
	return (0);
}

/* programme pour une seule commande */

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*path;
// 	char	**command;
// 	int		file_fd;
// 	int		pid;
// 	argc++;

// 	command = ft_split(argv[2], ' ');
// 	path = find_command_path(envp, argv[2]);

// 	//open infile

// 	file_fd = open(argv[1], O_RDONLY);
// 	if (file_fd == -1)
// 		return(0);
// 	dup2(file_fd, STDIN_FILENO);
// 	close(file_fd);
	
// 	if ((pid = fork()) < 0)
// 		return (0);
// 	file_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
// 	if (file_fd == -1)
// 		return(0);
// 	if (pid == 0)
// 	{
// 		dup2(file_fd, STDOUT_FILENO);
//         close(file_fd);
// 		execve(path, command, envp);
// 	}
// 	else
// 	{
// 		wait(0);
// 		close(file_fd);
// 	}
// 	free_split(command);
// 	free(path);
// }