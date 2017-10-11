
#pragma once
#include <stdint.h>

struct Rz
{
	uint32_t * thirdarg;
	uint32_t returnaddr;
	static void GrabArg();
};

static Rz Rz_;


