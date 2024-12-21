/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:27:34 by rdennaou          #+#    #+#             */
/*   Updated: 2024/12/20 20:54:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_special_variable(char **input)
{
	if (**input >= '0' && **input <= '9')
	{
		(*input)++;
		while (**input && (isalnum(**input) || is_special_char(**input)))
		{
			printf("%c", **input);
			(*input)++;
		}
		return ;
	}
	else if (is_special_char(**input))
	{
		printf("$");
		while (**input && (isalnum(**input) || is_special_char(**input)))
		{
			printf("%c", **input);
			(*input)++;
		}
		return ;
	}
}

void	process_normal_variable(char **input, int i, t_env env)
{
	char	*expanded;

	(*input)--;
	if (i == 1) // if there's a quote before
		(*input)--;
	printf("expanded = %s\n", *input); // check what goes to process variable
	expanded = process_variable(*input, &env);
	if (expanded)
	{
		printf("%s", expanded);
		free(expanded);
	}
	(*input) += strlen(*input);
}

void	print_expanded_input(char **input, bool inside_single_quotes, int i, t_env env)
{
	(void)i;
	if (**input == '$' && !inside_single_quotes)
	{
		(*input)++;
		if (**input == '\0' || **input == '\"' || **input == ' ')
		{
			printf("$");
			return ;
		}
		else if (**input == '?')
		{
			printf("%d", global_var);
			(*input)++;
			return ;
		}
		else if ((**input >= '0' && **input <= '9') || is_special_char(**input))
		{
			process_special_variable(input);
			return ;
		}
		else
		{
			while (**input)
			{
				char *var_name_start = *input;
				while (**input && (isalnum(**input) || **input == '_'))
					(*input)++;
				size_t var_name_length = *input - var_name_start;
				if (var_name_length > 0)
				{
					char var_name[var_name_length + 1];
					strncpy(var_name, var_name_start, var_name_length);
					var_name[var_name_length] = '\0';
					char *value = ft_getenv(&env, var_name);
					if (value)
						printf("%s", value);
				}
				if (**input == '$')
				{
					(*input)++;
					continue;
				}
				else
					break;
			}
		}
	}
}

void	printable(char **input)
{
	if (**input == '\"' || **input == '\\')
		printf("%c", **input);
	else
		printf("\\%c", **input);
}

void	builtin_echo_helper(char **input, char quote, t_env env)
{
	bool	inside_single_quotes;

	inside_single_quotes = (quote == '\'');
	while (**input && **input != quote)
	{
		if (**input == '\\' && !inside_single_quotes)
		{
			(*input)++;
			printable(input);
			(*input)++;
		}
		else if (**input == '$' && !inside_single_quotes)
		{
			print_expanded_input(input, inside_single_quotes, 1, env);
			continue ;
		}
		else
		{
			printf("%c", **input);
			(*input)++;
		}
	}
	if (**input == quote)
		(*input)++;
}
