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

#ifndef PRF_PROFIT_H
#define PRF_PROFIT_H

#include <profit/basics.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

PROFIT_API  int prf_profit_major(void);
PROFIT_API  int prf_profit_minor(void);
PROFIT_API  int prf_profit_micro(void);

PROFIT_API  int prf_interface_version(void);
PROFIT_API  int prf_interface_revision(void);
PROFIT_API  int prf_interface_age(void);
PROFIT_API  int prf_interface_supported( int version, int revision );

PROFIT_API  bool_t prf_init( void );
PROFIT_API  bool_t prf_exit( void );

PROFIT_API  bool_t prf_openflight_check_file( const char * filename );

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */

#endif /* ! PRF_PROFIT_H */
