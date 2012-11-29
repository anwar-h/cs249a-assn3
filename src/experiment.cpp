//In addition, set up a shipping network with 100 sources and 1 destination. 
//The destination should be connected to a terminal, which is in turn connected to 10 terminals, 
//each of which is connected to 10 sources. All connections are via truck segments. 
//Have each source send shipments holding 100 packages to the destination at the normal truck speed. 
//Run the simulation for a while.

//Now, reset the simulation and do the same thing, but vary the shipment sizes 
//(use a randomly chosen shipment size for each source) from 1 package to 1,000 packages. 
//Record the results for each case.



#include <iostream>
#include <sstream>
#include <vector>
#include "Instance.h"
#include "ActivityImpl.h"

using namespace std;

int main(int argc, char *argv[]) {
//  try
//  {
    Ptr<Instance::Manager> manager = shippingInstanceManager();

	/* Set up the network */
	vector< Ptr<Instance> > sources;
	vector< Ptr<Instance> > terminals;
	vector< Ptr<Instance> > segs1;
	vector< Ptr<Instance> > segs10;
	vector< Ptr<Instance> > segs100;

	// Locations
    Ptr<Instance> dest = manager->instanceNew("destcustomer", "Customer");
	Ptr<Instance> hub = manager->instanceNew("termhub", "Truck terminal");
	

	Ptr<Instance> seg0 = manager->instanceNew("seg0", "Truck segment");
	Ptr<Instance> seg1 = manager->instanceNew("seg1", "Truck segment");
	seg0->attributeIs("source", "destcustomer");
	seg1->attributeIs("source", "termhub");
	seg0->attributeIs("return segment", "seg1");



	for(int i = 0; i < 10; i++){
		stringstream tname;
		tname << "t" << i;
		terminals.push_back( manager->instanceNew(tname.str(), "Truck terminal") );
		stringstream sname0, sname1;
		sname0 << "s" << i * 2;
		sname1 << "s" << i * 2 + 1;


		segs10.push_back(manager->instanceNew(sname0.str(), "Truck segment"));
		segs10.push_back( manager->instanceNew(sname1.str(), "Truck segment"));
		segs10[i*2]->attributeIs("source", "termhub");
		segs10[i*2 + 1]->attributeIs("source", tname.str());
		segs10[i*2]->attributeIs("return segment", sname1.str());
		

		for (int j = 0; j < 10; j++){
			stringstream cname;
			cname << "scust"<< j + i * 20;
			sources.push_back( manager->instanceNew(cname.str(), "Customer") );
			
			stringstream ssname0, ssname1;
			ssname0 << "sg" << i * 20 + j * 2;
			ssname1 << "sg" << i * 20 + j * 2 + 1;

			segs100.push_back(manager->instanceNew(ssname0.str(), "Truck segment"));
			segs100.push_back(manager->instanceNew(ssname1.str(), "Truck segment"));
			segs100[i*20 + j*2]->attributeIs("source", tname.str());
			segs100[i*20 + j*2 + 1]->attributeIs("source", cname.str());
			segs100[i*20 + j*2]->attributeIs("return segment", ssname1.str());		
		}
	}

	seg0->attribute("length", "50");
	seg1->attribute("Capacity", "30");

	for(size_t i = 0; i < segs10.size(); i ++){
		segs10[i]->attributeIs("length", "100");
		segs10[i]->attributeIs("Capacity", "20");
	}
	for(size_t i = 0; i < segs100.size(); i++){
		segs100[i]->attributeIs("length", "200");
		segs100[i]->attributeIs("Capacity", "20");
	}

/*	cout << sources.size() << " sources" << endl;
	cout << terminals.size() << " terminals" << endl;
	cout << segs10.size() << " segments in the row of 10" << endl;
	cout << segs100.size() << " segments in the row of 100" << endl;
*/
//	
/*	cout << seg0->attribute("return segment")<<endl;
	for(int i = 0; i < segs10.size(); i ++){
		cout<<segs10[i]->attribute("return segment")<<endl;
	}
    for(int i = 0; i < segs100.size(); i++){
    	cout<<segs100[i]->attribute("return segment")<<endl;
    }
*/

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

    Ptr<Instance> fleet = manager->instanceNew("Fleet", "Fleet");
    fleet->attributeIs("Truck speed", "1");
    fleet->attributeIs("Truck capacity", "1");

	// Set some segment (shipment) capacities
	seg[4]->attributeIs("Capacity", "1");
	seg[6]->attributeIs("Capacity", "1");
*/
	/* For groups, you could set routing algorithm here
	 * Note that we are not advocating any particular design
	 * here, but only giving an example of how you might 
	 * set the routing algorithm. You may also use attribute
	 * names other than "routing algorithm" 
	 */
//	Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
//	conn->attributeIs("routing algorithm", "Dijkstra"); 
	// conn->attributeIs("routing algorithm", "Some very cool algorithm worthy of a Turing award");

	/* Switching between real-time and virtual-time managers
	 * can be as simple as simple commenting and uncommenting certain 
	 * statements in the program. You are not required to support fancy 
	 * switching, though it will ease our grading effort (and time needed) 
	 * quite a bit if the switching did not require searching some lines 
	 * in lots of code and recompiling =)
	 *
	 * When you use the real-time manager, there's no need for the client to 
	 * interact directly with the virtual-time manager, since the latter is 
	 * driven as an activity by the real-time manager. 
	 *
	 * Again, the attribute names here are not set in stone. You are free to 
	 * use any names that make sense and follow the attribute-only interface 
	 * design conventions.
	 *
	 * Another thing to notice is that using real-time manager doesn't mean 
	 * you need to simulate an event flow that synchronizes with real-time. 
	 * For example, in the code snippet below, we're setting the elapsed 
	 * number of real seconds to be some value. The manager then sleeps for 
	 * the time difference between the two settings (18 seconds in this case). 
	 * Upon awakening, the 18 seconds is multipled by the scaling factor to get 
	 * the number of virtual hours passed, and every (virtual) activity that 
	 * have been scheduled between those 18 hours are executed in order.
	 *
	 * Thus, the simulation is really a batch processing engine, where the 
	 * batch size is determined by the client's settings of the real/virtual 
	 * times at difference places.
	 */
//    Activity::Manager::Ptr activityManager = activityManagerInstance();
//    activityManager->nowIs(6.0);
//    RealTimeManager::Ptr realTimeManager = realTimeManagerInstance();
//  realTimeManager->realTimePassedIs(6.0);

	// Stop injection activity from the first two customers
//    loc[0]->attributeIs("Transfer Rate", "0");
//    loc[1]->attributeIs("Transfer Rate", "0");

//    activityManager->nowIs(24.0);
//  realTimeManager->realTimePassedIs(18.0);

	/* Print simulation statistics for analysis 
	 * You'll need some numbers to put into your README and for analysis. 
	 * The format is completely up to you, but make sure it is easily 
	 * readable, otherwise we might misunderstand your analysis
	 */
//	printSimStats();
//  }
//  catch(Exception e)
//  {
//	cout << e.what() << endl;
//  }
//  catch(...)
//  {
//  }

  return 0;
}

