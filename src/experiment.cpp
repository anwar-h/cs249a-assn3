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


void SetUpNetwork1(Ptr<Instance::Manager> &manager){


	/* Set up the network */
	vector< Ptr<Instance> > sources;
	vector< Ptr<Instance> > terminals;
	vector< Ptr<Instance> > segs1;
	vector< Ptr<Instance> > segs10;
	vector< Ptr<Instance> > segs100;

	Ptr<Instance> fleet = manager->instanceNew("fleet", "Fleet");
	fleet->attributeIs("Truck, speed", "20");


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

	seg0->attributeIs("length", "50");
	seg1->attributeIs("Capacity", "30");

	for(size_t i = 0; i < segs10.size(); i ++){
		segs10[i]->attributeIs("length", "100");
		segs10[i]->attributeIs("Capacity", "20");
	}
	for(size_t i = 0; i < segs100.size(); i++){
		segs100[i]->attributeIs("length", "200");
		segs100[i]->attributeIs("Capacity", "20");
	}

	//Set shipment stuff:
	for(size_t i = 0; i < sources.size(); i ++){
		sources[i]->attributeIs("Destination", "destcustomer");
		sources[i]->attributeIs("Shipment Size", "100");
		sources[i]->attributeIs("Transfer Rate", "10");
	}
}


void SetUpNetwork2(Ptr<Instance::Manager> &manager){
	/* Set up the network */
	vector< Ptr<Instance> > sources;
	vector< Ptr<Instance> > terminals;
	vector< Ptr<Instance> > segs1;
	vector< Ptr<Instance> > segs10;
	vector< Ptr<Instance> > segs100;

	Ptr<Instance> fleet = manager->instanceNew("fleet", "Fleet");
	fleet->attributeIs("Truck, speed", "20");


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

	seg0->attributeIs("length", "50");
	seg1->attributeIs("Capacity", "30");

	for(size_t i = 0; i < segs10.size(); i ++){
		segs10[i]->attributeIs("length", "100");
		segs10[i]->attributeIs("Capacity", "20");
	}
	for(size_t i = 0; i < segs100.size(); i++){
		segs100[i]->attributeIs("length", "200");
		segs100[i]->attributeIs("Capacity", "20");
	}

	//Set shipment stuff:
	for(size_t i = 0; i < sources.size(); i ++){
		sources[i]->attributeIs("Destination", "destcustomer");
		int shipmentSize = rand()%1000 + 1;
		stringstream s;
		s<<shipmentSize;
		sources[i]->attributeIs("Shipment Size", s.str());
		sources[i]->attributeIs("Transfer Rate", "10");
	}
}


int main(int argc, char *argv[]) {

/*	// CAN ONLY RUN THESE ONE AT A TIME
	Ptr<Instance::Manager> manager1 = shippingInstanceManager();
	//Sets up the network with equal shipments
	SetUpNetwork1(manager1);
 	Activity::Manager::Ptr activityManager1 = activityManagerInstance(manager1->network());


    activityManager1->nowIs(72.0); //let 3 days pass and see what happens...
    cout<<manager1->instance("stats")->attribute("stats output");
*/
    // CAN ONLY RUN THESE ONE AT A TIME
    
    Ptr<Instance::Manager> manager2 = shippingInstanceManager();
	//Sets up the network with random shipments between 1 package and 1000 packages.  
	SetUpNetwork2(manager2);
	Activity::Manager::Ptr activityManager2 = activityManagerInstance(manager2->network());

    activityManager2->nowIs(72.0); //let 3 days pass and see what happens...
    cout<<manager2->instance("stats")->attribute("stats output");

	return 0;



}

