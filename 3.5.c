#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define WAIT_INTERVAL 10

int main() {

	void sigint_handler(int sig);

    	int num, i, flag = 0;
	int check, fd[2];


	//init signal
	if(signal(SIGINT, sigint_handler) == SIG_ERR){
		perror("signal");
		exit(1);
	}

	//loop
	do{
	//prompt user
	printf("\nDo you want to check prime numbers? Select one below.\n");
	printf("[1] Yes, I want to check prime numbers.\n");
	printf("[2] No, I vented.\n");
	printf("Please make a selection : ");
	scanf("%d", &check);

	
		//user input
		if (check == 1){
			printf("\nEnter a positive integer : ");
    			scanf("%d", &num);
			printf("Checking the number...\n");
		}
		else if (check == 2){
			exit(EXIT_SUCCESS);
		}

		//processing
    		for (i = 2; i <= num / 2; ++i) {
        		// condition for non-prime
        		if (num % i == 0) {
            			flag = 1;
            			break;
        		}
    		}

    		if (num == 1)
       			printf("--> 1 is neither prime nor composite.\n\n");

    		else {
        		if (flag == 0)
            			printf("--> %d is a prime number.\n\n", num);
        		else
           			printf("--> %d is not a prime number.\n\n", num);
    		}

		printf("Check another numbers? [1-yes|2-no] : ");
		scanf("%d",&check);
	}while(check == 1);

	sleep(WAIT_INTERVAL);
    	return EXIT_SUCCESS;

}

void sigint_handler(int sig){
	printf("\n--Ending all process--\n");	
}
