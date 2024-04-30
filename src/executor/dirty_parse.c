#include "../../minishell.h"
/*
void	exec_builtins(t_utils *utils, t_parse *process) //BORRAR EVENTUALMENTE
{
	if (ft_strncmp(process->cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		ft_echo(process->cmd);
	else if (ft_strncmp(process->cmd[0], "pwd", 3) == 0 && ft_strlen(process->cmd[0]) == 3)
		ft_pwd();
	else if (ft_strncmp(process->cmd[0], "env", 3) == 0 && ft_strlen(process->cmd[0]) == 3)
		ft_env(utils->env, process->cmd);
	else if (ft_strncmp(process->cmd[0], "unset", 5) == 0 && ft_strlen(process->cmd[0]) == 5)
		ft_unset(&utils->env, process->cmd);
	else if (ft_strncmp(process->cmd[0], "cd", 2) == 0 && ft_strlen(process->cmd[0]) == 2)
		ft_cd(&utils->env, process->cmd);
	else if (ft_strncmp(process->cmd[0], "exit", 4) == 0 && ft_strlen(process->cmd[0]) == 4)
		ft_exit(process->cmd); //Ojo que como vamos a hacer exit habrá que liberar todo lo que tengamos hasta el momento
	else if (ft_strncmp(process->cmd[0], "export", 6) == 0 && ft_strlen(process->cmd[0]) == 6)
		ft_export(&utils->env, process->cmd);
	free_matrix(process->cmd);
	return (&utils->env);
}
*/
static void	create_out(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->heredoc_file = NULL;
	node->next = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = GREAT;
	node->fd = -1;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

static void	create_in(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->heredoc_file = NULL;
	node->next = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = MINUS;
	node->fd = -1;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

static void	create_out_append(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->heredoc_file = NULL;
	node->next = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = APPEND;
	node->fd = -1;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

static void	create_heredoc(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->heredoc_file = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = HEREDOC;
	node->next = NULL;
	node->fd = -1;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

void	create_new_parse_node(t_parse **process)
{
	t_parse	*node;

	node = malloc(sizeof(t_parse));
	node->cmd = ft_calloc(20, sizeof(char *));
	node->built_in = 0;
	node->redirec = NULL;
	node->redirec_head = NULL;
	node->next = NULL;
	if (!*process)
		*process = node;
	while((*process)->next != NULL)
		*process = (*process)->next;
	(*process)->next = node;
	*process = (*process)->next;
}

static void print_cmds_and_docs(t_utils *utils)
{
	int i = 0;

	while (utils->process->redirec)
	{
		printf("REDIREC DOC: %s\n", utils->process->redirec->doc);
		utils->process->redirec = utils->process->redirec->next;
		i++;
	}
	i = 0;
	while (utils->process->cmd[i])
	{
		printf("PROCESS CMD: %s\n",utils->process->cmd[i]);
		i++;
	}
}

void	dirty_parse(char *input, t_utils *utils)
{
	char	**tokens;
	t_parse	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	utils->process = malloc(sizeof(t_parse));
	utils->process->cmd = ft_calloc(20, sizeof(char *));
	utils->process->built_in = 0;
	utils->process->redirec = NULL;
	utils->process->next = NULL;
	utils->process->redirec_head = NULL;
	head = utils->process;
	tokens = ft_split(input, ' ');
	while(tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			create_out(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			create_in(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			create_out_append(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "<<") == 0)
		{
			create_heredoc(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "|") == 0)
		{
	 //		print_cmds_and_docs(utils);
			create_new_parse_node(&utils->process);
			j = 0;
			i++;
		}
		else
		{
			utils->process->cmd[j] = ft_strdup(tokens[i]);
			i++;
			j++;
		}
	}
	utils->process = head;
	free_matrix(tokens);
	//print_cmds_and_docs(utils);
}
