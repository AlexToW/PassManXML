all: passman

passman: main.o passman.o storage.o account.o encryption.o password_item.o
	g++ main.o passman.o storage.o account.o encryption.o password_item.o -o passman -lcryptopp

main.o: main.cpp passman.h
	g++ -c main.cpp

passman.o: passman.cpp passman.h storage.h encryption.h
	g++ -c passman.cpp

storage.o: storage.cpp storage.h account.h password_item.h
	g++ -c storage.cpp

account.o: account.cpp account.h 
	g++ -c account.cpp 

encryption.o: encryption.cpp encryption.h
	g++ -c encryption.cpp -lcryptopp

password_item.o: password_item.cpp password_item.h
	g++ -c password_item.cpp
