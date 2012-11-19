#include "gtest/gtest.h"
#include "Engine.h"
#include "Instance.h"
#include <iostream>

using namespace Shipping;

class LocationRepTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		manager = shippingInstanceManager();
	    customer1 = manager->instanceNew("customer1", "Customer");
    	port1 = manager->instanceNew("port1", "Port");  
	    terminal1 = manager->instanceNew("terminal1", "Boat terminal");
	    terminal2 = manager->instanceNew("terminal1", "Plane terminal");
	    terminal3 = manager->instanceNew("terminal1", "Truck terminal");      

	}
	
	Ptr<Instance::Manager> manager;
	Ptr<Instance> port1;
	Ptr<Instance> terminal1, terminal2, terminal3;
	Ptr<Instance> customer1;

};

TEST_F(LocationRepTest, InstanceNew) {
	EXPECT_EQ(manager->instance("customer1"), customer1);
	EXPECT_EQ(manager->instance("port1"), port1);
	EXPECT_EQ(manager->instance("terminal1"), terminal1);
	EXPECT_EQ(manager->instance("terminal2"), terminal2);
	EXPECT_EQ(manager->instance("terminal3"), terminal3);
		
}

class SegmentRepTest : public ::testing::Test {





};

class FleetRepTest : public ::testing::Test {






};

class StatsRepTest : public ::testing::Test {






};

class ConnRepTest : public ::testing::Test {






};