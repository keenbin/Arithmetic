#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
/*
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>

 */
#define HELLO_WORLD_SERVER_PORT    9981
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main(int argc, char **argv)
{
	//设置一个socket地址结构server_addr,代表服务器internet地址, 端口
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr)); //把一段内存区的内容全部设置为0
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY );
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

	int server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		printf("Create Socket Failed!");
		exit(1);
	}

	{
		int opt = 1;
		setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	}

	//把socket和socket地址结构联系起来
	if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)))
	{
		printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);
		exit(1);
	}

	//server_socket用于监听
	if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
	{
		printf("Server Listen Failed!");
		exit(1);
	}

	//定义客户端的socket地址结构client_addr
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	int new_server_socket = accept(server_socket, (struct sockaddr*) &client_addr,
			&length);

	if (new_server_socket < 0)
	{
		printf("Server Accept Failed!\n");
		exit(1);
	}

	/*
	 int iMode;
	 iMode = fcntl(new_server_socket, F_GETFL, 0);
	 iMode |= O_NONBLOCK;
	 if (fcntl(new_server_socket, F_SETFL, iMode) < 0)
	 {

	 return -1;
	 }
	 */
	int sum = 0;
	while (1) //服务器端要一直运行
	{

		char buffer[BUFFER_SIZE];
		bzero(buffer, BUFFER_SIZE);

		strcpy(buffer, "1234567890");

		int sendlen = send(new_server_socket, buffer, strlen(buffer), 0);
		if (sendlen < 0)
		{
			printf("Send Failed,%d,%s\n", errno, strerror(errno));
			sleep(30);
			break;
		}
		sum += sendlen;

		if (sendlen != (int) strlen(buffer))
		{
			printf("Send:%d ,str:%d \n", sendlen, strlen(buffer));
		}
		printf("send Data:%d !\n", sendlen);
	}

	printf("sum send Data:%d !\n", sum);
	//关闭与客户端的连接
	close(new_server_socket);
	close(server_socket);
	return 0;
}
