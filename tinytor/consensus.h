/*
 * This file is part of TinyTor.
 * Copyright (C) 2018  Marten4n6
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TINYTOR_CONSENSUS_H
#define TINYTOR_CONSENSUS_H

#include <bits/types/FILE.h>
#include "onion_router.h"

/**
 * Represents a directory authority.
 */
struct directory_authority {
    char *nickname;
    char *ip;
    unsigned int clearnet_port;
    unsigned int tor_port;
};

/**
 * Array of all directory authorities.
 *
 * Taken from: https://consensus-health.torproject.org/
 */
static struct directory_authority DIRECTORY_AUTHORITIES[9] = {
        {"maatuska",   "171.25.193.9",    443,  80},
        {"tor26",      "86.59.21.38",     80,   443},
        {"longclaw",   "199.58.81.140",   80,   443},
        {"dizum",      "194.109.206.212", 80,   443},
        {"bastet",     "204.13.164.118",  80,   443},
        {"gabelmoo",   "131.188.40.189",  80,   443},
        {"moria1",     "128.31.0.34",     9131, 9101},
        {"dannenberg", "193.23.244.244",  80,   443},
        {"faravahar",  "154.35.175.225",  80,   443}
};

/**
 * The maximum amount of each list of Guard, Middle and Exit relays stored in the cache.
 */
#define MAX_CONSENSUS_SIZE 10

#define CONSENSUS_GUARD_INDEX  0
#define CONSENSUS_MIDDLE_INDEX 1
#define CONSENSUS_EXIT_INDEX   2

/**
 * Initializes the consensus cache.
 *
 * @param stream The HTTP or file stream to retrieve the consensus from.
 */
void consensus_init(FILE *stream);

/**
 * Cleans up any memory allocated by the consensus.
 */
void consensus_free();

/**
 * @return A random directory authority.
 */
struct directory_authority get_random_directory_authority();

/**
 * @return The URL to the consensus of the given directory authority.
 */
char *get_consensus_url(struct directory_authority authority);

/**
 * @return A random onion router.
 * @param relay_type Flag which can be FLAG_GUARD, FLAG_FAST or FLAG_EXIT.
 */
struct onion_router get_random_onion_router(Flag flag);

#endif //TINYTOR_CONSENSUS_H
