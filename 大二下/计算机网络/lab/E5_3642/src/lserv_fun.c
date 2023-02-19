#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PROTNUM 2020
#define MSGLEN 128
#define TICKET_AVAIL 0
#define MAXUSERS 3
#define oops(x) {perror(x);exit(-1);}

int ticket_array[MAXUSERS];
int sd = -1;
int num_ticket_out = 0;
char *do_hello();
char* do_goodbye();
int make_dgram_server_socket(int);
void narrate(char*,char*,struct sockaddr_in *);


int setup(){
    sd = make_dgram_server_socket(SERVER_PROTNUM);
    if(sd == -1){
        oops("make socket");
    }
    int i;
    for(int i =0;i<MAXUSERS;i++){
        ticket_array[i]=TICKET_AVAIL;
    }
    return sd;
}


void shut_down(){
    close(sd);
}

void handle_request(char*req,struct sockaddr_in *client ,socklen_t addlen){
    char *response;
    int ret;
    if(strncmp (req,"HELO",4)==0)
    response = do_hello(req);
    else if(strncmp(req,"GBYE",4)==0)
    response = do_goodbye(req);
    else
    {
        response = "FAIL invalid request";
    }
    narrate("SAID:",response,client);
    ret = sendto(sd,response,strlen(response),0,(struct sockaddr*)client,addlen);
    if(ret == -1)
    perror("SERVER sendto failed");
    
}

char* do_hello(char*msg_p){
    int x;
    static char replybuf[MSGLEN];

    if(num_ticket_out>=MAXUSERS){
        return("FAIL no ticket available");
    }
    for(x = 0;x<MAXUSERS&&ticket_array[x]!=TICKET_AVAIL;x++);
    if(x == MAXUSERS){
        narrate("database corrupt","",NULL);
        return("FAIL database corrupt");
    }
    ticket_array[x]=atoi(msg_p+5);
    sprintf(replybuf,"TICK %d.%d",ticket_array[x],x);
    num_ticket_out++;
    return(replybuf);
}

char* do_goodbye(char*msg_p){
    int pid,solt;
    if((sscanf((msg_p+5),"%d.%d",&pid,&solt)!=2)||(ticket_array[solt]!=pid)){
        narrate("Bogus ticket",msg_p+5,NULL);
        return ("FIAL invalid ticket");
    }
    ticket_array[solt]=TICKET_AVAIL;
    num_ticket_out--;
    return("THNX See ya!");
}

void narrate(char*msg1,char*msg2,struct sockaddr_in *clientp){
    fprintf(stderr,"\t\tSERVER:%s%s",msg1,msg2);
    if(clientp){
        fprintf(stderr,"(%s%d)",inet_ntoa(clientp->sin_addr),ntohs(clientp->sin_port));
        putc('\n',stderr);
    }
}
