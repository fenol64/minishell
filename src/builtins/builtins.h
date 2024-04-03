/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:10:22 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/03 11:05:36 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../proc_creator/proc_creator.h"

//	builtins1.c
void	ts_putstr(const char *str);
int		ft_echo(t_proc *proc, t_main *main);
int		ft_cd(t_proc *proc, t_main *main);

#endif