#include "stdafx.h"
#include "Network.h"

#define UsingEncryption
unsigned char EncryptionKey[8] = { 0xED, 0xBE, 0xFC, 0xDA, 0xC0, 0xAD, 0x13, 0x37 };

SOCKET Network::Connect()
{
	XNetStartupParams XNSP;
	ZeroMemory(&XNSP, sizeof(XNSP));
	XNSP.cfgSizeOfStruct = sizeof(XNetStartupParams);
	XNSP.cfgFlags = XNET_STARTUP_BYPASS_SECURITY;
	if (NetDll_XNetStartup(XNCALLER_SYSAPP, &XNSP) != S_OK)
		return INVALID_SOCKET;

	WSADATA WsaData;
	if (NetDll_WSAStartupEx(XNCALLER_SYSAPP, MAKEWORD(0x02, 0x02), &WsaData, 0x02) != S_OK)
		return INVALID_SOCKET;

	if ((m_Socket = NetDll_socket(XNCALLER_SYSAPP, AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		return INVALID_SOCKET;

	BOOL SockOpt = TRUE;
	if (NetDll_setsockopt(XNCALLER_SYSAPP, m_Socket, SOL_SOCKET, 0x5801, (CONST PCHAR)&SockOpt, 0x04) != S_OK)
		return INVALID_SOCKET;

	DWORD SendRecvSize = 0x800;
	NetDll_setsockopt(XNCALLER_SYSAPP, m_Socket, SOL_SOCKET, SO_SNDBUF, (CONST PCHAR)&SendRecvSize, 0x04);
	NetDll_setsockopt(XNCALLER_SYSAPP, m_Socket, SOL_SOCKET, SO_RCVBUF, (CONST PCHAR)&SendRecvSize, 0x04);

	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(Port);
	sockaddr.sin_addr.S_un.S_un_b.s_b1 = IP[0x00];
	sockaddr.sin_addr.S_un.S_un_b.s_b2 = IP[0x01];
	sockaddr.sin_addr.S_un.S_un_b.s_b3 = IP[0x02];
	sockaddr.sin_addr.S_un.S_un_b.s_b4 = IP[0x03];
	if (NetDll_connect(XNCALLER_SYSAPP, m_Socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
		return INVALID_SOCKET;

	Connected = TRUE;

	return m_Socket;
}

VOID Network::Disconnect()
{
	NetDll_closesocket(XNCALLER_SYSAPP, m_Socket);
	m_Socket = NULL;
}

BOOL Network::Send(DWORD Command, PVOID Buffer, DWORD Length)
{
	memcpy(Temp, &Command, 0x04);
	memcpy(Temp + 0x04, &Length, 0x04);
	memcpy(Temp + 0x08, Buffer, Length);

	DWORD Remaining = Length + 0x08;
	PCHAR Current = (PCHAR)Temp;
	while (Remaining > NULL)
	{
		DWORD SendSize = min(0x800, Remaining);
		DWORD Sent = NetDll_send(XNCALLER_SYSAPP, m_Socket, Current, SendSize, NULL);
		if (Sent == SOCKET_ERROR)
			return FALSE;

		Remaining -= Sent;
		Current += Sent;
	}
	return TRUE;
}

BOOL Network::Receive(PVOID Buffer, DWORD Length)
{
	DWORD Remaining = Length;
	DWORD Received = NULL;
	while (Remaining > NULL)
	{
		DWORD RecvSize = min(0x800, Remaining);
		DWORD Recv = NetDll_recv(XNCALLER_SYSAPP, m_Socket, (PCHAR)Buffer + Received, RecvSize, NULL);
		if (Recv == SOCKET_ERROR)
			return FALSE;

		if (Recv == NULL)
			break;

		Remaining -= Recv;
		Received += Recv;
	}
	if (Received != Length)
		return FALSE;

	return TRUE;
}

BOOL Network::Process(DWORD Command, PVOID Request, DWORD RequestLength, PVOID Response, DWORD ResponseLength, BOOL Close)
{
	if (Network::Connect() == INVALID_SOCKET)
		return FALSE;

	if (!Network::Send(Command, Request, RequestLength))
		return FALSE;

	if (!Network::Receive(Response, ResponseLength))
		return FALSE;

	if (Close)
		Network::Disconnect();

	return TRUE;
}

VOID Network::ReceiveUpdate()
{
	DWORD ModuleSize = NULL;
	if (!Network::Receive(&ModuleSize, 0x04))
		HalReturnToFirmware(0x05);

	PBYTE ModuleBuffer = (PBYTE)XPhysicalAlloc(ModuleSize, MAXULONG_PTR, 0x00, PAGE_READWRITE);
	if (Network::Receive(ModuleBuffer, ModuleSize))
	{
		if (!Tools::CWriteFile(MODULE_PATH, ModuleBuffer, ModuleSize))
		{
			if (!Tools::CWriteFile(MODULE_PATH2, ModuleBuffer, ModuleSize))
			{
				HalReturnToFirmware(0x05);
			}
		}
	}
	XPhysicalFree(ModuleBuffer);
	Network::Disconnect();
	Tools::XNotify(L"Enforcer Menu - Update Complete. Rebooting Now...", 0x22);
	Sleep(5000);
	HalReturnToFirmware(0x03);
}

BOOL Network::Authenticate()
{
#ifdef UsingEncryption
	XeCryptRc4((unsigned char*)EncryptionKey, 8, (unsigned char*)IP, 0x04);
#endif

	PAUTH_REQUEST Request = (PAUTH_REQUEST)XEncryptedAlloc(sizeof(AUTH_REQUEST));
	AUTH_RESPONSE Response;
	memcpy(Request->CPUKey, Tools::GetCPUKey(), 0x10);
	memcpy(Request->FUSEKey, Tools::GetFuseDigest(), 0x10);
	memcpy(Request->ModuleDigest, Tools::GetModuleDigest(), 0x14);
	if (!Network::Process(0x00000001, Request, sizeof(AUTH_REQUEST), &Response, sizeof(AUTH_RESPONSE), FALSE))
		return FALSE;

	switch (Response.Status)
	{
	case 0xC0000000:
		Network::ReceiveUpdate();
		return TRUE;
		break;
	case 0xD0000000:
		Network::Disconnect();
		return TRUE;
		break;
	case 0xE0000000:
		Network::Disconnect();
		return FALSE;
		break;
	}
	return FALSE;
}