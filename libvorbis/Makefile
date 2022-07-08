### 2022-06-01 K.OHWADA

CXX =g++
CXXFLAGS=-Wall -std=c++11
LIBS=-lvorbis  -logg
LIBS_ENCODE=-lvorbisenc
LIBS_PLAY= -framework OpenAL 



decode: src/conv_ogg_to_wav.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

encode: src/conv_wav_to_ogg.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) $(LIBS_ENCODE)

list: src/conv_ogg_to_wav_list.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

play: src/play_ogg.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) $(LIBS_PLAY)


%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o
