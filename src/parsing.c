/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:06:34 by aranger           #+#    #+#             */
/*   Updated: 2024/01/18 12:12:02 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	parse_entry(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*command_path;

	i = 2;
	if (check_path_acces(argv[1]) == FALSE)
		return (file_error(argv[1]));
	while (i < argc - 1)
	{
		command_path = find_command_path(envp, argv[i]);
		if (command_path == NULL)
			return (command_error(argv[i]));
		ft_printf("%s\n", command_path); //affiche le path 
		free (command_path);
		i++;
	}
	if (check_file_exist(argv[argc - 1]) == -1)
		return (file_error(argv[argc - 1]));
	return (TRUE);
}


