/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:21:30 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/12 21:33:21 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define SHROOM_TIME 37
# define YES 1
# define NO 0

//different colour codes
//R red
//W white
//G green
//M magenta
//CY cyan
//B blue
//wr is white bg red text and rw is the other way around
# define R "\033[1;31m"
# define W "\033[1;37m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define M "\033[1;35m"
# define CY "\033[1;36m"
# define B "\033[1;34m"
# define RW "\033[1;31;47m"
# define WR "\033[1;37;41m"
# define C "\033[0m"

# define MINI_SHROOM "🍄"W"Mini"C R"Shroom"C
# define ERROR_SHROOM R"🕸Error"C W"🕸Shroom: "C

#endif
