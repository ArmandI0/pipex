/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:16:18 by aranger           #+#    #+#             */
/*   Updated: 2024/01/18 13:40:29 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	command_error(char *command)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("/n", 2);
	return (FALSE);
}

t_bool	file_error(char *file)
{
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("/n", 2);
	return (FALSE);
}