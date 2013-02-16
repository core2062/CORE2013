#ifndef LINE_H
#define LINE_H

namespace insight
{
	/* These are the configuration option that are currently 
	 * supported. Each zone contains DisplayData elements that
	 * are displayed on the screen
	 * 
	 * If you pass strings that don't fit the data is cut off. The data is 
	 * given precedence, so if the header and the data don't fit the data 
	 * will cut off the header first before the display then cuts off data.
	 * 
	 * These are the layouts for the zones
	 * 
	 * FOUR_ZONES
	 * 11111111112222222222
	 * 33333333334444444444
	 * Here each zone has 10 characters available. Multiple data items in a zone
	 * are scrolled through at the configured speed. If you want a zone to display
	 * only one value you should register only one type and set the scroll time to 
	 * 0. Zones scroll times can all be set independantly using the 
	 * setZoneScrollTime(zone, time).
	 * 
	 * ONE_TWO_LINE_ZONE
	 * 11111111111111111111
	 * 11111111111111111111
	 * Here each zone has 20 characters available. The seperate lines will display 
	 * the subsequent data items registered to the zone.
	 * 
	 * TWO_ONE_LINE_ZONES
	 * 11111111111111111111
	 * 22222222222222222222
	 * Again each zone has 20 characters available. This zone is ideal if you
	 * want to scroll different sets of data at different rates, or have some 
	 * data displayed staticly while other data is scrolled.
	 * 
	 */
	enum Config_Option
	{
		FOUR_ZONES,
		ONE_TWO_LINE_ZONE,
		TWO_ONE_LINE_ZONES
	};
	
 	enum Line
 	{
 		LINE_1,
 		LINE_2
 	}; 	
}

#endif
