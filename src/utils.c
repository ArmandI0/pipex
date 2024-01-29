/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:31:10 by aranger           #+#    #+#             */
/*   Updated: 2024/01/18 11:58:52 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file_exist(char *path)
{
	int	a;

	a = access(path, F_OK);
	if (a == -1)
		return(0);
	a = access(path, W_OK);
	if (a == -1)
		return (-1);
	return (1);
}

t_bool	check_path_acces(char *path)
{
	int	a;

	a = access(path, F_OK | R_OK);
	if (a == -1)
		return(FALSE);
	return (TRUE);
}