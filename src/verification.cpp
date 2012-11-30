//Construct a shipping network with at least four locations, and confirm that shipments move between 
//them as expected. Run tests with different segment capacity values to compare your network under light 
//and heavy congestion. Add a diagram of this network to your README file, and discuss the tests performed. 
//The code for this client should be named verification.cpp.

#include <iostream>
#include <sstream>
#include <vector>
#include "Instance.h"
#include "ActivityImpl.h"

using namespace std;

int main(int argc, char *argv[]) {
try{
	Ptr<Instance::Manager> manager = shippingInstanceManager();
	vector< Ptr<Instance> > locs;
	vector< Ptr<Instance> > segments;

	locs.push_back( manager->instanceNew("customer1", "Customer") );
	locs.push_back( manager->instanceNew("customer2", "Customer") );
	locs.push_back( manager->instanceNew("terminal1", "Boat terminal") );
	locs.push_back( manager->instanceNew("terminal2", "Boat terminal") );
	locs.push_back( manager->instanceNew("terminal3", "Boat terminal") );

	segments.push_back( manager->instanceNew("segment1", "Boat segment") );
	segments.push_back( manager->instanceNew("segment1r", "Boat segment") );
	segments.push_back( manager->instanceNew("segment2", "Boat segment") );
	segments.push_back( manager->instanceNew("segment2r", "Boat segment") );
	segments.push_back( manager->instanceNew("segment3", "Boat segment") );
	segments.push_back( manager->instanceNew("segment3r", "Boat segment") );
	segments.push_back( manager->instanceNew("segment4", "Boat segment") );
	segments.push_back( manager->instanceNew("segment4r", "Boat segment") );
	segments.push_back( manager->instanceNew("segment5", "Boat segment") );
	segments.push_back( manager->instanceNew("segment5r", "Boat segment") );

	segments[0]->attributeIs("length", "3");
	segments[1]->attributeIs("length", "3");
	segments[0]->attributeIs("return segment", "segment1r");

	segments[2]->attributeIs("length", "2");
	segments[3]->attributeIs("length", "2");
	segments[2]->attributeIs("return segment", "segment2r");
	segments[2]->attributeIs("Capacity", "9");
	segments[3]->attributeIs("Capacity", "9");


	segments[4]->attributeIs("length", "1");
	segments[5]->attributeIs("length", "1");
	segments[4]->attributeIs("return segment", "segment3r");
	segments[4]->attributeIs("Capacity", "8");
	segments[5]->attributeIs("Capacity", "8");


	segments[6]->attributeIs("length", "4");
	segments[7]->attributeIs("length", "4");
	segments[6]->attributeIs("return segment", "segment4r");

	segments[8]->attributeIs("length", "5");
	segments[9]->attributeIs("length", "5");
	segments[8]->attributeIs("return segment", "segment5r");
	segments[8]->attributeIs("Capacity", "8");
	segments[9]->attributeIs("Capacity", "8");


	locs[0]->attributeIs("Transfer Rate", "24");
	locs[0]->attributeIs("Shipment Size", "400");
	locs[0]->attributeIs("Destination", "customer2");

	Activity::Manager::Ptr activityManager = activityManagerInstance();
	activityManager->nowIs(24);

	locs[0]->attributeIs("Transfer Rate", "0");
	locs[1]->attributeIs("Transfer Rate", "12");
	locs[1]->attributeIs("Shipment Size", "200");
	locs[1]->attributeIs("Destination", "customer1");

	activityManager->nowIs(48);
}
catch(Fwk::Exception e){
	cout << e.what() << endl;
}
/*
	loc.push_back( manager->instanceNew("customer2", "Customer") );
    loc.push_back( manager->instanceNew("port1", "Port") );
    loc.push_back( manager->instanceNew("tt1", "Truck terminal") );
    loc.push_back( manager->instanceNew("tt2", "Truck terminal") );
    loc.push_back( manager->instanceNew("customer3", "Customer") );

	// Segments
    seg.push_back( manager->instanceNew("ps1", "Plane segment") );
    seg.push_back( manager->instanceNew("ps2", "Plane segment") );
    seg.push_back( manager->instanceNew("bs1", "Boat segment") );
    seg.push_back( manager->instanceNew("bs2", "Boat segment") );
    seg.push_back( manager->instanceNew("ts1", "Truck segment") );
    seg.push_back( manager->instanceNew("ts2", "Truck segment") );
    seg.push_back( manager->instanceNew("ts3", "Truck segment") );
    seg.push_back( manager->instanceNew("ts4", "Truck segment") );
    seg.push_back( manager->instanceNew("ts5", "Truck segment") );
    seg.push_back( manager->instanceNew("ts6", "Truck segment") );
    seg.push_back( manager->instanceNew("ts7", "Truck segment") );
    seg.push_back( manager->instanceNew("ts8", "Truck segment") );

	// Connections...
	seg[0]->attributeIs("source", "customer1");
	seg[1]->attributeIs("source", "port1");
	seg[1]->attributeIs("return segment", "ps1");

	seg[2]->attributeIs("source", "customer2");
	seg[2]->attributeIs("source", "port1");
	seg[3]->attributeIs("return segment", "ps2");

	// And so on...
*/



  return 0;
}

