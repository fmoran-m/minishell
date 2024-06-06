/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:29:47 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 14:09:32 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_great(t_utils *utils, t_parse *process, int last_outfile)
{
	process->redirec->fd = open(process->redirec->doc,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	last_outfile = process->redirec->fd;
	return (last_outfile);
}

static int	open_append(t_utils *utils, t_parse *process, int last_outfile)
{
	process->redirec->fd = open(process->redirec->doc,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	last_outfile = process->redirec->fd;
	return (last_outfile);
}

void	open_files(t_utils *utils, t_parse *process,
	int *last_infile, int *last_outfile)
{
	while (process->redirec)
	{
		if (process->redirec->redir_type == MINUS
			|| process->redirec->redir_type == HEREDOC)
		{
			open_infiles(process, utils, last_infile);
			if (*last_infile == -2)
				return ;
		}
		else if (process->redirec->redir_type == GREAT
			|| process->redirec->redir_type == APPEND)
		{
			open_outfiles(process, utils, last_outfile);
			if (*last_outfile == -2)
				return ;
		}
		process->redirec = process->redirec->next;
	}
}
