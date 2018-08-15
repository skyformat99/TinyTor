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
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <time.h>
#include "onion_router.c"
#include "consensus.h"

/**
 * Multidimensional array which contains a list of Guard, Middle and Exit relays.
 */
struct onion_router CONSENSUS_CACHE[3][MAX_CONSENSUS_SIZE];

FILE *create_file_stream(char *file_path) {
    return fopen(file_path, "r");
}

FILE *create_http_stream(char *url) {
    // TODO -
}

void consensus_init(FILE *stream) {
    char read_buffer[128];

    const char LINE_TYPE_ONION_ROUTER[3] = "r ";
    const char LINE_TYPE_FLAGS[3] = "s ";
    const char LINE_TYPE_VERSION[3] = "v ";
    const char LINE_TYPE_ACCEPTED_PORTS[3] = "p ";

    // Temporarily store the onion router's values until it's flags
    // are known and it's then added to the cache.
    char *nickname, *ip, *fingerprint;
    int clearnet_port, tor_port;

    int added_guard_relays = 0;
    int added_middle_relays = 0;
    int added_exit_relays = 0;

    while ((fgets(read_buffer, 128, stream)) != NULL) {

        // Check if the consensus cache is full.
        if (added_guard_relays == MAX_CONSENSUS_SIZE &&
            added_middle_relays == MAX_CONSENSUS_SIZE &&
            added_exit_relays == MAX_CONSENSUS_SIZE) {
            break;
        }

        if (strncmp(read_buffer, LINE_TYPE_ONION_ROUTER, 2) == 0) {
            /*
             * This line is the start of the onion router:
             * r Neldoreth ABUk3UA9cp8I9+XXeBPvEnVs+o0 tJYdOgQvW+HfiWR+2gmgU8Yu4to 2018-06-29 07:40:08 185.13.39.197 443 80
             */
            char *token;
            int token_index = 0;
            char *str = strdup(read_buffer);

            while ((token = strsep(&str, " "))) {
                if (token_index == 1) {
                    nickname = token;
                } else if (token_index == 6) {
                    ip = token;
                } else if (token_index == 7) {
                    clearnet_port = atoi(token);
                } else if (token_index == 8) {
                    tor_port = atoi(token);
                }

                token_index++;
            }
        } else if (strncmp(read_buffer, LINE_TYPE_FLAGS, 2) == 0) {
            /*
             * This line contains the router's flags:
             * s Fast Guard HSDir Running Stable V2Dir Valid
             */
            char *token;
            char *str = strdup(read_buffer);

            bool valid_guard_relay = false;
            bool valid_middle_relay = false;
            bool valid_exit_relay = false;

            while ((token = strsep(&str, " ")) != NULL) {
                if (strcmp(token, get_flag_name(FLAG_EXIT)) == 0) {
                    valid_exit_relay = true;
                }
                if (strcmp(token, get_flag_name(FLAG_GUARD)) == 0) {
                    valid_guard_relay = true;
                }
                if (strcmp(token, get_flag_name(FLAG_FAST)) == 0) {
                    valid_middle_relay = true;
                }
            }

            struct onion_router created_onion_router = {nickname, ip, clearnet_port, tor_port, fingerprint};

            if (valid_guard_relay && added_guard_relays <= MAX_CONSENSUS_SIZE) {
                CONSENSUS_CACHE[CONSENSUS_GUARD_INDEX][added_guard_relays] = created_onion_router;
                added_guard_relays++;
            } else if (valid_middle_relay && added_middle_relays <= MAX_CONSENSUS_SIZE) {
                CONSENSUS_CACHE[CONSENSUS_MIDDLE_INDEX][added_middle_relays] = created_onion_router;
                added_middle_relays++;
            } else if (valid_exit_relay && added_exit_relays <= MAX_CONSENSUS_SIZE) {
                CONSENSUS_CACHE[CONSENSUS_EXIT_INDEX][added_exit_relays] = created_onion_router;
                added_exit_relays++;
            }
        } else if (strncmp(read_buffer, LINE_TYPE_VERSION, 2) == 0) {
            /*
             * This line contains the running Tor version.
             * v Tor 0.3.3.7
             */
        } else if (strncmp(read_buffer, LINE_TYPE_ACCEPTED_PORTS, 2) == 0) {
            /*
             * This line contains all allowed exit ports:
             * p reject 1-65535
             * p accept 80-443
             */
        }
    }

    fclose(stream);

    puts("[DEBUG] Using guard relays: ");
    for (int i = 0; i <= 10; i++) {
        struct onion_router relay = CONSENSUS_CACHE[CONSENSUS_GUARD_INDEX][i];

        printf("- %s (%s)\n", relay.nickname, relay.ip);
    }
    puts("[DEBUG] Using middle relays: ");
    for (int i = 0; i <= 10; i++) {
        struct onion_router relay = CONSENSUS_CACHE[CONSENSUS_MIDDLE_INDEX][i];

        printf("- %s (%s)\n", relay.nickname, relay.ip);
    }
    puts("[DEBUG] Using exit relays: ");
    for (int i = 0; i <= 10; i++) {
        struct onion_router relay = CONSENSUS_CACHE[CONSENSUS_EXIT_INDEX][i];

        printf("- %s (%s)\n", relay.nickname, relay.ip);
    }
}

void consensus_free() {
    memset(CONSENSUS_CACHE, 0, sizeof(CONSENSUS_CACHE));
}

struct directory_authority get_random_directory_authority() {
    int directory_size = sizeof(DIRECTORY_AUTHORITIES) / sizeof(*DIRECTORY_AUTHORITIES);

    srand((unsigned int) time(NULL));
    return DIRECTORY_AUTHORITIES[rand() % directory_size];
}

char *_append_string(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // (!) Leave space for \0

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *get_consensus_url(struct directory_authority authority) {
    char *consensus_url = NULL;
    char authority_port[sizeof(authority.clearnet_port) * 4 + 1];

    sprintf(authority_port, "%d", authority.clearnet_port);

    consensus_url = append_string("http://", authority.ip);
    consensus_url = append_string(consensus_url, append_string(":", authority_port));
    consensus_url = append_string(consensus_url, "/tor/status-vote/current/consensus");
    return consensus_url;
}

struct onion_router get_random_onion_router(Flag relay_type) {
    srand((unsigned int) time(NULL));

    if (relay_type == FLAG_GUARD) {
        return CONSENSUS_CACHE[0][rand() % MAX_CONSENSUS_SIZE];
    } else if (relay_type == FLAG_FAST) {
        return CONSENSUS_CACHE[1][rand() % MAX_CONSENSUS_SIZE];
    } else if (relay_type == FLAG_EXIT) {
        return CONSENSUS_CACHE[2][rand() % MAX_CONSENSUS_SIZE];
    }
}