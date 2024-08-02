#include "minishell.h"

int	add_quote(t_stream *stream, char *input, int i)
{
	int		start;
	char	quote;

	quote = input[i];
	start = i++;
	while (input[i] && input[i] != quote)
		++i;
	if (input[i] != quote)
	{
		if (quote == '\'')
			clear_token_stream(stream, "Invalid single quote!\n");
		else
			clear_token_stream(stream, "Invalid double quote!\n");
		return -1;
	}
	add_token(stream, TOKEN_WORD, ft_substr(input, start, i - start + 1));
	return i;
}

int	add_redirect(t_stream *stream, char *input, int i)
{
	int	start;

	start = i++;
	if (input[i] == '<' || input[i] == '>')
		++i;
	while (is_space(input[i]))
		++i;
	if (!input[i] || input[i] == '<' || input[i] == '>' || input[i] == '|')
	{
		clear_token_stream(stream, "Invalid redirection!\n");
		return -1;
	}
	if (input[start] == '<')
	{
		if (input[start + 1] == '<')
			add_token(stream, TOKEN_HEREDOC, "<<");
		else
			add_token(stream, TOKEN_REDIRECT_IN, "<");
	}
	else
	{
		if (input[start + 1] == '>')
			add_token(stream, TOKEN_APPEND, ">>");
		else
		add_token(stream, TOKEN_REDIRECT_OUT, ">");
	}
	return start;
}

int	add_pipe(t_stream *stream, char *input, int i)
{
	int start;

	start = i;
	if (i == 0)
	{
		clear_token_stream(stream, "Invalid pipe!\n");
		return -1;
	}
	++i;
	while (is_space(input[i]))
		++i;
	if (!input[i] || input[i] == '<' || input[i] == '>' || input[i] == '|')
	{
		clear_token_stream(stream, "Invalid pipe!\n");
		return -1;
	}
	add_token(stream, TOKEN_PIPE, "|");
	return start;
}

int	add_env_var(t_stream *stream, char *input, int i)
{
	int start;

	start = ++i;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		++i;
	add_token(stream, TOKEN_ENV_VAR, ft_substr(input, start, i - start + 1));
	return i - 1;
}

int	add_word(t_stream *stream, char *input, int i)
{
	int start;

	start = i;
	while (input[i] && !is_space(input[i]) && !is_token_type(input[i]))
		++i;
	add_token(stream, TOKEN_WORD, ft_substr(input, start, i - start));
	return i - 1;
}

bool    lexer(char *input, t_stream *stream)
{
	int	i;

	i = -1;
    while (input[++i])
    {
        if (is_space(input[i]))
            continue;
		if ((input[i] == '|' && input[i + 1] == '|') || (input[i] == '&'))
		{
			clear_token_stream(stream, "Logical operators are invalid!\n");
			i = -1;
		}
		else if (input[i] == '\'' || input[i] == '\"')
			i = add_quote(stream, input, i);
        else if (input[i] == '<' || input[i] == '>')
			i = add_redirect(stream, input, i);
		else if (input[i] == '|')
			i = add_pipe(stream, input, i);
        else if (input[i] == '$')
			i = add_env_var(stream, input, i);
		else
			i = add_word(stream, input, i);
		if (i == -1)
			return false;
    }
	return true;
}
