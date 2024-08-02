#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#include "libft.h"

typedef enum e_token_type
{
    TOKEN_PIPE,
    TOKEN_WORD,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ENV_VAR,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
}   t_token_type;

typedef struct s_token
{
    t_token_type	type;
    char			*value;
    struct s_token  *next;
}   t_token;

typedef struct s_stream
{
    t_token	*head;
	t_token	*tail;
}   t_stream;

typedef struct s_engine
{
	char**      envp;
	t_stream    stream;
}   t_engine;

// utils.c
bool	is_space(char c);
void	error_message(char *text, bool is_errno);
void	init_engine(t_engine *engine, char **envp);

// lexer.c
int     add_quote(t_stream *stream, char *input, int i);
int     add_redirect(t_stream *stream, char *input, int i);
int     add_env_var(t_stream *stream, char *input, int i);
bool    lexer(char *input, t_stream *stream);

// lexer_utils.c
bool	is_token_type(char c);
void    add_token(t_stream *stream, t_token_type type, char *value);
void    clear_token_stream(t_stream *stream, char *text);

// parser.c
void    parser(t_engine *engine);

#endif  /* MINISHELL_H */