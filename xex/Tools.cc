#include "stdafx.h"
#include "Tools.h"

#pragma warning(push)
#pragma warning(disable:4826)

pDmSetMemory DevSetMemory = NULL;
typedef VOID(*CryptRC4)(const PBYTE pbKey, DWORD cbKey, PBYTE pbInpOut, DWORD cbInpOut);
CryptRC4 RC4Crypt;
typedef VOID(*CryptSHA)(PBYTE pbInp1, DWORD cbInp1, const PBYTE pbInp2, DWORD cbInp2, const PBYTE pbInp3, DWORD cbInp3, PBYTE pbOut, DWORD cbOut);
CryptSHA SHACrypt;

BOOL Tools::TrayOpen()
{
	BYTE Input[0x10], Output[0x10];
	ZeroMemory(Output, 0x10);
	Input[0x00] = 0x0A;
	HalSendSMCMessage(Input, Output);
	return Output[0x01] == 0x60 ? TRUE : FALSE;
}

VOID XNotifyThread(PWCHAR String)
{
	XNotifyUISetOptions(TRUE, TRUE, TRUE, TRUE);
	XNotifyQueueUI(0x22, 0xFF, 0x02, String, NULL);
}

VOID Tools::XNotify(PWCHAR String, DWORD Type)
{
	if (KeGetCurrentProcessType() != PROC_USER)
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)XNotifyThread, (PVOID)String, NULL, NULL);
	else
		XNotifyThread(String);
}

VOID Tools::ApplyPatches(PVOID Buffer)
{
	DWORD PatchCount = NULL;
	PDWORD PatchData = (PDWORD)Buffer;
	while (*PatchData != 0xFFFFFFFF)
	{
		memcpy((PVOID)PatchData[0x00], &PatchData[0x02], PatchData[0x01] * 0x04);
		PatchData += (PatchData[0x01] + 0x02);
		PatchCount++;
	}
}

BOOL Tools::FileExists(CONST PCHAR FilePath)
{
	if (GetFileAttributes(FilePath) == INVALID_FILE_ATTRIBUTES)
	{
		DWORD LastError = GetLastError();
		if ((LastError == ERROR_FILE_NOT_FOUND || ERROR_PATH_NOT_FOUND))
			return FALSE;
	}
	return TRUE;
}

BOOL Tools::CReadFile(CONST PCHAR FilePath, MemoryBuffer &Buffer)
{
	HANDLE Handle = CreateFile(FilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (Handle == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD FileSize = GetFileSize(Handle, NULL);
	PBYTE pBuffer = (PBYTE)malloc(FileSize);
	if (pBuffer == NULL)
	{
		CloseHandle(Handle);
		return FALSE;
	}
	DWORD ReadSize = NULL;
	if (!ReadFile(Handle, pBuffer, FileSize, &ReadSize, NULL))
	{
		free(pBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	else if (ReadSize != FileSize)
	{
		free(pBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	CloseHandle(Handle);
	Buffer.Add(pBuffer, FileSize);
	free(pBuffer);
	return TRUE;
}

BOOL Tools::CWriteFile(CONST PCHAR FilePath, CONST PVOID Buffer, DWORD Length)
{
	HANDLE Handle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (Handle == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD WriteSize = Length;
	if (!WriteFile(Handle, Buffer, WriteSize, &WriteSize, NULL))
		return FALSE;

	CloseHandle(Handle);
	return TRUE;
}

static HvxCall HvxExpansionInstall(DWORD PhysicalAddress, DWORD CodeSize)
{
	__asm {
		li r0, 0x70
			sc
			blr
	}
}

static HvxCall HvxExpansionCall(DWORD ExpansionId, QWORD r4 = NULL, QWORD r5 = NULL, QWORD r6 = NULL, QWORD r7 = NULL)
{
	__asm {
		li r0, 0x71
			sc
			blr
	}
}

BOOL Tools::InitializeHvxPeekPoke()
{
	PVOID Buffer = XPhysicalAlloc(0x1000, MAXULONG_PTR, NULL, PAGE_READWRITE);
	DWORD Address = (DWORD)MmGetPhysicalAddress(Buffer);
	ZeroMemory(Buffer, 0x1000);
	memcpy(Buffer, HvxPeekPokeExp, 0x2F0);
	DWORD Result = (DWORD)HvxExpansionInstall(Address, 0x1000);
	XPhysicalFree(Buffer);
	return Result == S_OK ? TRUE : FALSE;
}

void Tools::TestThread()
{
	//DWORD a = Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(0x3F5AE148, KEYS[3]), KEYS[6]), KEYS[7]), KEYS[1]), KEYS[12]), KEYS[9]), KEYS[2]);
	//DWORD b = Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Response.Patches[1], KEYS[12]), KEYS[3]), KEYS[4]), KEYS[6]), KEYS[2]), KEYS[0]), KEYS[5]);
	//memcpy((PVOID)0xC01D06D0, &a, 4);
	//memcpy((PVOID)(0xC01D06D0 + 0x6), &b, 4);
}

BYTE Tools::HvxPeekBYTE(QWORD Address)
{
	return (BYTE)HvxExpansionCall(HvxPeekPokeExpID, PEEK_BYTE, Address);
}

WORD Tools::HvxPeekWORD(QWORD Address)
{
	return (WORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_WORD, Address);
}

DWORD Tools::HvxPeekDWORD(QWORD Address)
{
	return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_DWORD, Address);
}

QWORD Tools::HvxPeekQWORD(QWORD Address)
{
	return HvxExpansionCall(HvxPeekPokeExpID, PEEK_QWORD, Address);
}

DWORD Tools::HvxPeekBytes(QWORD Address, PVOID Buffer, DWORD Length)
{
	PVOID pBuffer = XPhysicalAlloc(Length, MAXULONG_PTR, NULL, PAGE_READWRITE);
	ZeroMemory(pBuffer, Length);
	DWORD Result = (DWORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_BYTES, Address, (QWORD)MmGetPhysicalAddress(pBuffer), Length);
	if (Result == S_OK)
		memcpy(Buffer, pBuffer, Length);

	XPhysicalFree(pBuffer);
	return Result;
}

DWORD Tools::HvxPokeBYTE(QWORD Address, BYTE Value)
{
	return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_BYTE, Address, Value);
}

DWORD Tools::HvxPokeWORD(QWORD Address, WORD Value)
{
	return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_WORD, Address, Value);
}

DWORD Tools::HvxPokeDWORD(QWORD Address, DWORD Value)
{
	return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_DWORD, Address, Value);
}

DWORD Tools::HvxPokeQWORD(QWORD Address, QWORD Value)
{
	return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_QWORD, Address, Value);
}

DWORD Tools::HvxPokeBytes(QWORD Address, CONST PVOID Buffer, DWORD Length)
{
	PVOID pBuffer = XPhysicalAlloc(Length, MAXULONG_PTR, NULL, PAGE_READWRITE);
	memcpy(pBuffer, Buffer, Length);
	DWORD Result = (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_BYTES, Address, (QWORD)MmGetPhysicalAddress(pBuffer), Length);
	XPhysicalFree(pBuffer);
	return Result;
}

QWORD Tools::HvxGetFuseLine(DWORD Index)
{
	return Tools::HvxPeekQWORD(0x8000020000020000 + (Index * 0x200));
}


HRESULT Tools::SetMemory(LPVOID lpDest, LPVOID lpSrc, DWORD dwLength)
{
	memcpy(lpDest, lpSrc, dwLength);
	return ERROR_SUCCESS;
}


DWORD Tools::ResolveFunction(PCHAR ModuleName, DWORD Ordinal)
{
	HANDLE ModuleHandle; DWORD Address;
	XexGetModuleHandle(ModuleName, &ModuleHandle);
	XexGetProcedureAddress(ModuleHandle, Ordinal, &Address);
	return Address;
}

VOID Tools::DetourFunction(PDWORD FunctionAddress, DWORD DestinationFunction)
{
	if (DestinationFunction & 0x8000)
	{
		FunctionAddress[0] = 0x3D600000 + (((DestinationFunction >> 16) & 0xFFFF) + 1);
	}
	else
	{
		FunctionAddress[0] = 0x3D600000 + ((DestinationFunction >> 16) & 0xFFFF);
	}
	FunctionAddress[1] = 0x396B0000 + (DestinationFunction & 0xFFFF);
	FunctionAddress[2] = 0x7D6903A6;
	FunctionAddress[3] = 0x4E800420;
}

VOID Tools::PatchInJump(PDWORD Address, DWORD Destination, BOOL linked)
{
	if (Destination & 0x8000)
		Address[0] = 0x3D600000 + (((Destination >> 16) & 0xFFFF) + 1);
	else
		Address[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);

	Address[1] = 0x396B0000 + (Destination & 0xFFFF);
	Address[2] = 0x7D6903A6;

	if (linked)
		Address[3] = 0x4E800421;
	else
		Address[3] = 0x4E800420;
	__dcbst(0, Address);
	__sync();
}

VOID __declspec(naked) GLPR(VOID)
{
	__asm {
		std r14, -0x98(sp)
			std r15, -0x90(sp)
			std r16, -0x88(sp)
			std r17, -0x80(sp)
			std r18, -0x78(sp)
			std r19, -0x70(sp)
			std r20, -0x68(sp)
			std r21, -0x60(sp)
			std r22, -0x58(sp)
			std r23, -0x50(sp)
			std r24, -0x48(sp)
			std r25, -0x40(sp)
			std r26, -0x38(sp)
			std r27, -0x30(sp)
			std r28, -0x28(sp)
			std r29, -0x20(sp)
			std r30, -0x18(sp)
			std r31, -0x10(sp)
			stw r12, -0x08(sp)
			blr
	}
}

DWORD Tools::RelinkGPLR(DWORD SFSOffset, PDWORD SaveStubAddress, PDWORD OriginalAddress)
{
	DWORD Instruction = 0, Replacing;
	PDWORD Saver = (PDWORD)GLPR;
	if (SFSOffset & 0x2000000)
	{
		SFSOffset = SFSOffset | 0xFC000000;
	}
	Replacing = OriginalAddress[SFSOffset / 4];
	for (int i = 0; i < 20; i++)
	{
		if (Replacing == Saver[i])
		{
			int NewOffset = (int)&Saver[i] - (int)SaveStubAddress;
			Instruction = 0x48000001 | (NewOffset & 0x3FFFFFC);
		}
	}
	return Instruction;
}

VOID Tools::hookFunctionStartEx(...)
{
	DWORD *addr, *saveStub, dest;
	__asm
	{
		mr addr, r3
			mr saveStub, r4
			mr dest, r5
	}
	if (saveStub != NULL && addr != NULL)
	{
		DWORD addrReloc = (DWORD)(&addr[4]);

		if (addrReloc & 0x8000)
			saveStub[0] = 0x3D600000 + (((addrReloc >> 16) & 0xFFFF) + 1);
		else
			saveStub[0] = 0x3D600000 + ((addrReloc >> 16) & 0xFFFF);

		saveStub[1] = 0x396B0000 + (addrReloc & 0xFFFF);
		saveStub[2] = 0x7D6903A6;

		for (int i = 0; i < 4; i++)
		{
			if ((addr[i] & 0x48000003) == 0x48000001)
				saveStub[i + 3] = Tools::RelinkGPLR((addr[i] & ~0x48000003), &saveStub[i + 3], &addr[i]);
			else
				saveStub[i + 3] = addr[i];
		}
		saveStub[7] = 0x4E800420;
		__dcbst(0, saveStub);
		__sync();
		__isync();

		Tools::PatchInJump((PDWORD)addr, dest, FALSE);
	}
}

DWORD Tools::PatchModuleImport(PLDR_DATA_TABLE_ENTRY Handle, PCHAR ImportedModule, DWORD Ordinal, DWORD PatchAddress)
{
	DWORD Address = (DWORD)Tools::ResolveFunction(ImportedModule, Ordinal);
	if (Address == NULL)
		return S_FALSE;

	PVOID HeaderBase = Handle->HeaderBase;
	PXEX_IMPORT_DESCRIPTOR ImportDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(HeaderBase, 0x000103FF);
	if (ImportDesc == NULL)
		return S_FALSE;

	DWORD Result = 0x02;
	PCHAR StringTable = (PCHAR)(ImportDesc + 0x01);
	PXEX_IMPORT_TABLE_ORG ImportTable = (PXEX_IMPORT_TABLE_ORG)(StringTable + ImportDesc->TableSize);
	for (DWORD a = NULL; a < ImportDesc->ModuleCount; a++)
	{
		PDWORD ImportAdd = (PDWORD)(ImportTable + 0x01);
		for (DWORD b = NULL; b < ImportTable->ImportTable.ImportCount; b++)
		{
			DWORD Value = *((PDWORD)ImportAdd[b]);
			if (Value == Address)
			{
				memcpy((PDWORD)(ImportAdd[b]), &PatchAddress, 0x04);
				DWORD NewAddress[0x04];
				Tools::PatchInJump(NewAddress, PatchAddress, FALSE);
				memcpy((PDWORD)(ImportAdd[b + 0x01]), NewAddress, 0x10);
				Result = S_OK;
			}
		}
		ImportTable = (PXEX_IMPORT_TABLE_ORG)(((PBYTE)ImportTable) + ImportTable->TableSize);
	}
	return Result;
}

DWORD Tools::getAddedValueDWORD(DWORD first, DWORD second, int type)
{
	switch (type)
	{
	case 0:
		return (first + second);
	case 1:
		return (first - second);
	case 2:
		return (first * second);
	case 3:
		return (first / second);
	}
}

BOOL hasResolved = FALSE;
DWORD Tools::XOREncryptDWORD(DWORD vals, DWORD key)
{
	if (hasResolved == FALSE)
	{
		RC4Crypt = (CryptRC4)ResolveFunction("xboxkrnl.exe", 0x10D + getAddedValueDWORD(0x5C, 0x24, 0));
		SHACrypt = (CryptSHA)ResolveFunction("xboxkrnl.exe", 0x94 + getAddedValueDWORD(0xDD, 0x21, 0));
		hasResolved = TRUE;
	}
	BYTE * pbyte = (BYTE *)&vals;
	BYTE x[4];
	for (int i = 0; i < 4; i++)
	{
		x[i] = pbyte[i] ^ key;
	}
	return (x[0]) | (x[1] << 8) | (x[2] << 16) | (x[3] << 24);
}

DWORD Tools::calc(DWORD num1, DWORD num2)
{
	return num1 + num2;
}

DWORD Tools::PatchModuleImport(PCHAR Module, PCHAR ImportedModule, DWORD Ordinal, DWORD PatchAddress)
{
	PLDR_DATA_TABLE_ENTRY Handle = (PLDR_DATA_TABLE_ENTRY)GetModuleHandle(Module);
	return (Handle == NULL) ? S_FALSE : Tools::PatchModuleImport(Handle, ImportedModule, Ordinal, PatchAddress);
}

VOID Tools::SpoofyPatch()
{
	BYTE spoofyCheck[0x10];
	Tools::HvxPeekBytes(0xFF90, &spoofyCheck, 0x10);
	for (int PatchSpoofy = 0; PatchSpoofy < 0x10; PatchSpoofy++)
	{
		if (spoofyCheck[PatchSpoofy] != 0)
		{
			HalReturnToFirmware(0x05);
		}
	}
}

PBYTE Tools::GetCPUKey()
{
	QWORD Fuses[0x02] = { Tools::HvxGetFuseLine(0x03) | Tools::HvxGetFuseLine(0x04), Tools::HvxGetFuseLine(0x05) | Tools::HvxGetFuseLine(0x06) };
	memcpy(CPUKey, Fuses, 0x10);
	return CPUKey;
}

PBYTE Tools::GetModuleDigest()
{
	MemoryBuffer mbMD;
	if (!Tools::CReadFile(MODULE_PATH, mbMD))
	{
		if (!Tools::CReadFile(MODULE_PATH2, mbMD))
		{
			HalReturnToFirmware(0x05);
		}
	}
	SHACrypt(mbMD.GetBuffer(), mbMD.GetLength(), NULL, NULL, NULL, NULL, ModuleDigest, 0x14);
	return ModuleDigest;
}

PBYTE Tools::GetUniqueConsoleKey()
{
	BYTE UCK[0x10];
	BYTE fuseLine2[0x8];
	BYTE smcVersion[0x5];
	DWORD consoleSpecificFlags = XboxHardwareInfo->Flags;
	Tools::HvxPeekBytes(0x8000020000020800, fuseLine2, 0x8);
	HalSendSMCMessage((PVOID)0x10, smcVersion);
	SHACrypt(fuseLine2, 0x8, (BYTE*)consoleSpecificFlags, 4, NULL, NULL, UCK, 0x10);
	return UCK;
}

PBYTE Tools::GetFuseDigest()
{
	BYTE FuseDigestRC4[0x10];
	DWORD Address/*0x8E03AA30*/ = Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(Tools::XOREncryptDWORD(0x26BC1598, KEYS[12]), KEYS[15]), KEYS[9]), KEYS[5]), KEYS[16]), KEYS[19]), KEYS[13]);
	RC4Crypt((BYTE*)Address, 0x10, FuseDigestRC4, 0x10);
	RC4Crypt(FuseDigestRC4, 0x10, FuseDigestRC4, 0x10);
	SHACrypt((BYTE*)Address, 0x10, GetCPUKey(), 0x10, NULL, NULL, FuseDigestRC4, 0x10);
	return FuseDigestRC4;
}
#pragma warning(pop)