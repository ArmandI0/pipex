/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/01/31 15:05:21 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	exec_pipe(int argc, char **argv, char **envp)
{
	t_command	*cmd;
	t_pipe		*p_fd;
	int			i = 2;

	p_fd = init_s_pipe();
	if (p_fd == NULL)
		return (-1);
	while (i < argc - 1)
	{
		cmd = struct_command(argv[i], envp);
		if (cmd == NULL)
			command_error(argv[i]);
		if (i == 2)
		{
			if (first_child(cmd, argv[1], p_fd->pipe_fd1, envp) == 0)
				return (close_and_finish(cmd, p_fd, argv[1]));
		}
		else if (i == argc - 2)
		{
			if (last_child(cmd, argv[argc - 1], p_fd, envp) == 0)
				return (close_and_finish(cmd, p_fd, argv[argc - 1]));
		}
		else
			pipe_to_pipe_child(cmd, p_fd, envp);
		ft_putstr_fd(ft_itoa(p_fd->status), 2);
		i++;
	}
	return (0);
	// cmd = struct_command(argv[2], envp);
	// if (cmd == NULL)
	// 	command_error(argv[2]);
	// else
	// 	if (first_child(cmd, argv[1], pipe_fd, envp) == 0)
	// 		return (close_and_finish(cmd, pipe_fd, argv[1]));
	// cmd = struct_command(argv[3], envp);
	// pipe_to_pipe_child(cmd, pipe_fd, pipe_fd2, envp);
	// cmd = struct_command(argv[4], envp);
	// if (last_child(cmd, argv[5], pipe_fd2, envp) == 0)
	// 	return (close_and_finish(cmd, pipe_fd2, argv[5]));
	// return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd;
	int			file_fd;

	if (argc < 5)
	{
		ft_putstr_fd("too few arguments\n", 2);
		return (0);
	}
	cmd = struct_command(argv[argc - 2], envp);
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
	exec_pipe(argc, argv, envp);
	return (0);
}
