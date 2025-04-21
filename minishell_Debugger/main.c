/*int     main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *line = NULL;
	t_env *my_env;
	t_tokenlist *token_list;
	t_parser *parser;
	int value ;
	if(envp == NULL || *envp == NULL)
		my_env = manage_env_i();
	else
		my_env = init_env(envp);
	restore_signals();
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		if (*line)
			add_history(line);
		token_list = tokenize_input(line);
		if (!token_list)
		{
			printf("Error: Failed to tokenize input.\n");
			free(line);
			continue ;
		}
		// Print tokens (for debugging)
		printf("\nTokens:______________________\n");
		print_token_list(token_list);
		// Parse tokens
		parser = create_parser(); // Initialize parser
		if (!parser)
		{
			printf("Error: Failed to create parser.\n");
			free(line);
			free_token_list(token_list); // Free token list
			continue ;
		}
		value = parse_tokens(&parser, token_list, my_env);
		if (!parser || !parser->command || value == -1)
		{
			free(line);
			free_token_list(token_list);
			free_parser(parser);
			continue ;
		}
		printf("\nParsed commands:\n");
		print_parser(parser);
		cmds_exec(parser, my_env);
		free_token_list(token_list);
		free(line);
		free_parser(parser);
	}
	ft_free_env(&my_env);
	return (EXIT_SUCCESS);
}*/