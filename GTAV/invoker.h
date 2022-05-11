//2much4u
#pragma once
#include "types.h"
struct Native_s
{
	Native_s* LastNativeTable;
	uint64_t NativeFunctions[7];
	uint64_t NativeCount;
	uint64_t NativeHashes[7];
};

struct NativeArg_s
{
	uint64_t* Retvalue;
	uint32_t Argcount;
	uint64_t* Argvalues;
	uint32_t Readcount;
};

uint64_t i[30];
static Native_s** NativeTable = (Native_s**)0x3F60028;
static NativeArg_s NativeArg;

void CallHash(uint64_t hash)
{
	Native_s *Natives = NativeTable[hash & 0xFF];
	while (Natives != 0) 
	{
		for (uint64_t i = 0; i < Natives->NativeCount; i++) 
		{
			if (Natives->NativeHashes[i] == hash) {
				((void(*)(NativeArg_s*))Natives->NativeFunctions[i])(&NativeArg);
				return;
			}
		}
		Natives = Natives->LastNativeTable;
	}
}

void ResetArgs() 
{
	NativeArg.Argcount = 0;
	NativeArg.Readcount = 0;
	NativeArg.Argvalues = NativeArg.Retvalue = i;
}

template<typename T>
inline void PushArg(T value) 
{
	*(T*)&NativeArg.Argvalues[NativeArg.Argcount] = value;
	NativeArg.Argcount++;
}

template<typename R>
inline R GetRet() 
{
	return *(R*)&NativeArg.Retvalue[0];
}

template <>
inline Vector3 GetRet<Vector3>()
{
	return{ *(float*)&NativeArg.Retvalue[0], *(float*)&NativeArg.Retvalue[1], *(float*)&NativeArg.Retvalue[2] };
}

template<typename N, typename... A>
N invoke(uint64_t hash, A &&... args)
{
	ResetArgs();
	int dum[] = { 0, ((void)PushArg(std::forward<A>(args)), 0) ... };
	CallHash(hash);
	return GetRet<N>();
}



