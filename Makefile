CC=g++ -std=c++11
exe=hunt

$(exe): event.o room.o wumpus.o bats.o pit.o gold.o game.o event.h room.h wumpus.h bats.h pit.h gold.h game.h driver.cpp
	$(CC) event.o room.o wumpus.o bats.o pit.o gold.o game.o driver.cpp -o $(exe)

event.o: event.cpp event.h
	$(CC) -c event.cpp

room.o: room.cpp room.h
	$(CC) -c room.cpp

wumpus.o: wumpus.cpp wumpus.h
	$(CC) -c wumpus.cpp

bats.o: bats.cpp bats.h 
	$(CC) -c bats.cpp

pit.o: pit.cpp pit.h 
	$(CC) -c pit.cpp

gold.o: gold.cpp gold.h 
	$(CC) -c gold.cpp
 
game.o: game.cpp game.h
	$(CC) -c game.cpp

clean: 
	rm -f *.o $(exe)
