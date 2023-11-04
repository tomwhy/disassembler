#include "opcode.h"
#include <string.h>
#include "errors.h"

#define PREFIX_GROUP1 (LOCK | REPNZ | REPZ)
#define PREFIX_GROUP2 (CS_OVERRIDE | SS_OVERRIDE | DS_OVERRIDE | FS_OVERRIDE | GS_OVERRIDE | ES_OVERRIDE | BRANCH_TAKEN | BRANCH_NOT_TAKEN)
#define PREFIX_GROUP3 (OPERAND_SIZE_OVERRIDE)
#define PREFIX_GROUP4 (ADDRESS_SIZE_OVERRIDE)

#define REX_PREFIX_MASK 0xF0
#define REX_PREFIX 0x40

#define PREFIX_CASE(_byte, _prefix, _group)							\
case _byte:															\
	if(opcode->prefixes & PREFIX_GROUP##_group) {					\
		EXIT_FUNC(SUCCESS);											\
	}																\
	opcode->prefixes |= _prefix;									\
	break;

static error_t parse_opcode_prefixes(const uint8_t **bytes, struct opcode *opcode)
{
	error_t res = SUCCESS;
	const uint8_t *current_prefix = *bytes;
	opcode->prefixes = 0;

	while(1) {
		switch(*current_prefix) {
			PREFIX_CASE(0xF0, LOCK, 1);
			PREFIX_CASE(0xF2, REPNZ, 1);
			PREFIX_CASE(0xF3, REPZ, 1);

			// 0x2E is BRANCH_NOT_TAKEN on Jcc instructions
			PREFIX_CASE(0x2E, CS_OVERRIDE, 2);
			PREFIX_CASE(0x36, SS_OVERRIDE, 2);
			// 0x3E is BRANCH_TAKEN on Jcc instructions
			PREFIX_CASE(0x3E, DS_OVERRIDE, 2);
			PREFIX_CASE(0x26, ES_OVERRIDE, 2);
			PREFIX_CASE(0x64, FS_OVERRIDE, 2);
			PREFIX_CASE(0x65, GS_OVERRIDE, 2);

			PREFIX_CASE(0x66, OPERAND_SIZE_OVERRIDE, 3);
			
			PREFIX_CASE(0x67, ADDRESS_SIZE_OVERRIDE, 4);

		default:
			EXIT_FUNC(SUCCESS);
		}

		current_prefix++;
	}


cleanup:
	*bytes = current_prefix;
	return res;
}

static error_t parse_rex_prefix(const uint8_t **bytes, struct opcode *opcode)
{
	uint8_t prefix = **bytes;

	if((prefix & REX_PREFIX_MASK) == REX_PREFIX) {
		opcode->rex = *(const struct rex *)(*bytes);
		opcode->flags |= F_REX;
	}

	return SUCCESS;
}

error_t parse_opcode(const uint8_t *bytes, struct opcode *opcode)
{
	error_t res = SUCCESS;
	const uint8_t *opcode_start = bytes;
	memset(opcode, 0, sizeof(*opcode));

	res = parse_opcode_prefixes(&bytes, opcode);
	VERIFY_SUCCESS();

	res = parse_rex_prefix(&bytes, opcode);
	VERIFY_SUCCESS();

	

	opcode->opcode_len = bytes - opcode_start;

cleanup:
	return res;
}
