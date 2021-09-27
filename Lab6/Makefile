FLAGS_G++ = -pedantic -Wall -std=c++17 -Werror -Wno-sign-compare -O2 -lm -g -Wextra

all: main.cpp
	g++ $(FLAGS_G++) main.cpp BigInteger.cpp -o solution

clean:
	rm -rf *.o solution