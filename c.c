#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
int udp_fd;
if((udp_fd=socket(AF_INET,SOCK_DGRAM,0))<0)perror("socket error");
struct sockaddr_in add;
memset(&add,0,sizeof(add));
add.sin_addr.s_addr=htonl(INADDR_ANY);
add.sin_family=AF_INET;
add.sin_port=htons(2000);
if(bind(udp_fd,(struct sockaddr*)&add,sizeof(add))!=0)perror("bind error");

struct ip_mreq group_add;
memset(&group_add,0,sizeof(group_add));
group_add.imr_interface.s_addr=htonl(INADDR_ANY);
if(inet_pton(AF_INET,"224.0.0.10",&group_add.imr_multiaddr.s_addr)==0)perror("inet_pton error");

if(setsockopt(udp_fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&group_add,sizeof(group_add))!=0)perror("setsockopt error");
char buff[1024];
while(1)
{
 	recv(udp_fd,buff,1024,0);
}
 	return 0;
}
