#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "opcode.h"

int main(int argc, const char **argv)
{
	error_t res = SUCCESS;
	struct opcode opcode;

	uint8_t *bytes = (uint8_t *)"\x66\xF0\x0F\xC2";

	res = parse_opcode(bytes, &opcode);
	VERIFY_SUCCESS();
	
	printf("prefixes: %x\n", opcode.prefixes);

cleanup:
	return res;
}
