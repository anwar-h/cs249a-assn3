#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include "Instance.h"
#include "Engine.h"

namespace Shipping {

using namespace std;

//
// Rep layer classes
//
class ConnRep;
class FleetRep;
class StatsRep;

class ManagerImpl : public Instance::Manager {
public:
    ManagerImpl();

    // Manager method
    Ptr<Instance> instanceNew(const string& name, const string& type);

    // Manager method
    Ptr<Instance> instance(const string& name);

    // Manager method
    void instanceDel(const string& name);

private:
    Network::Ptr network_;
    Ptr<ConnRep> conn_;
    Ptr<FleetRep> fleet_;
    Ptr<StatsRep> stats_;
    map<string,Ptr<Instance> > instance_;
};

//-------------------------LOCATION-----------------------------------
class LocationRep : public Instance {
public:

    LocationRep(const string& name, ManagerImpl* manager, Ptr<Network> n) :
        Instance(name), network_(n), manager_(manager){}

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

protected:
    Ptr<Location> location_;
    Ptr<Network> network_;

private:
    Ptr<ManagerImpl> manager_;
    int segmentNumber(const string& name);
    
};


string LocationRep::attribute(const string& name) {
    int i = segmentNumber(name);
    if (i != 0) {
        Segment::PtrConst seg = location_->segment(i - 1);
        if(seg) return seg->name();
    }
    cerr << "Error with segment #" << i;
    return "";
}


void LocationRep::attributeIs(const string& name, const string& v) {
    //nothing to do
}

static const string segmentStr = "segment";
static const int segmentStrlen = segmentStr.length();

int LocationRep::segmentNumber(const string& name) {
    if (name.substr(0, segmentStrlen) == segmentStr) {
        const char* t = name.c_str() + segmentStrlen;
        return atoi(t);
    }
    return 0;
}

                                                                                                  
class TruckTerminalRep : public LocationRep {
public:

    TruckTerminalRep(const string& name, ManagerImpl *manager, Ptr<Location> l, Ptr<Network> n) :
        LocationRep(name, manager, n)
    {
        location_ = l;
    }

protected:
    void onZeroReferences() {
        network_->terminalDel(location_->name());
    }

};

class BoatTerminalRep : public LocationRep {
public:

    BoatTerminalRep(const string& name, ManagerImpl *manager, Ptr<Location> l, Ptr<Network> n) :
        LocationRep(name, manager, n)
    {
        location_ = l;
    }
protected:
    void onZeroReferences() {
        network_->terminalDel(location_->name());
    }

};

class PlaneTerminalRep : public LocationRep {
public:

    PlaneTerminalRep(const string& name, ManagerImpl *manager, Ptr<Location> l, Ptr<Network> n) :
        LocationRep(name, manager, n)
    {
        location_ = l;
    }
protected:
    void onZeroReferences() {
        network_->terminalDel(location_->name());
    }

};

class CustomerRep : public LocationRep {
public:

    CustomerRep(const string& name, ManagerImpl *manager, Ptr<Location> l, Ptr<Network> n) :
        LocationRep(name, manager, n)
    {
        location_ = l;
    }
protected:
    void onZeroReferences() {
        network_->customerDel(location_->name());
    }

};

class PortRep : public LocationRep {
public:

    PortRep(const string& name, ManagerImpl *manager, Ptr<Location> l, Ptr<Network> n) :
        LocationRep(name, manager, n)
    {
        location_ = l;
    }
protected:
    void onZeroReferences() {
        network_->portDel(location_->name());
    }

};

//----------------------SEGMENT------------------------------------------------

class SegmentRep : public Instance {
public:
    SegmentRep(const string& name, ManagerImpl* manager, Network::Ptr n) :
        Instance(name), manager_(manager)
    {
        network_ = n;
    }
    string attribute(const string& name);
    void attributeIs(const string& name, const string& v);
protected:
    void onZeroReferences() {
        network_->segmentDel(segment_->name());
    }
    Ptr<Segment> segment_;

private:
    Ptr<ManagerImpl> manager_;
    Ptr<Network> network_;
};

class TruckSegmentRep : public SegmentRep {
public:
    TruckSegmentRep(const string& name, ManagerImpl *manager, Network::Ptr n, Ptr<Segment> s) :
        SegmentRep(name, manager, n)
    {
        segment_ = s;
    }
};

class BoatSegmentRep : public SegmentRep {
public:
    BoatSegmentRep(const string& name, ManagerImpl *manager, Network::Ptr n, Ptr<Segment> s) :
        SegmentRep(name, manager, n)
    {
        segment_ = s;
    }
};

class PlaneSegmentRep : public SegmentRep {
public:
    PlaneSegmentRep(const string& name, ManagerImpl *manager, Network::Ptr n, Ptr<Segment> s) :
        SegmentRep(name, manager, n)
    {
        segment_ = s;
    }
};

string SegmentRep::attribute(const string& name) {
    if(name == "source"){
        Location::Ptr src = segment_->source();
        if (!src) return "";
        return src->name();
    }
    else if (name == "length"){
       Mile m = segment_->length();
       return m.stringValue();
    }
    else if (name == "return segment"){
        Segment::Ptr ret = segment_->returnSegment();
        if (!ret) return "";
        return ret->name();
    }
    else if (name == "difficulty"){
        Difficulty diff = segment_ -> difficulty();
        return diff.stringValue();
    }
    else if (name == "expedite support"){
        Segment::ExpediteSupport es = segment_->expediteSupport();
        if (es == Segment::expediteSupported()) return "yes";
        if (es == Segment::expediteNotSupported()) return "no";
    }
    else if (name == "Shipments Received"){
        ShipmentCount s = segment_ -> shipmentsReceived();
        return s.stringValue();
    }
    else if (name == "Shipments Refused"){
        ShipmentCount s = segment_ -> shipmentsRefused();
        return s.stringValue();
    }
    else if (name == "Capacity"){
        ShipmentCount c = segment_ -> capacity();
        return c.stringValue();
    }
    
    return "";
}


void SegmentRep::attributeIs(const string& name, const string& v) {
    if(name == "source") {
        if (v==""){
            segment_->sourceIs(Location::Ptr());
        }
        else{
            Location::Ptr loc = network_->location(v);
            if (loc) {
                
                segment_->sourceIs(loc);
            }
        }
    }
    else if (name == "length"){
       float m = atof(v.c_str());
       if (m < 0) return;
       Mile mi = Mile(m);
       segment_->lengthIs(mi);
    }
    else if (name == "return segment"){
        Segment::Ptr seg = network_ -> segment(v);
        segment_->returnSegmentIs(seg);
    }
    else if (name == "difficulty"){
        float d = atof(v.c_str());
        if (d < 1.f || d > 5.f) return;
        Difficulty diff = Difficulty(d);
        segment_->difficultyIs(diff);
    }
    else if (name == "Capacity"){
        int c = atoi(v.c_str());
        if (c < 0) return;
        ShipmentCount count = ShipmentCount(c);
        segment_->capacityIs(count);

    }
    else if (name == "expedite support"){
        if (v == "yes" && segment_->expediteSupport() == Segment::expediteNotSupported()) {
            network_->expediteSupportIs(segment_->name(), Segment::expediteSupported());
        }
        if (v == "no" && segment_->expediteSupport() == Segment::expediteSupported()){
            network_->expediteSupportIs(segment_->name(), Segment::expediteNotSupported());
        }    
    }

}


//-------------------------STATS--------------------------------------------

class StatsRep : public Instance {
public:
    StatsRep(const string& name, ManagerImpl* manager, Ptr<Statistics> s) :
        Instance(name), manager_(manager)
    {
        statistics_ = s;

    }
    string attribute(const string& name);
    void attributeIs(const string& name, const string& v) {
        return;
    }
    ~StatsRep(){
        //do nothing
    }
private:
    Ptr<ManagerImpl> manager_;
    Ptr<Statistics> statistics_;
};


string StatsRep::attribute(const string& name){
    int v = -1;
    if (name == "Customer"){
        v = statistics_ -> numCustomers(); 
    }
    else if (name == "Port"){
        v = statistics_ -> numPorts();
    }
    else if (name == "Truck terminal"){
        v = statistics_ -> numTerminals(Segment::truck());
    }
    else if (name == "Boat terminal"){
        v = statistics_ -> numTerminals(Segment::boat());
    }
    else if (name == "Plane terminal"){
        v = statistics_ -> numTerminals(Segment::plane());
    }
    else if (name == "Truck segment"){
        v = statistics_ -> numSegments(Segment::truck());
    }
    else if (name == "Boat segment"){
        v = statistics_ -> numSegments(Segment::boat());
    }
    else if (name == "Plane segment"){
        v = statistics_ -> numSegments(Segment::plane());
    }
    if (v!= -1){
        return NumberConverter<size_t>::toString(v);
    }
    else if (name == "expedite percentage"){
        float w = statistics_ -> percentExpeditedSegments();
        return NumberConverter<float>::toString(w);
    }
    return "";
}




//-----------------CONNECTIVITY------------------------------------------------


class ConnRep : public Instance {
public:
    ConnRep(const string& name, ManagerImpl* manager, Network::Ptr n, Ptr<Connectivity> c) :
        Instance(name), manager_(manager)
    {
        connectivity_ = c;
        network_ = n;
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v) {
        
    }

private:
    void parseConstraints(string &c);
    Ptr<Network> network_;
    Ptr<ManagerImpl> manager_;
    Ptr<Connectivity> connectivity_;
};

string getTask(string n){
    if (n.length() < 7) {
        cerr<<"ConnRep::attribute() Input too short"<<endl;
        return "";
    }
    return n.substr(0, 7);
}

string getValue(string c, int &i, string constraint){
    i = constraint.length();
    string value;
    value = c.substr(i + 1, c.find(' ', i+1) - i - 1);
    return value;
}


void ConnRep::parseConstraints(string &c){
    string constraint = c.substr(0, c.find(' '));
    int i;
    if (constraint == "distance"){
        string value = getValue(c, i, constraint);
        float v = atof(value.c_str());
        i += value.length() + 1;
        connectivity_->constraintsActiveIs(Connectivity::distance());
        connectivity_->constraintDistanceIs(Mile(v));
    }
    else if (constraint == "expedited"){
        connectivity_->constraintsActiveIs(Connectivity::expedited());
        connectivity_->constraintExpeditedIs(Segment::expediteSupported());
        i = constraint.length();
    }
    else if (constraint == "cost"){
        string value = getValue(c, i, constraint);
        float v = atof(value.c_str());
        i += value.length() + 1;
        connectivity_->constraintsActiveIs(Connectivity::cost());
        connectivity_->constraintCostIs(Dollars(v));
    }
    else if (constraint == "time"){
        string value = getValue(c, i, constraint);
        float v = atof(value.c_str());
        i += value.length() + 1;
        connectivity_->constraintsActiveIs(Connectivity::hours());
        connectivity_->constraintHoursIs(Hours(v));
    }
    else return;
    if(c.length() - i != 0){
        string nextstring = c.substr(i + 1, c.length() - i);
        parseConstraints(nextstring);
    }
}

string getStart(string n){
    string start;
    size_t index = 8;
    while(n[index]!=' '){
        start.append(1, n[index]);
        index ++;
        if (index == n.length()) {
            start ="";
            break;
        }   
    }
    return start;
}

void getStartStop(string n, string &start, string &stop){
    start = getStart(n);
    if(n.length() <= 11 + start.length()){
        cerr<<"ConnRep::attribute() stop value too short";
        stop = "";
    }
    else stop = n.substr(8 + start.length() + 3, n.length());
}

string ConnRep::attribute(const string& name) {
    string returnval = "";
    string task = getTask(name);
    if (task=="connect"){
        string start = "";
        string stop = "";
        getStartStop(name, start, stop);
        connectivity_->constraintsActiveDel();
        if (start== "" || stop=="") return "";
        Location::Ptr strt = network_->location(start);
        Location::Ptr stp = network_->location(stop);
        if (!(strt) || !(stp)) return "";
        connectivity_->constraintStartIs(strt);
        connectivity_->constraintEndIs(stp);
        vector<string> paths = connectivity_->paths(Connectivity::connect());
        for(size_t i = 0; i < paths.size(); i ++){
            string p = paths[i];
            returnval+= p;
        }
        return returnval;
    }
    else if(task == "explore"){
        string start = "";
        string c = "";
        getStartStop(name, start, c);
         if (start== "" ) return "";
        Location::Ptr strt = network_->location(start);
        if (!strt) return "";
        connectivity_->constraintsActiveDel();
        parseConstraints(c);
        connectivity_->constraintStartIs(strt);
        vector<string> paths = connectivity_->paths(Connectivity::explore());
        for(size_t i = 0; i < paths.size(); i ++){
            string p = paths[i];
            returnval+= p;
        }
        return returnval;
    }
    return "";
}


//----------------------FLEET-----------------------------------------

class FleetRep : public Instance {
public:
    FleetRep(const string& name, ManagerImpl* manager, Ptr<Fleet> f) :
        Instance(name), manager_(manager)
    {
        fleet_ = f;
    }
    string attribute(const string& name);
    void attributeIs(const string& name, const string& v);
    Ptr<Fleet> fleet(){ return fleet_; }

private:
    Ptr<ManagerImpl> manager_;
    Ptr<Fleet> fleet_;
    void getModeAndProperty(const string& name, string &mode, string& property);
};

void FleetRep::getModeAndProperty(const string& name, string& mode, string& property){
    size_t commaindex = name.find(',');
    if (commaindex==string::npos){
        cerr<<"bad input"<<endl;
        return;
    }
    mode = name.substr(0, commaindex);
    property = name.substr(commaindex + 2, name.length());
}

string FleetRep::attribute(const string& name){
    string mode, property;
    getModeAndProperty(name, mode, property);

    Segment::Mode m;
    if (mode == "Truck"){
        m = Segment::truck();
    } else if (mode == "Boat"){
        m = Segment::boat();
    } else if (mode == "Plane"){
        m = Segment::plane();
    } else {
        cerr<<"bad input"<<endl;
        return "";
    }

    if (property=="speed"){
        return (fleet_ -> speed(m)).stringValue();
    }else if (property == "cost"){
        return fleet_ -> costPerMile(m).stringValue();
    }else if (property== "capacity"){
        return fleet_ -> capacity(m).stringValue();
    }else{
        cerr<<"bad input"<<endl;
        return "";
    }
}

void FleetRep::attributeIs(const string& name, const string& v) {
    string mode, property;
    getModeAndProperty(name, mode, property);

    Segment::Mode m;
    if (mode == "Truck"){
        m = Segment::truck();
    } else if (mode == "Boat"){
        m = Segment::boat();
    } else if (mode == "Plane"){
        m = Segment::plane();
    } else {
        cerr<<"bad input"<<endl;
        return;
    }

    if (property=="speed"){
        float f = atof(v.c_str());
        if (f < 0) return;
        MilesPerHour mph = MilesPerHour(f);
        fleet_ -> speedIs(m, mph);
    }else if (property == "cost"){
        float f = atof(v.c_str());
        if (f < 0) return;
        Dollars d = Dollars(f);
        fleet_ -> costPerMileIs(m, d);
    }else if (property== "capacity"){
        int c = atoi(v.c_str());
        if (c < 0) return;
        PackageCount p = PackageCount(c);
        fleet_ -> capacityIs(m, p);
    }else{
        cerr<<"bad input"<<endl;
    }
}

//---------------------MANAGER-----------------------------------------------

ManagerImpl::ManagerImpl() : network_(Network::NetworkNew("network"))
{

}


Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {
    if (instance(name)) return NULL;
    if(!fleet_){
        Ptr<Fleet> fleet = network_->fleetNew("fleet");
        fleet_ = new FleetRep("fleet", this, fleet);
        instance_["fleet"] = fleet_;
    }
    if(!stats_){
        Ptr<Statistics> stats = network_->statisticsNew("stats");
        stats->notifierIs(network_);
        stats_ = new StatsRep("stats", this, stats);
        instance_["stats"] = stats_;
    }
    if(!conn_){
        Ptr<Connectivity> conn = network_->connectivityNew("conn");
        conn->fleetIs(fleet_->fleet());
        conn_ = new ConnRep("conn", this, network_, conn);
        instance_["conn"] = conn_;
    }


    if(type == "Customer"){
        Ptr<Location> l = network_->customerNew(name);
        Ptr<CustomerRep> c = new CustomerRep(name, this, l, network_);
        instance_[name] = c;
        return c;
    }
 
    else if(type == "Port"){
        Ptr<Location> l = network_->portNew(name);
        Ptr<PortRep> p = new PortRep(name, this, l, network_);
        instance_[name] = p;
        return p;
    }

    else if (type == "Truck terminal") {
        Ptr<Location> l = network_->terminalNew(name, Segment::truck());
        Ptr<TruckTerminalRep> t = new TruckTerminalRep(name, this, l, network_);
        instance_[name] = t;
        return t;
    }

    else if (type == "Boat terminal"){
        Ptr<Location> l = network_->terminalNew(name, Segment::boat());
        Ptr<BoatTerminalRep> t = new BoatTerminalRep(name, this, l, network_);
        instance_[name] = t;
        return t;
    }

    else if (type == "Plane terminal"){
        Ptr<Location> l = network_->terminalNew(name, Segment::plane());
        Ptr<PlaneTerminalRep> t = new PlaneTerminalRep(name, this, l, network_);
        instance_[name] = t;
        return t;
    }

    else if (type == "Truck segment"){
        Ptr<Segment> seg = network_->segmentNew(name, Segment::truck());
        Ptr<TruckSegmentRep> s = new TruckSegmentRep(name, this, network_, seg);
        instance_[name] = s;
        return s;
    }

    else if (type == "Boat segment"){
        Ptr<Segment> seg = network_->segmentNew(name, Segment::boat());
        Ptr<BoatSegmentRep> s = new BoatSegmentRep(name, this, network_, seg);
        instance_[name] = s;
        return s;
    }

    else if (type == "Plane segment"){
        Ptr<Segment> seg = network_->segmentNew(name, Segment::plane());
        Ptr<PlaneSegmentRep> s = new PlaneSegmentRep(name, this, network_, seg);
        instance_[name] = s;
        return s;
    }

    else if (type == "Stats"){
        instance_[name] = stats_;
        return stats_;
    }

    else if (type == "Conn"){
        instance_[name] = conn_;
        return conn_;
    }

    else if (type == "Fleet"){
        instance_[name] = fleet_;
        return fleet_;
    }
    return NULL;
}



Ptr<Instance> ManagerImpl::instance(const string& name) {
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);

    return t == instance_.end() ? Ptr<Instance>() : (*t).second;

}

void ManagerImpl::instanceDel(const string& name) {
    Ptr<Instance> entityToDel = instance(name);
    instance_.erase(name);
    entityToDel->referencesDec(entityToDel->references());
}



} /* end namespace */

/*
 * This is the entry point for your library.
 * The client program will call this function to get a handle
 * on the Instance::Manager object, and from there will use
 * that object to interact with the middle layer (which will
 * in turn interact with the engine layer).
 */
Ptr<Instance::Manager> shippingInstanceManager() {
    return new Shipping::ManagerImpl();
}