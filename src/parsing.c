/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:06:34 by aranger           #+#    #+#             */
/*   Updated: 2024/01/17 16:12:38 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	parse_entry(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*command_path;

	i = 2;
	if (check_file_exist(argv[1]) == FALSE)
	{	
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(argv[1], 2);
		return (FALSE);
	}
	while (i < argc - 1)
	{
		command_path = set_command_path(envp, argv[i]);
		if (command_path == NULL)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(argv[i], 2);	
			return (FALSE);
		}
		free (command_path);
		i++;
	}
	return (TRUE);
}
