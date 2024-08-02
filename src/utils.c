#include "minishell.h"

bool	is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
        return (true);
    return (false);
}

void	error_message(char *text, bool is_errno)
{
	if (is_errno)
		perror(text);
	else if (text)
		ft_putstr_fd(text, 2);
	exit(EXIT_FAILURE);
}

void	init_engine(t_engine *engine, char **envp)
{
	engine->envp = envp;
	engine->stream.head = NULL;
	engine->stream.tail = NULL;
}
