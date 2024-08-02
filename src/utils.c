#include "minishell.h"

bool	is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	error_message(char *text, bool is_errno)
{
	if (is_errno)
		perror(text);
	else if (text)
		ft_putstr_fd(text, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	init_engine(t_engine *engine, char **envp)
{
	engine->envp = envp;
	engine->stream.head = NULL;
	engine->stream.tail = NULL;
}
