#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#define SERV_TCP_PORT 8236 
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{

<<<<<<< HEAD
    int sockfd;
    //int bytesReceived = 0;
    struct sockaddr_in serv_addr;
    unsigned char recvBuff[50000];

    char *ip = "127.0.0.1";
    char *puerto = "5001";
=======
  int sockfd;
  struct sockaddr_in serv_addr;
  char *serv_host = "localhost";
  struct hostent *host_ptr;
  int port;
  int buff_size = 0;
  char recvBuff[5000];
>>>>>>> 1803d5b8b121d2a2554064725511694849f71380

  /* command line: client [host [port]]*/
  if(argc >= 2) 
     serv_host = argv[1]; /* read the host if provided */
  if(argc == 3)
     sscanf(argv[2], "%d", &port); /* read the port if provided */
  else 
     port = SERV_TCP_PORT;

  /* get the address of the host */
  if((host_ptr = gethostbyname(serv_host)) == NULL) {
     perror("gethostbyname error");
     exit(1);
  }
  
  if(host_ptr->h_addrtype !=  AF_INET) {
     perror("unknown address type");
     exit(1);
  }
  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = 
     ((struct in_addr *)host_ptr->h_addr_list[0])->s_addr;
  serv_addr.sin_port = htons(port);
  

  /* open a TCP socket */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
     perror("can't open stream socket");
     exit(1);
  }

  /* connect to the server */    
  if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
     perror("can't connect to server");
     exit(1);
  }

<<<<<<< HEAD
    //Se envía información al socket
    int n = write(sockfd,"PRUEBA DE SOCKET\n",strlen("PRUEBA DE SOCKET\n"));
    if (n < 0)
        error("ERROR writing to socket");

    read(sockfd, recvBuff, 10*sizeof(recvBuff));
    printf("--%s",recvBuff);
=======
  /* write a message to the server */
  read(sockfd, recvBuff, sizeof(recvBuff));
  printf("%s\n", recvBuff);
    
  close(sockfd);
>>>>>>> 1803d5b8b121d2a2554064725511694849f71380
       
    return 0;
}