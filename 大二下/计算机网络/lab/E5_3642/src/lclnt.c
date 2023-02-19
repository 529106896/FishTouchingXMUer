#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_ticket();
int release_ticket();
char* do_transcation(char*);
void shut_down();
void set_up();

void do_regular_work(){
    printf("SuperSleep version 1.0 Running-Licensed Software\n");
    sleep(15);
}

int main(int ac,char *av[]){
    set_up();
    if(get_ticket()!=0){
        exit(0);
    }

    do_regular_work();

    release_ticket();
    shut_down();
}

