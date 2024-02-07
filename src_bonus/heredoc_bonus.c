/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:23:43 by aranger           #+#    #+#             */
/*   Updated: 2024/02/06 19:56:25 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*read_entry(char *limiter, int p_fd[2])
{
	
	char	*tmp;
	int size;
	size = ft_strlen(limiter);
	tmp = ft_calloc(1, sizeof(char));
	while (ft_strncmp(tmp, limiter, size) != 0)
	{
		if (tmp != NULL)
			free(tmp);
		ft_putstr_fd("heredoc >", STDOUT_FILENO);
		tmp = get_next_line(0);
		ft_putstr_fd(tmp, p_fd[1]);
	}
	if (tmp != NULL)
		free(tmp);
	return (0);
}