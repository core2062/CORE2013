#include "COREAuto.h"
#include "WPILib.h"
using namespace CORE;

Action::Action(void){};

TimeAction::TimeAction(Action& action, float duration, bool blocking){
	TimeAction::TimeAction(&action, duration);
}

TimeAction::TimeAction(Action* action, float duration, bool blocking):
	timer(){
	m_action	= action;
	m_duration	= duration;
	m_blocking	= blocking;
	
	started = false;
}

int TimeAction::operator()(void){
	if(!started){
		timer.Start();
		started = true;
	}
	if(timer.Get()<=m_duration){
		(*m_action)();
		return 0;
	}else{
		return 1;
	}
}

//void TimeAction

AutoSequencer::AutoSequencer():
	aqueue(),
	background(){}

void AutoSequencer::add_action(Action& task){
	add_action(&task);
}

void AutoSequencer::add_action(Action* task){
	aqueue.push(task);
}

void AutoSequencer::iter(void){
	Action* a = aqueue.front();
	
	Action::ControlFlow return_val = (*a)();
	
	switch(return_val){
	case Action::CONTINUE:
		break;
	case Action::BACKGROUND:
		background.push_back(a);
		aqueue.pop();
		break;
	case Action::END:
		aqueue.pop();
		delete a;
		break;
	}
	
	for(std::vector<Action*>::iterator it = background.begin(); it != background.end(); ++it){
		Action::ControlFlow return_val = (**it)();
		if (return_val == Action::END){
			background.erase(it);
		}
	}
}

//int AutoTask::async(void* class_ref){
//	AutoTask* at = (AutoTask*) class_ref;
//	Timer timer;
//	timer.Start();
//	while(timer.Get() <= at->m_duration){
//		(*(at->m_action))();
//	}
//	
//	return 0;
//}
