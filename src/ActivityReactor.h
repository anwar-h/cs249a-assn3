#ifndef __ACTIVITY_REACTOR_H__
#define __ACTIVITY_REACTOR_H__

#include "ActivityImpl.h"

class InjectActivityReactor : public Activity::Notifiee {
public:
	typedef Fwk::Ptr<InjectActivityReactor> Ptr;

	void onStatus();

	static InjectActivityReactor::Ptr
	InjectActivityReactorNew(Fwk::Ptr<Activity::Manager> manager, Activity *activity, double rate) {
		Ptr m = new InjectActivityReactor(manager, activity, rate);
		m->referencesDec(1);
		return m;
	}

protected:
	InjectActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity *activity, double rate):
		Notifiee(activity),
		rate_(rate),
		activity_(activity),
		manager_(manager)
		{}

	double rate_;
	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
	
};

class ForwardActivityReactor : public Activity::Notifiee {
public:
	typedef Fwk::Ptr<ForwardActivityReactor> Ptr;

	void onStatus();

	static ForwardActivityReactor::Ptr
	ForwardActivityReactorNew(Fwk::Ptr<Activity::Manager> manager, Activity *activity) {
		Ptr m = new ForwardActivityReactor(manager, activity);
		m->referencesDec(1);
		return m;
	}

protected:
	ForwardActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity *activity):
		Notifiee(activity),
		activity_(activity),
		manager_(manager)
		{}

	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
};

#endif
