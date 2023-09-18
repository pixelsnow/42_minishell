/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:48:30 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 14:11:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fetches PATH env var, splits it into an array of paths and returns it
static char	**fetch_paths_array(t_shell *core)
{
	char	*paths;
	char	**paths_split;

	paths = fetch_env("PATH", core);
	if (!paths)
		return (NULL);
	paths_split = ft_split(paths, ':');
	if (!paths_split)
		core->cur_process.error_index = MALLOC_FAIL;
	free(paths);
	return (paths_split);
}

static int	find_path_problem(char **paths, char *cmd_name)
{
	struct stat	file_info;

	if (access(cmd_name, F_OK) || paths)
	{
		ft_putstr_fd(ERROR_SHROOM, 2);
		ft_putstr_fd(cmd_name, 2);
		if (paths)
			ft_putstr_fd(": shroom not found🐛\n", 2);
		else
			ft_putstr_fd(": No such file or directory🐛\n", 2);
		return (127);
	}
	if (stat(cmd_name, &file_info))
		return (MALLOC_FAIL);
	ft_putstr_fd(ERROR_SHROOM, 2);
	ft_putstr_fd(cmd_name, 2);
	if (S_ISDIR(file_info.st_mode))
		ft_putstr_fd(": is a directory🐛\n", 2);
	else
		ft_putstr_fd(": Permission denied🐛\n", 2);
	return (126);
}

// Goes through Paths and finds the correct one.
// If not found returns NULL
char	*find_exe_path(t_shell *core, t_command *command)
{
	int		i;
	char	*exe_path;
	char	**paths_split;

	paths_split = fetch_paths_array(core);
	if (!paths_split && core->cur_process.error_index == MALLOC_FAIL)
		return (NULL);
	i = 0;
	while (paths_split && paths_split[i] && command->cmd_name[0])
	{
		exe_path = join_three_strings(paths_split[i], "/", command->cmd_name);
		if (!exe_path || access(exe_path, X_OK) == SUCCESS)
		{
			if (!exe_path)
				core->cur_process.error_index = MALLOC_FAIL;
			free_ar(paths_split);
			return (exe_path);
		}
		free(exe_path);
		i++;
	}
	core->cur_process.ret = find_path_problem(paths_split, command->cmd_name);
	if (paths_split)
		free_ar(paths_split);
	return (NULL);
}
