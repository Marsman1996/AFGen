#include "AFG-jfif.c-AFG_default-jfif_decode.h"
/* This is the copy of /opt/disk/marsman/ffjpeg/23dffdf/code/src/jfif.c */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/* Structure definition needed by the fuzz driver */

void* AFG_alloc_list[117+16] = { NULL };
int AFG_alloc_cnt = 0;
FILE* AFG_fopen_list[1] = { NULL };
int AFG_fopen_cnt = 0;

int AFG_func(JFIF* ctxt,BMP* pb)
{
	jfif_decode(ctxt, pb); 
	return 0;
}

size_t minimum_size = sizeof(JFIF)*1+sizeof(HUFCODEC)*32+sizeof(HUFCODEITEM)*8192+sizeof(int)*6+sizeof(BMP)*1;

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
	size_t pt_size = (Size - minimum_size) / (116+16);
	if (pt_size < sizeof(int) || pt_size < sizeof(unsigned char) ) { return -1; }
	JFIF * ctxt;
	ctxt = (JFIF*)malloc(sizeof(JFIF));
	AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt;
		for(int temp_AFG_2 = 0; temp_AFG_2 < 16; temp_AFG_2++) {
		ctxt->phcac[temp_AFG_2] = (HUFCODEC*)malloc(sizeof(HUFCODEC));
		AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->phcac[temp_AFG_2];
			for (int temp_AFG_3 = 0; temp_AFG_3 < 256; temp_AFG_3++) {
				memcpy((void *)&ctxt->phcac[temp_AFG_2]->codelist[temp_AFG_3], AFG_Data+AFG_offset, sizeof(HUFCODEITEM));
				AFG_offset+=sizeof(HUFCODEITEM);
			}
			memcpy((void *)&ctxt->phcac[temp_AFG_2]->first, AFG_Data+AFG_offset, sizeof(int)*16);
			AFG_offset+=sizeof(int)*16;
			memcpy((void *)&ctxt->phcac[temp_AFG_2]->index, AFG_Data+AFG_offset, sizeof(int)*16);
			AFG_offset+=sizeof(int)*16;
			memcpy((void *)&ctxt->phcac[temp_AFG_2]->huftab, AFG_Data+AFG_offset, sizeof(unsigned char)*272);
			AFG_offset+=sizeof(unsigned char)*272;
			ctxt->phcac[temp_AFG_2]->input = (void *)malloc(pt_size);
			AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->phcac[temp_AFG_2]->input;
			memcpy((void *)ctxt->phcac[temp_AFG_2]->input, AFG_Data+AFG_offset, pt_size);
			AFG_offset+=pt_size;
			ctxt->phcac[temp_AFG_2]->output = (void *)malloc(pt_size);
			AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->phcac[temp_AFG_2]->output;
			memcpy((void *)ctxt->phcac[temp_AFG_2]->output, AFG_Data+AFG_offset, pt_size);
			AFG_offset+=pt_size;
		}
		for(int temp_AFG_2 = 0; temp_AFG_2 < 16; temp_AFG_2++) {
		ctxt->phcdc[temp_AFG_2] = (HUFCODEC*)malloc(sizeof(HUFCODEC));
		AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->phcdc[temp_AFG_2];
			for (int temp_AFG_3 = 0; temp_AFG_3 < 256; temp_AFG_3++) {
				memcpy((void *)&ctxt->phcdc[temp_AFG_2]->codelist[temp_AFG_3], AFG_Data+AFG_offset, sizeof(HUFCODEITEM));
				AFG_offset+=sizeof(HUFCODEITEM);
			}
			memcpy((void *)&ctxt->phcdc[temp_AFG_2]->first, AFG_Data+AFG_offset, sizeof(int)*16);
			AFG_offset+=sizeof(int)*16;
			memcpy((void *)&ctxt->phcdc[temp_AFG_2]->index, AFG_Data+AFG_offset, sizeof(int)*16);
			AFG_offset+=sizeof(int)*16;
			memcpy((void *)&ctxt->phcdc[temp_AFG_2]->huftab, AFG_Data+AFG_offset, sizeof(unsigned char)*272);
			AFG_offset+=sizeof(unsigned char)*272;
			ctxt->phcdc[temp_AFG_2]->input = (void *)malloc(pt_size);
			AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->phcdc[temp_AFG_2]->input;
			memcpy((void *)ctxt->phcdc[temp_AFG_2]->input, AFG_Data+AFG_offset, pt_size);
			AFG_offset+=pt_size;
			ctxt->phcdc[temp_AFG_2]->output = (void *)malloc(pt_size);
			AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->phcdc[temp_AFG_2]->output;
			memcpy((void *)ctxt->phcdc[temp_AFG_2]->output, AFG_Data+AFG_offset, pt_size);
			AFG_offset+=pt_size;
		}
		for(int temp_AFG_2 = 0; temp_AFG_2 < 16; temp_AFG_2++) {
			ctxt->pqtab[temp_AFG_2] = (int *)malloc(pt_size);
			AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->pqtab[temp_AFG_2];
			memcpy((void *)ctxt->pqtab[temp_AFG_2], AFG_Data+AFG_offset, pt_size);
			AFG_offset+=pt_size;
		}
		memcpy((void *)&ctxt->comp_num, AFG_Data+AFG_offset, sizeof(int));
		AFG_offset+=sizeof(int);
		memcpy((void *)&ctxt->datalen, AFG_Data+AFG_offset, sizeof(int));
		AFG_offset+=sizeof(int);
		memcpy((void *)&ctxt->height, AFG_Data+AFG_offset, sizeof(int));
		AFG_offset+=sizeof(int);
		memcpy((void *)&ctxt->width, AFG_Data+AFG_offset, sizeof(int));
		AFG_offset+=sizeof(int);
		for (int temp_AFG_2 = 0; temp_AFG_2 < 4; temp_AFG_2++) {
			memcpy((void *)&ctxt->comp_info[temp_AFG_2], AFG_Data+AFG_offset, sizeof(ctxt->comp_info)/4);
			AFG_offset+=sizeof(ctxt->comp_info)/4;
		}
		ctxt->databuf = (unsigned char *)malloc(pt_size+1);
		AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->databuf;
		memcpy((void *)ctxt->databuf, AFG_Data+AFG_offset, pt_size);
		memset((void *)(ctxt->databuf + pt_size), '\0', 1);
		AFG_offset+=pt_size;
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

	ctxt->comp_num =  ctxt->comp_num < 4 ? ctxt->comp_num : 4;
	AFG_offset = 0;
	for(int temp_AFG_2 = 0; temp_AFG_2 < 16; temp_AFG_2++) {
		ctxt->pqtab[temp_AFG_2] = (int *)malloc(64 * sizeof(int));
		AFG_alloc_list[AFG_alloc_cnt++] = (void*) ctxt->pqtab[temp_AFG_2];
		memcpy((void *)ctxt->pqtab[temp_AFG_2], AFG_Data+AFG_offset, 64 * sizeof(int));
		AFG_offset+=pt_size;
	}

	AFG_func(ctxt, pb);

AFG_fail:
	for(int AFG_free_i = 0; AFG_free_i < AFG_alloc_cnt; AFG_free_i++)
		free(AFG_alloc_list[AFG_free_i]);
	for(int AFG_free_i = 0; AFG_free_i < AFG_fopen_cnt; AFG_free_i++)
		fclose(AFG_fopen_list[AFG_free_i]);
	AFG_alloc_cnt = 0;
	AFG_fopen_cnt = 0;

	return 0;
}
