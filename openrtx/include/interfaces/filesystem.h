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

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>
#include <stdbool.h>
#include <lfs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Interface for filesystem implementation.
 * This interface handles:
 * - Filesystem initialization
 * - Filesystem format
 * - File operations
 * - Filesystem de-initialization
 */

/**
 * This function handles filesystem initialization.
 * To be called at power-on.
 *
 * @return Error code: 0 on success, -1 on error
 */
int filesystem_init();

/**
 * This function handles filesystem format.
 *
 * @return Error code: 0 on success, -1 on error
 */
int filesystem_format();

/**
 * This function handles filesystem de-initialization.
 * To be called at power-down.
 */
void filesystem_terminate();

/**
 * Return an handle to the filesystem data structure.
 *
 * @return a pointer to the filesystem data structure or NULL if filesystem is
 * not initialised.
 */
lfs_t *filesystem_getHandle();

#ifdef __cplusplus
}
#endif

#endif /* FILESYSTEM_H */
