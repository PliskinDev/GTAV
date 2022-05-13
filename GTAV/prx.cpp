#include <pthread.h>
#include <sys\time.h>
#include <string.h>
#include <functional>
#include <queue>
#include "enum.h"
#include "natives.h"

void print(const char* str, int ms = 4000)
{
	UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str);
	UI::END_TEXT_COMMAND_PRINT(ms, 1);
}

void* main_thread(void*)
{
	sceKernelSleep(10);
	print("Hello Sprx", 1000);
	scePthreadExit(0);
}

ScePthread threadid;
extern "C" int module_start(size_t args, const void* argp)
{
	scePthreadSetcancelstate(PTHREAD_CANCEL_ENABLE, 0);
	scePthreadCreate(&threadid, NULL, main_thread, NULL, "GTAV");
	return 0;
}

extern "C" int module_stop(size_t args, const void* argp)
{
	scePthreadCancel(threadid);
	return 0;
}
