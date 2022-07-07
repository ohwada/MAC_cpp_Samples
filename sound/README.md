sound
===============

### sound.h
play sound using paplay or afplay <br/>

paplay: Play back audio files on a PulseAudio sound server <br/>
https://linux.die.net/man/1/paplay <br/>

afplay: Audio File Play <br/>
https://ss64.com/osx/afplay.html <br/>

Build and Run <br/>
% gcc test_sound.c -o sound <br/>
% ./sound <br/>

Note: <br/>
paplay can not play mp3 aiff <br/>
afplay can not play oga <br/>

### sound2.h
play oga <br/>
Require: paplay <br/>
