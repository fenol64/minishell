/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_typedefs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:46:08 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/15 10:37:45 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_TYPEDEFS_H
# define LIST_TYPEDEFS_H

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

typedef struct s_list2
{
	void			*data;
	struct s_list2	*next;
	struct s_list2	*prev;
}					t_list2;

#endif
