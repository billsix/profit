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

#ifndef PROFIT_INSTANCE_REFERENCE_H
#define PROFIT_INSTANCE_REFERENCE_H

#include <profit/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct prf_instance_reference_data 
{
  int16_t spare;
  int16_t instance_definition_number;
}; /* struct prf_instance_reference_number */

void prf_instance_reference_init();

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */

#endif  /* PROFIT_INSTANCE_REFERENCE_H */

/* $Id$ */

