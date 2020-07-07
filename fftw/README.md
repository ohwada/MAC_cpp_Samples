fftw
===============

fftw sample <br/>
calc FFT <br/>

fftw is a C subroutine library for computing the discrete Fourier transform <br/>
http://www.fftw.org/ <br/>

###  install fftw
% brew install fftw <br/>
https://formulae.brew.sh/formula/fftw <br/>

###fft_sin.cpp <br/>
calc FFT of single sin wave <br/>

build sample code <br/>
% g++ fft_sin.cpp -o fft `pkg-config --cflags --libs fftw3` <br/>

run sample code  <br/>
Usage: ./fft \< freq \>  <br/>
%  ./fft 440<br/>

display as below <br/>
createSin: 440 <br/>
index 10 <br/>
max 222778 <br/>
freq 430.664 <br/>

plot graph by plot_fft.py <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/fftw/result/plot_fft_sin_440.png" width="300" /><br/>


### Reference <br/>
- https://github.com/FFTW/fftw3

