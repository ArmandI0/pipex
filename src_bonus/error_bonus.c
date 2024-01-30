/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:16:18 by aranger           #+#    #+#             */
/*   Updated: 2024/01/30 11:10:59 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command_error(char *command)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
}

void	file_error(char *file)
{
	ft_putstr_fd("no such file or directory, or access denied : ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
}
