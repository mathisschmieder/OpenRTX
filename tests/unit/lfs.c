#include "lfs.h"
#include "bd/lfs_testbd.h"
#include <stdio.h>
extern const char *lfs_testbd_path;
uint32_t lfs_testbd_cycles = 0;

#define LFS_READ_SIZE 16
#define LFS_PROG_SIZE LFS_READ_SIZE
#define LFS_BLOCK_SIZE 512
#define LFS_BLOCK_COUNT 1024
#define LFS_BLOCK_CYCLES -1
#define LFS_CACHE_SIZE (64 % LFS_PROG_SIZE == 0 ? 64 : LFS_PROG_SIZE)
#define LFS_LOOKAHEAD_SIZE 16
#define LFS_ERASE_VALUE 0xff
#define LFS_ERASE_CYCLES 0
#define LFS_BADBLOCK_BEHAVIOR LFS_TESTBD_BADBLOCK_PROGERROR

// Variables used by the filesystem
lfs_t lfs;
lfs_file_t file;

// Entry point
int main(void) {

    // Configure LittleFS to use file backend
    __attribute__((unused)) lfs_t lfs;
    __attribute__((unused)) lfs_testbd_t bd;
    __attribute__((unused)) lfs_file_t file;
    __attribute__((unused)) lfs_dir_t dir;
    __attribute__((unused)) struct lfs_info info;
    __attribute__((unused)) char path[1024];
    __attribute__((unused)) uint8_t buffer[1024];
    __attribute__((unused)) lfs_size_t size;
    __attribute__((unused)) int err;

    __attribute__((unused)) const struct lfs_config cfg = {
        .context        = &bd,
        .read           = lfs_testbd_read,
        .prog           = lfs_testbd_prog,
        .erase          = lfs_testbd_erase,
        .sync           = lfs_testbd_sync,
        .read_size      = LFS_READ_SIZE,
        .prog_size      = LFS_PROG_SIZE,
        .block_size     = LFS_BLOCK_SIZE,
        .block_count    = LFS_BLOCK_COUNT,
        .block_cycles   = LFS_BLOCK_CYCLES,
        .cache_size     = LFS_CACHE_SIZE,
        .lookahead_size = LFS_LOOKAHEAD_SIZE,
    };

    __attribute__((unused)) const struct lfs_testbd_config bdcfg = {
        .erase_value        = LFS_ERASE_VALUE,
        .erase_cycles       = LFS_ERASE_CYCLES,
        .badblock_behavior  = LFS_BADBLOCK_BEHAVIOR,
        .power_cycles       = lfs_testbd_cycles,
    };

    lfs_testbd_createcfg(&cfg, "./lfs_test.bin", &bdcfg);

    // Mount the filesystem
    err = lfs_mount(&lfs, &cfg);

    // Reformat if we can't mount the filesystem
    // This should only happen on the first boot
    if (err) {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    // Read current count
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    // Update boot count
    boot_count += 1;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // Read back count
    uint32_t new_count = 0;
    lfs_file_rewind(&lfs, &file);
    lfs_file_read(&lfs, &file, &new_count, sizeof(new_count));
    if (new_count != boot_count) {
        printf("Failed LittleFS read modify write test!");
        return -1;
    }

    // Remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // Release any resources we were using
    lfs_unmount(&lfs);

    // Print the boot count
    printf("boot_count: %d\n", boot_count);

    printf("PASS!\n");
    return 0;
}
