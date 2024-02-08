/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:23:43 by aranger           #+#    #+#             */
/*   Updated: 2024/02/08 12:19:55 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*read_entry(char *limiter, int p_fd[2], t_command *cmd)
{
	char	*tmp;
	int		size;

	tmp = ft_calloc(1, sizeof(char));
	limiter = ft_strjoin(limiter, "\n", 0);
	size = ft_strlen(limiter);
	while (ft_strncmp(tmp, limiter, size) != 0)
	{
		ft_putstr_fd(tmp, p_fd[1]);
		if (tmp != NULL)
			free(tmp);
		ft_putstr_fd("heredoc >", STDOUT_FILENO);
		tmp = get_next_line(0);
		if (tmp == NULL)
		{
			tmp = ft_strdup("");
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	if (tmp != NULL)
		free(tmp);
	if (cmd != NULL)
		free_cmd_struct(cmd);
	free(limiter);
	return (0);
}
