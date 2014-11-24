all: rfm

rfm:
	mkdir -p build
	gcc -pthread -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -fPIC -I/usr/include/python2.7 -c py_rfm69.c -o build/py_rfm69.o
	gcc -pthread -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -fPIC -I/usr/include/python2.7 -lwiringPi -c rfm69.c -o build/rfm69.o
	gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -Wl,-z,relro build/py_rfm69.o build/rfm69.o wiringPi/wiringPi/*.o -o build/RFM69.so

clean:
	rm -rf build
