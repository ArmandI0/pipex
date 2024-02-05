/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/02/01 18:27:58 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_pipe(int argc, char **argv, char **envp)
{
	t_command	*cmd;
	int			p_fd[2];
	int			new_p_fd[2];
	int			i = 2;

	if (pipe(p_fd) < 0)
		return ;
	while (i < argc - 1)
	{
		cmd = struct_command(argv[i], envp);
		if (cmd == NULL)
			command_error(argv[i]);
		if (i == 2)
			first_child(cmd, argv[1], p_fd, envp);
		else if (i == argc - 2)
			last_child(cmd, argv[argc - 1], p_fd, envp);
		else if(cmd != NULL)
		{
			if (pipe(new_p_fd) < 0)
				return ;
			pipe_to_pipe_child(cmd, p_fd, new_p_fd, envp);
		}
		free_cmd_struct(cmd);
		i++;
	}
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
