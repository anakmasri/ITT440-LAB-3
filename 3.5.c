
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define WAIT_INTERVAL 10

int main() {

        void sigint_handler(int sig);

        int i;
        int check;

        int fd[2];
        pipe(fd);
        pid_t pid = fork();

        //init signal
        if(signal(SIGINT, sigint_handler) == SIG_ERR){
                perror("signal");
                exit(1);
        }


        if(pid > 0){
                close(0);
                close(fd[1]);
                dup(fd[0]);

                int numP, flag = 0;
                read(fd[0], &numP, sizeof(numP));
                printf("Checking the number...\n");
                wait(NULL);

                for(i = 2; i <= numP/2; i++){
                        //condition for non-prime
                        if(numP % i == 0){
                                flag == 1;
                                break;
                        }
                }
                if(numP == 1)
                        printf("--> 1 is neither prime nor composite.\n\n");
                else{
                        if(flag == 0)
                                printf("--> %d is a prime number.\n\n", numP);
                        else
                                printf("--> %d is not a prime number.\n\n", numP);
                }
        }
        else if(pid == 0){
                int num;
                //prompt user
                printf("\nDo you want to check prime numbers? Select one below.\n");
                printf("[1] Yes, I want to check prime numbers.\n");
                printf("[2] Nope.\n");
                printf("Please make a selection : ");
                scanf("%d", &check);
                if(check == 1){
                        printf("\nPlease enter positive integer : ");
                        scanf("%d", &num);
                        write(fd[1], &num, sizeof(num));

                        exit(EXIT_SUCCESS);
                }
                else if(check == 2)
                        exit(EXIT_SUCCESS);
        }

        sleep(WAIT_INTERVAL);
        return EXIT_SUCCESS;
}

void sigint_handler(int sig){
        printf("\n--Ending all process--\n");
}

