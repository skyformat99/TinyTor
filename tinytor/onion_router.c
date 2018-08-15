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

#include <memory.h>
#include <malloc.h>
#include "onion_router.h"

char *get_flag_name(Flag flag) {
    char *flag_names[] = {"Authority", "BadExit", "Exit", "Fast", "Guard", "H2Dir",
                          "NoEdConsensus", "Stable", "Running", "Valid", "V2Dir"};

    return flag_names[flag];
}

char *append_string(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // (!) Leave space for \0

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *get_descriptor_url(struct onion_router router) {
    char *descriptor_url = NULL;
    char router_port[sizeof(router.clearnet_port) * 4 + 1];

    sprintf(router_port, "%d", router.clearnet_port);

    descriptor_url = append_string("http://", router.ip);
    descriptor_url = append_string(descriptor_url, append_string(":", router_port));
    descriptor_url = append_string(descriptor_url, "/tor/server/fp/");
    descriptor_url = append_string(descriptor_url, router.fingerprint);

    return descriptor_url;
}