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

#ifndef PRF_EXTERNAL_REFERENCE_NODE_H
#define PRF_EXTERNAL_REFERENCE_NODE_H

#include <profit/basics.h>
#include <profit/profit.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct prf_external_reference_data {
    char filename[200];
    int8_t reserved1;
    int8_t reserved2;
    int16_t reserved3[2];
    int32_t flags;
}; /* struct prf_external_reference_data */
  
PROFIT_API prf_node_t * prf_external_reference_node_create(prf_model_t * model,
                             int index, const char * filename );

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */

#endif /* ! PRF_EXTERNAL_REFERENCE_NODE_H */