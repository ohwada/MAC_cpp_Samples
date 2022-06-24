#!/bin/sh

# Example script to launch a 1-player (vs. computer) game of 3dpong on the
# current X-Window display

# By Bill Kendrick; 1997-2004

3dpong $DISPLAY --computer -g 0.5 -n 0.125 $*
