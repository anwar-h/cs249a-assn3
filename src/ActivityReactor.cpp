#include "ActivityReactor.h"

void InjectActivityReactor::onStatus() {
    ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);

    switch (activity_->status()) {
	    case Activity::executing:
			//I am executing now

			break;
		
	    case Activity::free:
			//when done, automatically enqueue myself for next execution
			activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
			activity_->statusIs(Activity::nextTimeScheduled);
			break;

	    case Activity::nextTimeScheduled:
			//add myself to be scheduled
			manager_->lastActivityIs(activity_);
			break;
		
	    default: break;
    }
}

void ForwardActivityReactor::onStatus() {
    ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);

    switch (activity_->status()) {
	    case Activity::executing:
			//I am executing now

			break;
	
	    case Activity::free:
			//When done, automatically enqueue myself for next execution
			activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
			activity_->statusIs(Activity::nextTimeScheduled);
			break;

	    case Activity::nextTimeScheduled:
			//add myself to be scheduled
			manager_->lastActivityIs(activity_);
			break;

	    default: break;
    }
}