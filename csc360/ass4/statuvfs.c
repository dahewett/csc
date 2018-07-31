#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "disk.h"

int main(int argc, char *argv[]) {
    superblock_entry_t sb;
    int  i;
    char *imagename = NULL;
    FILE  *f;
    int   fat_data;
	
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--image") == 0 && i+1 < argc) {
            imagename = argv[i+1];
            i++;
        }
    }

    if (imagename == NULL)
    {
        fprintf(stderr, "usage: statuvfs --image <imagename>\n");
        exit(1);
    }
	// open and read the file disk
	// read first 30 bytes
	f = fopen(imagename, "r");
	fread(&sb, sizeof(sb), 1, f);
	fclose(f);
	
	// Reference: Csc 360 A4 Appendix.pdf 
	// using apre/inet.h set all the variables in the superblock_entry_t struct
	sb.block_size = htons(sb.block_size);
	sb.num_blocks = htonl(sb.num_blocks);
	sb.fat_start = htonl(sb.fat_start);
	sb.fat_blocks = htonl(sb.fat_blocks);
	sb.dir_start = htonl(sb.dir_start);
	sb.dir_blocks = htonl(sb.dir_blocks);
	
	//print title
	printf("  %s (%s)\n", sb.magic, &imagename[7]);
	//print the stats read from the disk image
	printf("\n-------------------------------------------------\n");
	printf("  Bsz   Bcnt  FATst FATcnt  DIRst DIRcnt\n");
	printf("%5d%7d%7d%7d%7d%7d\n", sb.block_size,sb.num_blocks, sb.fat_start, sb.fat_blocks, sb.dir_start, sb.dir_blocks);
    
	f = fopen(imagename, "r");

	int count =0;
	int c = 0;
	// 
	int resv = 0;
	int alloc = 0;
	int freee = 0;
	do{
		// increment till superblock
		if (count < sb.block_size) {
			c = fgetc(f);
			count++;
		}
		if(count >= sb.block_size)
		{
			
			// convert 4 byte hex to decimals
			
			for ( i = 0; i < 4; i++){
				c = fgetc(f);

				if(i == 0) {
					fat_data = c * 16*16*16;
				} else if (i == 1){
					fat_data += (c *16*16);
				} else if (i == 2) {
					fat_data += (c*16);
				} else if (i == 3) {
					fat_data += c;
				}
				count++;
			}
			// check what each block is an incr count for it
			if (fat_data == FAT_RESERVED){
				resv++;
			}else if (fat_data == FAT_AVAILABLE){
				freee++;
			} else if (fat_data != FAT_LASTBLOCK ){
				
				alloc++;
			}
		}
		// end when the number of blocks looked at
		if(count >= sb.block_size + (sb.num_blocks*4)){//sb.block_size*sb.fat_blocks + sb.block_size){
				
			break;
		}

	}while(c != EOF);
	fclose(f);

	printf("\n-------------------------------------------------\n");
	printf(" Free   Resv  Alloc\n");
	printf("%5d%7d%7d\n", freee, resv, alloc);
	
	return 0; 
	
	
}