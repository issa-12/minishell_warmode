/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdennaou <rdennaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:20:53 by rdennaou          #+#    #+#             */
/*   Updated: 2025/01/02 17:32:21 by skreik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	handle_exit_input(t_parser *parser)
{
	if (parser->input != NULL && parser->input[0] != NULL)
		parser->input[0] = remove_paired_quotes(parser->input[0]);
}

int	adjust_number(int num)
{
	if (num < 0)
		num = (num % 256 + 256) % 256;
	else if (num >= 256)
		num = num % 256;
	return (num);
}

void	validate_numeric_input(char *input)
{
	char		*endptr;
	long long	num;

	errno = 0;
	num = ft_strtoll(input, &endptr, 10);
	if (is_numeric(input))
	{
		if (*endptr != '\0' || errno == ERANGE)
		{
			ft_putendl_fd("minishell : exit: numeric argument required", 2);
			g_v = 2;
		}
		else
		{
			num = adjust_number(num);
			g_v = (int)num;
		}
	}
	else
	{
		ft_putendl_fd("minishell : exit: numeric argument required", 2);
		g_v = 2;
	}
}

void	cleanup_and_exit(t_env *myenv, t_parser *parser)
{
	ft_free_env(&myenv);
	free_parser(parser);
	exit(g_v);
}

void	builtin_exit(t_parser *parser, t_env *myenv)
{
	if (parser->next == NULL && parser->prev == NULL)
		printf("exit\n");
	handle_exit_input(parser);
	if (parser->input == NULL)
	{
		g_v = 0;
		cleanup_and_exit(myenv, parser);
	}
	else if (parser->input[1])
	{
		if (handle_exit_arguments(parser->input) != 1)
			cleanup_and_exit(myenv, parser);
	}
	else
	{
		validate_numeric_input(parser->input[0]);
		cleanup_and_exit(myenv, parser);
	}
}
