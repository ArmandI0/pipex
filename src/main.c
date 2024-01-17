/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:35 by aranger           #+#    #+#             */
/*   Updated: 2024/01/17 16:07:13 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	//char	*path;
	char	*command;

	i = 0;
	command = "ls";
	if (argc != 5)
		return (0);
	ft_printf("retour parsing : %d", parse_entry(argc, argv, envp));
	// path = set_command_path(envp, command);
	// ft_printf("%s", path);
	// free(path);
}