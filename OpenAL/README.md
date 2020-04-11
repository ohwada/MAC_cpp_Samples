OpenAL
===============

OpenAL Sample <br/>
play tone, wav file <br/>

###  requires
- macOS OpenAL.framework <br/>
https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview/CoreAudioFrameworks/CoreAudioFrameworks.html <br/>
- ALURE <br/>
% brew install alure <br/>
https://formulae.brew.sh/formula/alure <br/>


## test_tone.cpp <br/>
play 440 Hz tone for 3 seconds

% g++ test_tone.cpp  -framework OpenAL

## test_wav.cpp <br/>
play wav file <br/>

% g++ test_wav.cpp  -framework OpenAL -I/usr/local/Cellar/alure/1.2_1/include/  -L/usr/local/Cellar/alure/1.2_1/lib/ -lalure-static

### Reference <br/>
- https://openal-soft.org/
- https://kcat.strangesoft.net/alure.html



