#include "filesystem.h"

#include <string.h>

void fs_init() {
    for (int i = 0; i < MAX_FILE_NUMBER; i++) {
        ilist[i].inode_num = i;
    }

    restaure_fs_from_disk();
}

int fs_get_inode(char *name) {
    for (uint32_t i = 0; i < MAX_FILE_NUMBER; i++) {
        if (ilist[i].inode_num & FS_INODE_USED &&
            strcmp(ilist[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

int find_block() {
    for (int i = 0; i < BLOCK_NUM; i++) {
        if (!(bitset_blocks[i / 8] & (1 << (i % 8)))) {
            bitset_blocks[i / 8] |= (1 << (i % 8));
            return i;
        }
    }

    return -1;
}

void free_block(int num) {
    bitset_blocks[num / 8] &= ~(1 << (num % 8));
}

void fs_clear() {
    for (int i = 0; i < MAX_FILE_NUMBER; i++) {
        ilist[i].inode_num &= ~FS_INODE_USED;
    }

    memset(bitset_blocks, 0, BLOCK_NUM / 8);
}

int fs_create(char *name) {
    for (int i = 0; i < MAX_FILE_NUMBER; i++) {
        if (ilist[i].inode_num & FS_INODE_USED) {
            continue;
        }

        strcpy(ilist[i].name, name);
        ilist[i].inode_num |= FS_INODE_USED;
        ilist[i].size = 0;
        ilist[i].block_num = 0;

        return i;
    }

    return -1;
}

uint32_t fs_append(int inode, char *txt, uint32_t size) {
    inode_t *f = &ilist[inode];
    while (f->block_num <= FS_INODE_MAX_BLOCK && f->block_num * BLOCK_SIZE < f->size + size) {
        int bl = find_block();
        if (bl == -1)
            break;

        f->addrs[f->block_num] = bl;
        f->block_num++;
    }

    if (f->size + size > f->block_num * BLOCK_SIZE) {
        size = f->block_num * BLOCK_SIZE - f->size;
    }

    int current_block = (f->size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    uint32_t diff = current_block * BLOCK_SIZE - f->size;
    if (diff > size) {
        diff = size;
    }

    memcpy(&blocks[f->addrs[current_block]], txt, diff);
    f->size += diff;
    size -= diff;
    txt += diff;
    current_block++;

    while (size != 0) {
        diff = size < BLOCK_SIZE ? size : BLOCK_SIZE;

        memcpy(&blocks[f->addrs[current_block]], txt, diff);
        f->size += diff;
        txt += diff;
        size -= diff;
        current_block++;

    }

    return f->size;
}

uint32_t fs_truncate(int inode, uint32_t size) {
    inode_t *f = &ilist[inode];

    if (size < f->size) {
        f->size = size;
    }

    return f->size;
}

void fs_remove(int inode) {
    inode_t *f = &ilist[inode];
    for (uint32_t i = 0; i < f->block_num; i++) {
        free_block(f->addrs[i]);
    }

    f->inode_num &= ~FS_INODE_USED;
}

void fs_move(int inode, char *name) {
    inode_t *f = &ilist[inode];
    strcpy(f->name, name);
}

int fs_copy(int inode, char *name) {
    inode_t *f = &ilist[inode];
    int new = fs_create(name);
    if (new == -1) {
        return -1;
    }

    uint32_t block_num = (f->size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (uint32_t i = 0; i < block_num; i++) {
        fs_append(new, (char *)&blocks[f->addrs[i]], BLOCK_SIZE);
    }

    return new;
}

uint32_t fs_read(int inode, uint32_t off, char *buffer, uint32_t size) {
    inode_t *f = &ilist[inode];

    if (off >= f->size) {
        return 0;
    }

    if (f->size > off + size) {
        size = f->size - off;
    }

    for (uint32_t i = off; i < off + size; i++) {
        buffer[0] = (&blocks[f->addrs[i / BLOCK_SIZE]])[i % BLOCK_SIZE];
        buffer++;
    }

    return size;
}

file_view * fs_iter(file_view *f) {
    uint32_t inode = f->inode_num & ~FS_INODE_USED;
    inode++;

    while (inode < MAX_FILE_NUMBER && !(ilist[inode].inode_num & FS_INODE_USED)) {
        inode++;
    }

    if (inode >= MAX_FILE_NUMBER) {
        return NULL;
    }

    memcpy(f, &ilist[inode], sizeof(file_view));
    f->inode_num &= ~FS_INODE_USED;

    return f;
}

void restaure_fs_from_disk() {
    fs_clear();

    // write calls to functions above to generate the "initial" disk state
    uint32_t doc      = fs_create("doc");
    fs_append(doc, "some text", 13);

    uint32_t img      = fs_create("img");
    fs_append(img, "this is a very nice image", 25);

    uint32_t music    = fs_create("music");
    fs_copy(music, "music2");

    uint32_t dev      = fs_create("dev");
    fs_append(dev, "the dev repository contains peripherics", 39);
    fs_append(dev, "such as tty0, stdout or usb", 27);

    uint32_t tmp      = fs_create("tmp");
    fs_append(tmp, "a lot of text just to fill the file", 35);
    fs_truncate(tmp, 5);

    uint32_t download = fs_create("download");
    fs_move(download, "dl");

    //done
    return;
}
