#include "DisplayData.h"

using namespace insight;

DisplayData::DisplayData()
{
	forCleanup = NULL;
}

DisplayData::~DisplayData()
{
	if(forCleanup != NULL)
	{
		forCleanup->removeDataElement(this);
	}
}

void DisplayData::registerZone(Zone *zone)
{
	
	forCleanup = zone;
}
