# Python: show default Window Size
# change Window Size
# 2025-04-10  K.OHWADA


import matplotlib.pyplot as plt
import matplotlib as mpl
import sys


def ex1():
# show params
	params = plt.rcParams
	print('figsize: ', params['figure.figsize'] )  # [6.4, 4.8]
	print('dpi: ', params['figure.dpi'] )  # 100.0
	print('backend: ', params['backend'])  # MacOSX
# end


def ex2():
# create default Figure
	fig2  = plt.figure()
	print(' plt.figure() : ', fig2)  #  Figure(640x480)
# get the current Figure'	
	print( "gcf: ", plt.gcf() )  # Figure(640x480)
	plt.show()
# end


def ex3():
# show current Figure
	print('figums: ', plt.get_fignums() ) #  []
# If there is currently no figure on the pyplot figure stack, 
# a new one is created using figure()
	print( "gcf: ", plt.gcf() ) # Figure(640x480)
	print('figums: ', plt.get_fignums() ) #  [1]
# end


def ex4():
# change Window Size
	figsize = ( 3.2, 2.4 ) # QVGA
# If num is a string, the figure label and the window title is set to this value. 
# figsize(float, float), Width, height in inches.
	fig4 = plt.figure(num='QVGA', figsize=figsize )
	print(' plt.figure(figsize=(3.2, 2,4)) : ', fig4)  # Figure(320x240)
	plt.show()
# end


def ex5():
# change Window Posision Size
	mpl.use('QtAgg') # require PyQt
	manager = plt.get_current_fig_manager()
	print(manager)  # matplotlib.backends.backend_qt.FigureManagerQT 
	win = manager.window
	print(win) # matplotlib.backends.backend_qt.MainWindow
	win.setGeometry(50, 100, 320, 240)
	win.setWindowTitle('PyQt QVGA')
	print( "gcf: ", plt.gcf() ) # Figure(640x480)
	plt.show()
# end


# main
args = sys.argv
argc = len(args)
script = args[0]

if argc < 2:
	print("Usage: python %s  <num>" % script)
	exit()
# end

num = int(args[1])
if num == 1:
	ex1()
	exit()
elif num == 2:
	ex2()
	exit()
elif num == 3:
	ex3()
	exit()
elif num == 4:
	ex4()
	exit()
elif num == 5:
	ex5()
	exit()
# end



