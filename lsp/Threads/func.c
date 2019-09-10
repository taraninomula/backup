#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void function(void *arg);

char message[] = "Hello World";

int main() {
    
    function(message);
    printf("Waiting for function to finish...\n");
    
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void function(void *arg) {
    printf("function is running. Argument was %s\n", (char *)arg);
    sleep(3);
    strcpy(message, "Bye!");
}
