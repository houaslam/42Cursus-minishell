/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/01 13:12:36 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	lexer(t_data *data)
{
	int		i;
	t_exec	*tmp;
	t_file	*tmp_f;

	i = 0;
	data->exec = NULL;
	tmp_f = NULL;
	tmp = ft_lstnew_exec("*", STRING, NULL);
	while (data->s[i])
	{
		if (data->s[i] == RED_IN && data->s[i + 1] == RED_IN)
			i = handle_here_doc_in(data, i, tmp_f);
		else if (data->s[i] == RED_OUT && data->s[i + 1] == RED_OUT)
			i = handle_here_doc_out(data, i, tmp_f);
		else if (data->s[i] == RED_IN)
			i = handle_redin(data, i, tmp_f);
		else if (data->s[i] == RED_OUT)
			i = handle_redout(data, i, tmp_f);
		else if (data->s[i] == PIPE)
			i = handle_pipe(data, i, tmp, tmp_f);
		else if (data->s[i] == D_QUOT || data->s[i] == S_QUOT)
			i = handle_s_quote(data, i, tmp, (int)data->s[i]);
		else
			i = handle_string(data, i, tmp);
		i++;
		if (data->s[i] == '\0')
			ft_lstnew_exec(ft_strdup(tmp->value), STRING, tmp_f);
	}
	aff1(data->exec, data->exec->file);
}

int	main(int ac, char **av, char **en)
{
	t_data	*data;
	char	**menv;
	char	**export;

	(void)av;
	menv = ft_envo(en);
	export = ft_envo(en);
	sort_export(export);
	if (ac == 1)
	{
		data = malloc(sizeof(t_data));
		while (1)
		{
			data->s = readline("minishell>");
			add_history(data->s);
			lexer(data);
			if (data->g_exit_status)
            //system("leaks minishell");
			// transmettre(data, &menv, &export);
			free(data->s);
			// free_exec(&data->exec);
		}
	}
    ft_free(menv);
    ft_free(export);
}
