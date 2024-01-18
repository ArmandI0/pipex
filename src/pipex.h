/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:46 by aranger           #+#    #+#             */
/*   Updated: 2024/01/18 11:30:14 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define TRUE 1
# define FALSE 0
# include <fcntl.h>
# include <unistd.h>
# include "../lib/libft/src/libft.h"

typedef int	t_bool;

int		check_file_exist(char *path);
char	*find_command_path(char *envp[], char *command);
void	print_split(char **split); // a supprimer
void	free_split(char **split);
t_bool	parse_entry(int argc, char *argv[], char *envp[]);
t_bool	check_path_acces(char *path);
t_bool	command_error(char *command);
t_bool	file_error(char *file);
#endif 