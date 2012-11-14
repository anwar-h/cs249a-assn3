#include "gtest/gtest.h"
#include "Engine.h"

class SegmentTest : public ::testing::Test {
protected:
	typedef Shipping::Mile Mile;
	typedef Shipping::Difficulty Difficulty;
	typedef Shipping::MilesPerHour MilesPerHour;
	typedef Shipping::PackageCount PackageCount;
	typedef Shipping::Dollars Dollars;


	typedef Shipping::Segment Segment;
	typedef Shipping::Location Location;
	typedef Segment::Mode Mode;
	typedef Segment::ExpediteSupport ExpediteSupport;

	virtual void SetUp() {
		truck = Segment::truck();
		boat = Segment::boat();
		plane = Segment::plane();
		expediteSupported = Segment::expediteSupported();
		expediteNotSupported = Segment::expediteNotSupported();

		seg1 = Segment::SegmentNew("truckSeg", truck);
		seg2 = Segment::SegmentNew("boatSeg", boat);
		seg3 = Segment::SegmentNew("planeSeg", plane);

		loc1 = Location::LocationNew("loc1", Location::customer());
		loc2 = Location::LocationNew("loc2", Location::port());
		loc3 = Location::LocationNew("loc3", Location::terminal());
	}
	
	Segment::Mode truck;
	Segment::Mode boat;
	Segment::Mode plane;
	Segment::ExpediteSupport expediteSupported;
	Segment::ExpediteSupport expediteNotSupported;

	Segment::Ptr seg1, seg2, seg3;
	Location::Ptr loc1, loc2, loc3;
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
	EXPECT_EQ(Mile(0), seg1->length());
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
	EXPECT_EQ(loc1, seg1->source());
	seg2->sourceIs(loc2);
	EXPECT_EQ(loc2, seg2->source());
	seg3->sourceIs(loc3);
	EXPECT_EQ(loc3, seg3->source());
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

TEST_F(SegmentTest, ReturnSegmentAttr) {
	seg1->returnSegmentIs(seg2);
	EXPECT_EQ(seg2, seg1->returnSegment());
	EXPECT_EQ(seg1, seg2->returnSegment());
}

TEST_F(SegmentTest, ReturnSegmentSwitch) {
	seg1->returnSegmentIs(seg2);
	EXPECT_EQ(seg2, seg1->returnSegment());
	EXPECT_EQ(seg1, seg2->returnSegment());

	seg3->returnSegmentIs(seg1);
	EXPECT_EQ(seg1, seg3->returnSegment());
	EXPECT_EQ(seg3, seg1->returnSegment());
	EXPECT_EQ(Segment::Ptr(), seg2->returnSegment());
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

TEST_F(SegmentTest, SourceDestruction) {
	// when source is destroyed, this segment gets destroyed
	EXPECT_EQ(1,0);
}

TEST_F(SegmentTest, ReturnSegmentDestruction) {
	// when return segment gets destroyed
	//seg1->returnSegmentIs(seg2);

	// when we get destroyed
	EXPECT_EQ(1,0);
}

/*

// Test tissue creation
TEST(InfectionSimulationTest, TissueCreation) {
	InfectionSimulation sim;
	string tissueName = "tissue1";
	sim.tissueNew(tissueName);
	Tissue::Ptr t = sim.tissue(tissueName);
	EXPECT_EQ(tissueName, t->name());
	size_t numCells = t->cells();
	EXPECT_EQ(ZERO, numCells);
}

// Test tissue reactor creation
TEST(TissueReactor, TissueReactorCreation) {
	InfectionSimulation sim;
	string tissueName = "tissue1";
	sim.tissueNew(tissueName);
	Tissue::Ptr t = sim.tissue(tissueName);
	TissueReactor *tr = sim.tissueReactor(tissueName);
	TissueReactor *null = NULL;
	EXPECT_NE(null, tr);
	Tissue::PtrConst notifier = tr->notifier();
	EXPECT_EQ(tissueName, notifier->name());
}

// Test cytotoxic cell creation
TEST(CellCreation, CytotoxicCellCreation) {
	InfectionSimulation sim;
	string tissueName = "tissue1";
	sim.tissueNew(tissueName);
	Cell::Coordinates loc;
	loc.x = 10;
	loc.y = 11;
	loc.z = -30;
	Tissue::Ptr t = sim.tissue(tissueName);
	Cell::Ptr cell = sim.tissueCellNew(t, Cell::cytotoxicCell(), loc);
	EXPECT_EQ(loc.x, cell->location().x);
	EXPECT_EQ(loc.y, cell->location().y);
	EXPECT_EQ(loc.z, cell->location().z);
	EXPECT_EQ(Cell::cytotoxicCell(), cell->cellType());
	EXPECT_EQ(Cell::healthy(), cell->health());
	EXPECT_NE(Cell::Ptr().ptr(), t->cell(loc).ptr());
	CellMembrane::Side sides[6] = {CellMembrane::north(), CellMembrane::east(), CellMembrane::south(),
 				CellMembrane::west(), CellMembrane::up(), CellMembrane::down()};
	for(int i = 0; i < 6; i++) {
		Cell::Ptr c = t->cell(loc);
		CellMembrane::Ptr m = c->membrane(sides[i]);
		EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
		EXPECT_EQ(AntibodyStrength(100), m->antibodyStrength());
	}
}

// Test helper cell creation
TEST(CellCreation, HelperCellCreation) {
	InfectionSimulation sim;
	string tissueName = "tissue1";
	sim.tissueNew(tissueName);
	Cell::Coordinates loc;
	loc.x = 20;
	loc.y = 21;
	loc.z = -10;
	Tissue::Ptr t = sim.tissue(tissueName);
	Cell::Ptr cell = sim.tissueCellNew(t, Cell::helperCell(), loc);
	EXPECT_EQ(loc.x, cell->location().x);
	EXPECT_EQ(loc.y, cell->location().y);
	EXPECT_EQ(loc.z, cell->location().z);
	EXPECT_EQ(Cell::helperCell(), cell->cellType());
	EXPECT_EQ(Cell::healthy(), cell->health());
	EXPECT_NE(Cell::Ptr().ptr(), t->cell(loc).ptr());
	CellMembrane::Side sides[6] = {CellMembrane::north(), CellMembrane::east(), CellMembrane::south(),
	 				CellMembrane::west(), CellMembrane::up(), CellMembrane::down()};
	for(int i = 0; i < 6; i++) {
		Cell::Ptr c = t->cell(loc);
		CellMembrane::Ptr m = c->membrane(sides[i]);
		EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
		EXPECT_EQ(AntibodyStrength(0), m->antibodyStrength());
	}
}

class TissueReactorTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		// Define commonly used variables
		healthy = Cell::healthy();
		infected = Cell::infected();
		cytotoxic = Cell::cytotoxicCell();
		helper = Cell::helperCell();
		loc.x = loc.y = loc.z = 0;

		// Set the tissue names
		tissueName1 = "tissue1";
		tissueName2 = "tissue2";
		tissueName3 = "tissue3";

		// Create new tissues
		sim.tissueNew(tissueName1);
		sim.tissueNew(tissueName2);
		sim.tissueNew(tissueName3);

		// Retrieve the tissue reactors
		tr1 = sim.tissueReactor(tissueName1);
		tr2 = sim.tissueReactor(tissueName2);
		tr3 = sim.tissueReactor(tissueName3);
		TissueReactor *null = NULL;
		ASSERT_NE(tr1, null);
		ASSERT_NE(tr2, null);
		ASSERT_NE(tr3, null);

		// Retrieve the tissues from the reactors
		t1 = tr1->notifier();
		t2 = tr2->notifier();
		t3 = tr3->notifier();
		ASSERT_NE(t1, Tissue::Ptr());
		ASSERT_NE(t2, Tissue::Ptr());
		ASSERT_NE(t3, Tissue::Ptr());

		// Add cells to tissue 2
		Cell::Coordinates cellLoc;
		cellLoc.x = cellLoc.y = cellLoc.z = 0;
		numHealthyCells = 10;
		for(size_t i = 0; i < numHealthyCells; i++) {
			sim.tissueCellNew(t2, helper, cellLoc);
			cellLoc.x++;
			sim.tissueCellNew(t2, cytotoxic, cellLoc);
			cellLoc.y++;
		}

		// Add infected cells to tissue 3
		numInfectedCells = 7;
		cellLoc.x = cellLoc.y = cellLoc.z = 0;
		for(size_t i = 0; i < numInfectedCells; i++) {
			Cell::Ptr helperCell = sim.tissueCellNew(t3, helper, cellLoc);
			ASSERT_NE(helperCell.ptr(), Cell::Ptr().ptr());
			helperCell->healthIs(infected);
			tr3->cellIsInfected(helper);
			cellLoc.x++;
			Cell::Ptr cytotoxicCell = sim.tissueCellNew(t3, cytotoxic, cellLoc);
			ASSERT_NE(cytotoxicCell.ptr(), Cell::Ptr().ptr());
			cytotoxicCell->healthIs(infected);
			tr3->cellIsInfected(cytotoxic);
			cellLoc.y++;
		}
	}

	Cell::HealthId healthy;
	Cell::HealthId infected;
	Cell::CellType cytotoxic;
	Cell::CellType helper;
	Cell::Coordinates loc;

	InfectionSimulation sim;
	string tissueName1, tissueName2, tissueName3;
	Tissue::Ptr t1, t2, t3;
	size_t numHealthyCells, numInfectedCells;
	TissueReactor *tr1, *tr2, *tr3;
};

TEST_F(TissueReactorTest, InitialState) {
	size_t cytotoxicHealthy = tr1->numCytotoxicCells(healthy);
	size_t cytotoxicInfected = tr1->numCytotoxicCells(infected);
	size_t helperHealthy = tr1->numHelperCells(healthy);
	size_t helperInfected = tr1->numHelperCells(infected);
	size_t totalCytotoxic = tr1->numCells(cytotoxic);
	size_t totalHelper = tr1->numCells(helper);
	EXPECT_EQ(ZERO, cytotoxicHealthy);
	EXPECT_EQ(ZERO, cytotoxicInfected);
	EXPECT_EQ(ZERO, helperHealthy);
	EXPECT_EQ(ZERO, helperInfected);
	EXPECT_EQ(ZERO, totalCytotoxic);
	EXPECT_EQ(ZERO, totalHelper);
}

TEST_F(TissueReactorTest, LogHealthyCellCreation) {
	size_t cytotoxicHealthy = tr2->numCytotoxicCells(healthy);
	size_t cytotoxicInfected = tr2->numCytotoxicCells(infected);
	size_t helperHealthy = tr2->numHelperCells(healthy);
	size_t helperInfected = tr2->numHelperCells(infected);
	size_t totalCytotoxic = tr2->numCells(cytotoxic);
	size_t totalHelper = tr2->numCells(helper);
	EXPECT_EQ(numHealthyCells, cytotoxicHealthy);
	EXPECT_EQ(ZERO, cytotoxicInfected);
	EXPECT_EQ(numHealthyCells, helperHealthy);
	EXPECT_EQ(ZERO, helperInfected);
	EXPECT_EQ(numHealthyCells, totalCytotoxic);
	EXPECT_EQ(numHealthyCells, totalHelper);
}

TEST_F(TissueReactorTest, LogInfectedCellCreation) {
	size_t cytotoxicHealthy = tr3->numCytotoxicCells(healthy);
	size_t cytotoxicInfected = tr3->numCytotoxicCells(infected);
	size_t helperHealthy = tr3->numHelperCells(healthy);
	size_t helperInfected = tr3->numHelperCells(infected);
	size_t totalCytotoxic = tr3->numCells(cytotoxic);
	size_t totalHelper = tr3->numCells(helper);
	EXPECT_EQ(ZERO, cytotoxicHealthy);
	EXPECT_EQ(numInfectedCells, cytotoxicInfected);
	EXPECT_EQ(ZERO, helperHealthy);
	EXPECT_EQ(numInfectedCells, helperInfected);
	EXPECT_EQ(numInfectedCells, totalCytotoxic);
	EXPECT_EQ(numInfectedCells, totalHelper);
}

TEST_F(TissueReactorTest, LogHealthyCellDeletion) {
	Tissue::CellIterator itr = t2->cellIter();
	size_t cyto_i = 0, help_i = 0;
	size_t cytotoxicHealthy, cytotoxicInfected, helperHealthy,
			helperInfected, totalCytotoxic, totalHelper;
	while (itr.ptr()) {
		Cell::Ptr cell = itr.ptr();
		if (cell->cellType() == cytotoxic) {
			cyto_i++;
		}
		else if (cell->cellType() == helper) {
			help_i++;
		}
		t2->cellDel(cell->name());
		cytotoxicHealthy = tr2->numCytotoxicCells(healthy);
		cytotoxicInfected = tr2->numCytotoxicCells(infected);
		helperHealthy = tr2->numHelperCells(healthy);
		helperInfected = tr2->numHelperCells(infected);
		totalCytotoxic = tr2->numCells(cytotoxic);
		totalHelper = tr2->numCells(helper);
		EXPECT_EQ(numHealthyCells - cyto_i, cytotoxicHealthy);
		EXPECT_EQ(ZERO, cytotoxicInfected);
		EXPECT_EQ(numHealthyCells - help_i, helperHealthy);
		EXPECT_EQ(ZERO, helperInfected);
		EXPECT_EQ(numHealthyCells - cyto_i, totalCytotoxic);
		EXPECT_EQ(numHealthyCells - help_i, totalHelper);
		++itr;
	}
}

TEST_F(TissueReactorTest, LogInfectedCellDeletion) {
	Tissue::CellIterator itr = t3->cellIter();
	size_t cyto_i = 0, help_i = 0;
	size_t cytotoxicHealthy, cytotoxicInfected, helperHealthy,
			helperInfected, totalCytotoxic, totalHelper;
	while (itr.ptr()) {
		Cell::Ptr cell = itr.ptr();
		if (cell->cellType() == cytotoxic) {
			cyto_i++;
		}
		else if (cell->cellType() == helper) {
			help_i++;
		}
		t3->cellDel(cell->name());
		cytotoxicHealthy = tr3->numCytotoxicCells(healthy);
		cytotoxicInfected = tr3->numCytotoxicCells(infected);
		helperHealthy = tr3->numHelperCells(healthy);
		helperInfected = tr3->numHelperCells(infected);
		totalCytotoxic = tr3->numCells(cytotoxic);
		totalHelper = tr3->numCells(helper);
		EXPECT_EQ(ZERO, cytotoxicHealthy);
		EXPECT_EQ(numInfectedCells - cyto_i, cytotoxicInfected);
		EXPECT_EQ(ZERO, helperHealthy);
		EXPECT_EQ(numInfectedCells - help_i, helperInfected);
		EXPECT_EQ(numInfectedCells - cyto_i, totalCytotoxic);
		EXPECT_EQ(numInfectedCells - help_i, totalHelper);
		++itr;
	}
}

class CellTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		// Define commonly used variables
		healthy = Cell::healthy();
		infected = Cell::infected();
		cytotoxic = Cell::cytotoxicCell();
		helper = Cell::helperCell();
		loc.x = loc.y = loc.z = 0;
		sides[0] = CellMembrane::north();
		sides[1] = CellMembrane::east();
		sides[2] = CellMembrane::south();
 		sides[3] = CellMembrane::west();
 		sides[4] = CellMembrane::up();
 		sides[5] = CellMembrane::down();


		// Set the tissue names
		tissueName1 = "tissue1";
		tissueName2 = "tissue2";
		tissueName3 = "tissue3";

		// Create new tissues
		sim.tissueNew(tissueName1);
		sim.tissueNew(tissueName2);
		sim.tissueNew(tissueName3);

		// Retrieve the tissues from the reactors
		t1 = sim.tissue(tissueName1);
		t2 = sim.tissue(tissueName2);
		t3 = sim.tissue(tissueName3);
		ASSERT_NE(t1, Tissue::Ptr());
		ASSERT_NE(t2, Tissue::Ptr());
		ASSERT_NE(t3, Tissue::Ptr());


		// Add cells to tissue 1
		Cell::Coordinates cellLoc;
		cellLoc.x = cellLoc.y = cellLoc.z = 0;
		numHealthyCells = 8;
		for(size_t i = 0; i < numHealthyCells; i++) {
			sim.tissueCellNew(t1, helper, cellLoc);
			cellLoc.x++;
			sim.tissueCellNew(t1, cytotoxic, cellLoc);
			cellLoc.y++;
		}

		// Add infected cells to tissue 2
		numInfectedCells = 9;
		cellLoc.x = cellLoc.y = cellLoc.z = 0;
		for(size_t i = 0; i < numInfectedCells; i++) {
			Cell::Ptr helperCell = sim.tissueCellNew(t2, helper, cellLoc);
			ASSERT_NE(helperCell.ptr(), Cell::Ptr().ptr());
			helperCell->healthIs(infected);
			cellLoc.x++;
			Cell::Ptr cytotoxicCell = sim.tissueCellNew(t2, cytotoxic, cellLoc);
			ASSERT_NE(cytotoxicCell.ptr(), Cell::Ptr().ptr());
			cytotoxicCell->healthIs(infected);
			cellLoc.y++;
		}
	}

	void deleteAllCellsInTissue(Tissue::Ptr &tissue) {
		Tissue::CellIterator itr = tissue->cellIter();
		while(itr.ptr()) {
			Cell *curr = itr.ptr();
			tissue->cellDel(curr->name());
			++itr;
		}
	}

	Cell::HealthId healthy;
	Cell::HealthId infected;
	Cell::CellType cytotoxic;
	Cell::CellType helper;
	Cell::Coordinates loc;

	CellMembrane::Side sides[6];

	InfectionSimulation sim;
	string tissueName1, tissueName2, tissueName3;
	Tissue::Ptr t1, t2, t3;
	size_t numHealthyCells, numInfectedCells;
	TissueReactor *tr1, *tr2, *tr3;
};


TEST_F(CellTest, CellCreation) {
	Tissue::CellIterator itr = t1->cellIter();
	ASSERT_NE(Cell::Ptr().ptr(), itr.ptr());

	size_t numHelper = 0, numCytotoxic = 0;
	while(itr.ptr()) {
		Cell::Ptr cell = itr.ptr();
		if (cell->cellType() == cytotoxic) {
			numCytotoxic++;
			for(int i = 0; i < 6; i++) {
				CellMembrane::Ptr m = cell->membrane(sides[i]);
				EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
				EXPECT_EQ(AntibodyStrength(100).value(), m->antibodyStrength().value());
			}
		}
		else if (cell->cellType() == helper) {
			numHelper++;
			for(int i = 0; i < 6; i++) {
				CellMembrane::Ptr m = cell->membrane(sides[i]);
				EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
				EXPECT_EQ(AntibodyStrength(0).value(), m->antibodyStrength().value());
			}
		}
		EXPECT_EQ(healthy, cell->health());
		++itr;
	}
	EXPECT_EQ(numHealthyCells, numHelper);
	EXPECT_EQ(numHealthyCells, numCytotoxic);
}

TEST_F(CellTest, CytotoxicCellClone) {
	Cell::Coordinates cytoLoc;
	cytoLoc.x = cytoLoc.y = cytoLoc.z = 4;

	Cell::Ptr cytotoxicOrig = sim.tissueCellNew(t3, cytotoxic, cytoLoc);

	for(size_t i = 0; i < 6; i++) {
		Cell::Ptr cytotoxicClone = sim.tissueCellNewClone(t3, cytoLoc, sides[i]);
		ASSERT_NE(cytotoxicClone.ptr(), Cell::Ptr().ptr());
		EXPECT_EQ(cytotoxicOrig->health(), cytotoxicClone->health());
		EXPECT_NE(cytotoxicOrig->location(), cytotoxicClone->location());
		EXPECT_EQ(Command::directionNew(cytoLoc, sides[i]), cytotoxicClone->location());
		EXPECT_EQ(cytotoxicOrig->cellType(), cytotoxicClone->cellType());

		for(int i = 0; i < 6; i++) {
			CellMembrane::Ptr m = cytotoxicClone->membrane(sides[i]);
			EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
			EXPECT_EQ(AntibodyStrength(100).value(), m->antibodyStrength().value());
		}
	}

	size_t numCellsExpected = 1 + 6;
	EXPECT_EQ(numCellsExpected, t3->cells());
}

TEST_F(CellTest, HelperCellClone) {
	Cell::Coordinates helpLoc;
	helpLoc.x = helpLoc.y = helpLoc.z = 0;

	Cell::Ptr helperOrig = sim.tissueCellNew(t3, helper, helpLoc);

	for(size_t i = 0; i < 6; i++) {
		Cell::Ptr helperClone = sim.tissueCellNewClone(t3, helpLoc, sides[i]);
		ASSERT_NE(helperClone.ptr(), Cell::Ptr().ptr());
		EXPECT_EQ(helperOrig->health(), helperClone->health());
		EXPECT_NE(helperOrig->location(), helperClone->location());
		EXPECT_EQ(Command::directionNew(helpLoc, sides[i]), helperClone->location());
		EXPECT_EQ(helperOrig->cellType(), helperClone->cellType());
	
		for(int i = 0; i < 6; i++) {
			CellMembrane::Ptr m = helperClone->membrane(sides[i]);
			EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
			EXPECT_EQ(AntibodyStrength(0).value(), m->antibodyStrength().value());
		}
	}

	size_t numCellsExpected = 1 + 6;
	EXPECT_EQ(numCellsExpected, t3->cells());
}

TEST_F(CellTest, MultiHelperCellClone) {
	Cell::Coordinates helpLoc;
	helpLoc.x = helpLoc.y = helpLoc.z = 0;

	Cell::Ptr helperOrig = sim.tissueCellNew(t3, helper, helpLoc);
	size_t numClones = 4;
	for(size_t i = 0; i < 6; i++) {
		for(size_t n = 0; n < numClones; n++) {
			sim.tissueCellsNewClone(t3, sides[i]);
		}
		
		Cell::Coordinates coordinates = helpLoc;
		for(size_t k = 0; k < numClones; k++) {
			coordinates = Command::directionNew(coordinates, sides[i]);
			Cell::Ptr cell = t3->cell(coordinates);
			ASSERT_NE(Cell::Ptr().ptr(), cell.ptr());
			EXPECT_EQ(helperOrig->health(), cell->health());
			EXPECT_EQ(helperOrig->cellType(), cell->cellType());
			for(int j = 0; j < 6; j++) {
				CellMembrane::Ptr m = cell->membrane(sides[j]);
				EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
				EXPECT_EQ(AntibodyStrength(0).value(), m->antibodyStrength().value());
			}
		}
		size_t numCellsExpected = 1 + numClones;
		EXPECT_EQ(numCellsExpected, t3->cells());
		deleteAllCellsInTissue(t3);
		helperOrig = sim.tissueCellNew(t3, helper, helpLoc);
	}
}

TEST_F(CellTest, MultiCytotoxicCellClone) {
	Cell::Coordinates cytoLoc;
	cytoLoc.x = cytoLoc.y = cytoLoc.z = 0;

	Cell::Ptr cytotoxicOrig = sim.tissueCellNew(t3, cytotoxic, cytoLoc);
	size_t numClones = 4;
	for(size_t i = 0; i < 6; i++) {
		for(size_t n = 0; n < numClones; n++) {
			sim.tissueCellsNewClone(t3, sides[i]);
		}
		
		Cell::Coordinates coordinates = cytoLoc;
		for(size_t k = 0; k < numClones; k++) {
			coordinates = Command::directionNew(coordinates, sides[i]);
			Cell::Ptr cell = t3->cell(coordinates);
			ASSERT_NE(Cell::Ptr().ptr(), cell.ptr());
			EXPECT_EQ(cytotoxicOrig->health(), cell->health());
			EXPECT_EQ(cytotoxicOrig->cellType(), cell->cellType());
			for(int j = 0; j < 6; j++) {
				CellMembrane::Ptr m = cell->membrane(sides[j]);
				EXPECT_NE(CellMembrane::Ptr().ptr(), m.ptr());
				EXPECT_EQ(AntibodyStrength(100).value(), m->antibodyStrength().value());
			}
		}
		size_t numCellsExpected = 1 + numClones;
		EXPECT_EQ(numCellsExpected, t3->cells());
		deleteAllCellsInTissue(t3);
		cytotoxicOrig = sim.tissueCellNew(t3, cytotoxic, cytoLoc);
	}
}


TEST_F(CellTest, InfectedCellDeletion) {

}
TEST_F(CellTest, AntibodyStrengthSet) {

}

*/




















