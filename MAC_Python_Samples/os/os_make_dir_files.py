# Python: make sub directory and files for os_walk.py
# 2025-04-10  K.OHWADA

import os

def mkfile(fpath):
	f = open(fpath, 'w')
	f.write(fpath)  
	f.close()
# end

def makefies(dir, name, ext, max):
	for i in range(max):
		fname = name + str(i) + "." + ext
		fpath = os.path.join(dir, fname)
		print(fpath)
		mkfile(fpath)
# end

def mkdirfiles(parent, name, ext, max):
	subdir = os.path.join(parent, name)
	print(subdir)
	os. makedirs(subdir)
	makefies(subdir, name, ext, max)
# end

# main
PARENT = "test"
MAX = 5
EXT = "txt"
mkdirfiles(PARENT, "aa", EXT, MAX)
mkdirfiles(PARENT, "bb", EXT, MAX)




