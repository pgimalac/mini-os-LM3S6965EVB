#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "inode.h"

#define RAM2_MIN_ADDR 0xF0000000
#define RAM2_MAX_ADDR 0xF0A00000

#define MAX_FILE_NUMBER 2048
#define BLOCK_NUM 16384

// use real variables instead of define for gdb

extern inode_t *ilist;
extern uint8_t *blocks;
extern uint8_t *bitset_blocks;

void fs_init();
void restaure_fs_from_disk();
void fs_clear();
int fs_get_inode(char *name);

int fs_create(char *name);
uint32_t fs_append(int inode, char *txt, uint32_t size);
uint32_t fs_truncate(int inode, uint32_t size);
uint32_t fs_write(int inode, uint32_t off, char *buffer, uint32_t size);

uint32_t fs_read(int inode, uint32_t off, char *buffer, uint32_t size);

void fs_remove(int inode);
void fs_move(int inode, char *name);
int fs_copy(int inode, char *name);

// at the start give a ptr to a file_view with num_inode = -1
// returns NULL at the end
file_view *fs_iter(file_view *f);
file_view *fs_get_view(int inode, file_view *f);

#endif
