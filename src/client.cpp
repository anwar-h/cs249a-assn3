#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
    Ptr<Instance::Manager> manager = shippingInstanceManager();
    if (manager == Ptr<Instance::Manager>()) {
        cerr << "Unexpected NULL manager." << endl;
        return 1;
    }


    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");
    Ptr<Instance> nullInstance;
    if (stats == nullInstance) {
        cerr << "Unexpected NULL stats." << endl;
        return 1;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (fleet == nullInstance) {
        cerr << "Unexpected NULL." << endl;
        return 1;
    }
    fleet->attributeIs("Boat, speed", "45");
    fleet->attributeIs("Truck, capacity", "75");
    fleet->attributeIs("Plane, cost", "70");
    cout << "fleet->attribute('Boat, speed'): " << fleet->attribute("Boat, speed") << endl;
    // --- Create instances
    // -- Locations
    // customers
    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");  
    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");  

    // ports
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");  
    Ptr<Instance> port2 = manager->instanceNew("port2", "Port");  

    Ptr<Instance> terminal1 = manager->instanceNew("terminal1", "Boat terminal");      

    if (!customer1 || !customer2) {
        cerr << "Unexpected NULL customer." << endl;
        return 1;
    }
    if (!terminal1) {
        cerr << "Unexpected NULL terminal." << endl;
        return 1;
    }
    if (!port1 || !port2) {
        cerr << "Unexpected NULL port." << endl;
	   return 1;
    }
    // -- Segments
    // boat
    Ptr<Instance> boatSeg1 = manager->instanceNew("boatSeg1", "Boat segment");  
    Ptr<Instance> boatSeg2 = manager->instanceNew("boatSeg2", "Boat segment");  
    Ptr<Instance> boatSeg3 = manager->instanceNew("boatSeg3", "Boat segment");  
    Ptr<Instance> boatSeg4 = manager->instanceNew("boatSeg4", "Boat segment");  
    // truck
    Ptr<Instance> truckSeg1 = manager->instanceNew("truckSeg1", "Truck segment");  
    Ptr<Instance> truckSeg2 = manager->instanceNew("truckSeg2", "Truck segment");  
    Ptr<Instance> truckSeg3 = manager->instanceNew("truckSeg3", "Truck segment");  
    Ptr<Instance> truckSeg4 = manager->instanceNew("truckSeg4", "Truck segment");  
    //plane
    Ptr<Instance> planeSeg1 = manager->instanceNew("planeSeg1", "Plane segment");  
    Ptr<Instance> planeSeg2 = manager->instanceNew("planeSeg2", "Plane segment");  

    if (!boatSeg1 || !boatSeg2 || !boatSeg3 || !boatSeg4 || !truckSeg1 || !truckSeg2 || !truckSeg3 || !truckSeg4
        || !planeSeg1 || !planeSeg2) {
        cerr << "Unexpected NULL segment." << endl;
        return 1;
    }

    // connections
    // customer1 <---> port1
    truckSeg1->attributeIs("source", "customer1");
    truckSeg2->attributeIs("source", "port1");
    truckSeg1->attributeIs("return segment", "truckSeg2");
    cout << "truckSeg1->attribute('source'): " << truckSeg1->attribute("source") << endl;
    
    // customer2 <---> port1
    boatSeg1->attributeIs("source", "customer2");
    boatSeg2->attributeIs("source", "port1");
    boatSeg1->attributeIs("return segment", "boatSeg2");
    cout << "boatSeg1->attribute('return segment'): " << boatSeg1->attribute("return segment") << endl;


     // port2 <---> port1
    planeSeg1->attributeIs("source", "port2");
    planeSeg2->attributeIs("source", "port1");
    planeSeg1->attributeIs("return segment", "planeSeg2");
    cout << "planeSeg1->attribute('return segment'): " << planeSeg1->attribute("return segment") << endl;

     // port2 <---> customer2
    truckSeg4->attributeIs("source", "customer2");
    truckSeg3->attributeIs("source", "port2");
    truckSeg4->attributeIs("return segment", "truckSeg3");
    cout << "truckSeg4->attribute('return segment'): " << truckSeg4->attribute("return segment") << endl;
   
     // boat terminal <---> customer2
    boatSeg4->attributeIs("source", "terminal1");
    boatSeg3->attributeIs("source", "customer2");
    boatSeg4->attributeIs("return segment", "boatSeg3");
    cout << "boatSeg4->attribute('return segment'): " << boatSeg4->attribute("return segment") << endl;


    // -- Segment lengths
    boatSeg1->attributeIs("length", "400");
    boatSeg2->attributeIs("length", "400");
    boatSeg3->attributeIs("length", "600");
    boatSeg4->attributeIs("length", "600");
    truckSeg1->attributeIs("length", "900");
    truckSeg2->attributeIs("length", "900");
    truckSeg3->attributeIs("length", "1000");
    truckSeg4->attributeIs("length", "1000");
    planeSeg1->attributeIs("length", "300");
    planeSeg2->attributeIs("length", "300");
    // -- Segment difficulties
    boatSeg1->attributeIs("difficulty", "1");
    boatSeg2->attributeIs("difficulty", "1");
    boatSeg3->attributeIs("difficulty", "1");
    boatSeg4->attributeIs("difficulty", "1");
    truckSeg1->attributeIs("difficulty", "3");
    truckSeg2->attributeIs("difficulty", "3");
    truckSeg3->attributeIs("difficulty", "1");
    truckSeg4->attributeIs("difficulty", "1");
    planeSeg1->attributeIs("difficulty", "1");
    planeSeg2->attributeIs("difficulty", "1");
    // -- Segment expedite support
    boatSeg1->attributeIs("expedite support", "yes");
    boatSeg2->attributeIs("expedite support", "yes");
    boatSeg3->attributeIs("expedite support", "no");
    boatSeg4->attributeIs("expedite support", "no");
    truckSeg1->attributeIs("expedite support", "yes");
    truckSeg2->attributeIs("expedite support", "yes");
    truckSeg3->attributeIs("expedite support", "yes");
    truckSeg4->attributeIs("expedite support", "yes");
    planeSeg1->attributeIs("expedite support", "yes");
    planeSeg2->attributeIs("expedite support", "yes");
    // -- Connectivity queries
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

    if (conn == nullInstance) {
        cerr << "Unexpected NULL conn." << endl;
        return 1;
    }
    cout << "**** explore customer1 : distance 1500 ****" << endl;
    cout << conn->attribute("explore customer1 : distance 1500") << endl;
    cout << endl;
    
    cout << "*** connect customer2 : customer1 ****" << endl;
    cout << conn->attribute("connect customer2 : customer1") << endl;
    cout << endl;

    cout << "*** connect terminal1 : customer1 ****" << endl;
    cout << conn->attribute("connect terminal1 : customer1") << endl;
    cout << endl;


// -- Statistics queries
    cout << "===== Stats attributes =====" << endl;
    cout << " --- Segments --- " << endl;
    cout << "# Truck segments : " << stats->attribute("Truck segment") << endl;
    cout << "Expediting %     : " << stats->attribute("expedite percentage") << endl;
    cout << " --- Terminals --- " << endl;
    cout << "# Plane terminals: " << stats->attribute("Plane terminal") << endl;
    cout << " --- Ports and customers --- " << endl;
    cout << "# Ports          : " << stats->attribute("Port") << endl;
    cout << endl;

    
    cout<<"deleting things"<<endl;
    manager->instanceDel("terminal1");  
    manager->instanceDel("boatSeg1");

    cout << "customer2 segment 1: should be truckseg4" <<endl;
    cout << customer2->attribute("segment1") << endl;

    cout << "*** connect terminal1 : customer1 ****" << endl;
    cout << conn->attribute("connect terminal1 : customer1") << endl;
    cout << endl;

    
    Ptr<Instance> stats2 = manager->instanceNew("stats2", "Stats");
        // -- Statistics queries
    cout << "===== Stats attributes =====" << endl;
    cout << " --- Segments --- " << endl;
    cout << "# Truck segments : " << stats2->attribute("Truck segment") << endl;
    cout << "Expediting %     : " << stats2->attribute("expedite percentage") << endl;
    cout << " --- Terminals --- " << endl;
    cout << "# Plane terminals: " << stats2->attribute("Plane terminal") << endl;
    cout << " --- Ports and customers --- " << endl;
    cout << "# Ports          : " << stats2->attribute("Port") << endl;


    cerr << "Done!" << endl;

    return 0;
}
