/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef qd_router_core_event_types
#define qd_router_core_event_types 1

typedef struct qdrc_event_subscription_t qdrc_event_subscription_t;

#include "router_core_private.h"

#endif

#ifndef qd_router_core_events
#define qd_router_core_events 1

#include "qpid/dispatch/ctools.h"

typedef uint32_t qdrc_event_t;

/**
 * QDRC_EVENT_CONN_OPENED                A connection has opened
 * QDRC_EVENT_CONN_CLOSED                A connection has closed
 * QDRC_EVENT_CONN_EDGE_ESTABLISHED      An edge connection has been established
 * QDRC_EVENT_CONN_EDGE_LOST             An edge connection has been lost
 * QDRC_EVENT_CONN_IR_ESTABLISHED        An inter-router connection has been established
 * QDRC_EVENT_CONN_IR_LOST               An inter-router connection has been lost
 *
 * QDRC_EVENT_LINK_IN_ATTACHED           An inbound link has been attached
 * QDRC_EVENT_LINK_IN_DETACHED           An inbound link has been detached
 * QDRC_EVENT_LINK_OUT_ATTACHED          An outbound link has been attached
 * QDRC_EVENT_LINK_OUT_DETACHED          An outbound link has been detached
 * QDRC_EVENT_LINK_EDGE_OUTLINK          On an edge router, the outgoing message link(s) are attached
 *
 * QDRC_EVENT_ADDR_ADDED                 An address has been added
 * QDRC_EVENT_ADDR_REMOVED               An address has been removed
 * QDRC_EVENT_ADDR_BECAME_LOCAL_DEST     An address transitioned from zero to one local destination
 * QDRC_EVENT_ADDR_NO_LONGER_LOCAL_DEST  An address transitioned from one to zero local destinations
 * QDRC_EVENT_ADDR_BECAME_DEST           An address transitioned from zero to one destination
 * QDRC_EVENT_ADDR_NO_LONGER_DEST        An address transitioned from one to zero destinations
 * QDRC_EVENT_ADDR_ONE_LOCAL_DEST        An address transitioned from N destinations to one local dest
 * QDRC_EVENT_ADDR_TWO_DEST              An address transisioned from one local dest to two destinations
*/

#define QDRC_EVENT_CONN_OPENED               0x00000001
#define QDRC_EVENT_CONN_CLOSED               0x00000002
#define QDRC_EVENT_CONN_EDGE_ESTABLISHED     0x00000004
#define QDRC_EVENT_CONN_EDGE_LOST            0x00000008
#define QDRC_EVENT_CONN_IR_ESTABLISHED       0x00000010
#define QDRC_EVENT_CONN_IR_LOST              0x00000020
#define _QDRC_EVENT_CONN_RANGE               0x0000003F

#define QDRC_EVENT_LINK_IN_ATTACHED          0x00000100
#define QDRC_EVENT_LINK_IN_DETACHED          0x00000200
#define QDRC_EVENT_LINK_OUT_ATTACHED         0x00000400
#define QDRC_EVENT_LINK_OUT_DETACHED         0x00000800
#define QDRC_EVENT_LINK_EDGE_OUTLINK         0x00001000
#define _QDRC_EVENT_LINK_RANGE               0x00001F00

#define QDRC_EVENT_ADDR_ADDED                0x00010000
#define QDRC_EVENT_ADDR_REMOVED              0x00020000
#define QDRC_EVENT_ADDR_BECAME_LOCAL_DEST    0x00040000
#define QDRC_EVENT_ADDR_NO_LONGER_LOCAL_DEST 0x00080000
#define QDRC_EVENT_ADDR_BECAME_DEST          0x00100000
#define QDRC_EVENT_ADDR_NO_LONGER_DEST       0x00200000
#define QDRC_EVENT_ADDR_ONE_LOCAL_DEST       0x00400000
#define QDRC_EVENT_ADDR_TWO_DEST             0x00800000
#define _QDRC_EVENT_ADDR_RANGE               0x00FF0000


/**
 * Callbacks - Connection, Link, and Address event notifications
 *
 * @param context The opaque context provided in the mobile address binding
 * @param event_type The type of event being raised
 * @param conn/link/addr The object involved in the event
 */
typedef void (*qdrc_connection_event_t) (void             *context,
                                         qdrc_event_t      event_type,
                                         qdr_connection_t *conn);

typedef void (*qdrc_link_event_t) (void         *context,
                                   qdrc_event_t  event_type,
                                   qdr_link_t   *link);

typedef void (*qdrc_address_event_t) (void          *context,
                                      qdrc_event_t   event_type,
                                      qdr_address_t *addr);

/**
 * qdrc_event_subscribe_CT
 *
 * Subscribe to receive a set of event types for connections, links, or addresses.
 *
 * @param core Pointer to the router core object
 * @param events Logical OR of the set of events that the caller wishes to receive
 * @param on_conn_event Callback for connection events, must be non-null if there are connection events in 'events'
 * @param on_link_event Callback for link events, must be non-null if there are link events in 'events'
 * @param on_addr_event Callback for address events, must be non-null if there are address events in 'events'
 * @param context The opaque context that will be passed back with the raised events
 * @return Pointer to an object that tracks the subscription
 */
qdrc_event_subscription_t *qdrc_event_subscribe_CT(qdr_core_t             *core,
                                                   qdrc_event_t            events,
                                                   qdrc_connection_event_t on_conn_event,
                                                   qdrc_link_event_t       on_link_event,
                                                   qdrc_address_event_t    on_addr_event,
                                                   void                   *context);

/**
 * qdrc_event_unsubscribe_CT
 *
 * Cancel an active subscription
 *
 * @param core Pointer to the router core object
 * @param sub Pointer to the subscription returned by the subscribe function
 */
void qdrc_event_unsubscribe_CT(qdr_core_t *core, qdrc_event_subscription_t *sub);


//=====================================================================================
// Private functions, not part of the API
//=====================================================================================

DEQ_DECLARE(qdrc_event_subscription_t, qdrc_event_subscription_list_t);

void qdrc_event_conn_raise(qdr_core_t *core, qdrc_event_t event, qdr_connection_t *conn);
void qdrc_event_link_raise(qdr_core_t *core, qdrc_event_t event, qdr_link_t *link);
void qdrc_event_addr_raise(qdr_core_t *core, qdrc_event_t event, qdr_address_t *addr);

#endif
