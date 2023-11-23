/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:02:22 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 10:37:55 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "expander.h"
# include "struct.h"
# include "utils.h"
# include "errors.h"

// executor.c
void	expand_cmd(t_cmds *cmd, t_tools *tools);
int		multi_fork(t_tools *tools, int end[2], int fd_in, t_cmds *cmd);
int		check_heredoc_fd(t_tools *tools, int end[2], t_cmds *cmd);
int		wait_pipe(t_tools *tools, int *pid, int pipes);
void	executor(t_tools *tools);

// handle_cmd.c
int		seek_cmd(t_tools *tools, t_cmds *cmd);
void	handle_cmd(t_tools *tools, t_cmds *cmd);
void	dup_cmd(t_tools *tools, t_cmds *cmd, int end[2], int fd_in);
void	single_cmd(t_tools *tools, t_cmds *cmd);

// check_redirects.c
int		check_append(t_lex *redirect);
int		check_outfile(t_lex *redirect);
int		check_infile(char *filename);
int		check_redirects(t_cmds *cmd);

// heredoc.c
int		heredoc(t_tools *tools, t_lex *heredoc, char *file_name);
int		init_heredoc(t_tools *tools, t_lex *heredoc, char *temp_file);
char	*name_hd_file(void);
void	seek_heredoc(t_tools *tools, t_cmds *cmd);

#endif
