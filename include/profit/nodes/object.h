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

#ifndef PROFIT_OBJECT_H
#define PROFIT_OBJECT_H

#include <profit/basic_types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct prf_object_data {
    char       ascii_id[ 8 ];
    uint32_t   flags;
    int16_t    relative_priority;
    uint16_t   transparency;
    int16_t    special_effect_id1;
    int16_t    special_effect_id2;
    int16_t    significance;
    int16_t    spare;
}; /* struct prf_object_data */

void prf_object_init( void );

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */

#endif /* ! PROFIT_OBJECT_H */

/* $Id$ */

