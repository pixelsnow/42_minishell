/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/17 23:42:10 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	slightly_special_atoi(char *str, int *overflow)
{
	long long int	res;
	long long int	prev_res;
	int				i;
	int				sign;
	
	if (!ft_strcmp("-9223372036854775808", str))
		return (LL_INT_MIN - 1);
	sign = 1;
	i = 0;
	res = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		prev_res = res;
		res = res * 10 + (str[i] - '0');
		if (prev_res > res)
		{
			*overflow = 1;
			return (2);
		}
		i++;
	}
	return (sign * res);
}

static t_bool	print_exit_error(const char *arg, const char *message)
{
	ft_putstr_fd(ERROR_SHROOM, 2);
	ft_putstr_fd("exit: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
	return (TRUE);
}

int	non_numeric_error(t_shell *core, const char *arg)
{
	print_exit_error(arg, "numeric argument required");
	core->cur_process.shroom_time = FALSE;
	return (2);
}

t_bool	is_numeric(char *str)
{
	(void)str;
	return (FALSE);
}

long long int	ft_exit(t_shell *core, t_command *command)
{
	long long int	res;
	int				i;
	int				overflow;
	char			*num_str;

	// no args -> return curr_process ret
	if (!command->cmd_ar[1])
	{
		core->cur_process.shroom_time = FALSE;
		return (core->cur_process.ret);
	}
	i = 1;
	overflow = 0;
	num_str = ft_strtrim(command->cmd_ar[0], " \t");
	if (!num_str)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		core->cur_process.shroom_time = FALSE;
		return (MALLOC_FAIL);
	}
	if (!is_numeric(num_str))
		return(non_numeric_error(core, command->cmd_ar[0]));
	res = slightly_special_atoi(num_str, &overflow);
	if (overflow)
		return(non_numeric_error(core, command->cmd_ar[0]));
	if (command->cmd_ar[2])
	{
		print_exit_error(NULL, "too many arguments");
		return (1);
	}
	core->cur_process.shroom_time = FALSE;
	return(res);
}
