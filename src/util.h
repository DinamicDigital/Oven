#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

typedef uint8_t  u8;
typedef int8_t   s8;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint64_t u64;
typedef int64_t  s64;

// FREE BUFFER WHEN DONE WITH IT.
char* read_entire_file(char* file, u32* size)
{
	FILE* source_file = fopen(file, "rb");
	if (!source_file)
	{
		perror("skycloud");
		return 0;
	}
	fseek(source_file, 0, SEEK_END);
	
	long src_size = ftell(source_file);
	
	fseek(source_file, 0, SEEK_SET);
	
	char* buffer = malloc(src_size + 1);
	fread(buffer, 1, src_size, source_file);
	
	fclose(source_file);
	
	buffer[src_size] = 0;
	
	*size = src_size;
	
	return buffer;
}