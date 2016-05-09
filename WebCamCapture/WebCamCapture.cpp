// WebCamCapture.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "PipeServer.h"
#include "WebCamCapture.h"



extern "C" __declspec(dllexport) void VoidFunc()
{
	
	PipeServer *Server = new PipeServer(L"\\\\.\\pipe\\test_pipe");
	Server->startServer();
	Server->data = L"Hello from pipe\n";

	while (Server->data != L"exit" || Server->data != L"EXIT")
	{
		Server->sendData();
		//wait for command to record video
		Server->receiveData();
		std::cout << "Received data: " << Server->data << "\n";
	}
	Server->stopServer();
}