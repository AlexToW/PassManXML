all: passman

passman: main.o password_item.o storage.o passman.o encryption.o
	g++ main.o storage.o passman.o encryption.o password_item.o -o passman -lcryptopp

main.o: main.cpp passman.h
	g++ -c main.cpp

storage.o: storage.cpp storage.h account.h password_item.h
	g++ -c storage.cpp

passman.o: passman.cpp passman.h storage.h encryption.h
	g++ -c passman.cpp

encryption.o: encryption.cpp encryption.h
	g++ -c encryption.cpp -lcryptopp

password_item.o: password_item.cpp password_item.h
	g++ -c password_item.cpp
