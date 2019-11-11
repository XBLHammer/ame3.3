#ifndef _NETWORK_H
#define _NETWORK_H

#pragma once
#include "stdafx.h"
#include "Tools.h"

typedef enum _XNCALLER_TYPE : DWORD {
	XNCALLER_INVALID = 0x00,
	XNCALLER_TITLE = 0x01,
	XNCALLER_SYSAPP = 0x02,
	XNCALLER_XBDM = 0x03,
	XNCALLER_TEST = 0x04,
} XNCALLER_TYPE;

#pragma pack(1)
typedef struct _AUTH_REQUEST {
	BYTE CPUKey[0x10];
	BYTE FUSEKey[0x10];
	BYTE ModuleDigest[0x14];
} AUTH_REQUEST, *PAUTH_REQUEST;
typedef struct _AUTH_RESPONSE {
	DWORD Status;
	DWORD FreeMode;
} AUTH_RESPONSE, *PAUTH_RESPONSE;
typedef struct _GOBALS_REQUEST {
	BYTE CPUKey[0x10];
	BYTE FUSEKey[0x10];
} GOBALS_REQUEST, *PGOBALS_REQUEST;
typedef struct _GOBALS_RESPONSE {
	DWORD Patches[2];
} GOBALS_RESPONSE, *PGOBALS_RESPONSE;
#pragma pack()

static SOCKET m_Socket;
static DWORD SocketError;
static BYTE Temp[0x4080];
static BOOL Connected;

static unsigned char IP[4] = { 0x7C, 0x3D, 0xA5, 0xC6 }; //74.91.116.149
static WORD Port = 2245;

class Network {
public:
	static SOCKET Connect();
	static VOID Disconnect();
	static BOOL Send(DWORD Command, PVOID Buffer, DWORD Length);
	static BOOL Receive(PVOID Buffer, DWORD Length);
	static BOOL Process(DWORD Command, PVOID Request, DWORD RequestLength, PVOID Response, DWORD ResponseLength, BOOL Close = TRUE);
	static VOID ReceiveUpdate();
	static BOOL Authenticate();
};

static SOCKET(_cdecl *NetDll_socket)(XNCALLER_TYPE Xnc, DWORD Af, DWORD Type, DWORD Protocol)
= (SOCKET(*)(XNCALLER_TYPE, DWORD, DWORD, DWORD))Tools::ResolveFunction("xam.xex", 0x03);

static DWORD(_cdecl *NetDll_closesocket)(XNCALLER_TYPE Xnc, SOCKET s)
= (DWORD(*)(XNCALLER_TYPE, SOCKET))Tools::ResolveFunction("xam.xex", 0x04);

static DWORD(_cdecl *NetDll_shutdown)(XNCALLER_TYPE Xnc, SOCKET s, DWORD Method)
= (DWORD(*)(XNCALLER_TYPE, SOCKET, DWORD))Tools::ResolveFunction("xam.xex", 0x05);

static DWORD(_cdecl *NetDll_setsockopt)(XNCALLER_TYPE Xnc, SOCKET s, DWORD Level, DWORD Option, CONST PCHAR Value, DWORD Length)
= (DWORD(*)(XNCALLER_TYPE, SOCKET, DWORD, DWORD, CONST PCHAR, DWORD))Tools::ResolveFunction("xam.xex", 0x07);

static DWORD(_cdecl *NetDll_connect)(XNCALLER_TYPE Xnc, SOCKET s, CONST struct sockaddr *Name, DWORD Length)
= (DWORD(*)(XNCALLER_TYPE, SOCKET, CONST struct sockaddr*, DWORD))Tools::ResolveFunction("xam.xex", 0x0C);

static DWORD(_cdecl *NetDll_recv)(XNCALLER_TYPE Xnc, SOCKET s, CONST CHAR FAR *Buffer, DWORD Length, DWORD Flags)
= (DWORD(*)(XNCALLER_TYPE, SOCKET, CONST CHAR FAR*, DWORD, DWORD))Tools::ResolveFunction("xam.xex", 0x12);

static DWORD(_cdecl *NetDll_send)(XNCALLER_TYPE Xnc, SOCKET s, CONST CHAR FAR *Buffer, DWORD Length, DWORD Flags)
= (DWORD(*)(XNCALLER_TYPE, SOCKET, CONST CHAR FAR*, DWORD, DWORD))Tools::ResolveFunction("xam.xex", 0x16);

static DWORD(_cdecl *NetDll_WSAStartupEx)(XNCALLER_TYPE Xnc, WORD VersionA, LPWSADATA Wsad, DWORD VersionB)
= (DWORD(*)(XNCALLER_TYPE, WORD, LPWSADATA, DWORD))Tools::ResolveFunction("xam.xex", 0x24);

static DWORD(_cdecl *NetDll_XNetStartup)(XNCALLER_TYPE Xnc, XNetStartupParams *Xnsp)
= (DWORD(*)(XNCALLER_TYPE, XNetStartupParams*))Tools::ResolveFunction("xam.xex", 0x33);

#endif