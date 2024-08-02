#include "minishell.h"
#include "debug.h"

int main(int argc, char **argv, char **envp)
{
	(void)argv;
    t_engine	engine;
    char		*input;

    if (argc != 1)
		error_message("Minishell takes no argument! \n", false);
	if (!isatty(STDIN_FILENO))
		error_message("Minishell isn't run in interactive mode!\n", false);

	init_engine(&engine, envp);
    while (true)
    {
		input = readline("Minishell$ ");
		if (!input)
			break;
		lexer(input, &(engine.stream));
		free(input);
		// parser(&engine);

		// *********** Testing *********** //
		debug_print_tokens(&engine.stream);
		clear_token_stream(&engine.stream, NULL);
    }
    return (0);
}