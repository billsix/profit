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

#ifndef PRF_LEVEL_OF_DETAIL_NODE_H
#define PRF_LEVEL_OF_DETAIL_NODE_H

#include <profit/basics.h>
#include <profit/profit.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct prf_level_of_detail_data {
  char id[8];
  int32_t reserved;
  double switch_in_distance;
  double switch_out_distance;
  int16_t special_effect_id1;
  int16_t special_effect_id2;
  int32_t flags;
  double center_x;
  double center_y;
  double center_z;
  double transition_range;
}; /* struct prf_level_of_detail_data */
  
PROFIT_API prf_node_t * prf_level_of_detail_node_create( prf_model_t * model,
                             int index, const char * filename );

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */

#endif /* ! PRF_LEVEL_OF_DETAIL_NODE_H */
