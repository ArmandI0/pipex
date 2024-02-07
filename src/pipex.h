/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:20:46 by aranger           #+#    #+#             */
/*   Updated: 2024/02/07 11:53:42 by aranger          ###   ########.fr       */
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

typedef struct s_command
{
	char	*command_path;
	char	**command;
}				t_command;

int			check_file_exist(char *path);
char		*find_command_path(char **envp, char *command);
void		free_split(char **split);
t_bool		check_path_acces(char *path);
void		command_error(char *command);
void		file_error(char *file);
void		free_cmd_struct(t_command *cmd);
int			first_child(t_command *cmd, char *f_path,
				int pipe_fd[2], char **envp);
int			last_child(t_command *cmd, char *f_path,
				int pipe_fd[2], char **envp);
t_command	*struct_command(char *arg, char **envp);
int			close_pipe(int pipe_fd[2]);
int			exit_file_error(t_command *cmd, int p_fd[2], char *arg);

#endif