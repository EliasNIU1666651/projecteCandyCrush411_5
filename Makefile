CXXFLAGS = -g -Wall
CXX = g++
OBJECTS = 

app: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o app
	rm -rf *.o

clean:
	rm -rf *.o app.exe