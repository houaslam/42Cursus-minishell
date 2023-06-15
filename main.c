# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>

int k;

int main()
{
    k=3;
    int ph[0];
    pipe(ph);
    int id=fork();
    if(id==0)
    {
        k=5;
        write(ph[1],"jjjjjjjjj\n",10);
        close(ph[1]);
        return 0;
    }
    char s[11];
    read(ph[0],s,11);
    printf("%s",s);
}
