#include "types.h"
#include "user.h"
#include "stdbool.h"


//doesn't work atm

int main(){
    int i;
    int j;
    int k;
    int f;
    int pid;
    //int p_pid;
    //int waitr;
    //int child;
    
    //create 5 children and run with different nice values
    //p_pid = getpid();

    for(k=0; k>5; k++){
        pid = fork();
        if(pid == 0){
            break;
        }
    }


        if(pid == 0){
            //p_pid = 0;
            pid = getpid();
            assign_nice(pid, k);
            printf(1, "new process %d\n", pid);
            //now change niceness relative to k value    
            for(i = 2; i < 40; i++){
                j = i % 7;
                if( j != 0){
                }
                else{
                    sleep(25);
                    printf(1, "Returning seven multiple %d", i);
                    printf(1 ," from process %d", pid);
                    printf(1 ," with nice value %d\n", k);

                }
            }
        }
        else{
            wait();
        }
    
    }/*
    if(p_pid > 0){
        waitr = wait();
        if(waitr == -1){
            printf(1, "child creation failed\n");
        }
    }*/
    

exit();
}
