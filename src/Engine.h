#ifndef ENGINE_H
#define ENGINE_H


#include "fwk/BaseNotifiee.h"
#include "fwk/NamedInterface.h"
#include "fwk/HashMap.h"
#include "fwk/ListRaw.h"
#include "fwk/LinkedList.h"
#include "fwk/LinkedQueue.h"
#include "fwk/Array.h"
#include "fwk/String.h"
#include "Instance.h"
#include "Nominal.h"
#include "ActivityImpl.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <typeinfo>

namespace Shipping {

using namespace std;

template<typename T>
class NumberConverter {
public:
	static string toString(T value)
	{
		stringstream stream;
		if(typeid(float) == typeid(value)) {
			stream.setf(ios::fixed, ios::floatfield);
			stream.precision(2);
			stream << value;
			return stream.str();
		}
		else if (typeid(size_t) == typeid(value)) {
			stream << value;
			string str = stream.str();
			return NumberConverter::fmtSizeT(str);
		}
		stream << value;
		return stream.str();
	}

	static string fmtSizeT(string s)
	{
		return s;
	}
};

class Mile : public Ordinal<Mile, float> {
public:
	Mile() : Ordinal<Mile, float>(0.f) {
		if(value_ < 0.f) throw Fwk::RangeException("value=range()"); 
	}
	Mile(float f) : Ordinal<Mile, float>(f) {
		if(value_ < 0.f) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<float>::toString(value_);
	}
};

class Hours : public Ordinal<Hours, float> {
public:
	Hours() : Ordinal<Hours, float>(0.f) {
		if(value_ < 0.f) throw Fwk::RangeException("value=range()"); 
	}
	Hours(float f) : Ordinal<Hours, float>(f) {
		if(value_ < 0.f) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<float>::toString(value_);
	}
};


class Difficulty : public Ordinal<Difficulty, float> {
public:
	Difficulty() : Ordinal<Difficulty, float>(1.f) {
		if(value_ < 1.f || value_ > 5.f) throw Fwk::RangeException("value=range()"); 
	}
	Difficulty(float f) : Ordinal<Difficulty, float>(f) {
		if(value_ < 1.f || value_ > 5.f) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<float>::toString(value_);
	}
};

class MilesPerHour : public Ordinal<MilesPerHour, float>{
public:
	MilesPerHour() : Ordinal<MilesPerHour, float>(0.f) { 
		if(value_ < 0.f) throw Fwk::RangeException("value=range()");
	}
	MilesPerHour(float f) : Ordinal<MilesPerHour, float>(f) {
		if(value_ < 0.f) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<float>::toString(value_);
	}
};

class PackageCount : public Ordinal<PackageCount, size_t> {
public:
	PackageCount() : Ordinal<PackageCount, size_t>(0) {
		if(value_ < 0) throw Fwk::RangeException("value=range()");
	}
	PackageCount(size_t n) : Ordinal<PackageCount, size_t>(n) {
		if(value_ < 0) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<size_t>::toString(value_);
	}
};

class ShipmentCount : public Ordinal<ShipmentCount, size_t> {
public:
	ShipmentCount() : Ordinal<ShipmentCount, size_t>(0) {
		if(value_ < 0) throw Fwk::RangeException("value=range()");
	}
	ShipmentCount(size_t n) : Ordinal<ShipmentCount, size_t>(n) {
		if(value_ < 0) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<size_t>::toString(value_);
	}
};

class VehicleCount : public Ordinal<VehicleCount, size_t> {
public:
	VehicleCount() : Ordinal<VehicleCount, size_t>(10) {
		if(value_ < 0) throw Fwk::RangeException("value=range()");
	}
	VehicleCount(size_t n) : Ordinal<VehicleCount, size_t>(n) {
		if(value_ < 0) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<size_t>::toString(value_);
	}
};


class Dollars : public Ordinal<Dollars, float> {
public:
	Dollars() : Ordinal<Dollars, float>(0.f) {
		if(value_ < 0.f) throw Fwk::RangeException("value=range()");
	}
	Dollars(float f) : Ordinal<Dollars, float>(f) {
		if(value_ < 0.f) throw Fwk::RangeException("value=range()");
	}

	string stringValue() const {
		return NumberConverter<float>::toString(value_);
	}
};

class Shipment; // forward declared
class Location; // forward declared
class Segment : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Segment> Ptr;
	typedef Fwk::Ptr<Segment const> PtrConst;

	enum Mode {
		truck_ = 0,
		boat_,
		plane_
	};
	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }

	enum ExpediteSupport {
		notSupported_ = 0,
		supported_
	};

	static inline ExpediteSupport expediteSupported() { return supported_; }
	static inline ExpediteSupport expediteNotSupported() { return notSupported_; }

	Mode mode() const { return mode_; }
	static string modeName(Mode m);
	void modeIs(Mode m) {
		mode_ = m;
	}

	Fwk::Ptr<Location> source() const { return source_; }
	void sourceIs(Fwk::Ptr<Location> s);

	Mile length() const { return length_; }
	void lengthIs(Mile l) {
		length_ = l;
	}

	Segment::Ptr returnSegment() const { return return_segment_; }
	void returnSegmentIs(Segment::Ptr &r);

	Difficulty difficulty() const { return difficulty_; }
	void difficultyIs(Difficulty d) {
		difficulty_ = d;
	}

	ExpediteSupport expediteSupport() const { return exp_support_; }
	void expediteSupportIs(ExpediteSupport es) {
		exp_support_ = es;
	}

	void arrivingShipmentIs(Fwk::Ptr<Shipment> &shipment);

	VehicleCount numVehicles() const { return numVehicles_; }
	void numVehiclesIs(VehicleCount vc){
		numVehicles_ = vc;
	}

	PackageCount segmentLoad() const { return segmentLoad_; }
	void segmentLoadIs(PackageCount pc){
		segmentLoad_ = pc;
	}

	ShipmentCount numShipmentsToldToWait() const { return shipments_told_to_wait_; }
	void numShipmentsToldToWaitIs(ShipmentCount c) { shipments_told_to_wait_ = c; }	

	ShipmentCount numShipmentsReceived() const { return shipments_received_; }
	void numShipmentsReceivedIs(ShipmentCount c) { shipments_received_ = c; }

	ShipmentCount numShipmentsRefused() const { return shipments_refused_; }
	void numShipmentsRefusedIs(ShipmentCount c) { shipments_refused_ = c; }

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;

		Fwk::String name() const { return notifier_->name(); }
		Segment::PtrConst notifier() const { return notifier_; }
		bool isNonReferencing() const { return isNonReferencing_; }
		 ~NotifieeConst();

		virtual void notifierIs(const Segment::PtrConst& _notifier);
		virtual void onShipmentArrival(Fwk::Ptr<Shipment> &shipment) {}

		void lrNextIs(NotifieeConst * _lrNext) {
		 lrNext_ = _lrNext;
		}
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }


		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			// decr. refer count to compensate for initial val of 1
			return m;
		}
	protected:
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			isNonReferencing_(false),
			lrNext_(0)
			{}

		bool isNonReferencing_;
		NotifieeConst * lrNext_;
		Segment::PtrConst notifier_;
	};
	class Notifiee : public virtual Segment::NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;

		Segment::PtrConst notifier() const { return NotifieeConst::notifier(); }
		Segment::Ptr notifier() { return const_cast<Segment *>(NotifieeConst::notifier().ptr()); }

		static Notifiee::Ptr NotifieeIs() {
		 Ptr m = new Notifiee();
		 m->referencesDec(1);
		 // decr. refer count to compensate for initial val of 1
		 return m;
		}
	protected:
		Notifiee(): Fwk::NamedInterface::Notifiee() {}
	};

	class SegmentReactor : public Segment::Notifiee {
	public:
		typedef Fwk::Ptr<SegmentReactor> Ptr;
		typedef Fwk::Ptr<SegmentReactor const> PtrConst;

		void onShipmentArrival(Fwk::Ptr<Shipment> &shipment);

		static SegmentReactor::Ptr SegmentReactorNew(const Segment::Ptr &notifier) {
			Ptr m = new SegmentReactor(notifier);
			m->referencesDec(1);
			return m;
		}

	protected:
		SegmentReactor(const Segment::Ptr &notifier):
			Segment::Notifiee(),
			activityManager_(activityManagerInstance())
			{
				notifierIs(notifier);
			}

		Activity::Manager::Ptr activityManager_;
	};

	void segmentReactorIs(SegmentReactor::Ptr reactor) { segmentReactor_ = reactor.ptr(); }
	static Segment::Ptr SegmentNew(Fwk::String name, Mode mode) {
		Ptr m = new Segment(name, mode);
		m->segmentReactorIs( SegmentReactor::SegmentReactorNew(m.ptr()) );
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::Iterator NotifieeIterator;
   	NotifieeIterator notifieeIter() { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }

protected:
	Segment(Fwk::String name, Mode mode);

	void newNotifiee(Segment::NotifieeConst *n) const {
		Segment* me = const_cast<Segment*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee(Segment::NotifieeConst *n) const {
		Segment* me = const_cast<Segment*>(this);
		me->notifiee_.deleteMember(n);
	}
	
	NotifieeList notifiee_;
	SegmentReactor* segmentReactor_;
	Mode mode_;
	Fwk::Ptr<Location> source_;
	Mile length_;
	Segment::Ptr return_segment_;
	Difficulty difficulty_;
	ExpediteSupport exp_support_;
	VehicleCount numVehicles_;
	PackageCount segmentLoad_;
	ShipmentCount shipments_received_;
	ShipmentCount shipments_refused_;
	ShipmentCount shipments_told_to_wait_;
};

class Location : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Location> Ptr;
	typedef Fwk::Ptr<Location const> PtrConst;

	enum LocationType {
		customer_ = 0,
		port_,
		terminal_
	};
	static inline LocationType customer() { return customer_; }
	static inline LocationType port() { return port_; }
	static inline LocationType terminal() { return terminal_; }

	LocationType locationType() const { return location_type_; }

	Segment::PtrConst segment(size_t i) const {
		if (i < segments_.size())
			return segments_[i];
		else cerr << "Engine.h:"<<__LINE__<<": Location::segment() index out of bounds." << endl;
		return Segment::PtrConst();
	}
	virtual void segmentIs(const Segment::PtrConst &s) {
		segments_.push_back(s);
	}
	void segmentDel(const Fwk::String &name) {
		vector<Segment::PtrConst>::iterator it = segmentIterator(name);
		if (it != segments_.end())
			segments_.erase(it);		
		else cerr << "Engine.h:"<<__LINE__<<": Location::segmentDel() name does not exist." << endl;
	}

	void arrivingShipmentIs(Fwk::Ptr<Shipment> &shipment);

	typedef vector<Segment::PtrConst>::iterator SegmentIterator;
	typedef vector<Segment::PtrConst>::const_iterator SegmentIteratorConst;
	SegmentIterator segmentsIteratorBegin() {
		return segments_.begin();
	}
	SegmentIterator segmentsIteratorEnd() {
		return segments_.end();
	}
	SegmentIteratorConst segmentsIteratorConstBegin() const {
		return segments_.begin();
	}
	SegmentIteratorConst segmentsIteratorConstEnd() const {
		return segments_.end();
	}


	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
	  	typedef Fwk::Ptr<NotifieeConst const> PtrConst;
	  	typedef Fwk::Ptr<NotifieeConst> Ptr;

	  	Fwk::String name() const { return notifier_->name(); }
	  	Location::PtrConst notifier() const { return notifier_; }
	  	bool isNonReferencing() const { return isNonReferencing_; }
	   	~NotifieeConst();

	  	virtual void notifierIs(const Location::PtrConst& _notifier);
		virtual void onShipmentArrival(Fwk::Ptr<Shipment> &shipment) {}

		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }


	  	static NotifieeConst::Ptr NotifieeConstIs() {
		 	Ptr m = new NotifieeConst();
		 	m->referencesDec(1);
		 	// decr. refer count to compensate for initial val of 1
		 	return m;
	  	}
	protected:
	  	NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
	  		isNonReferencing_(false),
	  		lrNext_(0)
	  		{}

	  	bool isNonReferencing_;
	  	NotifieeConst * lrNext_;
	  	Location::PtrConst notifier_;
	};
	class Notifiee : public virtual Location::NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
	  	typedef Fwk::Ptr<Notifiee> Ptr;

	  	Location::PtrConst notifier() const { return NotifieeConst::notifier(); }
	  	Location::Ptr notifier() { return const_cast<Location *>(NotifieeConst::notifier().ptr()); }

	  	static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
		 	m->referencesDec(1);
		 	// decr. refer count to compensate for initial val of 1
		 	return m;
	  	}
	protected:
	  	Notifiee(): Fwk::NamedInterface::Notifiee() {}
	};

	class LocationReactor : public Location::Notifiee {
	public:
		typedef Fwk::Ptr<LocationReactor> Ptr;
		typedef Fwk::Ptr<LocationReactor const> PtrConst;

		void onShipmentArrival(Fwk::Ptr<Shipment> &shipment);

		static LocationReactor::Ptr LocationReactorNew(const Location::Ptr &notifier) {
			Ptr m = new LocationReactor(notifier);
			m->referencesDec(1);
			return m;
		}

	protected:
		LocationReactor(const Location::Ptr &notifier):
			Location::Notifiee(),
			activityManager_(activityManagerInstance())
			{
				notifierIs(notifier);
				//cout << "notifier=" << notifier.ptr() << endl;
				//cout << __FILE__ << ":" << __LINE__ << " LocationReactor()" << endl;
			}

		Activity::Manager::Ptr activityManager_;
	};

	void locationReactorIs(LocationReactor::Ptr reactor) { locationReactor_ = reactor.ptr(); }
	static Location::Ptr LocationNew(Fwk::String name, LocationType location_type) {
		Ptr m = new Location(name, location_type);
		m->locationReactorIs( LocationReactor::LocationReactorNew(m.ptr()) );
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}


	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::Iterator NotifieeIterator;
   	NotifieeIterator notifieeIter() { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }

protected:
	Location(Fwk::String name, LocationType location_type):
		Fwk::NamedInterface(name),
		location_type_(location_type)
		{
			//cout << "location(aka notifier)=" << this << endl;
			//cout << __FILE__ << ":" << __LINE__ << " Location()" << endl;
		}

	void newNotifiee(Location::NotifieeConst *n) const {
		Location* me = const_cast<Location*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee(Location::NotifieeConst *n) const {
		Location* me = const_cast<Location*>(this);
		me->notifiee_.deleteMember(n);
	}

	vector<Segment::PtrConst>::iterator
	segmentIterator(const string &name) {
		vector<Segment::PtrConst>::iterator it;
		for(it = segments_.begin(); it != segments_.end(); ++it) {
			if ((*it)->name() == name) {
				break;
			}
		}
		return it;
	}
	
	NotifieeList notifiee_;
	vector<Segment::PtrConst> segments_;
	LocationType location_type_;
	LocationReactor* locationReactor_;
};

class Customer : public Location {
public:
	typedef Fwk::Ptr<Customer> Ptr;
	typedef Fwk::Ptr<Customer const> PtrConst;

	ShipmentCount transferRate() const{
		return transfer_rate_;
	}
	void transferRateIs(ShipmentCount tr);

	PackageCount shipmentSize() const {
		return shipment_size_;
	}
	void shipmentSizeIs(PackageCount pc);

	Customer::Ptr destination() const{
		return destination_;
	}
	void destinationIs(Customer::Ptr c);
	
	ShipmentCount shipmentsReceived() const {
		return shipments_received_;
	}
	void shipmentsReceivedIs(ShipmentCount c) {
		shipments_received_ = c;
	}
	void totalLatencyInc(Hours l) {
		total_latency_ = Hours(total_latency_.value() + l.value());
	}
	Hours avgLatency() const{
		return Hours(total_latency_.value() / shipments_received_.value());
	}

	void totalCostInc(Dollars d) { total_cost_ = Dollars(total_cost_.value() + d.value()); }
	Dollars totalCost() const {
		return total_cost_;
	}

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
	  	typedef Fwk::Ptr<NotifieeConst const> PtrConst;
	  	typedef Fwk::Ptr<NotifieeConst> Ptr;

	  	Fwk::String name() const { return notifier_->name(); }
	  	Customer::PtrConst notifier() const { return notifier_; }
	  	bool isNonReferencing() const { return isNonReferencing_; }
	   	~NotifieeConst();

	  	virtual void notifierIs(const Customer::PtrConst& _notifier);
		virtual void onTransferRate(ShipmentCount transferRate) {}
		virtual void onShipmentSize(PackageCount shipmentSize) {}
		virtual void onDestination(Customer::Ptr destination) {}

		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }


	  	static NotifieeConst::Ptr NotifieeConstIs() {
		 	Ptr m = new NotifieeConst();
		 	m->referencesDec(1);
		 	// decr. refer count to compensate for initial val of 1
		 	return m;
	  	}
	protected:
	  	NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
	  		isNonReferencing_(false),
	  		lrNext_(0)
	  		{}

	  	bool isNonReferencing_;
	  	NotifieeConst * lrNext_;
	  	Customer::PtrConst notifier_;
	};
	class Notifiee : public virtual Customer::NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
	  	typedef Fwk::Ptr<Notifiee> Ptr;

	  	Customer::PtrConst notifier() const { return NotifieeConst::notifier(); }
	  	Customer::Ptr notifier() { return const_cast<Customer *>(NotifieeConst::notifier().ptr()); }

	  	static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
		 	m->referencesDec(1);
		 	// decr. refer count to compensate for initial val of 1
		 	return m;
	  	}
	protected:
	  	Notifiee(): Fwk::NamedInterface::Notifiee() {}
	};

	class CustomerReactor : public Customer::Notifiee {
	public:
		typedef Fwk::Ptr<CustomerReactor> Ptr;
		typedef Fwk::Ptr<CustomerReactor const> PtrConst;

		void onTransferRate(ShipmentCount transferRate);
		void onShipmentSize(PackageCount shipmentSize);
		void onDestination(Customer::Ptr destination);

		static CustomerReactor::Ptr CustomerReactorNew(const Customer::Ptr &notifier) {
			Ptr m = new CustomerReactor(notifier);
			m->referencesDec(1);
			return m;
		}

	protected:
		CustomerReactor(const Customer::Ptr &notifier):
			Customer::Notifiee(),
			activityManager_(activityManagerInstance())
			{
				notifierIs(notifier);
				attributesSet_[0] = attributesSet_[1] = attributesSet_[2] = 0;
				//cout << __FILE__ << ":" << __LINE__ << " CustomerReactor()" << endl;
			}

		enum Attributes {transferRate_ = 0, shipmentSize_, dest_};
		bool customerIsReady() const;
		void InjectActivityReactorNew();
		
		Activity::Manager::Ptr activityManager_;
		int attributesSet_[3];
		ShipmentCount transfer_rate_;
		PackageCount shipment_size_;
		Customer::Ptr destination_;
	};

	void customerReactorIs(CustomerReactor::Ptr reactor) { customerReactor_ = reactor.ptr(); }

	static Customer::Ptr CustomerNew(Fwk::String name) {
		Ptr m = new Customer(name);
		m->customerReactorIs( CustomerReactor::CustomerReactorNew(m.ptr()) );
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::Iterator NotifieeIterator;
   	NotifieeIterator notifieeIter() { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	
protected:
	Customer(Fwk::String name):
		Location(name, Location::customer())
		{
			//cout << __FILE__ << ":" << __LINE__ << " Customer()" << endl;
		}

	void newNotifiee(Customer::NotifieeConst *n) const {
		Customer* me = const_cast<Customer*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee(Customer::NotifieeConst *n) const {
		Customer* me = const_cast<Customer*>(this);
		me->notifiee_.deleteMember(n);
	}
	
	CustomerReactor* customerReactor_;
	NotifieeList notifiee_;
	ShipmentCount transfer_rate_;
	PackageCount shipment_size_;
	Customer::Ptr destination_;
	ShipmentCount shipments_received_;
	Hours total_latency_;
	Dollars total_cost_;
};

class Port : public Location {
public:
	typedef Fwk::Ptr<Port> Ptr;
	typedef Fwk::Ptr<Port const> PtrConst;

	static Location::Ptr PortNew(Fwk::String name) {
		Ptr m = new Port(name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:
	Port(Fwk::String name):
		Location(name, Location::port())
		{}
};

class Terminal : public Location {
public:
	typedef Fwk::Ptr<Terminal> Ptr;
	typedef Fwk::Ptr<Terminal const> PtrConst;

	Segment::Mode vehicleType() const { return vehicle_type_; }
	void vehicleTypeIs(Segment::Mode m) { vehicle_type_ = m; }

	void segmentIs(const Segment::PtrConst &s);
	static Location::Ptr TerminalNew(Fwk::String name, Segment::Mode vehicle_type) {
		Ptr m = new Terminal(name, vehicle_type);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:
	Terminal(Fwk::String name, Segment::Mode vehicle_type):
		Location(name, Location::terminal()),
		vehicle_type_(vehicle_type)
		{}

	Segment::Mode vehicle_type_;
};

class Fleet;
class FleetActivityReactor : public Activity::Notifiee {
public:

	static const double HALF_DAY = 12.0;

	void onStatus();

	FleetActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity *activity, Fleet *fleet):
		Notifiee(activity),
		fleet_(fleet),
		activity_(activity),
		manager_(manager)
		{}

protected:
	Fwk::Ptr<Fleet> fleet_;
	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
};


class Fleet : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Fleet> Ptr;
	typedef Fwk::Ptr<Fleet const> PtrConst;

	enum TimeOfDay {
		day_,
		night_,
	};

	static inline TimeOfDay day() { return day_; }
	static inline TimeOfDay night() { return night_; }
	static string timeOfDayString(TimeOfDay t) {
		switch(t) {
			case day_: return "day";
			case night_: return "night";
			default: return "";
		}
	}

	TimeOfDay timeOfDay() const { return time_of_day_; }
	void timeOfDayIs(TimeOfDay t) { time_of_day_ = t; }


	MilesPerHour speed(Segment::Mode m) const { return speed(m, timeOfDay()); }
	MilesPerHour speed(Segment::Mode m, TimeOfDay tod) const
	{
		map<string, MilesPerHour>::const_iterator found = speeds_.find(key(m, tod));
		if (found != speeds_.end()) return found->second;
		return MilesPerHour();
	}
	void speedIs(Segment::Mode m, MilesPerHour s, TimeOfDay tod) {
		speeds_[key(m, tod)] = s;
	}

	PackageCount capacity(Segment::Mode m) const { return capacity(m, timeOfDay()); }
	PackageCount capacity(Segment::Mode m, TimeOfDay tod) const
	{
		map<string, PackageCount>::const_iterator found = capacities_.find(key(m, tod));
		if (found != capacities_.end()) return found->second;
		return PackageCount();
	}
	void capacityIs(Segment::Mode m, PackageCount c, TimeOfDay tod) {
		capacities_[key(m, tod)] = c;
	}

	Dollars costPerMile(Segment::Mode m) const { return costPerMile(m, timeOfDay()); }
	Dollars costPerMile(Segment::Mode m, TimeOfDay tod) const
	{
		map<string, Dollars>::const_iterator found = costs_per_mile_.find(key(m, tod));
		if (found != costs_per_mile_.end()) return found->second;
		return Dollars();
	}
	void costPerMileIs(Segment::Mode m, Dollars cpm, TimeOfDay tod) {
		costs_per_mile_[key(m, tod)] = cpm;
	}

	static Fleet::Ptr FleetNew(Fwk::String name) {
		Ptr m = new Fleet(name);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:	
	Fleet(Fwk::String name):
		Fwk::NamedInterface(name),
		time_of_day_(Fleet::night()),
		activityManager_(activityManagerInstance())
		{
			vector<string> keys;
			keys.push_back(key(Segment::truck(), Fleet::day()));
			keys.push_back(key(Segment::boat(), Fleet::day()));
			keys.push_back(key(Segment::plane(), Fleet::day()));
			keys.push_back(key(Segment::truck(), Fleet::night()));
			keys.push_back(key(Segment::boat(), Fleet::night()));
			keys.push_back(key(Segment::plane(), Fleet::night()));

			for (size_t i = 0; i < keys.size(); i++) {
				costs_per_mile_[keys[i]] = Dollars(1.f);
				speeds_[keys[i]] = MilesPerHour(1.f);
				capacities_[keys[i]] = PackageCount(100);
			}

			Activity::Ptr activity = activityManager_->activityNew("FleetActivity");
			activity->lastNotifieeIs( new FleetActivityReactor(activityManager_, activity.ptr(), this) );
			activity->nextTimeIs(8.0);
			activity->statusIs(Activity::nextTimeScheduled);
		}

	string key(Segment::Mode m, TimeOfDay t) const {
		stringstream stream;
		stream << Segment::modeName(m) << "_" << Fleet::timeOfDayString(t);
		return stream.str();
	}

	map<string, MilesPerHour> speeds_;
	map<string, PackageCount> capacities_;
	map<string, Dollars> costs_per_mile_;

	TimeOfDay time_of_day_;
	Activity::Manager::Ptr activityManager_;
};

class Path : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Path> Ptr;
	typedef Fwk::Ptr<Path const> PtrConst;

	enum PartType {
		nil_ = 0,
		segment_,
		location_
	};
	static inline PartType segment() { return segment_; }
	static inline PartType location() { return location_; }
	static inline PartType nil() { return nil_; }

	enum Membership {
		notMember_ = 0,
		isMember_
	};
	static inline Membership notMember() { return notMember_; }
	static inline Membership isMember() { return isMember_; }

	struct Part {
		Part():
			type(Path::nil())
			{}
		Part(Location::PtrConst _loc):
			type(Path::location()),
			loc(_loc)
			{}
		Part(Segment::PtrConst _seg):
			type(Path::segment()),
			seg(_seg)
			{}

		PartType type;
		Location::PtrConst loc;
		Segment::PtrConst seg;
	};

	Part part(size_t index) const { return path_[index]; }
	Location::PtrConst start() const { return start_; }
	Location::PtrConst end() const { return endLocation_; }
	size_t locationIndex(const Location::PtrConst &location) const;
	Membership locationMembershipStatus(const Location::PtrConst &location) const;

	void endLocationIs(const Location::PtrConst &newEnd);
	void endSegmentIs(const Segment::PtrConst &seg);

	size_t numSegments() const { return numSegments_; }
	size_t numLocations() const { return numLocations_; }
	size_t numParts() const { return numSegments() + numLocations(); }

	Hours hours() const { return hours_; }
	Dollars cost() const { return cost_; }
	Mile distance() const { return distance_; }
	
	Segment::ExpediteSupport expedited() const { return expedited_; }
	void expeditedIs(Segment::ExpediteSupport es);
	
	string stringValue() const;


	static Path::Ptr PathNew(const Fleet::PtrConst &f) {
		Ptr m = new Path(f);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:
	Path(const Fleet::PtrConst &f):
		Fwk::NamedInterface("path"),
		fleet_(f),
		numSegments_(0),
		numLocations_(0),
		expedited_(Segment::expediteSupported())
		{
			endSegmentPart_.type = Path::nil();
		}

	void numSegmentsIs(size_t n) { numSegments_ = n; }
	void numLocationsIs(size_t n) { numLocations_ = n; }
	void hoursIs(Hours t) { hours_ = t; }
	void costIs(Dollars d) { cost_ = d; }
	void distanceIs(Mile m) { distance_ = m; }

	Dollars calculateCost(const Segment::PtrConst &segment) const;
	Hours calculateHours(const Segment::PtrConst &segment) const;

	Fleet::PtrConst fleet_;
	Location::PtrConst start_;
	Location::PtrConst endLocation_;
	Segment::PtrConst endSegment_;
	Part endSegmentPart_;

	set<Fwk::String> usedLocations_;
	vector<Part> path_;
	size_t numSegments_;
	size_t numLocations_;

	Segment::ExpediteSupport expedited_;
	Dollars cost_;
	Hours hours_;
	Mile distance_;
};

class Shipment : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Shipment> Ptr;
	typedef Fwk::Ptr<Shipment const> PtrConst;

	static string shipmentName(const Customer::Ptr &source, const Customer::Ptr &destination)
	{
		stringstream stream;
		stream << source->name() << ":" << destination->name();
		return stream.str(); 
	}
	
	Customer::Ptr source() { return src_; }
	void sourceIs(Customer::Ptr s) { src_ = s; }

	Customer::Ptr dest() const { return dest_; }
	void destIs(Customer::Ptr d) { dest_ = d; }

	PackageCount load() const { return load_; }
	void loadIs(PackageCount l) { load_ = l; }

	Path::PtrConst path() const { return path_; }
	void pathIs(const Path::PtrConst &path) { path_ = path; }

	Hours latency() const { return latency_; }
	void latencyInc(Hours l) { latency_ = Hours(latency_.value() + l.value()); }

	static Shipment::Ptr ShipmentNew(Customer::Ptr s, Customer::Ptr d, PackageCount p) {
		Ptr m = new Shipment(s, d, p);
		m->referencesDec(1);
		// decr. refer count to compensate for initial val of 1
		return m;
	}

protected:
	Shipment(Customer::Ptr s, Customer::Ptr d, PackageCount p);

	Customer::Ptr src_;
	Customer::Ptr dest_;
	PackageCount load_;
	Path::PtrConst path_;
	Hours latency_;
};

class RetryActivityReactor : public Activity::Notifiee {
public:
	void onStatus();

	static const double MAX_WAIT = 24.0;
	static const double WAIT_MULTIPLE = 2.0;

	RetryActivityReactor(Fwk::Ptr<Activity::Manager> manager,
				Activity *activity, Shipment *shipment,
				Segment *segment):
		Notifiee(activity),
		successfullyForwardedShipment_(false),
		totalTimeWaiting_(0.0),
		wait_(0.1),
		shipment_(shipment),
		segment_(segment),
		activity_(activity),
		manager_(manager)
		{}

	double wait() { return wait_; }

protected:
	bool successfullyForwardedShipment_;
	double totalTimeWaiting_;
	double wait_;
	Fwk::Ptr<Shipment> shipment_;
	Fwk::Ptr<Segment> segment_;
	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
};

class InjectActivityReactor : public Activity::Notifiee {
public:
	void onStatus();

	InjectActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity *activity, Customer *customer, double rate):
		Notifiee(activity),
		customer_(customer),
		rate_(rate),
		activity_(activity),
		manager_(manager)
		{}

protected:
	Customer::Ptr customer_;
	double rate_;
	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
};

class ForwardActivityReactor : public Activity::Notifiee {
public:
	void onStatus();

	ForwardActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity *activity,
						Segment *segment, Shipment *shipment):
		Notifiee(activity),
		segment_(segment),
		shipment_(shipment),
		activity_(activity),
		manager_(manager)
		{}

protected:
	Segment::Ptr segment_;
	Shipment::Ptr shipment_;
	Activity::Ptr activity_;
	Fwk::Ptr<Activity::Manager> manager_;
};



class Connectivity : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Connectivity> Ptr;
	typedef Fwk::Ptr<Connectivity const> PtrConst;

	enum SearchPattern {
		explore_,
		connect_
	};
	static inline SearchPattern explore() { return explore_; }
	static inline SearchPattern connect() { return connect_; }

	enum Constraint {
		constrainNone_ = 0,
		constrainDistance_ = 0x1,
		constrainCost_ = 0x2,
		constrainHours_ = 0x4,
		constrainExpedited_ = 0x8
	};
	static inline Constraint none() { return constrainNone_; }
	static inline Constraint distance() { return constrainDistance_; }
	static inline Constraint cost() { return constrainCost_; }
	static inline Constraint hours() { return constrainHours_; }
	static inline Constraint expedited() { return constrainExpedited_; }

	enum RoutingMethod {
		dijkstra_,
		bfs_
	};
	static inline RoutingMethod dijkstra() { return dijkstra_; }
	static inline RoutingMethod bfs() { return bfs_; }

	
	void constraintsActiveIs(int mask);
	void constraintsActiveDel();
	int constraintsActive() const { return mask_; }

	Location::PtrConst constraintStart() const { return start_; }
	void constraintStartIs(const Location::PtrConst &start) { start_ = start; }
	Location::PtrConst constraintEnd() const { return end_; }
	void constraintEndIs(const Location::PtrConst &end) { end_ = end; }

	Mile constraintDistance() const {
		return distance_;
	}
	void constraintDistanceIs(const Mile &m) {
		distance_ = m;
	}
	

	Dollars constraintCost() const {
		return cost_;
	}
	void constraintCostIs(const Dollars &d) {
		cost_ = d;
	}
	

	Hours constraintHours() const {
		return hours_;
	}
	void constraintHoursIs(const Hours &t) {
		hours_ = t;
	}


	Segment::ExpediteSupport constraintExpedited() const {
		return expedited_;
	}
	void constraintExpeditedIs(Segment::ExpediteSupport es) {
		expedited_ = es;
	}

	void fleetIs(const Fleet::PtrConst &f) { fleet_ = f; }
	Fleet::PtrConst fleet() const { return fleet_; }

	vector<string> paths(SearchPattern pattern) const;

	RoutingMethod routingMethod() const{
		return routing_method_;
	}
	void routingMethodIs(RoutingMethod rm) {
		routing_method_ = rm;
	}
	Path::PtrConst shipmentPath(const string &s) const {
		map<string, Path::Ptr>::const_iterator it;
		Path::Ptr p;

		if(routingMethod() == bfs()){
			it = routes_bfs_.find(s);
			if (it != routes_bfs_.end()) {
				p = it->second;
				return p;
			} 
		}
		if(routingMethod() == dijkstra()){
			it = routes_dijkstra_.find(s);
			if (it != routes_dijkstra_.end()) {
				p = it->second;
				return p;
			} 
		}
		return Path::Ptr();
	}

	static Connectivity::Ptr ConnectivityNew(Fwk::String name) {
		Ptr m = new Connectivity(name);
		m->referencesDec(1);
		return m;
	}

	enum SimulationStatus {off_, running_};
	static inline SimulationStatus off(){ return off_;}
	static inline SimulationStatus running(){ return running_;}

	SimulationStatus simulationStatus() const{
		return simulation_status_;
	}
	void simulationStatusIs(SimulationStatus s){
		if(simulation_status_ == off() && s == running()){ //simulation is starting
			routes_dijkstra_ = routes(dijkstra());
			routes_bfs_ = routes(bfs());
		}
		simulation_status_ = s;
	}
	

protected:	
	Connectivity(Fwk::String name):
		Fwk::NamedInterface(name),
		expedited_(Segment::expediteNotSupported()),
		mask_(0),
		routing_method_(dijkstra()),
		simulation_status_(off())
		{}

	bool isValidExplorePath(Path::Ptr path) const;
	bool isValidExplorePathNotExpedited(Path::Ptr one, Path::Ptr two) const;
	vector<string> stringifyPaths(SearchPattern pattern, vector<Path::Ptr> &completedPaths) const;
	map<string, Path::Ptr> routes(RoutingMethod rm);
	Path::Ptr DijkstraShortestPath(Location::PtrConst &startLoc, Location::PtrConst &endLoc);
	Path::Ptr BFSShortestPath(Location::PtrConst &startLoc, Location::PtrConst &endLoc);


	Segment::ExpediteSupport expedited_;
	int mask_;
	Location::PtrConst start_;
	Location::PtrConst end_;
	Fleet::PtrConst fleet_;
	Mile distance_;
	Dollars cost_;
	Hours hours_;
	RoutingMethod routing_method_;
	SimulationStatus simulation_status_;
	map<string, Path::Ptr> routes_dijkstra_;
	map<string, Path::Ptr> routes_bfs_;
	
};

class Statistics; // Forward declaration

class Network;
static Network* networkInstance_;
//Gets the singleton instance of Network
Fwk::Ptr<Network> networkInstance();

class Network : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Network> Ptr;
	typedef Fwk::Ptr<Network const> PtrConst;


	Location::Ptr location(const Fwk::String &name);
	vector<Location::PtrConst> locations() const {
		vector<Location::PtrConst> locs;
		for (map<string, Location::Ptr>::const_iterator itr = locations_.begin(); itr != locations_.end(); ++itr) {
			locs.push_back(itr->second.ptr());
		}
		return locs;
	}

	vector<Segment::PtrConst> segments() const {
		vector<Segment::PtrConst> segs;
		for (map<string, Segment::Ptr>::const_iterator itr = segments_.begin(); itr != segments_.end(); ++itr) {
			segs.push_back(itr->second.ptr());
		}
		return segs;
	}
	Segment::Ptr segment(const Fwk::String &name) {
		map<Fwk::String, Segment::Ptr>::iterator found = segments_.find(name);
		if(found == segments_.end()) return Segment::Ptr();
		return found->second;
	}

	Fleet::PtrConst fleet() const { return fleet_; }
	Connectivity::PtrConst connectivity() const { return connectivity_; }
	Fwk::Ptr<Statistics const> statistics() const { return statistics_; }

	void expediteSupportIs(Fwk::String name, Segment::ExpediteSupport supported);
	Segment::Ptr segmentNew(Fwk::String name, Segment::Mode mode);
	Segment::Ptr segmentDel(Fwk::String name);

	Customer::Ptr customerNew(Fwk::String name);
	Customer::Ptr customerDel(Fwk::String name);

	Location::Ptr portNew(Fwk::String name);
	Location::Ptr portDel(Fwk::String name);

	Location::Ptr terminalNew(Fwk::String name, Segment::Mode vehicle_type);
	Location::Ptr terminalDel(Fwk::String name);

	Fleet::Ptr fleetNew(Fwk::String name);
	Fleet::Ptr fleetDel(Fwk::String name);

	Fwk::Ptr<Statistics> statisticsNew(Fwk::String name);
	Fwk::Ptr<Statistics> statisticsDel(Fwk::String name);

	Connectivity::Ptr connectivityNew(Fwk::String name);
	Connectivity::Ptr connectivityDel(Fwk::String name);

	Shipment::Ptr shipmentNew(Customer::Ptr s, Customer::Ptr d, PackageCount p);

	static Network::Ptr NetworkNew(Fwk::String name) {
		Ptr m = new Network(name);		
		m->referencesDec(1);
		//cout << "NETWORK CONSTRUCTOR IS " << m.ptr() << endl;
		networkInstance_ = m.ptr();
		//networkInstance();
		return m;
	}

	
	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
	  	typedef Fwk::Ptr<NotifieeConst const> PtrConst;
	  	typedef Fwk::Ptr<NotifieeConst> Ptr;

	  	Fwk::String name() const { return notifier_->name(); }
	  	Network::PtrConst notifier() const { return notifier_; }
	  	bool isNonReferencing() const { return isNonReferencing_; }
	   	~NotifieeConst();
	  	virtual void notifierIs(const Network::PtrConst& _notifier);

		virtual void onSegmentNew(Segment::Ptr segment) {}
		virtual void onCustomerNew(Customer::Ptr customer) {}
		virtual void onPortNew(Port::Ptr port) {}
		virtual void onTerminalNew(Terminal::Ptr terminal) {}

		virtual void onSegmentDel(Segment::Ptr segment) {}
		virtual void onCustomerDel(Customer::Ptr customer) {}
		virtual void onPortDel(Port::Ptr port) {}
		virtual void onTerminalDel(Terminal::Ptr terminal) {}

		virtual void onShipmentNew(Shipment::Ptr shipment) {}

		virtual void onNumExpediteSupportedSegments(int n) {}


		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }


	  	static NotifieeConst::Ptr NotifieeConstIs() {
		 	Ptr m = new NotifieeConst();
		 	m->referencesDec(1);
		 	// decr. refer count to compensate for initial val of 1
		 	return m;
	  	}
	protected:
	  	NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
	  		isNonReferencing_(false),
	  		lrNext_(0)
	  		{}

	  	bool isNonReferencing_;
	  	NotifieeConst * lrNext_;
	  	Network::PtrConst notifier_;
	};
	class Notifiee : public virtual Network::NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
	  	typedef Fwk::Ptr<Notifiee> Ptr;

	  	Network::PtrConst notifier() const { return NotifieeConst::notifier(); }
	  	Network::Ptr notifier() { return const_cast<Network *>(NotifieeConst::notifier().ptr()); }

	  	static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
		 	m->referencesDec(1);
		 	// decr. refer count to compensate for initial val of 1
		 	return m;
	  	}
	protected:
	  	Notifiee(): Fwk::NamedInterface::Notifiee() {}
	};
	

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::Iterator NotifieeIterator;
   	NotifieeIterator notifieeIter() { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	
protected:
	Network(Fwk::String name):
		Fwk::NamedInterface(name)
		{
		}

	void newNotifiee(Network::NotifieeConst *n) const {
		Network* me = const_cast<Network*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee(Network::NotifieeConst * n) const {
		Network* me = const_cast<Network*>(this);
		me->notifiee_.deleteMember(n);
	}

	void locationIs(const Fwk::String &name, Location::Ptr m) {
		locations_[name] = m;
	}
	void segmentIs(const Fwk::String &name, Segment::Ptr m) {
		segments_[name] = m;
	}

	void locationSegmentsDel(Location::Ptr m);

	NotifieeList notifiee_;
	map<Fwk::String, Location::Ptr> locations_;
	map<Fwk::String, Segment::Ptr> segments_;
	Fleet::Ptr fleet_;
	Fwk::Ptr<Statistics> statistics_;
	Connectivity::Ptr connectivity_;
};


class Statistics : public Network::Notifiee {
public:
	typedef Fwk::Ptr<Statistics> Ptr;
	typedef Fwk::Ptr<Statistics const> PtrConst;

	enum ShipmentStatus {
		enroute_ = 0,
		delivered_,
		dropped_
	};

	static inline ShipmentStatus enroute() { return enroute_; }
	static inline ShipmentStatus delivered() { return delivered_; }
	static inline ShipmentStatus dropped() { return dropped_;}

	struct ShippingRecord {
		int record[3];

		void numEnRouteInc(int n = 1) { record[enroute_] += n; }
		void numDeliveredInc(int n = 1) { record[delivered_] += n; }
		void numDroppedInc(int n = 1) { record[dropped_] += n; }

		size_t numEnRoute() { return record[enroute_]; }
		size_t numDelivered() { return record[delivered_]; }
		size_t numDropped() { return record[dropped_]; }
	};

	size_t numCustomers() const { return numCustomers_; }
	size_t numPorts() const { return numPorts_; }
	size_t numTerminals(Segment::Mode mode) const { return numTerminals_[mode]; }
	size_t numSegments(Segment::Mode mode) const { return numSegments_[mode]; }
	size_t numShipments(ShipmentStatus status) const { return numShipments_[status]; }

	void deliveredShipmentIs(Shipment::Ptr shipment);
	void droppedShipmentIs(Shipment::Ptr shipment);

	float percentExpeditedSegments();

	string simulationStatisticsOutput() const;
	

	static Statistics::Ptr StatisticsNew(Fwk::String name) {
		Ptr m = new Statistics(name);
		m->referencesDec(1);
		return m;
	}

protected:
	Statistics(Fwk::String name):
		Network::Notifiee(),
		numCustomers_(0),
		numPorts_(0),
		numExpeditedSegments_(0)
		{
			for(size_t i = 0; i < 3; i++) {
				numTerminals_[i] = 0;
				numSegments_[i] = 0;
				numShipments_[i] = 0;
			}
		}

	void numCustomersIs(size_t n) {
		numCustomers_ = n;
	}
	void numPortsIs(size_t n) {
		numPorts_ = n;
	}
	void numTerminalsIs(Segment::Mode mode, size_t n) {
		numTerminals_[mode] = n;
	}
	void numSegmentsIs(Segment::Mode mode, size_t n) {
		numSegments_[mode] = n;
	}
	void numShipmentsIs(ShipmentStatus status, size_t n) {
		numShipments_[status] = n;
	}

	void onSegmentNew(Segment::Ptr segment);
	void onCustomerNew(Customer::Ptr customer);
	void onPortNew(Port::Ptr port);
	void onTerminalNew(Terminal::Ptr terminal);

	void onSegmentDel(Segment::Ptr segment);
	void onCustomerDel(Customer::Ptr customer);
	void onPortDel(Port::Ptr port);
	void onTerminalDel(Terminal::Ptr terminal);

	void onShipmentNew(Shipment::Ptr shipment);
	
	void onNumExpediteSupportedSegments(int n);

	map<string, ShippingRecord> shipmentRecords_;

	size_t numCustomers_;
	size_t numPorts_;
	size_t numTerminals_[3];
	size_t numSegments_[3];
	size_t numShipments_[3];
	size_t numExpeditedSegments_;
};

} /* end namespace */


#endif
