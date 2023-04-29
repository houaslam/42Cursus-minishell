/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:58:51 by aatki             #+#    #+#             */
/*   Updated: 2023/04/29 10:35:20 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex/pipex_bonus.h"

void	ft_lstadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = (*lst);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void in(char **av,t_pipe **pipe)
{
    int i=1;
    char **s;
    t_pipe *tmp;
    while(av[i])
    {
        s=ft_split(av[i],' ');
        tmp=malloc(sizeof(t_pipe));
        (tmp)->cmd=malloc(30);
        (tmp)->cmd[0]=s[0];
        (tmp)->cmd[1]=s[1];
        (tmp)->cmd[2]=NULL;
        (tmp)->infile=s[2];
        (tmp)->outfile=s[3];
        tmp->here_doc=NULL;
        tmp->next=NULL;
        ft_lstadd_back(pipe,tmp);
        i++;
    }
    (*pipe)->cmd[1]=NULL;
    // (*pipe)->next->infile=NULL;
}

int main(int c,char **av,char **env)
{
    (void)c;
    t_pipe *pipe;
    exit_status=55;
    char **menv=ft_envo(env);
    char **export=ft_envo(env);
    sort_export(export);
    in(av,&pipe);
    pipex(pipe,&menv,&export);
}




































    // while(pipe)
    // {
    //     printf("s1=%s s2=%s\n",pipe->cmd[0],pipe->cmd[1]);
    //     pipe=pipe->next;
    // }
    // exit(0);