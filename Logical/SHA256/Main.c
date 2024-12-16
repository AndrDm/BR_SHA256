#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "sha256.h"
 
static long long begin, begin_saved, end;

long long rdtsc() {
	unsigned int low, high;
	__asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
		return ((long long)high << 32) | low;
}

void _INIT ProgramInit(void)
{
	int i; //C99
	for(i = 0; i< sizeof(buffer); i++) buffer[i] = 'a';
	cycles_counter = 0;
}

void _CYCLIC ProgramCyclic(void)
{
	SHA256_CTX ctx;

	begin = rdtsc();
	cycle_time = (LREAL)(begin - begin_saved);
	begin_saved = begin;
	
	sha256_init(&ctx);
	sha256_update(&ctx, buffer, sizeof(buffer));
	sha256_final(&ctx, digest);

	end = rdtsc();
	cpu_time_used = ((LREAL)(end - begin));

	MBperSec = cycle_time / cpu_time_used;
	cycles_counter++;
}

void _EXIT ProgramExit(void) {}
