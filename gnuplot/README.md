gnuplot
===============

gnuplot sample <br/>

plot sin wave <br/>

gnuplot is a portable command-line driven graphing utility <br/>
http://www.gnuplot.info/ <br/>

###  install gnuplot
% brew install gnuplot <br/>
https://formulae.brew.sh/formula/gnuplot <br/>

### sin.plt <br/>
gnuplot script <br/>
plot sin wave <br/>

run script <br/>
% gnuplot
gnuplot \> load "script/sin.plt" <br/>

plot sin wave <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gnuplot/result/screenshot_sin_plt.png" width="300" /><br/>

### plot_sin.c <br/>
plot sin wave with popen <br/>

build code <br/>
% gcc src/plot_sin.c src/keyboard.c -o plot <br/>

run code <br/>
% ./plot <br/>

plot sin wave <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gnuplot/result/screenshot_plot_sin.png" width="300" /><br/>

### plot_sin_cgnuplot.cpp <br/>
plot sin wave with CGnuplot <br/>

build code <br/>
% g++ src/plot_sin_cgnuplot.cpp -o cgplot <br/>

run code <br/>
% ./cgplot <br/>

plot sin wave <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gnuplot/result/screenshot_cgplot_sin.png" width="300" /><br/>

### singen.c <br/>
genarete sin wave data to stdout <br/>

build code <br/>
% gcc src/singen.c -o singen <br/>

run code <br/>
% ./singen <br/>

display as below <br/>
0 <br/>
45 <br/>
90 <br/>
135 <br/>


### gp_wav.sh <br/>
shell with gnuplot script <br/>
plot input data to png file <br/>

run script <br/>
output only the first 5000 points <br/>
% ./singen  | head -5000 | script/gp_wav.sh > singen.png

created singen.png <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gnuplot/result/singen.png" width="300" /><br/>


### Reference <br/>
- https://github.com/gnuplot/gnuplot

