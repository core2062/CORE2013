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
	
	class WaitAction : public Action{
		float m_duration;
		
		Timer timer;
	public:
		WaitAction(float duration);
		virtual ControlFlow call(void);
		virtual ~WaitAction(void){};
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
