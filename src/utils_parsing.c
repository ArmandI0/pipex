/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:31:10 by aranger           #+#    #+#             */
/*   Updated: 2024/01/17 13:43:45 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	check_file_exist(char *path)
{
	int	a;

	a = access(path, F_OK | R_OK);
	if (a == -1)
		return(FALSE);
	return (TRUE);
}
