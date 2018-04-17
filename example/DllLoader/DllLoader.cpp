#define WIN32_LEAN_AND_MEAN
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <malloc.h>

#include "../../MemoryModule.h"
#include <stdlib.h>
#include "debug.h"
#include <iostream>

typedef int(*addNumberProc)(int, int);

//#define DLL_FILE TEXT("..\\SampleDLL\\Debug\\SampleDLL.dll")

bool LoadFromFile(TCHAR* filePath)
{
	addNumberProc addNumber;
	HRSRC resourceInfo;
	DWORD resourceSize;
	LPVOID resourceData;
	TCHAR buffer[100];

	if (nullptr == filePath)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		return false;
	}

	HINSTANCE handle = LoadLibrary(filePath);
	if (handle == NULL)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		return false;
	}

	/* addNumber = (addNumberProc)GetProcAddress(handle, "addNumbers");
	 _tprintf(_T("From file: %d\n"), addNumber(1, 2));

	 //resourceInfo = FindResource(handle, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	 //_tprintf(_T("FindResource returned 0x%p\n"), resourceInfo);

	 //resourceSize = SizeofResource(handle, resourceInfo);
	 //resourceData = LoadResource(handle, resourceInfo);
	 //_tprintf(_T("Resource data: %ld bytes at 0x%p\n"), resourceSize, resourceData);

	 //LoadString(handle, 1, buffer, sizeof(buffer));
	 //_tprintf(_T("String1: %s\n"), buffer);

	 //LoadString(handle, 20, buffer, sizeof(buffer));
	 //_tprintf(_T("String2: %s\n"), buffer);
	 */
	FreeLibrary(handle);
	return true;
}

void* ReadLibrary(size_t* pSize, TCHAR* filePath) {
	size_t read;
	void* result;
	FILE* fp;

	if (nullptr == filePath)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
	}

	fp = _tfopen(filePath, _T("rb"));
	if (fp == NULL)
	{
		_tprintf(_T("Can't open DLL file \"%s\"."), filePath);
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	*pSize = static_cast<size_t>(ftell(fp));
	if (*pSize == 0)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		fclose(fp);
		return NULL;
	}

	result = (unsigned char *)malloc(*pSize);
	if (result == NULL)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		return NULL;
	}

	fseek(fp, 0, SEEK_SET);
	read = fread(result, 1, *pSize, fp);
	fclose(fp);
	if (read != *pSize)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		free(result);
		return NULL;
	}

	return result;
}

void TestPEStruct(TCHAR* filePath)
{
	void *data;
	size_t size;
	HMEMORYMODULE handle;
	addNumberProc addNumber;
	HMEMORYRSRC resourceInfo;
	DWORD resourceSize;
	LPVOID resourceData;
	TCHAR buffer[100];
	if (nullptr == filePath)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
	}

	data = ReadLibrary(&size, filePath);
	if (data == NULL)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		return;
	}

	handle = MemoryLoadLibrary(data, size);
	if (handle == NULL)
	{
		_tprintf(_T("Can't load library from memory.\n"));
		goto exit;
	}

	//addNumber = (addNumberProc)MemoryGetProcAddress(handle, "addNumbers");
	//_tprintf(_T("From memory: %d\n"), addNumber(1, 2));

	MemoryCallEntryPoint(handle);

	MemoryFreeLibrary(handle);

exit:
	free(data);
}

void LoadFromMemory(TCHAR* filePath)
{
	void *data;
	size_t size;
	HMEMORYMODULE handle;
	addNumberProc addNumber;
	HMEMORYRSRC resourceInfo;
	DWORD resourceSize;
	LPVOID resourceData;
	TCHAR buffer[100];

	data = ReadLibrary(&size, filePath);
	if (data == NULL)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		return;
	}

	handle = MemoryLoadLibrary(data, size);
	if (handle == NULL)
	{
		_tprintf(_T("Can't load library from memory.\n"));
		goto exit;
	}

	addNumber = (addNumberProc)MemoryGetProcAddress(handle, "addNumbers");
	_tprintf(_T("From memory: %d\n"), addNumber(1, 2));

	resourceInfo = MemoryFindResource(handle, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	_tprintf(_T("MemoryFindResource returned 0x%p\n"), resourceInfo);

	resourceSize = MemorySizeofResource(handle, resourceInfo);
	resourceData = MemoryLoadResource(handle, resourceInfo);
	_tprintf(_T("Memory resource data: %ld bytes at 0x%p\n"), resourceSize, resourceData);

	MemoryLoadString(handle, 1, buffer, sizeof(buffer));
	_tprintf(_T("String1: %s\n"), buffer);

	MemoryLoadString(handle, 20, buffer, sizeof(buffer));
	_tprintf(_T("String2: %s\n"), buffer);

	MemoryFreeLibrary(handle);

exit:
	free(data);
}

#define MAX_CALLS 20

struct CallList {
	int current_alloc_call, current_free_call;
	CustomAllocFunc alloc_calls[MAX_CALLS];
	CustomFreeFunc free_calls[MAX_CALLS];
};

LPVOID MemoryFailingAlloc(LPVOID address, SIZE_T size, DWORD allocationType, DWORD protect, void* userdata)
{
	UNREFERENCED_PARAMETER(address);
	UNREFERENCED_PARAMETER(size);
	UNREFERENCED_PARAMETER(allocationType);
	UNREFERENCED_PARAMETER(protect);
	UNREFERENCED_PARAMETER(userdata);
	return NULL;
}

LPVOID MemoryMockAlloc(LPVOID address, SIZE_T size, DWORD allocationType, DWORD protect, void* userdata)
{
	CallList* calls = (CallList*)userdata;
	CustomAllocFunc current_func = calls->alloc_calls[calls->current_alloc_call++];
	assert(current_func != NULL);
	return current_func(address, size, allocationType, protect, NULL);
}

BOOL MemoryMockFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType, void* userdata)
{
	CallList* calls = (CallList*)userdata;
	CustomFreeFunc current_func = calls->free_calls[calls->current_free_call++];
	assert(current_func != NULL);
	return current_func(lpAddress, dwSize, dwFreeType, NULL);
}

void InitFuncs(void** funcs, va_list args) {
	for (int i = 0; ; i++) {
		assert(i < MAX_CALLS);
		funcs[i] = va_arg(args, void*);
		if (funcs[i] == NULL) break;
	}
}

void InitAllocFuncs(CallList* calls, ...) {
	va_list args;
	va_start(args, calls);
	InitFuncs((void**)calls->alloc_calls, args);
	va_end(args);
	calls->current_alloc_call = 0;
}

void InitFreeFuncs(CallList* calls, ...) {
	va_list args;
	va_start(args, calls);
	InitFuncs((void**)calls->free_calls, args);
	va_end(args);
	calls->current_free_call = 0;
}

void InitFreeFunc(CallList* calls, CustomFreeFunc freeFunc) {
	for (int i = 0; i < MAX_CALLS; i++) {
		calls->free_calls[i] = freeFunc;
	}
	calls->current_free_call = 0;
}

void TestFailingAllocation(void *data, size_t size) {
	CallList expected_calls;
	HMEMORYMODULE handle;

	InitAllocFuncs(&expected_calls, MemoryFailingAlloc, MemoryFailingAlloc, NULL);
	InitFreeFuncs(&expected_calls, NULL);

	handle = MemoryLoadLibraryEx(
		data, size, MemoryMockAlloc, MemoryMockFree, MemoryDefaultLoadLibrary,
		MemoryDefaultGetProcAddress, MemoryDefaultFreeLibrary, &expected_calls);

	assert(handle == NULL);
	assert(GetLastError() == ERROR_OUTOFMEMORY);
	assert(expected_calls.current_free_call == 0);

	MemoryFreeLibrary(handle);
	assert(expected_calls.current_free_call == 0);
}

void TestCleanupAfterFailingAllocation(void *data, size_t size) {
	CallList expected_calls;
	HMEMORYMODULE handle;
	int free_calls_after_loading;

	InitAllocFuncs(&expected_calls,
		MemoryDefaultAlloc,
		MemoryDefaultAlloc,
		MemoryDefaultAlloc,
		MemoryDefaultAlloc,
		MemoryFailingAlloc,
		NULL);
	InitFreeFuncs(&expected_calls, MemoryDefaultFree, NULL);

	handle = MemoryLoadLibraryEx(
		data, size, MemoryMockAlloc, MemoryMockFree, MemoryDefaultLoadLibrary,
		MemoryDefaultGetProcAddress, MemoryDefaultFreeLibrary, &expected_calls);

	free_calls_after_loading = expected_calls.current_free_call;

	MemoryFreeLibrary(handle);
	assert(expected_calls.current_free_call == free_calls_after_loading);
}

void TestFreeAfterDefaultAlloc(void *data, size_t size) {
	CallList expected_calls;
	HMEMORYMODULE handle;
	int free_calls_after_loading;

	// Note: free might get called internally multiple times
	InitFreeFunc(&expected_calls, MemoryDefaultFree);

	handle = MemoryLoadLibraryEx(
		data, size, MemoryDefaultAlloc, MemoryMockFree, MemoryDefaultLoadLibrary,
		MemoryDefaultGetProcAddress, MemoryDefaultFreeLibrary, &expected_calls);

	assert(handle != NULL);
	free_calls_after_loading = expected_calls.current_free_call;

	MemoryFreeLibrary(handle);
	assert(expected_calls.current_free_call == free_calls_after_loading + 1);
}

#ifdef _WIN64

LPVOID MemoryAllocHigh(LPVOID address, SIZE_T size, DWORD allocationType, DWORD protect, void* userdata)
{
	int* counter = static_cast<int*>(userdata);
	if (*counter == 0) {
		// Make sure the image gets loaded to an address above 32bit.
		uintptr_t offset = 0x10000000000;
		address = (LPVOID)((uintptr_t)address + offset);
	}
	(*counter)++;
	return MemoryDefaultAlloc(address, size, allocationType, protect, NULL);
}

void TestAllocHighMemory(void *data, size_t size) {
	HMEMORYMODULE handle;
	int counter = 0;
	addNumberProc addNumber;
	HMEMORYRSRC resourceInfo;
	DWORD resourceSize;
	LPVOID resourceData;
	TCHAR buffer[100];

	handle = MemoryLoadLibraryEx(
		data, size, MemoryAllocHigh, MemoryDefaultFree, MemoryDefaultLoadLibrary,
		MemoryDefaultGetProcAddress, MemoryDefaultFreeLibrary, &counter);

	assert(handle != NULL);

	addNumber = (addNumberProc)MemoryGetProcAddress(handle, "addNumbers");
	_tprintf(_T("From memory: %d\n"), addNumber(1, 2));

	resourceInfo = MemoryFindResource(handle, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	_tprintf(_T("MemoryFindResource returned 0x%p\n"), resourceInfo);

	resourceSize = MemorySizeofResource(handle, resourceInfo);
	resourceData = MemoryLoadResource(handle, resourceInfo);
	_tprintf(_T("Memory resource data: %ld bytes at 0x%p\n"), resourceSize, resourceData);

	MemoryLoadString(handle, 1, buffer, sizeof(buffer));
	_tprintf(_T("String1: %s\n"), buffer);

	MemoryLoadString(handle, 20, buffer, sizeof(buffer));
	_tprintf(_T("String2: %s\n"), buffer);

	MemoryFreeLibrary(handle);
}
#endif  // _WIN64

void TestCustomAllocAndFree(TCHAR* filePath)
{
	void *data;
	size_t size;

	data = ReadLibrary(&size, filePath);
	if (data == NULL)
	{
		{
			assert(FALSE);
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(__FILE__, nullptr, nullptr, fname, ext);
			strcat_s(fname,_MAX_FNAME, ext);
			OutputDebug("成功检测到错误,检测代码在:%s:%s:%d行\r\n ", fname, __FUNCTION__, __LINE__ - 7);
		}
		return;
	}

	_tprintf(_T("Test MemoryLoadLibraryEx after initially failing allocation function\n"));
	TestFailingAllocation(data, size);
	_tprintf(_T("Test cleanup after MemoryLoadLibraryEx with failing allocation function\n"));
	TestCleanupAfterFailingAllocation(data, size);
	_tprintf(_T("Test custom free function after MemoryLoadLibraryEx\n"));
	TestFreeAfterDefaultAlloc(data, size);
#ifdef _WIN64
	_tprintf(_T("Test allocating in high memory\n"));
	TestAllocHighMemory(data, size);
#endif

	free(data);
}

int main(int argc, TCHAR** argv)
{
	char FilePathBuffer[MAX_PATH] = { 0 };

	TCHAR* filePath = nullptr;
	if (argc > 1)
	{
		if(0==strcmp("-v",argv[1]))
		{
			char version[256] = { 0 };
			sprintf_s(version, "编译日期%s\r\n编译时间%s",__DATE__,__TIME__);
			MessageBoxA(0,version,"",0);
			return 1;
		}
		filePath = argv[1];
	}
	else
	{
		printf("Please Input a file path used check...:\r\n");
		
		std::cin.getline(FilePathBuffer,MAX_PATH);
		filePath = FilePathBuffer;
	}

	printf("Try Use LoadLibrary Load File");
	bool ret = LoadFromFile(filePath);

	if(ret)
	{
		printf("使用系统LoadLibrary成功加载，退出进一步检测请输入q。System Loadlibrary have not error:)\r\n");
		char a= getchar();
		if(a=='q')
		{
			return 2;
		}
	}
	else
	{
		printf("系统API加载该模块失败，意味着存在问题，正在执行深度检测\r\n");
	}


	printf("\n\n");
	//LoadFromMemory();

	__try
	{
		TestPEStruct(filePath);
	}
	__except (1)
	{
		OutputDebug("检测到加载模块\"%s\"的过程中一个异常被抛出\r\n", filePath);
	}
	printf("\n\n");
	system("pause");
	//TestCustomAllocAndFree(filePath);
	return 0;
}

