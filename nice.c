#include "types.h"
#include "param.h"
#include "user.h"

int norm_nice(int nicen){
    if(nicen > 5){
        nicen = 5;
    }
    if(nicen < 1){
        nicen = 1;
    }
    return nicen;
}

int main(int argc, char *argv[]){
    //int curr_nice;
    //int adjustment = 10;
    //struct proc *np;
   //char const *adjustment_given = NULL;
    //bool ok;
    int nice;
    int pid;
    int oldnice;
    if(argc > 1){
        if(argc == 2)
            {
                //get pid of current process and return pid and old nice. Update new nice with argv[0]
                pid = getpid();
                nice = norm_nice(atoi(argv[1]));

            }
        if(argc == 3){
            pid = atoi(argv[1]);
            nice = norm_nice(atoi(argv[2]));
            
        }
        else if (argc > 3)
        {
            printf(1, "Too many arguments passed\n");
            exit();
        }

    oldnice = assign_nice(pid, nice);
    }
    else{
        printf(1, "No arguments passed\n");
        exit();
    }
    if(oldnice == -100){
        printf(1, "Error, nice value passed invalid, exiting.\n");
        exit();
    }

    if(oldnice == -101){
        printf(1, "Error, PID %d not found, exiting.\n", pid);
        exit();
    }

    printf(1, "%d ", pid);
    printf(1, "%d\n", oldnice);

    exit();
};
