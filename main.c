/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalayan <isalayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:10:16 by isalayan          #+#    #+#             */
/*   Updated: 2025/04/21 17:38:46 by isalayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	g_v = 0;

int	handle_parse_tokens_error(char *line, t_tokenlist *token_list,
								t_parser *parser, int value)
{
	if (!parser || !parser->command || value == -1)
	{
		free(line);
		free_token_list(token_list);
		free_parser(parser);
		return (1);
	}
	return (0);
}

int	initiate_input(char *line, t_tokenlist **token_list,
					t_parser **parser, t_env *my_env)
{
	int	value;

	if (ft_manage_empty_input(line))
		return (0);
	if (*line)
		add_history(line);
	*token_list = tokenize_input(line);
	if (handle_tokenization_error(*token_list, line))
		return (0);
	*parser = create_parser();
	if (handle_parser_error(*parser, *token_list, line))
		return (0);
	value = parse_tokens(parser, *token_list, my_env);
	if (handle_parse_tokens_error(line, *token_list, *parser, value))
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*my_env;
	t_tokenlist	*token_list;
	t_parser	*parser;

	token_list = NULL;
	parser = NULL;
	(void)argc;
	(void)argv;
	line = NULL;
	my_env = initialize_environment(envp);
	restore_signals();
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			break ;
		if (initiate_input(line, &token_list, &parser, my_env) != 1)
			continue ;
		cmds_exec(parser, my_env);
		cleanup_resources(line, token_list, parser);
	}
	return (ft_free_env(&my_env), EXIT_SUCCESS);
}
