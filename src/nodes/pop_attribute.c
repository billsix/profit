/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
#include <profit/nodes/pop_attribute.h>
#include <config.h>

#include <assert.h>

/**************************************************************************/

static const prf_nodeinfo_t prf_pop_attribute_info;

/**************************************************************************/

void
prf_pop_attribute_init(
    void )
{
    prf_nodeinfo_set( &prf_pop_attribute_info );
} /* prf_pop_attribute_init() */

/**************************************************************************/

static
void
prf_pop_attribute_exit_f(
    prf_node_t * node,
    prf_state_t * state )
{
    assert( state != NULL && node != NULL );
    if ( node->opcode != prf_pop_attribute_info.opcode ) {
        prf_error( 9,
            "tried pop attribute exit state method on node of type %d.",
            node->opcode );
        return;
    }
    state->attribute_level--;
} /* prf_pop_attribute_exit_f() */

/**************************************************************************/

static const prf_nodeinfo_t prf_pop_attribute_info = {
    123, PRF_CONTROL | PRF_POP_NODE,
    "Pop Attribute",
    NULL,
    NULL,
    NULL,
    prf_pop_attribute_exit_f,
    NULL,
    NULL,
    NULL
}; /* struct prf_pop_attribute_info */

/**************************************************************************/

/* $Id$ */

