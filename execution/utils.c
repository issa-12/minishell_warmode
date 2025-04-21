/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalayan <isalayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:03:41 by isalayan          #+#    #+#             */
/*   Updated: 2025/04/21 17:30:16 by isalayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_directory_part(const char *path)
{
	char	*dir_part;
	size_t	path_len;
	char	*temp_path;

	dir_part = NULL;
	path_len = ft_strlen(path);
	if (path_len == 0)
		return (ft_strdup("."));
	temp_path = ft_strdup(path);
	path_len = ft_strlen(temp_path);
	dir_part = get_directory_part_helper(path_len, temp_path, dir_part);
	if (!dir_part)
		return (NULL);
	return (dir_part);
}

char	*get_directory_part_helper(size_t path_len, char *temp_path,
		char *dir_part)
{
	char	*last_slash;
	size_t	dir_len;

	while (path_len > 1 && temp_path[path_len - 1] == '/')
	{
		temp_path[path_len - 1] = '\0';
		path_len--;
	}
	last_slash = ft_strrchr(temp_path, '/');
	if (last_slash == NULL)
		dir_part = ft_strdup(".");
	else if (last_slash == temp_path)
		dir_part = ft_substr(temp_path, 0, 1);
	else
	{
		dir_len = last_slash - temp_path;
		dir_part = ft_substr(temp_path, 0, dir_len);
	}
	free(temp_path);
	return (dir_part);
}
