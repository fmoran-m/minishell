#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_redir
{
	char			*doc;
	int				redir_type; //tipo de redireccion
	struct s_redir	*next;
}	t_redir;

typedef	struct s_parse
{
	char			**cmd;
	int				built_in; //built-in - cmd
	t_redir			*redirec;
	struct s_parse	*next;
}	t_parse;


typedef struct s_token
{
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct s_utils
{
	char	**path; // Guardar los comandos de path por si hay que hacer rutas luego
	char	**env; // Para el env duplicado
	t_parse	*parse;
} t_utils;

#endif