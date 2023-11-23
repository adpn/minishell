/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:29:21 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 14:01:41 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>   // printf
# include <stdlib.h>  // malloc, free, exit
# include <unistd.h>  // access, open, read, close, fork, wait, waitpid,
// wait3, wait4, write, dup, execve, getcwd
# include <signal.h>  // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h> // stat, lstat, fstat
# include <fcntl.h>   // open
# include <dirent.h>  // opendir, readdir, closedir
# include <string.h>  // strerror
# include <errno.h>   // perror
# include <unistd.h>  // isatty, ttyname, ttyslot, ioctl
# include <stdlib.h>  // getenv
# include <termios.h> // tcsetattr, tcgetattr
# include <curses.h>  // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>
# include <readline/history.h>

# include "struct.h"

struct s_tools	g_tools;

#endif