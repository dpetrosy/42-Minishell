#include "minishell.h"
#include "debug.h"

int main(int argc, char **argv, char **envp)
{
	(void)argv;
    t_engine	engine;
    char		*input;

    if (argc != 1)
		error_message("Minishell takes no argument! \n", false);
	init_engine(&engine, envp);
    while (true)
    {
		if (isatty(STDIN_FILENO))
		{
			input = readline("Minishell$ ");
			if (!input)
				error_message("Input error!\n", false);
			lexer(input, &(engine.stream));
			free(input);
			// parser(&engine);
		}
		else
			error_message("Minishell isn't run in interactive mode!\n", false);

		// *********** Testing *********** //
		debug_print_tokens(&engine.stream);
		clear_token_stream(&engine.stream, NULL);
    }
    return (0);
}