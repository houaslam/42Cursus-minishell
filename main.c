/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 00:56:35 by aatki             #+#    #+#             */
/*   Updated: 2023/04/02 21:00:57 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ft_cd (char **av , char **env)
// {
//     av={"cd", "..",NULL};
//     execve("");
// }

void found(char *sa,char **env)
{
    int i=0;
    while(env[i])
    {
        if(strncmp(env[i],sa,ft_strlen(sa)))
            printf("%s",env[i]+ft_strlen(sa)+1);
        i++;
    }
    return ;
}

void ft_echo(char *str, int fd,char **env)
{
    dup2(fd,1);
    char **s=ft_split(str,' ');
    int i=0;
    if(strncmp(s[0],"-n",2))
        i++;
    while(s[i])
    {
        if(s[i][0]== '$')
        {
            if(s[i][1]== '\'' || s[i][1]== '\"')
                printf("%s",s[i]+2);
            else
                found(s[i]+1,env);
        }
        else
            printf("%s",s[i]);
    }
    if(strncmp(s[0],"-n",2))
        printf("\n");
}

int main (int c ,char **av,char **env)
{
    //printf("jhjbk\n");
    ft_echo("$PATH",1,env);
    //ft_cd(av,env);
}
