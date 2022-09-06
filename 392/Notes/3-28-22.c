int main(){
    pid_t children[5];
    int stat;
    for (size_t i = 0; i < 5; i++){
        if((children[i] - fork()) == 0){
            printf("Im a child %d in %d \n", getpid(), getpgrp());
            exit(EXIT_SUCCESS);
            //5 child are created because exit does not continue on
        }
    }
    return 0;
}

/* 
crtl + c: terminating - sigint
crtl + z: stopping - sigtstop
crtl + \: terminating and core dump -sigquit

(1) ignore
    except: SIGFPE, SIGKILL

(2) catch ad handle

(3) take the default action
    -ignore
    -terminate the process
    -terminate & gen core dumped
    -stop/pause the process
    -resume the stopped process
*/
