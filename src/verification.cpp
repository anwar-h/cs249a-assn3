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
	segments[0]->attributeIs("source", "customer1");
	segments[1]->attributeIs("source", "terminal1");
	segments[0]->attributeIs("return segment", "segment1r");
	segments[0]->attributeIs("Capacity", "5");
	segments[1]->attributeIs("Capacity", "5");

	segments[2]->attributeIs("length", "2");
	segments[3]->attributeIs("length", "2");
	segments[2]->attributeIs("source", "terminal1");
	segments[3]->attributeIs("source", "terminal2");
	segments[2]->attributeIs("return segment", "segment2r");
	segments[2]->attributeIs("Capacity", "9");
	segments[3]->attributeIs("Capacity", "9");


	segments[4]->attributeIs("length", "1");
	segments[5]->attributeIs("length", "1");
	segments[4]->attributeIs("source", "terminal2");
	segments[5]->attributeIs("source", "customer2");
	segments[4]->attributeIs("return segment", "segment3r");
	segments[4]->attributeIs("Capacity", "8");
	segments[5]->attributeIs("Capacity", "8");


	segments[6]->attributeIs("length", "4");
	segments[7]->attributeIs("length", "4");
	segments[6]->attributeIs("source", "customer1");
	segments[7]->attributeIs("source", "terminal3");
	segments[6]->attributeIs("return segment", "segment4r");
	segments[6]->attributeIs("Capacity", "10");
	segments[7]->attributeIs("Capacity", "10");

	segments[8]->attributeIs("length", "5");
	segments[9]->attributeIs("length", "5");
	segments[8]->attributeIs("source", "terminal3");
	segments[9]->attributeIs("source", "customer2");
	segments[8]->attributeIs("return segment", "segment5r");
	segments[8]->attributeIs("Capacity", "8");
	segments[9]->attributeIs("Capacity", "8");


//	manager->instance("conn")->attributeIs("routing algorithm", "BFS");
	manager->instance("conn")->attributeIs("routing algorithm", "dijkstra");

	locs[0]->attributeIs("Transfer Rate", "144");
	locs[0]->attributeIs("Shipment Size", "400");
	locs[0]->attributeIs("Destination", "customer2");

	Activity::Manager::Ptr activityManager = activityManagerInstance(manager->network());
	//REAL TIME ACTIVITY MANAGER.  COMMENT OUT THE PREVIOUS LINE AND UNCOMMENT THE LINE BELOW TO ACTIVATE IT.
//	Activity::Manager::Ptr activityManager = realTimeManagerInstance(manager->network());
	activityManager->nowIs(10.0);
	cout<<manager->instance("stats")->attribute("shipment output") << endl;


	activityManager->nowIs(24.0);
 	cout<<manager->instance("stats")->attribute("shipment output") << endl;
 	
 	activityManager->nowIs(40.0);
 	cout<<manager->instance("stats")->attribute("shipment output") << endl;
 	
 	activityManager->nowIs(60.0);
 	cout<<manager->instance("stats")->attribute("shipment output") << endl;


	cout<<manager->instance("stats")->attribute("stats output");

}
catch(Fwk::Exception e){
	cout << e.what() << endl;
}




  return 0;
}

