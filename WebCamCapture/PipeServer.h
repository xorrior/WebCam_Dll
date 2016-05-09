#pragma once
#include <Windows.h>
#include <iostream>

class PipeServer
{
public:
	PipeServer(LPCWSTR pipename);
	~PipeServer();

	LPWSTR command;
	LPWSTR data;
	void startServer();
	void stopServer();
	void receiveData();
	void sendData();
private:
	HANDLE pipe;
	BOOL result;

};

PipeServer::PipeServer(LPCWSTR pipename)
{
	pipe = CreateNamedPipe(pipename, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
	if (pipe == NULL || pipe == INVALID_HANDLE_VALUE)
	{
		//do something
	}

}

PipeServer::~PipeServer()
{
}

void PipeServer::startServer()
{
	//Wait for connection
	result = ConnectNamedPipe(pipe, NULL);
	if (!result)
	{
		//close the pipe and exit
		std::cout << "Closing pipe\n";
		CloseHandle(pipe);
	}
	else
	{
		std::cout << "Server Started\n";
	}

}

void PipeServer::sendData()
{
	DWORD numBytesWritten = 0;
	result = WriteFile(pipe, (LPCVOID **)data, wcslen(data) * sizeof(LPWSTR), &numBytesWritten, NULL);
	if (result)
	{
		std::cout << "Sent data\n";
		std::cout << "Sent " << numBytesWritten << " bytes\n";
	}
	else
	{
		std::cout << "Failed to send data\n";
	}
}

void PipeServer::receiveData()
{
	DWORD numBytesRead = 0;
	result = ReadFile(pipe, data, 127 * sizeof(LPWSTR), &numBytesRead, NULL);
	if (result)
	{
		std::cout << "Received command " << data << "\n" << "Read " << numBytesRead << " bytes\n";
	}
	else
	{
		std::cout << "Unable to read from the pipe\n";
	}
}

void PipeServer::stopServer()
{
	CloseHandle(pipe);
	std::cout << "Pipe closed";
}