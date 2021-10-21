#include "lfs.h"
#include "lfs_config.h"
#include <AVRdef.h>
#include "app.h"

#define ADDRESS 0x001D1000


int lfs_flash_init()
{
    cfg.read = lfs_flash_read;
    cfg.prog = lfs_flash_prog;
    cfg.erase = lfs_flash_erase;
    cfg.sync = lfs_flash_sync;

    /* 最小的读取单元大小 */
    cfg.read_size = 64;

    /* 最小的写入数据单元大小，也是数据metadata pair中tag的对齐尺寸 */
    cfg.prog_size = 64;

    /* 最小的擦除单元大小。可以比flash的实际block尺寸大。但是对于ctz类型的文件，
       block size是最小的分配单元。同时block size必须是read size和program size的倍数，
       block size会存储在superblock中 */
    cfg.block_size = 0x1000;

    /* 属于文件系统的block数量，block count会存储在superblock中 */
    cfg.block_count = 128;

    /* 文件系统进行垃圾回收时的block的擦除次数，推荐取值100-1000.值越大垃圾回收的次数越少，性能越好 */
    cfg.block_cycles = 500;

    /* littlefs需要一个read cache，一个program cache，每个文件也需要一个cache。cache越大性能越好，会减少会flash的访问次数，
    cache必须是block的read size和program size的倍数，同时是block size的因数 */
    cfg.cache_size = 1024;

    /* lookahead buffer的尺寸。lookahead buffer主要是block alloctor在分配块的时候用到。lookahead size必须是8的倍数，
    因为它是采用bitmap的形式存储的 */
    cfg.lookahead_size = 64;

    return 0;
}

int lfs_flash_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
    //HAL_Flash_ReadData_Test(ADDRESS + block * cfg->block_size + off,(unsigned char*) buffer, size);
    EEPROMreadString(ADDRESS + block * cfg->block_size + off, (unsigned char*) buffer, size);
    return 0;
}

int lfs_flash_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
    //HAL_Flash_WriteData_Test(ADDRESS + block * cfg->block_size + off,(unsigned char*) buffer, size);
    EEPROMwriteString(ADDRESS + block * cfg->block_size + off,(unsigned char*) buffer, size);
    return 0;
}

int lfs_flash_erase(const struct lfs_config *cfg, lfs_block_t block)
{
    //HAL_Flash_EraseData_Test(ADDRESS + block * cfg->block_size);
    return 0;
}

int lfs_flash_sync(const struct lfs_config *cfg)
{
    //HAL_Printf("[%s] flash_addr: 0x, len: \n", __FUNCTION__);
    return 0;
}

void Govee_littleFs_init(void)
{
    // 初始化参数
    lfs_flash_init();

    // mount the filesystem
    int err = lfs_mount(&lfs, &cfg);

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }


// 例子
/*     // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "s_user_config", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &s_user_config, sizeof(boot_count));
    // update boot count
    boot_count += 1;

    HAL_SleepMs(1000);
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count); */

}

