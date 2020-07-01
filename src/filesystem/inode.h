#ifndef INODE_H
#define INODE_H

#include <stdint.h>

#define BLOCK_SIZE 512

#define FS_INODE_USED (1 << 31)
#define FS_FILE_NAME_LENGTH 12
#define FS_INODE_MAX_BLOCK 10

typedef struct {
    char name[FS_FILE_NAME_LENGTH]; // little cheating
    uint32_t inode_num;
    uint32_t size;
    uint32_t block_num;
    uint32_t addrs[FS_INODE_MAX_BLOCK];
} inode_t;

typedef struct {
    char name[FS_FILE_NAME_LENGTH];
    uint32_t inode_num;
    uint32_t size;
    uint32_t block_num;
} file_view;

#endif
