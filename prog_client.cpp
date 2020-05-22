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

using namespace std;

int main(int argc, char *argv[])
{                           
	struct hostent* host = gethostbyname(argv[1]);    
	
	sockaddr_in addr;
	bzero((char*)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	addr.sin_port = htons(atoi(argv[2]));
	
	int client_socket = socket(AF_INET, SOCK_STREAM, 0); //make TCP-socket
	if (connect(client_socket, (sockaddr*)&addr, sizeof(addr)) < 0)
	{
		cerr<<"ERROR!!! Connection failed."<<endl;
		exit(0);
	}
	else
	{
		cout << "--------Connection is done--------" << endl;
		int flag = 1;
		while(flag == 1)
		{
			cout << ">> ";
			string my_buffer;
			char server_buffer [250];
		
			cin >> my_buffer;
			strcpy(server_buffer, my_buffer.c_str());
			if(my_buffer == "exit")
			{
				send(client_socket, (char*)&server_buffer, strlen(server_buffer), 0);
				flag = 0;
				break;
			}
			send(client_socket, (char*)&server_buffer, strlen(server_buffer), 0);
			cout << "Waiting for server response..." << endl;
			memset(&server_buffer, 0, sizeof(server_buffer));
			recv(client_socket, (char*)&server_buffer, sizeof(server_buffer), 0);
			if(server_buffer == "exit")
			{
				flag = 0;
				break;
			}
			cout << "Server message << " << server_buffer << endl;
		}
	}
	close(client_socket);
	cout << "---------Exit connection---------" << endl;
	return 0;
}
