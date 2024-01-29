/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:27:15 by aranger           #+#    #+#             */
/*   Updated: 2024/01/29 11:50:22 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd_struct(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->command != NULL)
		free_split(cmd->command);
	if (cmd->command != NULL)
		free(cmd->command_path);
	free(cmd);
	cmd = NULL;
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}