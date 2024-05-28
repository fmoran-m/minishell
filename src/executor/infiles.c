#include "../../minishell.h"

static int	open_infiles(t_utils *utils, t_parse *process)
{
	int	last_infile_fd;

	last_infile_fd = -1;
	process->redirec = process->redirec_head;
	while (process->redirec)
	{
		if (process->redirec->redir_type == MINUS)
		{
			process->redirec->fd = open(process->redirec->doc, O_RDONLY);
			if (process->redirec->fd == -1)
			{
				ft_puterror(process->redirec->doc);
				if (utils->parent_builtin == 1)
					return (-2);
				else
					exit_process(utils);
			}
			last_infile_fd = process->redirec->fd;
		}
		if (process->redirec->redir_type == HEREDOC)
		{
			process->redirec->fd = open(process->redirec->heredoc_file, O_RDONLY);
			if (process->redirec->fd == -1)
			{
				ft_puterror(process->redirec->doc);
				if (utils->parent_builtin == 1)
					return (FUNC_FAILURE);
				else
					exit_process(utils);
			}
			last_infile_fd = process->redirec->fd;
		}
		process->redirec = process->redirec->next;
	}
	return (last_infile_fd);
}

int	redirec_infile(t_utils *utils, t_parse *process)
{
	int	last_infile_fd;

	last_infile_fd = open_infiles(utils, process);
	if (last_infile_fd == -1)
		return (FUNC_FAILURE);
	if (last_infile_fd == -2)
		return (-2);
	if (dup2(last_infile_fd, STDIN_FILENO) == -1)
	{
		perror("minishell");
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	close_fds(utils->process, utils); 
	return(FUNC_SUCCESS);
}
