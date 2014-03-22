SOURCES=$(wildcard *.cpp)
TARGETS=$(SOURCES:%.cpp=%)

SDKOBJECTS=$(shell find .. -name "*.o" -a ! -wholename "*unittests*")


.PHONY : all clean

all: $(TARGETS)

$(TARGETS): % : %.o
	$(CXX) $(LDFLAGS) $(SDKOBJECTS) $(LIBS) $< -o $@

%.d: %.cpp
	@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
                      | sed '\''s_\($*\)\.o[ :]*_\1.o $@ : _g'\'' > $@; \
                      [ -s $@ ] || rm -f $@'

clean:
	rm -f *.o *.d *Test

-include $(OBJECTS:.o=.d)

