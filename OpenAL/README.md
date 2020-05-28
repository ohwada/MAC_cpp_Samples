OpenAL
===============

OpenAL Sample <br/>
play audio file  <br/>
 OpenAL is a cross-platform 3D audio API appropriate  <br/>
http://openal.org/ <br/>


###  requires
- macOS OpenAL.framework <br/>
https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview/CoreAudioFrameworks/CoreAudioFrameworks.html <br/>

- alure <br/>
% brew install alure <br/>
https://formulae.brew.sh/formula/allure <br/>

## Note 
display following warning when build <br/>
but don't mind <br/>
warning: 'alcOpenDevice' is deprecated: first deprecated in
      macOS 10.15 <br/>

 macOS Catalina 10.15 Release Notes <br/>
The OpenAL framework is deprecated <br/>
https://developer.apple.com/documentation/macos_release_notes/macos_catalina_10_15_release_notes <br/>

## play_tone.cpp <br/>
play tone <br/>

### build sample code 
% g++ play_tone.cpp -o tone -framework OpenAL <br/>

### run sample code 
Usage: ./tone [freq] [duration] <br/>
ex) <br/>
% ./tone  440 1 <br/>


## play_wav.cpp <br/>
play wav file with alure <br/>

### build sample code 
% g++ play_wav.cpp -o play -framework OpenAL -I/usr/local/Cellar/alure/1.2_1/include/  -L/usr/local/Cellar/alure/1.2_1/lib/ -lalure-static <br/>

### run sample code 
Usage: ./play \ <wavFile \> <br/> 
ex) <br/>
% ./play ./media/church-chime-daniel_simon.wav <br/>


## play mp3 file 
see libmad <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libmad <br/>


## play ogg file
see libvorbis <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libvorbis <br/>


## play flac file
see libflac <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libflac <br/>

## play aac file
see fdk_aac <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/fdk_aac <br/>

### Docement
- https://qiita.com/ohwada/items/f1f171908f8af769c56b

### Reference <br/>
- http://openal.org/
- https://kcat.strangesoft.net/alure.html

