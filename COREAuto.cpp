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

Action::ControlFlow TimeAction::call(void){
	if(!started){
		timer.Start();
		started = true;
	}
	if(timer.Get()<=m_duration){
		(*m_action).call();
		if(!m_blocking){
			return BACKGROUND;
		}
		return CONTINUE;
	}else{
		return END;
	}
}

//void TimeAction

AutoSequencer::AutoSequencer():
	aqueue(),
	background(){
	
}

void AutoSequencer::add_action(Action& action){
	add_action(&action);
}

void AutoSequencer::add_action(Action* action){
//	cout<<"adding action"<<endl;
//	cout<<action<<endl;
	aqueue.push(action);
}

void AutoSequencer::iter(void){
//	cout<<"iter start"<<endl;
	if(aqueue.empty()){
		cout << "No remaining auto actions!"<<endl;	
		return;
	}
	Action* a = aqueue.front();
//	cout <<a<<endl;
	Action::ControlFlow return_val = a->call();
	
//	cout<<"after action"<<endl;
	switch(return_val){
	case Action::CONTINUE:
//		cout<<" in countinue"<<endl;
		break;
	case Action::BACKGROUND:
//		cout<<"in background"<<endl;
		background.push_back(a);
		aqueue.pop();
		break;
	case Action::END:
//		cout<<"in end"<<endl;
		aqueue.pop();
		break;
	}
//	cout<<"before bkgrnd loop"<<endl;
	for(std::vector<Action*>::iterator it = background.begin(); it != background.end(); ++it){
		Action::ControlFlow return_val = (*it)->call();
		if (return_val == Action::END){
			background.erase(it);
		}
	}
	cout<<"after iter"<<endl;
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
