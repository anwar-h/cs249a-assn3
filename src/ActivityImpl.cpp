#include <iostream>
#include <time.h>

#include "ActivityImpl.h"

using namespace std;

Fwk::Ptr<Activity::Manager> activityManagerInstance() {
    return ActivityImpl::ManagerImpl::activityManagerInstance();
}

namespace ActivityImpl {
    //Definition of static member
    Fwk::Ptr<Activity::Manager> ManagerImpl::activityInstance_ = Fwk::Ptr<Activity::Manager>();
    
    //Gets the singleton instance of ManagerImpl
    Fwk::Ptr<Activity::Manager> ManagerImpl::activityManagerInstance() {
		if (!activityInstance_) {
		    activityInstance_ = new ManagerImpl();
		}
		return activityInstance_;
    }
    
    Activity::Ptr ManagerImpl::activityNew(const string& name) {
		Activity::Ptr activity = activities_[name];

		if (activity) {
		    cerr << "Activity already exists!" << endl;
		    return Activity::Ptr();
		}
		
		activity = new ActivityImpl(name, this);
		activities_[name] = activity;

		return activity;
    }

    Activity::Ptr ManagerImpl::activity(const string& name) const {
		map<string, Activity::Ptr>::const_iterator it = activities_.find(name);
		
		if(it != activities_.end() ) {
		    return (*it).second;
		}
		
		// dont throw an exception (accessor)
		return Activity::Ptr(); 
    }
    
    void ManagerImpl::activityDel(const string& name) {
		activities_.erase(name);
    }
    
    void ManagerImpl::lastActivityIs(Activity::Ptr activity) {
		scheduledActivities_.push(activity);
    }


} //end namespace ActivityImpl
