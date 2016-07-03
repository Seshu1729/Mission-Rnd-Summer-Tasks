#include "stdafx.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#define student_count 5
#define buffer_size 128
#define details_file "asserts/student_details.txt"
#define marks_file "asserts/student_marks.txt"

DWORD WINAPI SocketHandler(void*);


//////////////////////////////////////////////
//											//
//		    ***STRUCTURES DATA***			//
//											//
//////////////////////////////////////////////

struct student_details
{
	int student_id;
	char first_name[buffer_size];
	char last_name[buffer_size];
	char location[buffer_size];
	char gender[buffer_size];
};

struct student_marks
{
	int student_id;
	int *marks;
};

//////////////////////////////////////////////
//											//
//		    ***SERVER FUNCTIONS***			//
//											//
//////////////////////////////////////////////

void socket_server()
{
	int host_port = 1101;
	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0 || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2))
	{
		fprintf(stderr, "No sock dll %d\n", WSAGetLastError());
		goto FINISH;
	}

	int hsock;
	int *p_int;
	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if (hsock == -1)
	{
		printf("Error initializing socket %d\n", WSAGetLastError());
		goto FINISH;
	}

	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
	if ((setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1) || (setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1))
	{
		printf("Error setting options %d\n", WSAGetLastError());
		free(p_int);
		goto FINISH;
	}
	free(p_int);

	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1)
	{
		fprintf(stderr, "Error binding to socket %d\n", WSAGetLastError());
		goto FINISH;
	}

	if (listen(hsock, 10) == -1)
	{
		fprintf(stderr, "Error listening %d\n", WSAGetLastError());
		goto FINISH;
	}

	int* csock;
	sockaddr_in sadr;
	int	addr_size = sizeof(SOCKADDR);
	int request_count = 0;

	while (true)
	{
		csock = (int*)malloc(sizeof(int));

		if ((*csock = accept(hsock, (SOCKADDR*)&sadr, &addr_size)) != INVALID_SOCKET)
		{
			request_count++;
			printf("REQUEST RECEIVED :: %d\n", request_count);
			CreateThread(0, 0, &SocketHandler, (void*)csock, 0, 0);
		}
		else
		{
			fprintf(stderr, "Error accepting %d\n", WSAGetLastError());
		}
	}
	FINISH:
	/*DO NOTHING*/;
}

char *receive_message(int *csock)
{
	char buffer[1024];
	int bytecount;
	memset(buffer, 0, buffer_size);
	if ((bytecount = recv(*csock, buffer, buffer_size, 0)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		free(csock);
		return 0;
	}
	return buffer;
}

void send_message(int *csock, char *buffer)
{
	int bytecount;
	if ((bytecount = send(*csock, buffer, strlen(buffer), 0)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		free(csock);
	}
}

//////////////////////////////////////////////
//											//
//		 ***DATA IMPORT FUNCTIONS***		//
//											//
//////////////////////////////////////////////

struct student_details *import_student_details()
{
	int index;
	FILE *file_pointer = fopen(details_file, "r");
	struct student_details *std_details;
	std_details = (struct student_details *)malloc(5 * sizeof(struct student_details));
	if (file_pointer)
	{
		for (index = 0; index < student_count; index++)
		{
			fscanf(file_pointer, "%d\n", &std_details[index].student_id);
			fscanf(file_pointer, "%s\n", std_details[index].first_name);
			fscanf(file_pointer, "%s\n", std_details[index].last_name);
			fscanf(file_pointer, "%s\n", std_details[index].location);
			fscanf(file_pointer, "%s\n", std_details[index].gender);
		}
	}
	else
	{
		printf("IOError!!!\nplease check necessary files");
		exit(1);
	}
	return std_details;
}

struct student_marks *import_student_marks()
{
	int index;
	FILE *file_pointer = fopen(marks_file, "r");
	struct student_marks *std_marks;
	std_marks = (struct student_marks *)malloc(5 * sizeof(struct student_marks));
	if (file_pointer)
	{
		for (index = 0; index < student_count; index++)
		{
			std_marks[index].marks = (int *)malloc(sizeof(int) * 6);
			fscanf(file_pointer, "%d\n", &std_marks[index].student_id);
			fscanf(file_pointer, "%d ", &std_marks[index].marks[0]);
			fscanf(file_pointer, "%d ", &std_marks[index].marks[1]);
			fscanf(file_pointer, "%d ", &std_marks[index].marks[2]);
			fscanf(file_pointer, "%d ", &std_marks[index].marks[3]);
			fscanf(file_pointer, "%d ", &std_marks[index].marks[4]);
			fscanf(file_pointer, "%d\n", &std_marks[index].marks[5]);
		}
	}
	else
	{
		printf("IOError!!!\nplease check necessary files");
		exit(1);
	}
	return std_marks;
}

//////////////////////////////////////////////
//											//
//		    ***DATA EXTRACTION***			//
//											//
//////////////////////////////////////////////

int *group_by(struct student_details *std_details, struct student_marks *std_marks, char *where)
{
	int *vertical_checker, index;
	char field_name[buffer_size], target_name[buffer_size];
	vertical_checker = (int *)calloc(student_count, sizeof(int));
	sscanf(where, "%s = %s", field_name, target_name);
	if (!strcmp(field_name, "first_name"))
	{
		for (index = 0; index<student_count; index++)
			if (!strcmp(target_name, std_details[index].first_name))
				vertical_checker[index] = 1;
	}
	else if (!strcmp(field_name, "last_name"))
	{
		for (index = 0; index<student_count; index++)
			if (!strcmp(target_name, std_details[index].last_name))
				vertical_checker[index] = 1;
	}
	else if (!strcmp(field_name, "location"))
	{
		for (index = 0; index<student_count; index++)
		{
			if (!strcmp(target_name, std_details[index].location))
				vertical_checker[index] = 1;
		}
	}
	else if (!strcmp(field_name, "gender"))
	{
		for (index = 0; index<student_count; index++)
			if (!strcmp(target_name, std_details[index].gender))
				vertical_checker[index] = 1;
	}
	return vertical_checker;
}

char *get_avg(struct student_marks *std_marks, int *vertical_checker)
{
	char buffer[buffer_size];
	int index1, index2;
	char result[buffer_size] = "     STUDENT_ID         AVG\n";
	float sum_of_all_marks = 0;
	for (index1 = 0; index1<student_count; index1++)
	{
		if (vertical_checker[index1] == 1)
		{
			for (index2 = 0; index2<6; index2++)
				sum_of_all_marks += std_marks[index1].marks[index2];
			sprintf(buffer, "\t%d\t\t%f\n", std_marks[index1].student_id, sum_of_all_marks / 6);
			strcat(result, buffer);
		}
	}
	return result;
}

char *get_min(struct student_marks *std_marks, int *vertical_checker)
{
	char buffer[buffer_size];
	int index1, index2, min_mark;
	char result[buffer_size] = "     STUDENT_ID         MIN\n";
	for (index1 = 0; index1<student_count; index1++)
	{
		min_mark = std_marks[index1].marks[0];
		if (vertical_checker[index1] == 1)
		{
			for (index2 = 0; index2<6; index2++)
				if (min_mark>std_marks[index1].marks[index2])
					min_mark = std_marks[index1].marks[index2];
			sprintf(buffer, "\t%d\t\t%d\n", std_marks[index1].student_id, min_mark);
			strcat(result, buffer);
		}
	}
	return result;
}

char *get_max(struct student_marks *std_marks, int *vertical_checker)
{
	char buffer[buffer_size];
	int index1, index2, max_mark;
	char result[buffer_size] = "     STUDENT_ID         MAX\n";
	for (index1 = 0; index1<student_count; index1++)
	{
		max_mark = std_marks[index1].marks[0];
		if (vertical_checker[index1] == 1)
		{
			for (index2 = 0; index2<6; index2++)
				if (max_mark<std_marks[index1].marks[index2])
					max_mark = std_marks[index1].marks[index2];
			sprintf(buffer, "\t%d\t\t%d\n", std_marks[index1].student_id, max_mark);
			strcat(result, buffer);
		}
	}
	return result;
}

char *execute_command(char *command, struct student_marks *std_marks, struct student_details *std_details)
{
	int *vertical_checker;
	char calculate[buffer_size], where[buffer_size];
	char field_name[buffer_size], target_name[buffer_size];
	sscanf(command, "CALCULATE %s WHERE %[^;\n]s;", calculate, where);
	vertical_checker = group_by(std_details, std_marks, where);
	if (!strcmp(calculate, "AVG"))
		return get_avg(std_marks, vertical_checker);
	else if (!strcmp(calculate, "MIN"))
		return get_min(std_marks, vertical_checker);
	else if (!strcmp(calculate, "MAX"))
		return get_max(std_marks, vertical_checker);
	else
		return "INVALID COMMAND";
}

void process_message(int *csock)
{
	char *message, *responce;
	struct student_marks *std_marks = import_student_marks();
	struct student_details *std_details = import_student_details();
	message = receive_message(csock);
	responce = execute_command(message,std_marks,std_details);
	send_message(csock, responce);
}

//////////////////////////////////////////////
//											//
//		     ***SERVER THREAD***			//
//											//
//////////////////////////////////////////////

DWORD WINAPI SocketHandler(void* lp)
{
	int *csock = (int*)lp;
	process_message(csock);
	return 0;
}