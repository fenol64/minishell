/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulhenr <paulhenr@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:15:00 by paulhenr          #+#    #+#             */
/*   Updated: 2024/04/18 13:38:14 by paulhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc_creator.h"

static char	*read_file(int fd);
static char	*get_new_line(const char *del, int not_expand, t_main *main);

static void	here_doc_proc(t_file *file, int fd[2], t_main *main)
{
	int		status;
	int		not_expand;
	char	*line;

	close(fd[0]);
	not_expand = has_quote(file->name);
	status = EXIT_SUCCESS;
	while (true)
	{
		line = get_new_line(file->name, not_expand);
		if (errno)
			status = HDOC_FATAL_ERROR;
		if (!line)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	close(fd[1]);
	free_file(file, free);
	free(line);
	free_main(main);
	exit(status);
}

char	*get_here_doc(t_file *file, t_main *main)
{
	char	*tmp;
	pid_t	pid;
	int		fd[2];

	tmp = file->name;
	if (pipe(fd) == -1)
		return (perror(__func__), NULL);
	pid = fork();
	if (pid < 0)
		return (perror(__func__), NULL);
	if (pid == 0)
		here_doc_proc(file, main);
	close(fd[1]);
	file->name = read_file(fd[0]);
	close(fd[0]);
	free(tmp);
	wait(NULL);
	return (file->name);
}

static char	*get_new_line(const char *del, int not_expand, t_main *main)
{
	char	*line;
	char	*err_msg;
	char	*expanded_line;

	line = readline("> ");
	if (!line && !errno)
	{
		err_msg = ft_strsepjoin(HDOC_EOF_WARN, del, "')");
		if (!err_msg)
			return (perror(__func__), NULL);
		return (ft_perror("minishell: warning", err_msg), NULL);
	}
	else if (!line && errno)
		return (perror(__func__), NULL);
	else if (ft_strcmp(line, del) == 0)
		return (NULL);
	line = ft_strjoin_free(line, "\n", 1);
	if (!line)
		return (perror(__func__), NULL);
	if (not_expand == 0)
	{
		expand_args = hdoc_expand(line, main);
		return (free(line), expand_args);
	}
	return (line);
}

static char	*read_file(int fd)
{
	char	buffer[HDOC_READ_SIZE + 1];
	char	*str;
	int		bytes;
	t_list2	*node;
	t_list2	*reads;
	
	bytes = HDOC_READ_SIZE;
	reads = NULL;
	while (bytes >= HDOC_READ_SIZE)
	{
		bytes = read(fd, buffer, HDOC_READ_SIZE);
		if (bytes < 0)
			return (lst_destroy2(reads, NULL), perror(__func__), NULL);
		buffer[bytes] = '\0';
		node = new_node2(buffer, NULL);
		lst_append2(&reads, node);
		if (!node)
			return (lst_destroy2(reads, NULL), perror(__func__), NULL);
	}
	str = ft_strjoinlst(reads);
	return (lst_destroy2(reads, NULL), str);
}
