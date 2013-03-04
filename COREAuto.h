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
		virtual ControlFlow call(void){cout << "action base class operator"<< endl; return END;} // =0
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
		virtual ControlFlow call(void);
		virtual ~TimeAction(void){delete m_action;};
	};
	
	class AutoSequencer{
		
		std::queue<Action*> aqueue;
		
		std::vector<Action*> background;
	public:
		AutoSequencer(void);
		
		void add_action(Action& action);
		void add_action(Action* action);
		
		void iter(void);
	};
}
#endif
