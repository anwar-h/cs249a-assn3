#ifndef __ACTIVITY_H__
#define __ACTIVITY_H__

#include <string>
#include "fwk/BaseNotifiee.h"
#include "fwk/NamedInterface.h"
#include "Nominal.h"


using std::string;

/* Define the type 'Time' */
class Time : public Ordinal<Time,double> {
public:
    Time(double time) : Ordinal<Time,double>(time)
    {}
};

class Activity : public Fwk::NamedInterface {
 public:
    typedef Fwk::Ptr<Activity> Ptr;
    
    /* Notifiee class for Activities */
    class Notifiee : public virtual Fwk::NamedInterface::Notifiee {
    public:
        typedef Fwk::Ptr<Notifiee> Ptr;

        Notifiee(Activity* act):
            Fwk::NamedInterface::Notifiee(),
            act_(act)
            {}

        virtual void onNextTime() {}
        virtual void onStatus() {}

    protected:
        Activity *act_;
    };

    class Manager;

    enum Status {
        free, waiting, ready, executing, nextTimeScheduled, deleted
    };

    virtual Status status() const = 0;
    virtual void statusIs(Status s)  = 0;
    
    virtual Time nextTime() const = 0;
    virtual void nextTimeIs(Time t) = 0;

    virtual Fwk::Ptr<Notifiee> notifiee() const = 0;

    virtual void lastNotifieeIs(Notifiee* n) = 0;

protected:
    Activity(const string &name):
        Fwk::NamedInterface(name)
        {}
};

class Activity::Manager : public Fwk::NamedInterface {
public:
    typedef Fwk::Ptr<Activity::Manager> Ptr;

    virtual Fwk::Ptr<Activity> activityNew(const string &name) = 0;

    virtual Fwk::Ptr<Activity> activity(const string &name) const = 0;

    virtual void activityDel(const string &name) = 0;

    virtual void lastActivityIs(Activity::Ptr) = 0;

    virtual Time now() const = 0;
    virtual void nowIs(Time) = 0;


protected:
    Manager(const string &name):
        Fwk::NamedInterface(name)
        {}
};

extern Fwk::Ptr<Activity::Manager> activityManagerInstance();

#endif
