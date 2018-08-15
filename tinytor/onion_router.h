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

#ifndef TINYTOR_ONION_ROUTER_H
#define TINYTOR_ONION_ROUTER_H

/**
 * Represents an onion router.
 */
struct onion_router {
    char *nickname;
    char *ip;
    int clearnet_port;
    int tor_port;
    char *fingerprint;
    char *ntor_key;
};

/**
 * Enum class of all flags an onion router can have.
 */
typedef enum {
    FLAG_AUTHORITY,
    FLAG_BADEXIT,
    FLAG_EXIT,
    FLAG_FAST,
    FLAG_GUARD,
    FLAG_H2DIR,
    FLAG_NOEDCONSENSUS,
    FLAG_STABLE,
    FLAG_RUNNING,
    FLAG_VALID,
    FLAG_V2DIR
} Flag;

/**
 * @return The name of the given flag enum.
 */
char *get_flag_name(Flag flag);

/**
 * Format: http://AUTHORITY_IP:PORT/tor/server/fp/ONION_FINGERPRINT
 *
 * @return The URL to the descriptor which holds all of the onion router's keys.
 */
char *get_descriptor_url(struct onion_router);

#endif //TINYTOR_ONION_ROUTER_H
