/*******************************************************************************
 * Project: file system parsing - header
 * Date: 16/01/2023
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* #include <ext2fs/ext2_fs.h>  */
/******************************************************************************/
#include "ext2_fs.h"
/******************************************************************************/
#define BASE_OFFSET 1024
#define FD_DEVICE "/dev/ram0"

#define BLOCK_OFFSET(block) (BASE_OFFSET + (block - 1) * block_size)
/******************************************************************************/
void PrintFileSysContent(const char *file_path);
static void PrintSuperBlock(const char *file_path);
static void PrintGroupDescriptor(const char *file_path);

/******************************************************************************/
static unsigned int block_size = 0; 
/******************************************************************************/
int main()
{
    PrintFileSysContent(FD_DEVICE);
	
    return 0;
}
/******************************************************************************/
void PrintFileSysContent(const char *file_path)
{	
	printf("SuperBlock results:\n\n");
    PrintSuperBlock(file_path);
	printf("\n\nGroupDescriptor results:\n\n");
	PrintGroupDescriptor(file_path);
	
}
/******************************************************************************/
static void PrintSuperBlock(const char *file_path)
{
    struct ext2_super_block super;
	int fd;

	/* open floppy device */

	if ((fd = open(FD_DEVICE, O_RDONLY)) < 0) 
    {
		perror(FD_DEVICE);
		exit(1);  /* error while opening the floppy device */
	}

	/* read super-block */
	lseek(fd, BASE_OFFSET, SEEK_SET); 
	read(fd, &super, sizeof(super));
	close(fd);

	if (super.s_magic != EXT2_SUPER_MAGIC) 
    {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}
		
	block_size = 1024 << super.s_log_block_size;

	printf("Reading super-block from device " FD_DEVICE ":\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n"
	       ,
	       super.s_inodes_count,  
	       super.s_blocks_count,
	       super.s_r_blocks_count,     /* reserved blocks count */
	       super.s_free_blocks_count,
	       super.s_free_inodes_count,
	       super.s_first_data_block,
	       block_size,
	       super.s_blocks_per_group,
	       super.s_inodes_per_group,
	       super.s_creator_os,
	       super.s_first_ino,          /* first non-reserved inode */
	       super.s_inode_size);
}
/******************************************************************************/
static void PrintGroupDescriptor(const char *file_path)
{
	struct ext2_super_block super;
	struct ext2_group_desc group;
	int fd;

	/* open floppy device */

	if ((fd = open(FD_DEVICE, O_RDONLY)) < 0) {
		perror(FD_DEVICE);
		exit(1);  /* error while opening the floppy device */
	}

	/* read super-block */

	lseek(fd, BASE_OFFSET, SEEK_SET); 
	read(fd, &super, sizeof(super));

	if (super.s_magic != EXT2_SUPER_MAGIC) {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}
		
	block_size = 1024 << super.s_log_block_size;

	/* read group descriptor */

	lseek(fd, BASE_OFFSET + block_size, SEEK_SET);
	read(fd, &group, sizeof(group));
	close(fd);

	printf("Reading first group-descriptor from device " FD_DEVICE ":\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
	       group.bg_block_bitmap,
	       group.bg_inode_bitmap,
	       group.bg_inode_table,
	       group.bg_free_blocks_count,
	       group.bg_free_inodes_count,
	       group.bg_used_dirs_count);    /* directories count */
}
/******************************************************************************/
