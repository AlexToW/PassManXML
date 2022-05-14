all: passman

passman: main.o passman.o storage.o account.o encryption.o password_item.o hash.o
	g++ main.o passman.o storage.o account.o encryption.o password_item.o hash.o -o passman -lcryptopp -lxcb -pthread

main.o: main.cpp passman.h
	g++ -c main.cpp

passman.o: passman.cpp passman.h storage.h encryption.h clipboard.h
	g++ -c passman.cpp -lxcb -pthread

storage.o: storage.cpp storage.h account.h password_item.h hash.h
	g++ -c storage.cpp

account.o: account.cpp account.h 
	g++ -c account.cpp 

encryption.o: encryption.cpp encryption.h
	g++ -c encryption.cpp -lcryptopp

password_item.o: password_item.cpp password_item.h
	g++ -c password_item.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp -lcryptopp