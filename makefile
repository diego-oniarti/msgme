APPNAME  = msgme
CONFNAME = msgmecreds

MSGMEOUT = bin/$(APPNAME)
CONFOUT  = bin/$(CONFNAME)

MSGME = msgme.cpp
CONF  = msgmecreds.cpp

SRC   = $(wildcard src/*.cpp)
OBJ   = $(SRC:src/%.cpp=obj/%.o)

CXX   = g++
CXXFLAGS = -O3 -I./src -std=c++17
LDFLAGS  = -lTgBot -lboost_system -lssl -lcrypto -lpthread

PREFIX = /urs/local

all: $(MSGMEOUT) $(CONFOUT)

clean:
	rm -rf bin obj

run: $(MSGMEOUT)
	./$(MSGMEOUT)

install: $(MSGMEOUT) $(CONFOUT)
	mkdir -p $(PREFIX)/bin
	sudo cp $^ $(PREFIX)/bin

dependencies:
	sudo apt install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev
	git clone https://github.com/reo7sp/tgbot-cpp
	cmake -S tgbot-cpp -B tgbot-cpp/build
	make -C tgbot-cpp/build -j4
	sudo make -C tgbot-cpp/build install
	rm -fr tgbot-cpp
	touch dependencies

.PHONY: all clean run install


$(MSGMEOUT): $(OBJ) obj/msgme.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(CONFOUT): $(OBJ) obj/msgmecreds.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)


obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@


obj/msgme.o: $(MSGME)
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/msgmecreds.o: $(CONF)
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@
