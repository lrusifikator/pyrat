SOURVES = main.cpp functions.cpp pyrat.cpp db.cpp handler.cpp slist.cpp
OBJECTS = main.o functions.o pyrat.o db.o handler.o slist.o

all: pyrat

pyrat: $(OBJECTS)
	g++ $(OBJECTS) -o $@

main.o: main.cpp
	g++ -c main.cpp

slist.o: slist.cpp
	g++ -c slist.cpp
	
pyrat.o: pyrat.cpp
	g++ -c pyrat.cpp

db.o: db.cpp
	g++ -c db.cpp

functions.o: functions.cpp
	g++ -c functions.cpp

handler.o: handler.cpp
	g++ -c handler.cpp
	
clean:
	rm -rf *.o 

install:
	sudo cp pyrat /usr/bin/
	sudo cp ldetect /usr/bin/
	
uninstall:
	sudo rm /usr/bin/pyrat
