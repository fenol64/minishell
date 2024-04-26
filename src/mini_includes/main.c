/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:21 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/12 17:19:45 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getenvp(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		if (ft_strncmp(envp[i], name, j) == 0)
			return (envp[i] + j + 1);
		i++;
	}
	return (NULL);
}



void execute_command(char *s, char **envp)
{
	pid_t	pid;
	char	**args;
	int		status;

	args = ft_split(s, ' ');
	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, envp);
	}
	else
		waitpid(pid, &status, 0);
}

int	main(int c, char **v, char **envp)
{
	char	*str;
	char	*s;
	char	*pwd;

	(void) c;
	(void) v;
	while (1)
	{
		pwd = getenvp("PWD", envp);
		str = ft_strjoin(pwd, "$ ");
		str = ft_strjoin_free("minishell@", str, 2);
		s = readline(str);
		if (s == NULL)
			break ;
		if (ft_strlen(s) > 0)
			add_history(s);
		if (ft_strncmp(s, "exit", 4) == 0)
		{
			free(s);
			break ;
		}
		execute_command(s, envp);
		free(s);
	}
}
