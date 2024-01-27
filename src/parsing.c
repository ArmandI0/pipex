/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:06:34 by aranger           #+#    #+#             */
/*   Updated: 2024/01/22 09:41:52 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_entry	*set_entry(int argc, char *argv[], char *envp[])
{
	t_entry	*entry;
	int		i;

	i = 1;
	envp++;
	entry = malloc(sizeof(t_entry));
	if (entry != NULL)
		return (NULL);
	entry->infile = argv[i];
	while (i < argc - 1)
	{
		i++;	
		
	}

	return (entry);
}

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

// static t_command	*add_command_to_struct(int argc, char *argv[], char *envp[])
// {
// 	int			i;
// 	int			j;
// 	t_command	*commands;

// 	i = 2;
// 	j = 0;
// 	while (i < argc - 1)
// 		i++;
// 	commands = ft_calloc(i + 1, sizeof(commands));
// 	if (commands == NULL)
// 		return (NULL);
// 	i = 2;
// 	while (i < argc - 1)
// 	{
// 		commands[j].command = ft_split(argv[i], ' ');
// 		commands[j].command_path = find_command_path(argv[i], envp);
// 		if (commands[j].command == NULL || commands[j].command_path == NULL)
// 		{
// 			free_command_struct(commands);
// 			break;
// 		}
// 		i++;
// 	}
// 	return (commands);
// }
