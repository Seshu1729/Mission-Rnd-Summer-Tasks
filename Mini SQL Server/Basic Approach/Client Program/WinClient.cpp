/*
PROBLEM STATEMENT::

	Take 2 Arrays of Structs of student data with Values already stored in server
	[HardCode/Load from a file on server side].

	One struct is to store metadata of students like name,fname,mother name ,rollnum,phone etc
	and one struct is to store his subject marks [6 as of now] both structs will be linked to each other 
	by a common student_id field.

	Now you need to write a client program which sends queries [SQL Like],
	and your server should parse them and send the relavent data back and Client should display it .  
	[Main goal her is to support JOIN kind of queries]

SAMPLE COMMAND::

	1. CALCULATE MIN WHERE location = Hyderabad
	2. CALCULATE AVG WHERE first_name = Seshu
*/

#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <conio.h>
#define buffer_size 128


//////////////////////////////////////////////
//											//
//		  ***GLOBAL VARIABLES***			//
//											//
//////////////////////////////////////////////


int host_port = 1101;
char *host_name = "127.0.0.1";

unsigned short wVersionRequested;
WSADATA wsaData;
int err;

struct sockaddr_in my_addr;
int buffer_len = 1024, bytecount;

int hsock;

char buffer[buffer_size], result[buffer_size], *responce;

//////////////////////////////////////////////
//											//
//		  ***CLIENT FUNCTIONS***			//
//											//
//////////////////////////////////////////////

int getsocket()
{
	int hsock;
	int * p_int;
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if (hsock == -1)
	{
		printf("Error initializing socket %d\n", WSAGetLastError());
		return -1;
	}

	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
	if ((setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1) ||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1))
	{
		printf("Error setting options %d\n", WSAGetLastError());
		free(p_int);
		return -1;
	}
	free(p_int);

	return hsock;
}

void send_message(char *buffer)
{

	hsock = getsocket();
	if (connect(hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Error connecting socket %d\n", WSAGetLastError());
		return;
	}

	if ((bytecount = send(hsock, buffer, strlen(buffer), 0)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		return;
	}
}

char *receive_message()
{
	char buffer[buffer_size];
	memset(buffer, '\0', buffer_size);
	if ((bytecount = recv(hsock, buffer, buffer_len, 0)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		return NULL;
	}

	closesocket(hsock);
	return buffer;
}

void socket_client()
{

	char option = 'y';
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2))
	{
		fprintf(stderr, "Could not find sock dll %d\n", WSAGetLastError());
		return;
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = inet_addr(host_name);

	while (option == 'Y' || option == 'y')
	{
		printf("ENTER QUERY COMMAND::");
		fflush(stdin);
		scanf("%[^\n]s", buffer);
		send_message(buffer);
		responce = receive_message();
		strcpy(result, responce);
		puts(result);

		printf("\nDO YOU WANT TO CONTINUE[Y/N]::");
		fflush(stdin);
		scanf("%c", &option);
	}

}