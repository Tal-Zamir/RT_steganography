#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 10

void write_file(int sockfd)
{
    int n; 
    FILE *fp;
    unsigned counter = 0;
    char *filename = "bg_got.bmp";
    char buffer[SIZE];

    fp = fopen(filename, "wb");
    
    if(fp == NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }

    while(1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        printf("%d)Read %d Bytes...\n", counter, n);
        counter+=1;
        if(n<=0)
        {
            break;
            fclose(fp);
            return;
        }
        //fprintf(fp, "%s", buffer);
        fwrite(buffer,n,1,fp);
        bzero(buffer, SIZE);
    }
    fclose(fp);
    return;
    
}

int main ()
{
    char *ip = "127.0.0.1"; //IPv4
    int port = 1234;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

/* Socket() - Identify the IP protocol (IPv4\6) of the socket steam and return the file descriptor witch represent an endpoint of the communication or -1 if failed.*/

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
     printf("[+]Server socket created. \n");

     server_addr.sin_family = AF_INET;
     server_addr.sin_port = port;
     server_addr.sin_addr.s_addr = inet_addr(ip);

/* After the socket desriptor is created, bind API will get a unique PORT for the socket (The first to hit is the first to get). */

     e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e<0)
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     printf("[+]Binding Successfull.\n");
     
 /* Listen allows the server to accept incoming client connection (Waiting room to client connections). */    

     e = listen(sockfd, 10);
     if(e==0)
     {
         printf("[+]Listening...\n");
     }
     else 
     {
         perror("[-]Error in Binding");
         exit(1);
     }
     addr_size = sizeof(new_addr);
     
 /* Accept the connetion if there is a descriptor in waiting room (listen). */
     new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

/* send/recv = read/write */
     write_file(new_sock);

     printf("[+]Data written in the binary file ");
}
