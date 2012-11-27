#ifndef __NOTIFIEE_H__
#define __NOTIFIEE_H__

#include <string>
#include "fwk/NamedInterface.h"
#include "fwk/Ptr.h"

using namespace std;

namespace Fwk {

class ActivityRootNotifiee : public PtrInterface<ActivityRootNotifiee> {
	/* Deliberately empty */
};

template<typename Notifier>
class BaseNotifiee : public ActivityRootNotifiee {
public:
	BaseNotifiee(Notifier* n = NULL):
		notifier_(n)
		{
	    	if (n != NULL) {
				n->lastNotifieeIs(static_cast<typename Notifier::Notifiee*>(this));
	    	}
		}

	~BaseNotifiee()
	{
	    if (notifier_ != Ptr<Notifier>()) {
			notifier_->lastNotifieeIs(0);
	    }
	}

	Ptr<Notifier> notifier() const { return notifier_; }

	void notifierIs(Ptr<Notifier> n)
	{
	    if (notifier_ != n) {
			if (notifier_ != Ptr<Notifier>()) {
			    notifier_->lastNotifieeIs(0);
			}
			notifier_ = n;
			if (n != Ptr<Notifier>()) {
			    n->lastNotifieeIs(static_cast<typename Notifier::Notifiee*>(this));
			}
	    }
	}

private:
	Ptr<Notifier> notifier_;
};
 
} //end namespace Fwk   

#endif
    
