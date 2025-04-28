# Python: get environ
# 2025-04-10  K.OHWADA


import os


def print_environ(key):
    print( key, ' : ', os.environ.get(key) )
# end


# main
print_environ( 'HOME')

print_environ( 'USER')

print_environ( 'LANG')

print_environ( 'PWD')

# https://kledgeb.blogspot.com/2013/04/ubuntu-10-xdg-base-directory.html
print_environ( 'XDG_DATA_DIRS') # Linux


