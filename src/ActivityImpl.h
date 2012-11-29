#ifndef __ACTIVITY_IMPL_H__
#define __ACTIVITY_IMPL_H__

#include "Activity.h"
#include <map>
#include <string>
#include <queue>
#include <vector>

Fwk::Ptr<Activity::Manager> activityManagerInstance();
Fwk::Ptr<Activity::Manager> realTimeManagerInstance();

namespace ActivityImpl {

//Comparison class for activities   
class ActivityComp {
public:
	ActivityComp() {}

	bool operator()(Activity::Ptr a, Activity::Ptr b) const {
		return (a->nextTime() > b->nextTime());
	}
};
    

class ActivityImpl : public Activity {
protected:
    ActivityImpl(const string& name, Fwk::Ptr<class ManagerImpl> manager):
    	Activity(name),
    	status_(free),
    	nextTime_(0.0),
    	notifiee_(NULL),
    	manager_(manager)
    	{}
        
	Fwk::Ptr<class ManagerImpl> manager() const { return manager_; }

	virtual Status status() const { return status_; }
	virtual void statusIs(Status s) {
		status_ = s;
		if (notifiee_ != NULL) {
			notifiee_->onStatus();
		}
	}

	virtual Time nextTime() const { return nextTime_; }
	virtual void nextTimeIs(Time t) {
		nextTime_ = t;
		if (notifiee_ != NULL) {
			notifiee_->onNextTime();
		}
	}

	virtual Notifiee::Ptr notifiee() const { return notifiee_; }

	virtual void lastNotifieeIs(Notifiee* n) {
		ActivityImpl* me = const_cast<ActivityImpl*>(this);
		me->notifiee_ = n;
	}
private:
	friend class ManagerImpl;
	Status status_;
	Time nextTime_;
	Notifiee* notifiee_;
	Fwk::Ptr<class ManagerImpl> manager_;
};

class ManagerImpl : public Activity::Manager {
public:
	typedef Fwk::Ptr<ManagerImpl> Ptr;

	enum ManagerType {
		real_time_,
		virtual_time_
	};

	static inline ManagerType realtime() { return real_time_; }
	static inline ManagerType virtualtime() { return virtual_time_; }

	void managerTypeIs(ManagerType m) { managerType_ = m; }
	ManagerType managerType() const { return managerType_; }

	virtual Activity::Ptr activityNew(const string& name);
	virtual Activity::Ptr activity(const string& name) const;
	virtual void activityDel(const string& name);

	virtual Time now() const { return now_; }
	virtual void nowIs(Time time);

	static Fwk::Ptr<Activity::Manager> singletonActivityManagerInstance(ManagerType t);

	virtual void lastActivityIs(Activity::Ptr activity);

protected:
    ManagerImpl(ManagerType t):
    	Manager(),
    	managerType_(t),
    	now_(0)
    	{}

    ManagerType managerType_;
	//Data members
	std::priority_queue<Activity::Ptr, std::vector<Activity::Ptr>, ActivityComp> scheduledActivities_;
	std::map<string, Activity::Ptr> activities_; //pool of all activities
	Time now_;

	//singleton instance
	static Fwk::Ptr<Activity::Manager> activityInstance_;
};

} // end namespace ActivityImpl

#endif /* __ACTIVITY_IMPL_H__ */

