/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:54:48 by saoun             #+#    #+#             */
/*   Updated: 2024/10/08 17:22:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// void compare_with_ls_pwd(t_parser *list, t_env)
// {
//     int i;

//     i = 0;
//     if(list->input == NULL)
//         return;
//     while(list->input[i] != NULL)
//         i++;
//     if(!strcmp(list->input[i],"ls") || !strcmp(list->input[i],"pwd"))
//     {
//         if(!strcmp(list->input[i],"pwd"))
//             builtin_pwd()
//     }
// }
char *compare_input_with_str(t_parser *list, const char *str)
{
    int i;

    if (list == NULL || list->input == NULL || str == NULL)
        return (NULL);  // Return NULL if list, input, or str is NULL
    i = 0;
    while (list->input[i] != NULL)
    {
        if (strcmp(list->input[i], str) != 0)
            return (list->input[i]);  // Return the mismatched string
        i++;
    }
    return (NULL);  // Return NULL if all strings match
}

char	*ft_getenv(t_env *myenv, char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(str);
	while (myenv->env[i])
	{
		if (!strncmp(myenv->env[i], str, len) && myenv->env[i][len] == '=')
			return (myenv->env[i] + len + 1);
		i++;
	}
	return (NULL);
}
/*
void update_SHLVL(t_env *myenv)
{
    char *prev_level;
    int temp;
    int i;
    char *new_level_str;

    i = 0;
    while (myenv->env[i])
    {
        if (!ft_strncmp(myenv->env[i], "SHLVL=", 6))
        {
            prev_level = myenv->env[i] + 6;  
            if (prev_level[0] != '\0')
            {
                temp = ft_atoi(prev_level); 
                temp += 1;
                new_level_str = ft_itoa(temp); 
                add_or_update_to_env("SHLVL", new_level_str, myenv);
                free(new_level_str);
            }
            return;
        }
        i++;
    }
    add_or_update_to_env("SHLVL", "1", myenv);
}
 */

void update_SHLVL(t_env *myenv)
{
    char *prev_level;
    int temp;
    char *new_level_str;

    prev_level = ft_getenv(myenv, "SHLVL");
    if (prev_level && prev_level[0] != '\0')
    {
        temp = ft_atoi(prev_level); 
        temp += 1;
        new_level_str = ft_itoa(temp); 
        add_or_update_to_env("SHLVL", new_level_str, myenv);
        free(new_level_str);
    }
    else
        add_or_update_to_env("SHLVL", "1", myenv);
}
t_env *init_env(char **env)
{
    t_env *myenv;
    int i;
    
    i = 0;
    myenv = (t_env *)malloc(sizeof(t_env));
    if (!myenv)
        return (NULL);
    while (env[i])
        i++;
    myenv->env = (char **)malloc(sizeof(char *) * (i + 1));
    if (!myenv->env)
    {
        free(myenv);
        return (NULL);
    }
    i = 0;
    while (env[i])
    {
        myenv->env[i] = strdup(env[i]);
        i++;
    }
    myenv->env[i] = NULL;
    update_SHLVL(myenv);
    return (myenv);
}

int builtin_env(t_parser *list, t_env *myenv)
{
    char *mismatch_str;
    int i;

    mismatch_str = compare_input_with_str(list, "env");
    if (mismatch_str != NULL)  // If there's a mismatch
    {
        printf("env: '%s':  No such file or directory\n", mismatch_str);
        return (-1);
    }
    printf("WHY AREN'T YOU HERE?\n");
    i = 0;
    while (myenv->env[i])
    {
        if (ft_strchr(myenv->env[i], '=') != NULL)
            printf("%s\n", myenv->env[i]);
        i++;
    }

    return (0);
}

