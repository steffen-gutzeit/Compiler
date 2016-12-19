#include "Marker.h"
#include <stdint.h>


int Marker::markerCount = 0;

/*
 * Konstruktor
 */
Marker::Marker()
{
	myMarker = markerCount;
	Marker::markerCount++;
}

/*
 * Gibt den aktuellen Markerwert zurück
 */
int Marker::getName()
{
	return myMarker;
}
