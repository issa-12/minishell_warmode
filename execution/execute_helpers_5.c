/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalayan <isalayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:52:20 by saly              #+#    #+#             */
/*   Updated: 2025/01/05 10:51:35 by isalayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	process_dollar_strings(char **strs, t_env *env)
{
	char	*processed_str;
	int		i;

	i = 0;
	if (strs == NULL)
		return ;
	while (strs[i] != NULL)
	{
		if (strchr(strs[i], '$') != NULL)
		{
			processed_str = process_variable(strs[i], env);
			free(strs[i]);
			strs[i] = processed_str;
		}
		i++;
	}
}

char	*retreive_path(t_env env)
{
	if (ft_strcmp(ft_getenv(&env, "SHLVL"), "1") == 0)
		return (ft_strdup(
				"/home/isalayan/bin:"
				"/usr/local/sbin:"
				"/usr/local/bin:"
				"/usr/sbin:"
				"/usr/bin:"
				"/sbin:"
				"/bin:"
				"/usr/games:"
				"/usr/local/games:"
				"/snap/bin"
			));
	else
		return (ft_getenv(&env, "PATH"));
}
