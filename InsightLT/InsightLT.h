/*	InsightLT.h
 *	
 *	
 */
#ifndef INSIGHTLT_H
#define INSIGHTLT_H

#include "DigitalModule.h"
#include "Task.h"
#include "I2C.h"
#include "Zone.h"
#include "Line.h"
//included for ease of use by users, now they only need to include InsightLT.h
#include "StringData.h"
#include "IntegerData.h"
#include "DecimalData.h"

namespace insight
{
 	class InsightLT : public DigitalModule
	{
	public:
		InsightLT();
		InsightLT(Config_Option);
		InsightLT(Config_Option, UINT8 moduleNumber);
		~InsightLT();	
		Zone* getZone(int zoneNumber);
		void startDisplay();
		void pauseDisplay();		
		void stopDisplay();
		void writeMessage(std::string, int, int);
		bool registerData(DisplayData &, int);
		void setZoneScrollTime(int, int);
		void manualScroll(int, char);
		
	private:
		void clearScreen();
		bool getConnectionStatus();
		void setConnectionStatus(bool);
		static int taskFunction(InsightLT *);		
		void initializeDisplay();
		void welcomeMessage();
		void config(Config_Option);
		
		Task m_displayTask;	
		I2C *m_twiComm;
		bool m_wasPaused;
		bool m_displayConnected;
		bool m_started;
		std::vector<Zone*> m_zones;		
		
	};
}

#endif//INSIGHTLT_H
