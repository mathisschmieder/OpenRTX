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

#ifndef LITTLEFS_H
#define LITTLEFS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Interface for LittleFS implementation.
 * This interface handles:
 * - Filesystem initialization
 * - File operations
 */

/**
 * This function handles LittleFS initialization.
 * Called at power-on
 * @return Error code: 0=success, -1 on error
 */
int lfs_init();

/**
 * This function handles LittleFS storage format.
 * @return Error code: 0=success, -1 on error
 */
int lfs_format();

/**
 * This function handles LittleFS de-initialization.
 * Called at power-down
 */
void lfs_terminate();

#ifdef __cplusplus
}
#endif

#endif /* LITTLEFS_H */
