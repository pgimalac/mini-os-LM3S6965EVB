#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "inode.h"

#define RAM2_MIN_ADDR 0xF0000000
#define RAM2_MAX_ADDR 0xF0A00000

#define MAX_FILE_NUMBER 2048
#define BLOCK_NUM 16384

#define ilist ((inode_t *)RAM2_MIN_ADDR)
#define blocks ((uint8_t *)(RAM2_MAX_ADDR - BLOCK_NUM * BLOCK_SIZE))
#define bitset_blocks ((uint8_t *)(blocks - BLOCK_NUM / 8))

void fs_init();
void restaure_fs_from_disk();
void fs_clear();

int fs_create(char *name);
uint32_t fs_append(int inode, char *txt, uint32_t size);
uint32_t fs_truncate(int inode, uint32_t size);

uint32_t fs_read(int inode, uint32_t off, char *buffer, uint32_t size);

void fs_remove(int inode);
void fs_move(int inode, char *name);
int fs_copy(int inode, char *name);

file_view * fs_iter(file_view *f);
#endif
