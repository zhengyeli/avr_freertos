#ifndef _LFS_CONFIG_H
#define _LFS_CONFIG_H
#include "lfs.h"

// variables used by the filesystem
lfs_t lfs;

// configuration of the filesystem is provided by this struct
struct lfs_config cfg;

int lfs_flash_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
int lfs_flash_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
int lfs_flash_erase(const struct lfs_config *cfg, lfs_block_t block);
int lfs_flash_sync(const struct lfs_config *cfg);


#endif  // _LFS_CONFIG_H