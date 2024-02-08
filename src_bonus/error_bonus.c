/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:16:18 by aranger           #+#    #+#             */
/*   Updated: 2024/02/08 11:02:40 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command_error(t_command *command)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command->command_name, 2);
	ft_putstr_fd("\n", 2);
	free_cmd_struct(command);
	close_std();
}

void	file_error(char *file)
{
	ft_putstr_fd("no such file or directory, or access denied : ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
}
