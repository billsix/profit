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

#ifndef PROFIT_VERTEX_WITH_NORMAL_H
#define PROFIT_VERTEX_WITH_NORMAL_H

#include <profit/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct prf_vertex_with_normal_data {
    float64_t  x;
    float64_t  y;
    float64_t  z;
    uint16_t   color_name_index;
    uint16_t   flags;
    float32_t  normal[ 3 ];
    uint32_t   packed_color;
    uint32_t   color_index;
}; /* struct prf_vertex_with_normal_data */

void prf_vertex_with_normal_init( void );
void prf_vertex_with_normal_fill_vertex( prf_node_t * node,
         prf_vertex_t * vertex );

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */

#endif /* ! PROFIT_VERTEX_WITH_NORMAL_H */

/* $Id$ */

