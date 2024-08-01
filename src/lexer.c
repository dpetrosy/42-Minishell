#include "minishell.h"

int	add_bool_operator(t_stream *stream, char *input, int i)
{
	if (input[i] == '&')
	{
		if (input[i + 1] == '&')
		{
			add_token(stream, TOKEN_AND, "&&");
			i += 1;
		}
		else
			clear_token_stream(stream, 
				"Minishell: syntax error near unexpected token `&'\n");
	}
	else if (input[i] == '|')
	{
		if (input[i + 1] == '|')
		{
			add_token(stream, TOKEN_OR, "||");
			++i;
		}
		else
			add_token(stream, TOKEN_PIPE, "|");
	}
	return i;
}

int	add_quote(t_stream *stream, char *input, int i)
{
	int start;

	start = i;
	if (input[i] == '\'')
	{
		// add_token(stream, TOKEN_QUOTE_SINGLE, "\'");
		++i;
		while (input[i] && input[i] != '\'')
			i += 1;
		add_token(stream, TOKEN_WORD, ft_substr(input, start, i - start + 1));
		if (input[i] != '\'')
			clear_token_stream(stream, "Single quote error!\n");
		// add_token(stream, TOKEN_QUOTE_SINGLE, "\'");
	}
	else if (input[i] == '\"')
	{
		// add_token(stream, TOKEN_QUOTE_DOUBLE, "\"");
		++i;
		while (input[i] && input[i] != '\"')
			i += 1;
		add_token(stream, TOKEN_WORD, ft_substr(input, start, i - start + 1));
		if (input[i] != '\"')
			clear_token_stream(stream, "Double quote error!\n");
		// add_token(stream, TOKEN_QUOTE_DOUBLE, "\"");
	}
	return i;
}

int	add_redirect(t_stream *stream, char *input, int i)
{
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			add_token(stream, TOKEN_HEREDOC, "<<");
			i += 1;
		}
		else
			add_token(stream, TOKEN_REDIRECT_IN, "<");
	}
	else
	{
		if (input[i + 1] == '>')
		{
			add_token(stream, TOKEN_APPEND, ">>");
			i += 1;
		}
		else
			add_token(stream, TOKEN_REDIRECT_OUT, ">");
	}
	return i;
}

int	add_env_var(t_stream *stream, char *input, int i)
{
	int start;

	start = i++;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		++i;
	add_token(stream, TOKEN_ENV_VAR, ft_substr(input, start, i - start));
	return i;
}

void    lexer(char *input, t_stream *stream)
{
    int	start;
	int	i;

	i = -1;
    while (input[++i])
    {
        if (ft_isspace(input[i]))
            continue;
		if (input[i] == '&' || input[i] == '|')
			i = add_bool_operator(stream, input, i);
        else if (input[i] == '<' || input[i] == '>')
			i = add_redirect(stream, input, i);
        else if (input[i] == '\'' || input[i] == '\"')
			i = add_quote(stream, input, i);
        else if (input[i] == '$')
			i = add_env_var(stream, input, i);
		else // TOKEN_WORD
        {
            start = i;
            while (input[i] && !is_space(input[i]) && !is_token_type(input[i]))
            	++i;
            add_token(stream, TOKEN_WORD, ft_substr(input, start, i - start));
			--i;
		}
        // else if (input[i] == '*')
		// 	add_token(stream, TOKEN_WILDCARD, "*");
    }
}
