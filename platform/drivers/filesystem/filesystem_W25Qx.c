/***************************************************************************
 *   Copyright (C) 2022 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
 *                         Frederik Saraci IU2NRO                          *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include <interfaces/filesystem.h>
#include <hwconfig.h>
#include <W25Qx.h>

// Filesystem used: LittleFS

// Flash chip physical features
#ifdef FLASH_W25Q128FV
#define LFS_READ_SIZE 1
#define LFS_PROG_SIZE LFS_READ_SIZE
#define LFS_BLOCK_SIZE 4096
#define LFS_BLOCK_COUNT 4096
#define LFS_BLOCK_CYCLES 500
#define LFS_CACHE_SIZE (16 % LFS_PROG_SIZE == 0 ? 16 : LFS_PROG_SIZE)
#define LFS_LOOKAHEAD_SIZE 16
#endif

// variables used by the filesystem
static lfs_t lfs;

// block device API
static int lfs_W25Qx_read(const struct lfs_config *cfg, lfs_block_t block,
                          lfs_off_t off, void *buffer, lfs_size_t size);
static int lfs_W25Qx_prog(const struct lfs_config *cfg, lfs_block_t block,
                          lfs_off_t off, const void *buffer, lfs_size_t size);
static int lfs_W25Qx_erase(const struct lfs_config *cfg, lfs_block_t block);
static int lfs_W25Qx_sync(const struct lfs_config *cfg);

// Filesystem configuration data
const struct lfs_config cfg =
{
    // block device operations
    .read  = lfs_W25Qx_read,
    .prog  = lfs_W25Qx_prog,
    .erase = lfs_W25Qx_erase,
    .sync  = lfs_W25Qx_sync,

    // block device configuration
    .read_size      = LFS_READ_SIZE,
    .prog_size      = LFS_PROG_SIZE,
    .block_size     = LFS_BLOCK_SIZE,
    .block_count    = LFS_BLOCK_COUNT,
    .block_cycles   = LFS_BLOCK_CYCLES,
    .cache_size     = LFS_CACHE_SIZE,
    .lookahead_size = LFS_LOOKAHEAD_SIZE,
};

int filesystem_init()
{
    W25Qx_init();

    return lfs_mount(&lfs, &cfg);
}

int filesystem_format()
{
    return lfs_format(&lfs, &cfg);
}

void filesystem_terminate()
{
    lfs_unmount(&lfs);
}


/// Implementation of block device API ///
int lfs_W25Qx_read(const struct lfs_config *cfg, lfs_block_t block,
                   lfs_off_t off, void *buffer, lfs_size_t size)
{
    // check if data is valid
    LFS_ASSERT(off  % cfg->read_size == 0);
    LFS_ASSERT(size % cfg->read_size == 0);
    LFS_ASSERT(block < cfg->block_count);

    // read
    uint32_t addr = (block * cfg->block_size) + off;
    W25Qx_wakeup();
    W25Qx_readData(addr, buffer, size);

    return 0;
}

int lfs_W25Qx_prog(const struct lfs_config *cfg, lfs_block_t block,
                   lfs_off_t off, const void *buffer, lfs_size_t size)
{

    // check if data is valid
    LFS_ASSERT(off  % cfg->prog_size == 0);
    LFS_ASSERT(size % cfg->prog_size == 0);
    LFS_ASSERT(block < cfg->block_count);

    // prog
    uint32_t addr = (block * cfg->block_size) + off;
    W25Qx_wakeup();
    W25Qx_writePage(addr, buffer, size);

    return 0;
}

int lfs_W25Qx_erase(const struct lfs_config *cfg, lfs_block_t block)
{
    // check if data is valid
    LFS_ASSERT(block < cfg->block_count);

    // erase
    uint32_t addr = (block * cfg->block_size);
    W25Qx_wakeup();
    bool success = W25Qx_eraseSector(addr);

    return success ? 0 : 1;
}

int lfs_W25Qx_sync(const struct lfs_config *cfg)
{
    // W25Qx does not have a cache, thus it does not need syncing
    (void) cfg;
    return 0;
}
