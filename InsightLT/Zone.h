#ifndef ZONE_H
#define ZONE_H

#include <vector>
#include <string>
#include "Line.h"
#include <time.h>


namespace insight
{
	class DisplayData;
	class Zone
	{
	public:
		Zone();
		Zone(Line, int, int, int, unsigned short int);		
		void setTime(unsigned short int);
		void registerData(DisplayData *item);
		void removeDataElement(DisplayData *);
		void advanceZoneUp();
		void advanceZoneDown();
		Line getLine();
		int getPosition();
		std::string getLineOne();
		std::string getLineTwo();
		bool isTwoLines();
		void update();
		
	private:
		Line m_zoneLine;
		int m_zonePosition;
		int m_zoneLength;
		bool m_twoLines;
		bool m_rotate;
		int m_scrollPosition;
		timespec m_scrollTimer;
		// lenght of time each information item is displayed
		unsigned short int m_displayTime;
		// container for information items
		std::vector<insight::DisplayData*> m_infoItems;		
	};
}
#endif//Zone.h
