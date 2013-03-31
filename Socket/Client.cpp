#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define HELLO_WORLD_SERVER_PORT    9981
#define BUFFER_SIZE 10
#define FILE_NAME_MAX_SIZE 512

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./%s ServerIPAddress\n", argv[0]);
		exit(1);
	}

	//设置一个socket地址结构client_addr,代表客户机internet地址, 端口
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr)); //把一段内存区的内容全部设置为0
	client_addr.sin_family = AF_INET; //internet协议族
	client_addr.sin_addr.s_addr = htons(INADDR_ANY ); //INADDR_ANY表示自动获取本机地址
	client_addr.sin_port = htons(0); //0表示让系统自动分配一个空闲端口
	//创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0)
	{
		printf("Create Socket Failed!\n");
		exit(1);
	}
	//把客户机的socket和客户机的socket地址结构联系起来
	if (bind(client_socket, (struct sockaddr*) &client_addr, sizeof(client_addr)))
	{
		printf("Client Bind Port Failed!\n");
		exit(1);
	}

	//设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;

	if (inet_aton(argv[1], &server_addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
	{
		printf("Server IP Address Error!\n");
		exit(1);
	}
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
	socklen_t server_addr_length = sizeof(server_addr);

	if (connect(client_socket, (struct sockaddr*) &server_addr, server_addr_length) < 0)
	{
		printf("Can Not Connect To %s!\n", argv[1]);
		exit(1);
	}

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);

	//从服务器接收数据到buffer中
	bzero(buffer, BUFFER_SIZE);
	int length = 0;
	int sum = 0;

	int tttt = 0;
	while (1)
	{
		if (tttt != 2)
			cin >> tttt;
		length = recv(client_socket, buffer, BUFFER_SIZE, 0);
		if (length < 0)
		{
			printf("Recieve Data From Server %s Failed!\n", argv[1]);
			break;
		}
		else if (!length)
		{
			printf("Recieve Data From Server %s end!\n", argv[1]);
			break;
		}
		printf("Recieve Data%d !\n", length);
		sum += length;
	}

	printf("sum Recieve Data%d !\n", sum);
	close(client_socket);
	return 0;
}
