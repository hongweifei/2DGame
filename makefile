

CXX_linux = g++ -O3
CXX_window = i686-w64-mingw32-g++ -O3

#CFLAGS += -std=c++11
LDFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf -llua

src = $(wildcard *.cpp)
obj = $(patsubst %.cpp, %.o, $(src))

target_linux = ./linux/a.out
#target_window = ./window/game.exe

$(target_linux) : $(obj)
			$(CXX_linux) $(obj) $(LDFLAGS) -o $(target_linux)

#$(target_window) : $(obj)
#			$(CXX_window) $(obj) $(LDFLAGS) -o $(target_window)

