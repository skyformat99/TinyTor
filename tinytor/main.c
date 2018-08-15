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

#include <stdio.h>
#include "version.c"
#include "consensus.c"

int main() {
    printf("[INFO] Starting TinyTor v%s...\n", get_version());

    struct directory_authority random_authority = get_random_directory_authority();
    char *consensus_url = get_consensus_url(random_authority);

    printf("[DEBUG] Using directory authority \"%s\"...\n", random_authority.nickname);
    printf("[DEBUG] Retrieving the consensus from: %s\n", consensus_url);

    consensus_init(create_file_stream("/tmp/consensus"));

    struct onion_router random_guard_relay = get_random_onion_router(FLAG_GUARD);
    struct onion_router random_middle_relay = get_random_onion_router(FLAG_FAST);
    struct onion_router random_exit_relay = get_random_onion_router(FLAG_EXIT);

    printf("[DEBUG] Creating a circuit...\n");
    printf("[DEBUG] Using random guard relay: %s\n", random_guard_relay.nickname);
    printf("[DEBUG] Using random middle relay: %s\n", random_middle_relay.nickname);
    printf("[DEBUG] Using random exit relay: %s\n", random_exit_relay.nickname);

    consensus_free();
    return 0;
}