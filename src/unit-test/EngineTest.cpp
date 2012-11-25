#include "gtest/gtest.h"
#include "Engine.h"
#include <iostream>

using namespace Shipping;

class AbstractDataTypes : public ::testing::Test {
protected:
	virtual void SetUp() {

	}

	Mile m1, m2;
	Hours h1, h2;
	Difficulty df1, df2;
	MilesPerHour mph1, mph2;
	PackageCount pc1, pc2;
	Dollars dlrs1, dlrs2;
};

TEST_F(AbstractDataTypes, MileDefault) {
	EXPECT_EQ(0.f, m1.value());
}
TEST_F(AbstractDataTypes, HourDefault) {
	EXPECT_EQ(0.f, h1.value());
}
TEST_F(AbstractDataTypes, DifficultyDefault) {
	EXPECT_EQ(1.f, df1.value());
}
TEST_F(AbstractDataTypes, DifficultyUpperBound) {
	df1 = Difficulty(5.f);
	EXPECT_EQ(5.f, df1.value());
}
TEST_F(AbstractDataTypes, MilesPerHourDefault) {
	EXPECT_EQ(0.f, mph1.value());
}
TEST_F(AbstractDataTypes, PackageCountDefault) {
	size_t zero = 0;
	EXPECT_EQ(zero, pc1.value());
}
TEST_F(AbstractDataTypes, DollarsDefault) {
	EXPECT_EQ(0.f, dlrs1.value());
}



class SegmentTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		truck = Segment::truck();
		boat = Segment::boat();
		plane = Segment::plane();
		expediteSupported = Segment::expediteSupported();
		expediteNotSupported = Segment::expediteNotSupported();

		network = Network::NetworkNew("network");

		seg1 = network->segmentNew("truckSeg", truck);
		seg2 = network->segmentNew("boatSeg", boat);
		seg3 = network->segmentNew("planeSeg", plane);

		loc1 = network->customerNew("loc1");
		loc2 = network->portNew("loc2");
		loc3 = network->terminalNew("loc3", plane);
	}
	
	Segment::Mode truck;
	Segment::Mode boat;
	Segment::Mode plane;
	Segment::ExpediteSupport expediteSupported;
	Segment::ExpediteSupport expediteNotSupported;

	Segment::Ptr seg1, seg2, seg3;
	Location::Ptr loc1, loc2, loc3;
	Network::Ptr network;
};

TEST_F(SegmentTest, ModeTypes) {
	EXPECT_EQ(Segment::truck_, truck);
	EXPECT_EQ(Segment::boat_, boat);
	EXPECT_EQ(Segment::plane_, plane);
}

TEST_F(SegmentTest, ExpediteSupportTypes) {
	EXPECT_EQ(Segment::notSupported_, expediteNotSupported);
	EXPECT_EQ(Segment::supported_, expediteSupported);
	EXPECT_TRUE(expediteSupported);
	EXPECT_FALSE(expediteNotSupported);
}

TEST_F(SegmentTest, InitialState) {
	EXPECT_EQ(truck, seg1->mode());
	EXPECT_EQ(boat, seg2->mode());
	EXPECT_EQ(plane, seg3->mode());
	EXPECT_EQ(Location::Ptr(), seg1->source());
	EXPECT_EQ(Mile(), seg1->length());
	EXPECT_EQ(Segment::Ptr(), seg1->returnSegment());
	EXPECT_EQ(Difficulty(), seg1->difficulty());
	EXPECT_EQ(expediteNotSupported, seg1->expediteSupport());
}

TEST_F(SegmentTest, ModeAttr) {
	seg1->modeIs(truck);
	EXPECT_EQ(truck, seg1->mode());
	seg2->modeIs(boat);
	EXPECT_EQ(boat, seg2->mode());
	seg3->modeIs(plane);
	EXPECT_EQ(plane, seg3->mode());
}

TEST_F(SegmentTest, SourceAttr) {
	seg1->sourceIs(loc1);
	EXPECT_EQ(loc1.ptr(), seg1->source().ptr());
	seg2->sourceIs(loc2);
	EXPECT_EQ(loc2.ptr(), seg2->source().ptr());
	seg3->sourceIs(loc3);
	EXPECT_EQ(loc3.ptr(), seg3->source().ptr());
}

TEST_F(SegmentTest, LengthAttr) {
	Mile m1(434), m2(100.1), m3(432);
	seg1->lengthIs(m1);
	EXPECT_EQ(m1, seg1->length());
	seg2->lengthIs(m2);
	EXPECT_EQ(m2, seg2->length());
	seg3->lengthIs(m3);
	EXPECT_EQ(m3, seg3->length());
}

TEST_F(SegmentTest, ReturnSegmentDiffModes) {
	Segment::Ptr nil;

	seg1->returnSegmentIs(seg2);
	EXPECT_EQ(nil.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(nil.ptr(), seg2->returnSegment().ptr());

	seg1->returnSegmentIs(seg3);
	EXPECT_EQ(nil.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(nil.ptr(), seg3->returnSegment().ptr());

	seg2->returnSegmentIs(seg3);
	EXPECT_EQ(nil.ptr(), seg2->returnSegment().ptr());
	EXPECT_EQ(nil.ptr(), seg3->returnSegment().ptr());

	seg2->returnSegmentIs(seg1);
	EXPECT_EQ(nil.ptr(), seg2->returnSegment().ptr());
	EXPECT_EQ(nil.ptr(), seg1->returnSegment().ptr());

	seg3->returnSegmentIs(seg1);
	EXPECT_EQ(nil.ptr(), seg3->returnSegment().ptr());
	EXPECT_EQ(nil.ptr(), seg1->returnSegment().ptr());

	seg3->returnSegmentIs(seg2);
	EXPECT_EQ(nil.ptr(), seg3->returnSegment().ptr());
	EXPECT_EQ(nil.ptr(), seg2->returnSegment().ptr());
}

TEST_F(SegmentTest, ReturnSegmentTruckMode) {
	seg1->modeIs(truck);
	seg2->modeIs(seg1->mode());
	seg1->returnSegmentIs(seg2);
	EXPECT_EQ(seg2.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(seg1.ptr(), seg2->returnSegment().ptr());
}

TEST_F(SegmentTest, ReturnSegmentBoatMode) {
	seg1->modeIs(boat);
	seg2->modeIs(seg1->mode());
	seg1->returnSegmentIs(seg2);
	EXPECT_EQ(seg2.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(seg1.ptr(), seg2->returnSegment().ptr());
}

TEST_F(SegmentTest, ReturnSegmentPlaneMode) {
	seg1->modeIs(plane);
	seg2->modeIs(seg1->mode());
	seg1->returnSegmentIs(seg2);
	EXPECT_EQ(seg2.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(seg1.ptr(), seg2->returnSegment().ptr());
}

TEST_F(SegmentTest, ReturnSegmentSwitch) {
	seg2->modeIs(seg1->mode());
	seg3->modeIs(seg1->mode());

	seg1->returnSegmentIs(seg2);

	EXPECT_EQ(seg2.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(seg1.ptr(), seg2->returnSegment().ptr());

	seg3->returnSegmentIs(seg1);
	EXPECT_EQ(seg1.ptr(), seg3->returnSegment().ptr());
	EXPECT_EQ(seg3.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(Segment::Ptr(), seg2->returnSegment().ptr());
}

TEST_F(SegmentTest, ReturnSegmentSourceNull) {
	Location::Ptr nil;
	seg2->modeIs(seg1->mode());

	seg1->sourceIs(loc1);
	seg1->returnSegmentIs(seg2);

	EXPECT_EQ(seg2.ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(seg1.ptr(), seg2->returnSegment().ptr());

	seg1->sourceIs(nil);
	EXPECT_EQ(nil.ptr(), seg1->source().ptr());
	EXPECT_EQ(Segment::Ptr().ptr(), seg1->returnSegment().ptr());
	EXPECT_EQ(Segment::Ptr().ptr(), seg2->returnSegment().ptr());
}

TEST_F(SegmentTest, DifficultyAttr) {
	Difficulty d1(1.f), d2(5.f), d3(2.35f);
	seg1->difficultyIs(d1);
	EXPECT_EQ(d1, seg1->difficulty());
	seg2->difficultyIs(d2);
	EXPECT_EQ(d2, seg2->difficulty());
	seg3->difficultyIs(d3);
	EXPECT_EQ(d3, seg3->difficulty());
}

TEST_F(SegmentTest, ExpediteSupportAttr) {
	seg1->expediteSupportIs(expediteSupported);
	EXPECT_EQ(expediteSupported, seg1->expediteSupport());
	seg2->expediteSupportIs(expediteNotSupported);
	EXPECT_EQ(expediteNotSupported, seg2->expediteSupport());
}

TEST_F(SegmentTest, NetworkSourceDel) {
	// when source is destroyed, this segment's source is set to null
	seg1->sourceIs(loc1);
	EXPECT_EQ(loc1.ptr(), seg1->source().ptr());
	seg2->sourceIs(loc2);
	EXPECT_EQ(loc2.ptr(), seg2->source().ptr());
	seg3->sourceIs(loc3);
	EXPECT_EQ(loc3.ptr(), seg3->source().ptr());

	network->customerDel("loc1");
	network->portDel("loc2");
	network->terminalDel("loc3");

	Location::Ptr nil;
	EXPECT_EQ(nil.ptr(), seg1->source().ptr());
	EXPECT_EQ(nil.ptr(), seg2->source().ptr());
	EXPECT_EQ(nil.ptr(), seg3->source().ptr());
}


class LocationTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		truck = Segment::truck();
		boat = Segment::boat();
		plane = Segment::plane();
		expediteSupported = Segment::expediteSupported();
		expediteNotSupported = Segment::expediteNotSupported();

		customer = Location::customer();
		port = Location::port();
		terminal = Location::terminal();

		network = Network::NetworkNew("network");

		stringstream stream;
		for(size_t i = 0; i < 5; i++) {
			stream << i;
			string n = stream.str();
			truckSegs.push_back(network->segmentNew(string("truckSeg") + n, truck));
			boatSegs.push_back(network->segmentNew(string("boatSeg") + n, boat));
			planeSegs.push_back(network->segmentNew(string("planeSeg") + n, plane));
		}

		loc1 = network->customerNew("loc1");
		loc2 = network->portNew("loc2");
		loc3 = network->terminalNew("loc3", truck);
	}
	
	Segment::Mode truck;
	Segment::Mode boat;
	Segment::Mode plane;
	Segment::ExpediteSupport expediteSupported;
	Segment::ExpediteSupport expediteNotSupported;

	Location::LocationType customer;
	Location::LocationType port;
	Location::LocationType terminal;

	vector<Segment::Ptr> truckSegs;
	vector<Segment::Ptr> boatSegs;
	vector<Segment::Ptr> planeSegs;

	Location::Ptr loc1, loc2, loc3;
	Network::Ptr network;
};

TEST_F(LocationTest, LocationTypes) {
	EXPECT_EQ(Location::customer_, customer);
	EXPECT_EQ(Location::port_, port);
	EXPECT_EQ(Location::terminal_, terminal);	
}

TEST_F(LocationTest, LocationTypeAttr) {
	EXPECT_EQ(customer, loc1->locationType());
	EXPECT_EQ(port, loc2->locationType());
	EXPECT_EQ(terminal, loc3->locationType());
}

TEST_F(LocationTest, CustomerLocationSegmentAttr) {
	loc1->segmentIs(truckSegs[0]);
	Segment::PtrConst s = loc1->segment(0);
	EXPECT_EQ(truckSegs[0].ptr(), s.ptr());
}

TEST_F(LocationTest, PortLocationSegmentAttr) {
	loc2->segmentIs(truckSegs[0]);
	Segment::PtrConst s = loc2->segment(0);
	EXPECT_EQ(truckSegs[0].ptr(), s.ptr());
}

TEST_F(LocationTest, TerminalLocationSegmentAttr) {
	loc3->segmentIs(truckSegs[0]);
	Segment::PtrConst s = loc3->segment(0);
	EXPECT_EQ(truckSegs[0].ptr(), s.ptr());
}

TEST_F(LocationTest, SegmentDel) {
	EXPECT_EQ(1, 0);

}
TEST_F(LocationTest, SegmentIteratorBegin) {
	EXPECT_EQ(1, 0);	

}
TEST_F(LocationTest, SegmentIteratorEnd) {
	EXPECT_EQ(1, 0);

}
TEST_F(LocationTest, SegmentIteratorConstBegin) {
	EXPECT_EQ(1, 0);

}
TEST_F(LocationTest, SegmentIteratorConstEnd) {
	EXPECT_EQ(1, 0);

}































































