#ifndef __ACTIVITY_REACTOR_H__
#define __ACTIVITY_REACTOR_H__

#include "ActivityImpl.h"

class InjectActivityReactor : public Activity::Notifiee {
public:
	void onStatus();

	InjectActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity *activity, double rate):
		Notifiee(activity),
		rate_(rate),
		activity_(activity),
		manager_(manager)
		{}

protected:
	double rate_;
	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
	
};

class ForwardActivityReactor : public Activity::Notifiee {
public:
	void onStatus();

	ForwardActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity *activity):
		Notifiee(activity),
		activity_(activity),
		manager_(manager)
		{}

protected:
	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
};

#endif
