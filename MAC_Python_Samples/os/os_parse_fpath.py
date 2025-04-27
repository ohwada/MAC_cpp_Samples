# Python: parse file path
# 2025-04-10  K.OHWADA

# https://note.nkmk.me/python-os-basename-dirname-split-splitext/#google_vignette

import  os

fpath = "/dir/subdir/sample.txt"

print ('fpath: ', fpath)

print( 'dirname: ', os.path.dirname(fpath) )

basename = os.path.basename(fpath)

print( 'basename: ', basename )

splitext = os.path.splitext(basename)

print(' splitext: ',  splitext)

fname = os.path.splitext( os.path.basename(fpath) )[0]

print('fname: ', fname)

dot_ext = os.path.splitext( os.path.basename(fpath) )[1]

print('dot_ext: ', dot_ext)

ext= os.path.splitext(os.path.basename(fpath) )[1][1:]

print('ext: ', ext)

 


