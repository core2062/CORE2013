#include <string>
#include <queue>
#include <vector>
#include "WPILib.h"

#ifndef COREAUTO
#define COREAUTO
namespace CORE{
	
class Action{
	public:
		enum ControlFlow{
			CONTINUE,
			END,
			BACKGROUND
		};
		Action();
		virtual ControlFlow operator()(void) = 0;
		virtual ~Action(){};
	};
	
	class TimeAction : public Action{
		Action* m_action;
		float m_duration;
		bool m_blocking;
		
		Timer timer;
		bool started;
	public:
		TimeAction(Action& action, float duration, bool blocking = true);
		TimeAction(Action* action, float duration, bool blocking = true);
		virtual ControlFlow operator()(void);
		virtual ~TimeAction(void){delete m_action;};
	};
	
	class AutoSequencer{
		
		std::queue<Action*> aqueue;
		
		std::vector<Action*> background;
	public:
		AutoSequencer(void);
		
		void add_action(Action& task);
		void add_action(Action* task);
		
		void iter(void);
	};
}
#endif
