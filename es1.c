/*Processo padre crea 3 figli, attenda la terminazione e ne stampa la terminazione in ordine di creazione; 
ogni processo figlio genera un numero n pari al modulo tra il suo pid e 10, va in sleep(n) 
e termina con stato di terminazione pari ad n */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 3

int main(){
    pid_t pid[N];
    int stat[N];
    int n; //num generato da figlio

    for(int i=0;i<N;i++){
        pid[i]=fork;
        switch(pid[i]){
            case -1:
                perror("Fork failed");
                exit(EXIT_FAILURE);
                break;
            case 0:
                //figlio
                n = getpid()%10;
                printf("\nChild PID %d, number %d : n = %d",getpid(),i,n);
                sleep(n);
                exit(n);
                break;
            default:
                waitpid(pid[i],&stat[i],0);
                break;
                
        }       
    }

    printf("\nI child hanno terminato");
    for(int i=0;i<N;i++){
        if(WIFEXITED(stat[i])){
            printf("\nChild number %d exited with status %d",WEXITSTATUS(stat[i]));
        }else
            printf("\nAbnormal exit");
    }
    exit(EXIT_SUCCESS);
}