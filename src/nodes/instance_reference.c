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

#include <profit/basics.h>
#include <profit/node.h>
#include <profit/nodeinfo.h>
#include <profit/model.h>
#include <profit/state.h>
#include <profit/debug.h>
#include <profit/nodes/instance_reference.h>
#include <profit/util/bfile.h>
#include <profit/util/array.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static prf_nodeinfo_t prf_instance_reference_info = {
    61, PRF_CONTROL | PRF_REFERENCE,
    "Instance Reference",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
}; /* struct instance_reference_info */

/**************************************************************************/

typedef struct prf_instance_reference_data node_data;

/**************************************************************************/

static bool_t
prf_instance_reference_load_f(
    prf_node_t * node,
    prf_state_t * state,
    bfile_t * bfile)
{
    node_data * data;
    uint32_t pos = 4;

    assert( node != NULL && state != NULL && bfile != NULL );

    node->opcode = bf_get_uint16_be(bfile);
    if ( node->opcode != prf_instance_reference_info.opcode ) {
        prf_error( 9, "tried instance reference load method for "
                   "node of type %d.", node->opcode );
        bf_rewind( bfile, 2 );
        return FALSE;
    }

    node->length = bf_get_uint16_be( bfile );
    assert( node->length >= 8 );

    if ( node->data == NULL && node->length > 4 ) {
        assert( state->model != NULL );
        if ( state->model->mempool_id == 0 )
            node->data = (uint8_t *) malloc( node->length - 4 );
        else
            node->data = (uint8_t *) pool_malloc( state->model->mempool_id,
                                                  node->length - 4);
        if ( node->data == NULL ) {
            prf_error( 9, "memory allocation problem (returned NULL)" );
            bf_rewind( bfile, 4 );
            return FALSE;
        }
    }

    data = (node_data *) node->data;
    data->spare = bf_get_int16_be(bfile); pos += 2;
    data->instance_definition_number = bf_get_int16_be(bfile); pos += 2;

    if ( pos < node->length ) /* padding */
        pos += bf_read( bfile, node->data + pos - 4, node->length - pos );
    return TRUE;
} /* instance_reference_load_f() */

/**************************************************************************/

static bool_t
prf_instance_reference_save_f(
    prf_node_t * node,
    prf_state_t * state,
    bfile_t * bfile)
{
    node_data * data;
    int pos = 4;

    assert( node != NULL && state != NULL && bfile != NULL );

    if ( node->opcode != prf_instance_reference_info.opcode ) {
        prf_error( 9, "instance reference save method on node of type %d.",
                   node->opcode );
        return FALSE;
    }

    bf_put_uint16_be( bfile, node->opcode );
    bf_put_uint16_be( bfile, node->length );

    data = (node_data *) node->data;
    assert( data != NULL );
    bf_put_int16_be( bfile, data->spare ); pos += 2;
    bf_put_int16_be( bfile, data->instance_definition_number ); pos += 2;

    if ( pos < node->length ) /* padding */
        pos += bf_write( bfile, node->data + pos - 4, node->length - pos );
    return TRUE;
} /* instance_reference_save_f() */

/**************************************************************************/

void
prf_instance_reference_init()
{
    prf_instance_reference_info.load_f = prf_instance_reference_load_f;
    prf_instance_reference_info.save_f = prf_instance_reference_save_f;
    prf_nodeinfo_set( &prf_instance_reference_info );
} /* instance_reference_init() */

/**************************************************************************/
