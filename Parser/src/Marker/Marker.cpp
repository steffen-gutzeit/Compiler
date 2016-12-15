/*
 *  Marker.cpp
 *  sysprog
 *
 *  Created by Peter Schneider on 22.02.10.
 *  Copyright 2010 Schneider Medien Services. All rights reserved.
 *
 */

#include "Marker.h"
#include <stdint.h>


int Marker::markerCount = 0;


Marker::Marker()
{
	myMarker = markerCount;
	Marker::markerCount++;
}

int Marker::getName()
{
	//return markerCount;
	return myMarker;
}
