#include "minishell.h"

t_token    *parse_command(t_token *head, t_ast_node *node)
{
    if (head->type == TOKEN_WORD || head->type == TOKEN_ENV_VAR)
    {
        node->cmd = head->value;
        head = head->next;
    }

    while (head && head->type != TOKEN_OR &&
        head->type != TOKEN_AND && head->type != TOKEN_PIPE)
    {

    }
    return NULL;
}

t_ast_node  *create_ast_node()
{
    t_ast_node  *node;

    node = (t_ast_node*)malloc(sizeof(t_ast_node));
    node->cmd = NULL;
    node->arg = NULL;
    node->redir_in = NULL;
    node->redir_out = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void    parser(t_engine *engine)
{
    t_token     *head;
    t_ast_node  *root;

    head = engine->stream.head;
    root = create_ast_node();
    head = parse_command(head, root);
    while (head)
    {
        /* code */
    }

    engine->root = root;
    clear_token_stream(&engine->stream, NULL);
}