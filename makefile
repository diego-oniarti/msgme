APPNAME  = msgme
OUT = bin/$(APPNAME)
MAIN = main.cpp

SRC   = $(wildcard src/*.cpp)
OBJ   = $(SRC:src/%.cpp=obj/%.o)

CXX   = g++
CXXFLAGS = -O3 -I./src -std=c++17
LDFLAGS  = -lTgBot -lboost_system -lssl -lcrypto -lpthread

PREFIX = /usr/local

all: $(OUT)

clean:
	rm -rf bin obj

run: $(OUT)
	./$(OUT)

install: $(OUT)
	mkdir -p $(PREFIX)/bin
	sudo cp $^ $(PREFIX)/bin/

dependencies:
	sudo apt install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev
	git clone https://github.com/reo7sp/tgbot-cpp
	cmake -S tgbot-cpp -B tgbot-cpp/build
	make -C tgbot-cpp/build -j4
	sudo make -C tgbot-cpp/build install
	rm -fr tgbot-cpp
	touch dependencies

.PHONY: all clean run install


$(OUT): $(OBJ) obj/msgme.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/msgme.o: $(MAIN)
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@
