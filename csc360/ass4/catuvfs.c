#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "disk.h"


int main(int argc, char *argv[]) {
    superblock_entry_t sb;
    int  i, ii;
    char *imagename = NULL;
    char *filename  = NULL;
    FILE *f;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--image") == 0 && i+1 < argc) {
            imagename = argv[i+1];
            i++;
        } else if (strcmp(argv[i], "--file") == 0 && i+1 < argc) {
            filename = argv[i+1];
            i++;
        }
    }

    if (imagename == NULL || filename == NULL) {
        fprintf(stderr, "usage: catuvfs --image <imagename> " \
            "--file <filename in image>");
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
	
	f = fopen(imagename, "r");

	fseek(f, sb.dir_start *sb.block_size, SEEK_SET);
	
	directory_entry_t dir_ent;
	int search = 0;
	int count = 0;
	do{ 
		fread(&dir_ent, 64, 1, f);
		if (strcmp(filename,dir_ent.filename) == 0){
			// found the file 
			search = 1;
		}
		count++;
	}while(count < (sb.dir_blocks *(sb.block_size / 64)) && search == 0);
    
	//if file not found 
	if (search == 0) {
		printf("file not found\n");
		exit(0);
	}else {
		// seek to front of dir
		fseek(f, htonl(dir_ent.start_block)*sb.block_size, SEEK_SET);
		int f_size = htonl(dir_ent.file_size);
		ii = 0;
		while(1) {
			
			printf("%c", fgetc(f));
			if(ii >= f_size) {
				break;
			}
			ii++;
		}
		
	}
	
	return 0; 
}
