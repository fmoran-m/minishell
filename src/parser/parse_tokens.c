



#include  "../../minishell.h"

int init_process(t_parse **process)
{
    *process = ft_calloc(sizeof(t_parse), 1);
    if (!(*process))
        return (0);
    (*process)->cmd = NULL;
    (*process)->built_in = 0;
    (*process)->redirec = NULL;
    (*process)->redirec_head = NULL;
    (*process)->next = NULL;
}

int parse_tokens(t_utils *utils)
{
    t_parse *head;
    t_token *token_head;

    init_process(&head);
    token_head = utils->token_list;
    while (!ft_strcmp(utils->token_list->str, "|"))

    return (0);
}