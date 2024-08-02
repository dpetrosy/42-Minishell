#include "minishell.h"

bool	is_token_type(char c)
{
	return (c == '&' || c == '|' || c == '<' ||
        c == '>' || c == '\'' || c == '\"');
}

void	add_token(t_stream *stream, t_token_type type, char *value)
{
    t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
    if (!token)
    {
		clear_token_stream(stream, NULL);
        error_message("Failed to allocate memory for token!\n", false);
    }
    token->type = type;
    token->next = NULL;
	if (type != TOKEN_WORD)
    	token->value = ft_strdup(value);
	else
		token->value = value;
    if (!token->value)
    {
        free(token);
		clear_token_stream(stream, NULL);
        error_message("Failed to set token value!\n", false);
    }
    if (!stream->tail)
        stream->head = token;
	else
		stream->tail->next = token;
	stream->tail = token;
}

void    clear_token_stream(t_stream *stream, char *text)
{
    t_token *head;
    t_token *tmp;

    if (!stream)
        return;
    head = stream->head;
    while (head)
    {
        tmp = head->next;
        free(head->value);
        free(head);
        head = tmp;
    }
    stream->head = NULL;
    stream->tail = NULL;
    if (text)
        ft_putstr_fd(text, STDERR_FILENO);
}