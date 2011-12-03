/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

/* $Id$ */

#include <config.h>

#include <assert.h>

#include <profit/basics.h>
#include <profit/util/array.h>
#include <profit/profit.h>
#include <profit/model.h>
#include <profit/state.h>
#include <profit/node.h>
#include <profit/nodeinfo.h>

/*
 * This file contains old interface functions.  These functions have been
 * made obsolete by other functions in the interface, but they are still
 * compiled into the library for binary compatibility reasons.  These
 * functions are no longer declared in the profit header files.
 *
 * For an explanation of the current/revision/age interface versioning
 * system, look up "Versioning" in the Libtool manual.  That is the system
 * being used, except for the fact that we include "old cruft" to be able
 * to keep the age count non-zero even when we remove functions from the
 * interface.
 */

/***************************************************************************
 * cruft from earlier (prototypes):
 */

PROFIT_API  int     prf_model_traverse_bf( prf_model_t * model,
                        prf_cb_t callback );
PROFIT_API  int     prf_model_traverse_io_(prf_node_t * root,
                        prf_state_t * state);

/***************************************************************************
 * cruft from earlier (implementations):
 */

/*
  bf: breadth-first: (not implemented)
      traverse graph, level by level (e.g. find match closest to top)
*/

int
prf_model_traverse_bf_(
    prf_node_t * node,
    prf_state_t * state,
    prf_node_t *** this_level,
    prf_state_t ** this_level_states,
    prf_node_t *** next_level,
    prf_state_t ** next_level_states )
{
    return PRF_TRAV_CONTINUE;
} /* prf_model_traverse_bf_() */

int
prf_model_traverse_bf(
    prf_model_t * model,
    prf_cb_t callback )
{
    prf_node_t *** this_level;
    prf_node_t *** next_level;
    prf_state_t ** this_level_states;
    prf_state_t ** next_level_states;
    prf_state_t * state; /* working state */
    prf_node_t ** array;
    int traverse, i, j;
    /* only *real* losers recurse on this one */

    state = prf_state_create();
    state->model = model;

    assert( model != NULL && model->header != NULL );

    this_level = (prf_node_t ***)prf_array_init( 8, sizeof( prf_node_t ** ) );
    this_level_states = (prf_state_t **)prf_array_init(8,sizeof(prf_state_t*));
    next_level = (prf_node_t ***)prf_array_init( 8, sizeof( prf_node_t ** ) );
    next_level_states = (prf_state_t **)prf_array_init(8,sizeof(prf_state_t*));

    array = (prf_node_t **)prf_array_init( 1, sizeof( prf_node_t * ) );
    assert( array != NULL );
    array = (prf_node_t **)prf_array_append_ptr( array, model->header );
    this_level = (prf_node_t ***)prf_array_append_ptr( this_level, array );
    this_level_states = 
      (prf_state_t **)prf_array_append_ptr( this_level_states,
					    prf_state_clone( state ) );

    traverse = PRF_TRAV_CONTINUE;

    while ( prf_array_count( this_level ) > 0 ) {
        prf_node_t *** temp_nodes;
        prf_state_t ** temp_states;
        
        for ( i = 0; i < prf_array_count( this_level ); i++ ) {
            prf_node_t ** children;

            children = this_level[i];
            prf_state_copy( state, this_level_states[i] );
            for ( j = 0; j < prf_array_count( children ); j++ ) {
                prf_nodeinfo_t * info;
                state->node = children[j];
                info = prf_nodeinfo_get( state->node->opcode );
                assert( info != NULL );
                if ( info->entry_f != NULL )
                    (*(info->entry_f))( state->node, state );
                traverse = prf_cb_call( callback, state );

                if ( traverse == PRF_TRAV_EXIT )
                    break;

                if ( (children[j]->children != NULL) &&
                     (traverse != PRF_TRAV_SIBLING) ) {
                    prf_state_t * clone;
                    clone = prf_state_clone( state );
                    prf_state_push( clone );
                    clone->physical_level++;
                    next_level = (prf_node_t ***)prf_array_append_ptr( 
                        next_level, children[j]->children );
                    next_level_states = (prf_state_t **)prf_array_append_ptr(
                        next_level_states, clone );
                }
                if ( info->exit_f != NULL )
                    (*(info->exit_f))( state->node, state );
            }
            if ( traverse == PRF_TRAV_EXIT )
                break;
        }

        if ( traverse == PRF_TRAV_EXIT )
            break;

        for ( i = 0; i < prf_array_count( this_level_states ); i++ ) {
            prf_state_destroy( this_level_states[i] );
            this_level_states[i] = NULL;
        }
        /* save and rotate the growable arrays */
        temp_nodes = this_level;
        temp_states = this_level_states;
        this_level = next_level;
        this_level_states = next_level_states;
        next_level = temp_nodes;
        next_level = (prf_node_t ***)prf_array_set_count( next_level, 0 );
        next_level_states = temp_states;
        next_level_states = 
	  (prf_state_t **)prf_array_set_count( next_level_states, 0 );
    }

    prf_state_destroy( state );
    prf_array_free( this_level );
    for ( i = 0; i < prf_array_count( this_level_states ); i++ )
        if ( this_level_states[i] != NULL )
            prf_state_destroy( this_level_states[i] );
    prf_array_free( this_level_states );
    prf_array_free( next_level );
    for ( i = 0; i < prf_array_count( next_level_states ); i++ )
        if ( next_level_states[i] != NULL )
            prf_state_destroy( next_level_states[i] );
    prf_array_free( next_level_states );
    return traverse;
} /* prf_model_traverse_bf() */

/**************************************************************************/
