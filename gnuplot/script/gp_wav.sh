#!/usr/local/bin/gnuplot

# plot input data to png file
# reference : https://bluefish.orz.hm/sdoc/fftw_sim.html

set terminal png
set nokey
plot [:][:] '< cat -' with line linewidth 5

