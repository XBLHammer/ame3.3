#ifndef _TOOLS_H
#define _TOOLS_H

#pragma once
#include "stdafx.h"
#include "kernel.h"
#include <stdio.h>
#include <time.h>
#include <xtl.h>

extern BYTE CPUKey[0x10];
extern BYTE ModuleDigest[0x14];

#define MODULE_PATH "HDD:\\GTAVEnforcer.xex"
#define MODULE_PATH2 "USB:\\GTAVEnforcer.xex"

class Tools {
public:
	static BOOL TrayOpen();
	static VOID XNotify(PWCHAR String, DWORD Type);
	static VOID ApplyPatches(PVOID Buffer);
	static BOOL FileExists(CONST PCHAR FilePath);
	static BOOL CReadFile(CONST PCHAR FilePath, MemoryBuffer &Buffer);
	static BOOL CWriteFile(CONST PCHAR FilePath, CONST PVOID Buffer, DWORD Length);
	static BOOL InitializeHvxPeekPoke();
	static BYTE HvxPeekBYTE(QWORD Address);
	static WORD HvxPeekWORD(QWORD Address);
	static DWORD HvxPeekDWORD(QWORD Address);
	static QWORD HvxPeekQWORD(QWORD Address);
	static DWORD HvxPeekBytes(QWORD Address, PVOID Buffer, DWORD Length);
	static DWORD HvxPokeBYTE(QWORD Address, BYTE Value);
	static DWORD HvxPokeWORD(QWORD Address, WORD Value);
	static DWORD HvxPokeDWORD(QWORD Address, DWORD Value);
	static DWORD HvxPokeQWORD(QWORD Address, QWORD Value);
	static DWORD HvxPokeBytes(QWORD Address, CONST PVOID Buffer, DWORD Length);
	static QWORD HvxGetFuseLine(DWORD Index);
	static HRESULT SetMemory(LPVOID lpDest, LPVOID lpSrc, DWORD dwLength);
	static DWORD ResolveFunction(PCHAR ModuleName, DWORD Ordinal);
	static VOID DetourFunction(PDWORD FunctionAddress, DWORD DestinationFunction);
	static VOID PatchInJump(PDWORD Address, DWORD Destination, BOOL linked);
	static DWORD RelinkGPLR(DWORD Offset, PDWORD SaveStub, PDWORD Original);
	static VOID hookFunctionStartEx(...);
	static DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Handle, PCHAR ImportedModule, DWORD Ordinal, DWORD PatchAddress);
	static DWORD PatchModuleImport(PCHAR Module, PCHAR ImportedModule, DWORD Ordinal, DWORD PatchAddress);
	static DWORD getAddedValueDWORD(DWORD first, DWORD second, int type);
	static DWORD XOREncryptDWORD(DWORD vals, DWORD key);
	static DWORD calc(DWORD num1, DWORD num2);
	static VOID Tools::SpoofyPatch();
	static PBYTE GetCPUKey();
	static PBYTE GetModuleDigest();
	static PBYTE GetFuseDigest();

	//Testing
	static PBYTE GetUniqueConsoleKey();
	static void Tools::TestThread();
};

static DWORD (_cdecl *XamGetCurrentTitleId)()
	= (DWORD(*)())Tools::ResolveFunction("xam.xex", 0x1CF);

static VOID (_cdecl *XNotifyQueueUI)(DWORD Type, DWORD UserIndex, QWORD Areas, PWCHAR String, PVOID Context)
	= (VOID(*)(DWORD, DWORD, QWORD, PWCHAR, PVOID))Tools::ResolveFunction("xam.xex", 0x290);

static VOID (_cdecl *XNotifyUISetOptions)(BOOL Show, BOOL ShowMovie, BOOL PlaySound, BOOL ShowIPTV)
	= (VOID(*)(BOOL, BOOL, BOOL, BOOL))Tools::ResolveFunction("xam.xex", 0x292);

static VOID (_cdecl *XeCryptSha)(CONST PBYTE pbInp1, DWORD cbInp1, CONST PBYTE pbInp2, DWORD cbInp2, CONST PBYTE pbInp3, DWORD cbInp3, PBYTE pbOut, DWORD cbOut)
	= (VOID(*)(CONST PBYTE, DWORD, CONST PBYTE, DWORD, CONST PBYTE, DWORD, PBYTE, DWORD))Tools::ResolveFunction("xboxkrnl.exe", 0x192);

#pragma region Encryption
	static DWORD HID1 = Tools::calc(0xC, 0x01);
	static DWORD RAN1 = Tools::calc(0x50, 0x0E);
	static DWORD FUC3 = Tools::calc(0x70, 0x0D);
	static DWORD HOO2 = Tools::calc(0x80, 0x0A);
	static DWORD GJNJ2 = Tools::calc(0xC0, 0x0E);

	static DWORD KEYS[] = { HID1, 0xE3, 0x78, 0x04, 0x6A, 0x71, 0x0A,
	0xC1, 0x47, FUC3, 0x21, 0xB7, RAN1, 0x8D, 0x2C, GJNJ2,
	0x8D, 0x75, 0xDA, 0x8A };
#pragma endregion
#endif