/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/01/30 12:08:55 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_pipe(char **argv, char **envp)
{
	t_command	*cmd;
	int			pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (0);
	cmd = struct_command(argv[2], envp);
	if (cmd == NULL)
		command_error(argv[2]);
	else
		if (first_child(cmd, argv[1], pipe_fd, envp) == 0)
			return (close_and_finish(cmd, pipe_fd, argv[1]));
	cmd = struct_command(argv[3], envp);
	if (last_child(cmd, argv[4], pipe_fd, envp) == 0)
		return (close_and_finish(cmd, pipe_fd, argv[4]));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd;
	int			file_fd;

	if (argc != 5)
	{
		ft_putstr_fd("too few arguments\n", 2);
		return (0);
	}
	cmd = struct_command(argv[3], envp);
	if (cmd == NULL)
	{
		command_error(argv[3]);
		file_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			return (0);
		close(file_fd);
		return (1);
	}
	free_cmd_struct(cmd);
	exec_pipe(argv, envp);
	return (0);
}
