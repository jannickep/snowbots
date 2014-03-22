SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)

.PHONY : all clean

all: $(OBJECTS)

%.d: %.cpp
	@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
                      | sed '\''s_\($*\)\.o[ :]*_\1.o $@ : _g'\'' > $@; \
                      [ -s $@ ] || rm -f $@'

clean:
	rm -f *.o *.d

-include $(OBJECTS:.o=.d)

