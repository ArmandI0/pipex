/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/02/06 18:58:03 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_pipe(int argc, char **argv, char **envp, int heredoc)
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
		if (i == 2 && heredoc == 0)
			first_child(cmd, argv[1], p_fd, envp);
		else if(i == 2 && heredoc == 1)
		{
			read_entry(argv[2], p_fd);
			i++;
		}
		else if (i == argc - 2)
			last_child(cmd, argv[argc - 1], p_fd, envp);
		else
		{
			if (pipe(new_p_fd) < 0)
				return ;
			pipe_to_pipe_child(cmd, p_fd, new_p_fd, envp);
		}
		if (cmd == NULL && (heredoc != 1 && i != 3))
			command_error(argv[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	heredoc;

	heredoc = 0;
	if (argc < 5)
	{
		ft_putstr_fd("too few arguments\n", 2);
		return (0);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		heredoc = 1;
	exec_pipe(argc, argv, envp, heredoc);
	return (0);
}
