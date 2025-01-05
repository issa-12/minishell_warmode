/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skreik <skreik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:53:38 by saoun             #+#    #+#             */
/*   Updated: 2025/01/05 15:01:18 by skreik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	validate_variable_name(char *name, bool save_val)
{
	if (!is_valid_var_name(name))
	{
		if (includes_exlamation_mark(name))
		{
			g_v = 0;
			free(name);
			return (1);
		}
		if (!save_val && *name != '\0')
		{
			// printf("unset: `%s': not a valid identifier\n", name);
			g_v = 1;
		}
		free(name);
		return (1);
	}
	return (0);
}

void	process_variable_removal(t_env *myenv, char *name)
{
	int	index;

	index = find_env_var(myenv, name);
	if (index != -1)
		remove_env_var(myenv, index);
	free(name);
}

static int	process_unset_input(t_parser *parser, t_env *myenv, bool save_val)
{
	char	*name;
	int		i;

	i = 0;
	while (parser->input && parser->input[i])
	{
		name = process_variable(parser->input[i], myenv);
		if (validate_variable_name(name, save_val))
			return (g_v);
		process_variable_removal(myenv, name);
		i++;
	}
	return (g_v);
}

int	builtin_unset(t_parser *parser, t_env *myenv)
{
	int		dont_enter;
	bool	save_val;

	dont_enter = 0;
	save_val = false;
	if (!parser || (!parser->input && !parser->operations))
	{
		printf("\n");
		return (0);
	}
	if (parser->operations)
	{
		if (handle_operations_dash(parser, &save_val, &dont_enter))
			return (g_v);
		handle_operations_flags(parser, &dont_enter, &dont_enter, &save_val);
	}
	if (parser->input && handle_input_dash(parser, &save_val))
		return (g_v);
	return (process_unset_input(parser, myenv, save_val));
}