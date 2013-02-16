#include "Zone.h"
#include "time.h"
#include "DisplayData.h"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace insight;
/* Zone Constructor
 * 
 * line - starting line
 * position - starting position
 * length - lenght of the zone
 * numberOfLines - number of lines in the zone
 * timer - scroll time
 */
Zone::Zone(Line line, int position, int length, int numberOfLines, unsigned short int timer) :
		m_zoneLine(line), m_zonePosition(position), m_zoneLength(length),
		m_displayTime(timer)
{
	m_scrollPosition = 0;
	m_twoLines = false;
	if(numberOfLines > 1)
	{
		m_twoLines = true;
	}
	setTime(timer);
	clock_gettime(CLOCK_REALTIME, &m_scrollTimer);
}

/* Query if this zone is a 2 line zone or not
 * 
 * returns true if the zone is 2 lines
 */
bool Zone::isTwoLines()
{
	return m_twoLines;
}

/* Sets the zones rotate time
 * 
 * rotateTime - time in milliseconds to rotate data
 */
void Zone::setTime(unsigned short int rotateTime)
{
	m_displayTime = rotateTime;
	
	if(rotateTime == 0)
		m_rotate = false;
	else
		m_rotate = true;
}

/* Registers a data element from the main insight object
 */
void Zone::registerData(DisplayData* item)
{
	m_infoItems.push_back(item);
	item->registerZone(this);
}

void Zone::removeDataElement(DisplayData *item)
{
	vector<DisplayData*>::iterator iter = std::find(m_infoItems.begin(), m_infoItems.end(), item);
	if(iter != m_infoItems.end())
	{
		std::cout << "Removing item by destructor" << endl;
		m_infoItems.erase(iter);
	}
}

/* Scrolls the zone up by one element
 */
void Zone::advanceZoneUp()
{
	m_scrollPosition++;
	if(m_scrollPosition == (int)m_infoItems.size())
	{
		m_scrollPosition = 0;
	}
	
}

/* Scrolls the zone down by one element
 */
void Zone::advanceZoneDown()
{
	m_scrollPosition--;
	if(m_scrollPosition <= 0)
	{
		m_scrollPosition = m_infoItems.size() - 1;
		if(m_scrollPosition < 0)
		{
			m_scrollPosition = 0;
		}
	}
}

/* Gets the starting line of the zone
 * 
 * returns the starting Line the zone is on
 */
Line Zone::getLine()
{
	return m_zoneLine;
}

/* Gets the starting position for this zone
 * 
 * returns the starting position of the zone
 */
int Zone::getPosition()
{
	return m_zonePosition;
}

/* Checks the timer to scroll the display zones
 * 
 */
void Zone::update()
{
	if(m_rotate)
	{	
		timespec tmpTime;
		int milliSecs;
		clock_gettime(CLOCK_REALTIME, &tmpTime);
		
		if(tmpTime.tv_nsec > m_scrollTimer.tv_nsec)
		{
			milliSecs = (tmpTime.tv_sec - m_scrollTimer.tv_sec) * 1000 + (int)((tmpTime.tv_nsec - m_scrollTimer.tv_nsec)/1000000);
		}
		else
		{
			milliSecs = (tmpTime.tv_sec - m_scrollTimer.tv_sec) * 1000 + (int)((m_scrollTimer.tv_nsec - tmpTime.tv_nsec)/1000000);
		}
		if(milliSecs > m_displayTime)
		{
			advanceZoneDown();
			cout << "Class: " << this << " - scroll:" << m_scrollPosition << endl;
			clock_gettime(CLOCK_REALTIME, &m_scrollTimer);
		}
	}
}

/* Returns the formatted string that would be written to the first line of
 * the zone
 * 
 * returns the formatted string
 */
string Zone::getLineOne()
{
	string tmpString(m_zoneLength, '-');
	
	if(!m_infoItems.empty())
	{		
		tmpString = m_infoItems[m_scrollPosition]->getFormattedString(m_zoneLength);
	}
	return tmpString;
}

/* Returns the formatted string that would be written on the second line of
 * the zone
 * 
 * returns the formatted string for line 2
 */
string Zone::getLineTwo()
{
	string tmpString(m_zoneLength, '-');
		
	if(m_infoItems.size() > 1)
	{
		if(m_scrollPosition + 1 >= (int)m_infoItems.size())
		{
			tmpString = m_infoItems[0]->getFormattedString(m_zoneLength);
		}
		else
		{
			tmpString = m_infoItems[m_scrollPosition + 1]->getFormattedString(m_zoneLength);
		}
	}
	return tmpString;
}

