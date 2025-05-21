# Python: show matplotlib .rcParams
# 2025-04-10  K.OHWADA

#   https://qiita.com/cnloni/items/20b5908fbae755192498

import matplotlib as mpl

# main
params = mpl.rcParams

print( 'rcParams: ')
print( params )
print()
print( 'figsize: ', params['figure.figsize'] )
print( 'dpi: ', params['figure.dpi'] )
print( 'font family: ', params['font.family'] )

# figsize: [6.4, 4.8]
# dpi: 100.0
# font family:  ['sans-serif']