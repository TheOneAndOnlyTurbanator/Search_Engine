CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
GTESTINCL := -I /usr/include/gtest/  
GTESTLIBS := -lgtest -lgtest_main  -lpthread
VALGRIND := valgrind --tool=memcheck --leak-check=yes --track-origins=yes

# Uncomment for parser DEBUG
#DEFS=-DDEBUG
OBJS_COMPONENTS=searcheng.o searchui.o md_parser.o txt_parser.o util.o webpage.o handler.o cmdhandler.o combiners.o
OBJS=search-shell.o $(OBJS_COMPONENTS)

all: search-shell mdparser-tests

hw2-tests: hw2-tests.cpp $(OBJS_COMPONENTS)
	$(CXX) $(CXXFLAGS) $(GTESTINCL) $^ -o $@ $(GTESTLIBS)
	
mdparser-tests: mdparser-tests.cpp md_parser.o util.o webpage.o
	$(CXX) $(CXXFLAGS) $(DEFS) $(GTESTINCL)  -o $@ $^ $(GTESTLIBS)

parser-tests: mdparser-tests
	$(VALGRIND) ./mdparser-tests

search-shell.o: search-shell.cpp pageparser.h md_parser.h txt_parser.h cmdhandler.h handler.h webpage.h searcheng.h searchui.h util.h combiners.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ search-shell.cpp
util.o: util.cpp util.h webpage.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ util.cpp
txt_parser.o: txt_parser.cpp txt_parser.h pageparser.h webpage.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ txt_parser.cpp
md_parser.o: md_parser.cpp md_parser.h pageparser.h webpage.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ md_parser.cpp
searchui.o: searchui.cpp searchui.h searcheng.h handler.h webpage.h pageparser.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ searchui.cpp
handler.o: handler.cpp handler.h searcheng.h webpage.h pageparser.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ handler.cpp
webpage.o: webpage.cpp webpage.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ webpage.cpp

# Add targets for cmdhandler.o, searcheng.o and combiners.o
cmhandler.o: cmhandler.cpp util.h searcheng.h combiners.h webpage.h pageparser.h cmhandler.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ searchui.cpp
searcheng.o: searcheng.h searcheng.cpp webpage.h pageparser.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ handler.cpp
combiners.o: combiners.cpp combiners.h searcheng.h webpage.h pageparser.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ webpage.cpp



# Add a target for the overall executable search-shell that is dependent
# on all the object files and compiles them together to produce an 
# executable named search-shell. Use the OBJS variable defined near
# the top and ensure you compile with the CXXFLAGS.

search-shell: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)


clean:
	rm -f *.o search-shell mdparser-tests

.PHONY: clean parser-tests
