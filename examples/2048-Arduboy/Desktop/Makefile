TARGET := ardusdl
VPATH = ../2048-Arduboy
CPPFLAGS :=  -ggdb -D_REENTRANT -I/usr/include/SDL2
LDLIBS := -lSDL2
SOURCES := $(wildcard $(VPATH)/*.cpp *.cpp)
HEADERS := $(wildcard $(VPATH)/*.h *.h)
OBJECTS := $(SOURCES:%.cpp=%.o)

all: $(TARGET)

$(TARGET) : $(OBJECTS) 
	$(CXX) -o $@ $^ $(LDLIBS)

$(OBJECTS) : $(HEADERS)

.PHONY: clean
clean:
	@$(RM) $(TARGET)
	@$(RM) $(OBJECTS)
