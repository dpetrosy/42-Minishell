#include "debug.h"

char *get_token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return "TOKEN_WORD";
	else if (type == TOKEN_PIPE)
		return "TOKEN_PIPE";
	else if (type == TOKEN_REDIRECT_IN)
		return "TOKEN_REDIRECT_IN";
	else if (type == TOKEN_REDIRECT_OUT)
		return "TOKEN_REDIRECT_OUT";
	else if (type == TOKEN_APPEND)
		return "TOKEN_APPEND";
	else if (type == TOKEN_HEREDOC)
		return "TOKEN_HEREDOC";
	else if (type == TOKEN_ENV_VAR)
		return "TOKEN_ENV_VAR";
	else if (type == TOKEN_AND)
		return "TOKEN_AND";
	else if (type == TOKEN_OR)
		return "TOKEN_OR";
	else
		return "ANKAPUTYUN";
	// else if (type == TOKEN_QUOTE_SINGLE)
	// 	return "TOKEN_QUOTE_SINGLE";
	// else if (type == TOKEN_QUOTE_DOUBLE)
	// 	return "TOKEN_QUOTE_DOUBLE";
	// else if (type == TOKEN_WILDCARD)
	// 	return "TOKEN_WILDCARD";

}

void debug_print_tokens(t_stream *stream)
{
	t_token *head = stream->head;

	printf("\n\n\n");
	while (head)
	{
		char *type_str = get_token_type_str(head->type);
		printf("\nToken type: %s, token value: %s\n", type_str, head->value);
		head = head->next;
	}
}