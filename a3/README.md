# Build, Automated-testing, Run
cd <path>/project

mkdir build

cd build

cmake ../

make install

cd run/bin

../../tests_rgen

python3 ../../../test_ece650-a1.py

../../tests_ece650-a3

../../tests_ece650-a2

./ece650-a3


# Useful Examples
./ece650-a3 -s 5 -n 4 -l 5

./ece650-a3 -s 5 -n 8 -l 5

./ece650-a3 -s 5 -n 11 -l 5 -c 2

./ece650-a3 -s 5 -n 4 -l 5 -c 1

./ece650-a3