/* InsightLT.cpp
 * 
 * This is the main file exposed to the user. An InsightLT object
 * and supporting DisplayData objects make up the user interface 
 */
#include "WPILib.h"
#include "InsightLT.h"
#include <iostream>

using namespace std;
using namespace insight;

/*
 * Default Constructor
 * The default display configuration is for 2 one line zones
 */
InsightLT::InsightLT() : DigitalModule(GetDefaultDigitalModule()), 
		m_displayTask("InsightLT", (FUNCPTR)&this->taskFunction),
		m_displayConnected(false), m_started(false)
{
	config(TWO_ONE_LINE_ZONES);
	initializeDisplay();
}

/* Constructor, initializes the display with the correct
 * zone configuration.
 * 
 * option - the Config_Option you wish to have. See the Config_Options
 * 			enum in Line.h for more info
 * 
 */
InsightLT::InsightLT(Config_Option option) : DigitalModule(GetDefaultDigitalModule()),
		m_displayTask("InsightLT", (FUNCPTR)&this->taskFunction),
		m_displayConnected(false), m_started(false)
{
	config(option);
	initializeDisplay();
}

/* Constructor, initializes the display with both the correct zone
 * configuration and module number
 * 
 * option - the Config_Option you wish to have. See the Config_Options
 * 			enum in Line.h for more info
 * moduleNumber - module number if not using the first(default) Digital card
 */
InsightLT::InsightLT(Config_Option option, UINT8 moduleNumber) : DigitalModule(moduleNumber),
		m_displayTask("InsightLT", (FUNCPTR)&this->taskFunction),
		m_displayConnected(false), m_started(false)
{
	config(option);
	initializeDisplay();
}

/* Destructor
 * 
 */
InsightLT::~InsightLT()
{
	delete m_twiComm;
}

/* private fuction called by the constructors to configure the internals
 * of InsightLT
 * 
 * option - the zone configuration to initialize with
 */
void InsightLT::config(Config_Option option)
{
	m_wasPaused = false;
	m_twiComm = GetI2C(0x78);
	switch(option)
	{
	case FOUR_ZONES:
		m_zones.push_back(new Zone(LINE_1, 0, 10, 1, 1000));
		m_zones.push_back(new Zone(LINE_1, 10, 10, 1, 1000));
		m_zones.push_back(new Zone(LINE_2, 0, 10, 1, 1000));
		m_zones.push_back(new Zone(LINE_2, 10, 10, 1, 1000));
	case TWO_ONE_LINE_ZONES:
		m_zones.push_back(new Zone(LINE_1, 0, 20, 1, 1000));
		m_zones.push_back(new Zone(LINE_2, 0, 20, 1, 1000));
		break;
	case ONE_TWO_LINE_ZONE:
	default:
		m_zones.push_back(new Zone(LINE_1, 0, 20, 2, 1000));
		break;
	}
}

/* Sets the zones scroll time. If you don't want the zone to scroll set the 
 * scroll time to 0.
 * 
 * zone - zone to set the time for
 * timer - scroll time in milliseconds
 */
void InsightLT::setZoneScrollTime(int zone, int timer)
{
	Zone *tmpZone = getZone(zone);
	if(tmpZone != NULL)
	{
		tmpZone->setTime(timer);
	}
}

/* This function allows the user to scroll a zone manually, perhaps with a 
 * switch.
 * 
 * zone - zone to scroll
 * direction - direction to scroll(>0 to scroll up, <0 to scroll down)
 * 
 */
void InsightLT::manualScroll(int zone, char direction)
{
	Zone *tmpZone = getZone(zone);
	if(tmpZone != NULL)
	{
		if(direction > 0)
		{
			tmpZone->advanceZoneUp();
		}
		else
		{
			tmpZone->advanceZoneDown();
		}
	}	
}

/* Registers a DisplayData type to the display for writing.
 * data - The data element to monitor
 * zoneNumber - the zone to register the data for
 */
bool InsightLT::registerData(DisplayData &data, int zoneNumber)
{
	if(zoneNumber < 1 || zoneNumber > m_zones.size())
	{
		return false;
	}
	else
	{
		m_zones[zoneNumber - 1]->registerData(&data);
		return true;
	}
}

/* Display initialization routine
 * 
 */
void InsightLT::initializeDisplay()
{	
	std::cout << "Initializing the display " << std::endl;		
	UINT8 buffer[6];
	
	buffer[0] = 0x00;		
	buffer[1] = 0x38;		
	buffer[2] = 0x39;				
	buffer[3] = 0x14;
	buffer[4] = 0x78;
	buffer[5] = 0x5E;
	m_twiComm->Transaction(buffer, 6, NULL, 0);
	
	buffer[0] = 0x00;
	buffer[1] = 0x6D;	
	m_twiComm->Transaction(buffer, 2, NULL, 0);
	Wait(.2);			
	
	buffer[0] = 0x00;
	buffer[1] = 0x0C;
	buffer[2] = 0x01;
	buffer[3] = 0x06;
	m_twiComm->Transaction(buffer, 4, NULL, 0);			
	Wait(.01);
}

/* writeMessage puts text to the screen using the given parameters
 * 
 * message - string to put to the display, if the string is larger than the 
 * 			 area to write to the string will be cut off.
 * line - the line to put the message on, 0 or 1
 * position - left right position to start writing the message, 0 - 19. Text
 * 			  that doesn't fit on the screen will be cut off
 * 
 */
void InsightLT::writeMessage(std::string message, int line, int position)
{		
	char buffer[6];
	
	buffer[0] = 0x00;
	buffer[1] = ((line * 0x40) + position) | 0x80;	
	m_twiComm->Transaction((UINT8*)buffer, 2, NULL, 0);
	
	bool end = false;
	buffer[0] = 0x40;
	for(unsigned short int x = 0; x < message.length();)
	{
		for(unsigned short int y = 1; y < 6; y++)
		{
			buffer[y] = message[x];
			x++;
			if(x >= message.length())
			{
				m_twiComm->Transaction((UINT8*)buffer, y + 1, NULL, 0);
				end = true;
				break;
			}
		}
		if(!end)
			m_twiComm->Transaction((UINT8*)buffer, 6, NULL, 0);
	}
}

/* The initial message displayed for 3 seconds when the display first
 * connects
 */
void InsightLT::welcomeMessage()
{
	std::string message("Bit Built Tech");
	std::string message2("Robot Diagnostics");
	
	writeMessage(message, LINE_1, 0);
	writeMessage(message2, LINE_2, 3);
}

/* startDisplay initiates the display background task or restarts
 * a paused task
 *  
 */
void InsightLT::startDisplay()
{
	if(!m_started)
	{
		m_started = true;
		m_displayTask.Start((UINT32) this);
	}
	if(m_wasPaused)
	{
		m_wasPaused = false;
		m_displayTask.Resume();
	}		
}

/* pauseDisplay pauses the background display task. It is advised to pause
 * the display task during operator mode for competitions to free all the
 * cpu resources. Make sure to resume the task at the end of the operator 
 * function to enable the display after the match
 *  
 */
void InsightLT::pauseDisplay()
{
	m_wasPaused = true;
	m_displayTask.Suspend();
}

/* query if the display is connected
 * 
 * returns true if the display is connected
 * 
 */
bool InsightLT::getConnectionStatus()
{
	return m_displayConnected;
}

/* set the connection status when a connection is made
 * 
 */
void InsightLT::setConnectionStatus(bool status)
{
	m_displayConnected = status;
}

/* clear all text from the display
 * 
 */
void InsightLT::clearScreen()
{
	char buffer[2] = {0x00, 0x01};
	m_twiComm->Transaction((UINT8*)buffer, 2, NULL, 0);
}

/* getZone returns a pointer to the requested zone
 * 
 * zoneNumber - depending on the configuration, 1-4
 * returns a Zone*
 */
Zone* InsightLT::getZone(int zoneNumber)
{
	if(zoneNumber > (int)m_zones.size() || zoneNumber == 0)
	{
		return NULL;
	}
	else
	{
		return m_zones[zoneNumber - 1];
	}
}

/* The background display task function
 * 
 */
int InsightLT::taskFunction(InsightLT *object)
{
	Zone *tmpZone;
	while(1)
	{
		if(!object->getConnectionStatus())
		{
			while(object->m_twiComm->AddressOnly())
			{
				Wait(.5);
			}
			object->initializeDisplay();
			object->welcomeMessage();
			object->setConnectionStatus(true);
			Wait(2);
			object->clearScreen();
		}
		else
		{	
			while(1)
			{
				if(object->m_twiComm->AddressOnly())
				{
					object->setConnectionStatus(false);
					break;
				}
				for(int x = 1; x < 5; x++)
				{					
					tmpZone = object->getZone(x);
					if(tmpZone != NULL)
					{
						tmpZone->update();
						object->writeMessage(tmpZone->getLineOne(), tmpZone->getLine(), tmpZone->getPosition());
						if(tmpZone->isTwoLines())
						{
							object->writeMessage(tmpZone->getLineTwo(), tmpZone->getLine() + 1, tmpZone->getPosition());
						}
					}
				}	
				Wait(.05);
			}
		}
		
	}	
}

