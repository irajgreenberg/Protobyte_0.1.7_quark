/*
 *  Copyright (C) 2004 Steve Harris, Uwe Koloska
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  $Id: example_server.c,v 1.2 2005/04/25 21:46:46 xovo Exp $
 */
 
 #ifndef Protobyte_Library_V01_ProtoOSCServer_h
#define Protobyte_Library_V01_ProtoOSCServer_h


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lo/lo.h"


// function prototypes
int initOSCServer();

void error(int num, const char *m, const char *path);

int generic_handler(const char *path, const char *types, lo_arg **argv,
		    int argc, void *data, void *user_data);

int foo_handler(const char *path, const char *types, lo_arg **argv, int argc,
		 void *data, void *user_data);

int quit_handler(const char *path, const char *types, lo_arg **argv, int argc,
		 void *data, void *user_data);
		 
		 
		 
#endif
