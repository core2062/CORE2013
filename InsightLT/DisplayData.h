#ifndef DISPLAYDATA_H
#define DISPLAYDATA_H

#include "Zone.h"
#include <string>

namespace insight
{
	class DisplayData
	{
	
	public:
		DisplayData();
		virtual ~DisplayData();		
		virtual std::string getFormattedString(char) = 0;
		virtual void registerZone(Zone *);
	private:
		Zone *forCleanup;
	};
}

#endif
