#! /bin/sh

cd ../
make clean && make
cd unit-test
make clean && make
./UnitTest
