/**************************************************************************\
 * 
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the profit library.
 *
 *  This library (profit) is free software and comes without any warranty.
 *  You can redistribute it and / or modify it under the terms of the
 *  GNU General Public License, version 2, as published by the
 *  Free Software Foundation (see file named COPYING for details).
 *
 *  If you want to use profit in applications not covered by licenses
 *  compatible with the GNU GPL, you can contact SIM to acquire a
 *  Professional Edition license for profit.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/* $Id$ */

#include <profit/types.h>
#include <profit/nodeinfo.h>
#include <profit/state.h>
#include <profit/debug.h>
#include <profit/node.h>
#include <profit/nodes/push_extension.h>
#include <config.h>

#include <assert.h>

/**************************************************************************/

static prf_nodeinfo_t prf_push_extension_info = {
    21, PRF_CONTROL | PRF_PUSH_NODE,
    "Push Extension",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
}; /* struct prf_push_extension_info */

/**************************************************************************/

static
void
prf_push_extension_entry_f(
    prf_node_t * node,
    prf_state_t * state )
{
    assert( node != NULL && state != NULL );
    if ( node->opcode != prf_push_extension_info.opcode ) {
        prf_error( 9,
            "tried push extension entry state method on node of type %d.",
            node->opcode );
        return;
    }
    state->extension_level++;
} /* prf_push_extension_entry_f() */

/**************************************************************************/

void
prf_push_extension_init(
    void )
{
    prf_push_extension_info.entry_f = prf_push_extension_entry_f;
    prf_nodeinfo_set( &prf_push_extension_info );
} /* prf_push_extension_init() */

/**************************************************************************/
