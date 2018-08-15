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

#ifndef TINYTOR_CELL_H
#define TINYTOR_CELL_H

/**
 * Enum class which contains all reasons a cell can be destroyed.
 *
 * @see tor-spec 5.4. "Tearing down circuits"
 */
typedef enum cell_destroyed_reason {
    NONE,
    PROTOCOL,
    INTERNAL,
    REQUESTED,
    HIBERNATING,
    RESOURCE_LIMIT,
    CONNECTION_FAILED,
    ONION_ROUTER_IDENTITY,
    ONION_ROUTER_CONNECTION_CLOSED,
    FINISHED,
    TIMEOUT,
    DESTROYED,
    NO_SUCH_SERVICE
};

/**
 * Enum class which contains all available cell commands.
 */
typedef enum cell_command {
    //
    // Fixed-length command values
    //

    /**
     * PADDING cells are currently used to implement connection keepalive. <br/>
     * If there is no other traffic, ORs and OPs send one another a PADDING cell every few minutes.
     */
    PADDING = 0,
    CREATE = 1,
    CREATED = 2,
    RELAY = 3,
    DESTROY = 4,
    /**
     * When initializing the first hop of a circuit, the OP has already
     * established the OR's identity and negotiated a secret key using TLS. <br/>
     * Because of this, it is not always necessary for the OP to perform the
     * public key operations to create a circuit.
     *
     * In this case, the OP MAY send a CREATE_FAST cell instead of a CREATE cell for the first hop only. <br/>
     * The OR responds with a CREATED_FAST cell, and the circuit is created.
     */
    CREATE_FAST = 5,
    CREATED_FAST = 6,
    NETINFO = 8,
    RELAY_EARLY = 9,
    CREATE2 = 10,
    CREATED2 = 11,

    //
    // Variable-length command values.
    //

    VERSIONS = 7,
    VPADDING = 128,
    CERTS = 129,
    AUTH_CHALLENGE = 130,
    AUTHENTICATE = 131,

    //
    // The relay commands.
    // See tor-spec 6.1. "Relay cells"
    //
    // Within a circuit, the OP and the exit node use the contents of
    // RELAY packets to tunnel end-to-end commands and TCP connections
    // ("Streams") across circuits. End-to-end commands can be initiated
    // by either edge; streams are initiated by the OP.
    //

    RELAY_BEGIN = 1,
    RELAY_DATA = 2,
    RELAY_END = 3,
    RELAY_CONNECTED = 4,
    RELAY_SENDME = 5,
    RELAY_EXTEND = 6,
    RELAY_EXTENDED = 7,
    RELAY_TRUNCATE = 8,
    RELAY_TRUNCATED = 9,
    RELAY_DROP = 10,
    RELAY_RESOLVE = 11,
    RELAY_RESOLVED = 12,
    RELAY_BEGIN_DIR = 13,
    RELAY_EXTEND2 = 14,
    RELAY_EXTENDED2 = 15
};


/**
 * Represents a cell.
 *
 * @see tor-spec 3. "Cell Packet format"
 */
typedef struct cell {

    /**
     * Determines which circuit, if any, the cell is associated with.
     */
    char circuit_id[2];
    enum cell_command command;
};

#endif //TINYTOR_CELL_H
