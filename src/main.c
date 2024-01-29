/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/01/29 13:52:55 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include "unistd.h"
#include <sys/wait.h>


int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmd;
	int			pipe_fd[2];
	int			pid;

	if (argc != 5)
		return (0);
	if (pipe(pipe_fd) < 0)
		return (0);
	cmd = struct_command(argv[2], envp);
	if (cmd == NULL)
		command_error(*cmd->command);
	else
	{
		if ((pid = fork()) < 0)
			return (0);
		if (pid == 0)
			first_child(cmd, argv[1], pipe_fd, envp);
		else
		{
			waitpid(pid, NULL, 0);
			free_cmd_struct(cmd);
		}
	}
	cmd = struct_command(argv[3], envp);
	if ((pid = fork()) < 0)
		return (0);
	if (pid == 0)
		ft_printf("%d", last_child(cmd, argv[4], pipe_fd, envp));
	else
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
		free_cmd_struct(cmd);
	}
}
