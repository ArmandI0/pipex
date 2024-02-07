/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/02/07 11:52:54 by aranger          ###   ########.fr       */
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
	first_child(cmd, argv[1], pipe_fd, envp);
	cmd = struct_command(argv[3], envp);
	last_child(cmd, argv[4], pipe_fd, envp);
	if (cmd == NULL)
		command_error(argv[2]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putstr_fd("too few arguments\n", 2);
		return (0);
	}
	if (argc > 5)
	{
		ft_putstr_fd("too much arguments\n", 2);
		return (0);
	}
	exec_pipe(argv, envp);
	return (0);
}
