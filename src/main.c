#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "opcode.h"

int main(int argc, const char **argv)
{
	error_t res = SUCCESS;
	struct opcode opcode;

	uint8_t *bytes = (uint8_t *)"\xF3\x40\x0F\xE6";

	res = parse_opcode(bytes, &opcode);
	VERIFY_SUCCESS();
	
	printf("flags: %x\n", opcode.flags);
	printf("prefixes: %x\n", opcode.prefixes);
	printf("rex: %x\n", *(uint8_t *)&opcode.rex);
	printf("legacy: %x\n", opcode.legacy_prefix);

cleanup:
	return res;
}
