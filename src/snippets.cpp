//#include <map>
//#include "Engine.h"
//#include <typeinfo>
#include <iostream>

//using namespace Shipping;
using namespace std;

class B;

class A {
public:
	virtual void foo() { cout << "A::foo" << endl; }
};

class B : public A {
public:
	virtual void foo() { cout << "B::foo" << endl; }
};

void test( A &a );

void test( A &a ) {
	a.foo();
}

int main(int argc, char *argv[]) {
	A a;
	B b;

	test(a);
	test(b);
}
/*
float round(float r) {
	return (r > 0.f) ? floor(r + 0.5f) : ceil(r - 0.5f);
}


int main(int argc, char *argv[]) {
	string name = "anwar";
	Segment::Ptr segment = Segment::SegmentNew(name, Segment::truck());
	map<string, Segment::Ptr> mymap;
	mymap[name] = segment;

	Segment::Ptr segment1 = mymap[name];
	size_t n = mymap.erase(name);
	if(n == 0) {
		cout << "nothing was erased" << endl;
		return 0;
	}

	cout << &segment << " " << &segment1 << endl;
	cout << segment.ptr() << endl;
	cout << "something was erased" << endl;
	cout << segment1->name() << endl;
	cout << segment1.ptr() << endl;


	int p = 0;
	float t = 456.34234234;
	size_t u = 3.;
	cout << "type of p is " << typeid(p).name() << endl;
	cout << "type of t is " << typeid(t).name() << endl;
	cout << "type of u is " << typeid(u).name() << endl;

	cout << ( typeid(t)==typeid(u) ) << endl;
	cout << ( typeid(t)==typeid(float) ) << endl << endl;

	cout << NumberConverter<float>::toString(t + 0.0000001) << endl;
	cout << NumberConverter<size_t>::toString(u) << endl;

	cout << endl << endl;
	cout << "ROUNDING" << endl;
	float f = 906.6666667;
	cout << t << " " << round(t) << endl;
	cout << f << " " << round(f) << endl;

	return 0;
}*/