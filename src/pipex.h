/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:46 by aranger           #+#    #+#             */
/*   Updated: 2024/01/29 19:00:18 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define TRUE 1
# define FALSE 0
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../lib/libft/src/libft.h"

typedef int	t_bool;

typedef	struct s_command
{
	char	*command_path;
	char	**command;
}				t_command;

int		check_file_exist(char *path);
char	*find_command_path(char *envp[], char *command);
void	print_split(char **split); // a supprimer
void	free_split(char **split);
t_bool	parse_entry(int argc, char *argv[], char *envp[]);
t_bool	check_path_acces(char *path);
void	command_error(char *command);
void	file_error(char *file);
void	free_cmd_struct(t_command *cmd);
int	first_child(t_command *cmd, char *f_path, int pipe_fd[2], char *envp[]);
int	last_child(t_command *cmd, char *f_path, int pipe_fd[2], char *envp[]);
t_command	*struct_command(char *arg, char *envp[]);
int	close_pipe(int pipe_fd[2]);
int	close_and_finish(t_command *cmd, int pipe_fd[2], char *arg);


#endif