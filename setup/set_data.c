/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:33:41 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/20 21:49:53 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_start_data(t_shell *core, char **start_env)
{
	core->cur_process.ret = 0;
	core->env_list = NULL;
	core->env = copy_array(start_env);
	if (!core->env)
		exit(SETUP_ERROR);
}