#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>

using namespace std;

void work (int server_socket, int flag)
{
	cout << "Waiting for a client connection..." << endl;
	sockaddr_in second_sesv_addr;
	socklen_t second_sesv_addr_size = sizeof(second_sesv_addr);
	int second_socket = accept(server_socket, (sockaddr *)&second_sesv_addr, &second_sesv_addr_size);
	if(second_socket < 0)
	{
		cerr << "ERROR!!! Connection failed." << endl;
		exit(0);
	}
	cout << "--------Connection is done--------" << endl;
	while(flag == 1)
	{
		char client_buffer[250];
		string my_buffer;
		cout << "Waiting for client response..." << endl;
		memset(&client_buffer, 0, sizeof(client_buffer));
		recv(second_socket, (char*)&client_buffer, sizeof(client_buffer), 0);
		if(strcmp(client_buffer, "exit") == 0)
		{
			flag = 0;
		}
		cout << "Client1 message << " << client_buffer << endl;
		cout << ">> ";
		cin >> my_buffer;
		strcpy(client_buffer, my_buffer.c_str());
		if(my_buffer == "exit")
		{
			send(second_socket, (char*)&client_buffer, strlen(client_buffer), 0);
			flag = 0;
		}
		send(second_socket, (char*)&client_buffer, strlen(client_buffer), 0);
	}
	close(second_socket);
}

void work2 (int server_socket, int flag)
{
	cout << "Waiting for a client connection..." << endl;
	sockaddr_in second_sesv_addr;
	socklen_t second_sesv_addr_size = sizeof(second_sesv_addr);
	int second_socket = accept(server_socket, (sockaddr *)&second_sesv_addr, &second_sesv_addr_size);
	if(second_socket < 0)
	{
		cerr << "ERROR!!! Connection failed." << endl;
		exit(0);
	}
	cout << "--------Connection is done--------" << endl;
	while(flag == 1)
	{
		char client_buffer[250];
		string my_buffer;
                cout << "Waiting for client response..." << endl;
		memset(&client_buffer, 0, sizeof(client_buffer));
		recv(second_socket, (char*)&client_buffer, sizeof(client_buffer), 0);
		if(strcmp(client_buffer, "exit") == 0)
		{
			flag = 0;
		}
		cout << "Client2 message << " << client_buffer << endl;
		cout << ">> ";
		cin >> my_buffer;
		strcpy(client_buffer, my_buffer.c_str());
		if(my_buffer == "exit")
		{
			send(second_socket, (char*)&client_buffer, strlen(client_buffer), 0);
			flag = 0;
		}
		send(second_socket, (char*)&client_buffer, strlen(client_buffer), 0);
	}
	close(second_socket);
}

int main(int argc, char *argv[])
{
	sockaddr_in serv_addr;      
	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);          
	if(server_socket < 0)                                         
	{
		cerr << "Error while establishing the server socket" << endl;
		exit(0);
	}
	int bind_status = bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	if(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr) < 0)                                  {
		cerr << "Error while binding socket to local address" << endl;
		exit(0);
	}
	else
	{
		listen(server_socket, 3);
		int flag1 = 1, flag2 = 1;
		thread th (work, server_socket, flag1);
		thread th2 (work2, server_socket, flag2);
		th.join();
		th2.join();
		if (flag1 == 0)
			exit(0);
		if (flag2 == 0)
			exit(0);
		
	}
	close(server_socket);
	cout << "---------Exit connection---------" << endl;
	return 0;
}
