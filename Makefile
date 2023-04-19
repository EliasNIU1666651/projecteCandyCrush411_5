CXXFLAGS = -g -Wall
CXX = g++
OBJECTS = tauler.o candy.o partida.o main.o

app: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o app
	rm -rf *.o

partida.o: partida.cpp partida.h tauler.h
	$(CXX) $(CXXFLAGS) -c partida.cpp

tauler.o: tauler.cpp tauler.h definicions.h candy.h
	$(CXX) $(CXXFLAGS) -c tauler.cpp

candy.o: candy.cpp candy.h definicions.h
	$(CXX) $(CXXFLAGS) -c candy.cpp

clean:
	rm -rf *.o app.exe