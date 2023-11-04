#pragma once

#include <stdint.h>
#include <stddef.h>
#include "errors.h"

typedef enum {
	LOCK                  = (1 << 0),
	REPNZ                 = (1 << 1),
	REPZ                  = (1 << 2),
	CS_OVERRIDE           = (1 << 3),
	SS_OVERRIDE           = (1 << 4),
	DS_OVERRIDE           = (1 << 5),
	ES_OVERRIDE           = (1 << 6),
	FS_OVERRIDE           = (1 << 7),
	GS_OVERRIDE           = (1 << 8),
	BRANCH_NOT_TAKEN      = (1 << 9),
	BRANCH_TAKEN          = (1 << 10),
	OPERAND_SIZE_OVERRIDE = (1 << 11),
	ADDRESS_SIZE_OVERRIDE = (1 << 12),
} prefix_t;

struct opcode {
	size_t opcode_len;

	prefix_t prefixes;
};

error_t parse_opcode(const uint8_t *bytes, struct opcode *opcode);
