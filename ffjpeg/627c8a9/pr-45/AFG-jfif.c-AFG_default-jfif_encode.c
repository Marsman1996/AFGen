#include "AFG-jfif.c-AFG_default-jfif_encode.h"
/* This is the copy of /opt/disk/marsman/ffjpeg/627c8a9/code/jfif.c */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/* Structure definition needed by the fuzz driver */

void* AFG_alloc_list[3] = { NULL };
int AFG_alloc_cnt = 0;
FILE* AFG_fopen_list[1] = { NULL };
int AFG_fopen_cnt = 0;

int AFG_func(BMP* pb)
{
	jfif_encode(pb); 
	return 0;
}

size_t minimum_size = sizeof(BMP)*1;

#ifdef __cplusplus
extern "C" 
#endif
int LLVMFuzzerInitialize(int *argc, char ***argv) {
	printf("Minimum size is %ld\n", minimum_size);
	return 0;
}
#ifdef __cplusplus
extern "C" 
#endif
int LLVMFuzzerTestOneInput(const uint8_t *AFG_Data, size_t Size) {
	size_t AFG_offset = 0;
	if(Size <= minimum_size) {
		// printf("[Error]: Cannot pass size check %ld < %ld\n", Size, minimum_size);
		return -1;
	}
	size_t pt_size = (Size - minimum_size) / 2;
	
	BMP * pb;
	pb = (BMP*)malloc(sizeof(BMP));
	AFG_alloc_list[AFG_alloc_cnt++] = (void*) pb;
		memcpy((void *)&pb->height, AFG_Data+AFG_offset, sizeof(int));
		AFG_offset+=sizeof(int);
		memcpy((void *)&pb->stride, AFG_Data+AFG_offset, sizeof(int));
		AFG_offset+=sizeof(int);
		memcpy((void *)&pb->width, AFG_Data+AFG_offset, sizeof(int));
		AFG_offset+=sizeof(int);
		pb->pdata = (void *)malloc(pt_size);
		AFG_alloc_list[AFG_alloc_cnt++] = (void*) pb->pdata;
		memcpy((void *)pb->pdata, AFG_Data+AFG_offset, pt_size);
		AFG_offset+=pt_size;

	AFG_func(pb);

AFG_fail:
	for(int AFG_free_i = 0; AFG_free_i < AFG_alloc_cnt; AFG_free_i++)
		free(AFG_alloc_list[AFG_free_i]);
	for(int AFG_free_i = 0; AFG_free_i < AFG_fopen_cnt; AFG_free_i++)
		fclose(AFG_fopen_list[AFG_free_i]);
	AFG_alloc_cnt = 0;
	AFG_fopen_cnt = 0;

	return 0;
}
