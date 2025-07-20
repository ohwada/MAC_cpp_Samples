# Python: animate Analog Clock using PlotItem
# create anime gif using Pillow Image
# 2025-04-10  K.OHWADA

# https://github.com/ddside/analog_clock_python/blob/main/analog_clock.py

from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from PIL import Image
import numpy as np
import datetime
import glob
import sys, os

WIN_TITLE= "Analog Clock"
PX = 10
PY = 10
WIDTH = 512
HEIGHT = 512

BOTTOM = "bottom"
LEFT =  "left"

RESIZE_INTERVAL = 500 # msec
UPDATE_INTERVAL = 500 # msec

# number of points to draw circle
NUM_CIRCLE_POINTS =1000


# time for the hand to rotate one lap
ONE_LAP_HOUR = 12 # 12 houurs
# ONE_LAP_MIN = 60 # 60 minutess = one hour
# ONE_LAP_SEC = 60 # 60 secinds = one minute

# angle per unit time
SEC_DEG = 6 # 360/ONE_LAP_HOUR
MIN_DEG = 6 # 360/ONE_LAP_MIN
HOUR_DEG = 30 # 360/ONE_LAP_HOUR

# unit conversion
ONE_HOUR_MIN = 60 # one hour = 60minutes
ONE_MIN_SEC = 60 # one minute = 60 srconds

# second hand scale placed every 5 seconds on the outer circle
MAX_SEC = 60 # same  ONE_LAP_SEC
SEC_INTERVAL = 5

MIN_HOUR = 1
MAX_HOUR = 13 # MIN_HOUR + ONE_LAP_HOUR

DATE_FORMAT = '%Y-%m-%d %a'
TIME_FORMAT = '%H:%M:%S'
TIME_TEXT= '00:00:00'

RADIUS = 1

LINE_LENGTH_SEC_SCALE = 0.05
LINE_LENGTH_5SEC_SCALE = 0.1

PEN_WIDTH_SEC_SCALE= 2
PEN_WIDTH_5SEC_SCALE = 4

RATIO_HOUR_TEXT = 0.8
RATIO_SECOND_HAND = 0.85
RATIO_MINUTE_HAND = 0.8
RATIO_HOUR_HAND = 0.5

POS_HOUR_TEXT =  RADIUS * RATIO_HOUR_TEXT
LINE_LENGTH_SECOND_HAND =  RADIUS * RATIO_SECOND_HAND
LINE_LENGTH_MINUTE_HAND = RADIUS * RATIO_MINUTE_HAND
LINE_LENGTH_HOUR_HAND = RADIUS * RATIO_HOUR_HAND

FONT_SIZE_HOUR_TEXT = 48
FONT_SIZE_DATETIME = 32

PEN_WIDTH_CIRCLE = 4
PEN_WIDTH_HOUR_HAND =12
PEN_WIDTH_MINUTE_HAND =6
PEN_WIDTH_SECOND_HAND =3
 
RED = (255, 0,0)
GREEN = (0, 255,0)
BLUE = (0, 0,255)

# Anime gif
FRAMES = 120 # 60 sec

DIR_CLOCK = "clock"

FNAME_FORMAT = "clk_{:03d}.bmp"

GLOB_PATHNAME = "clock/*.bmp"

GIF_DURATION= 500 # msec

GIF_LOOP= 1 

GIF_OUTFILE = "pg_analog_clock_anime_write.gif"

USAGE_FORMAT = "Usage: python {:s} [anime gif]"


def create_amine_gif():
	file_list = sorted(glob.glob(GLOB_PATHNAME))
	images = []
	for f in file_list:
		if  os.path.isfile(f):
			im = Image.open(f)
			images.append(im)
# end
# save the images as an animated GIF
	images[0].save(GIF_OUTFILE,
	save_all=True,
	append_images = images[1:],
	duration= GIF_DURATION,  
	loop=GIF_LOOP
	)
	print('create ', GIF_OUTFILE)
# end


class Window(pg.GraphicsLayoutWidget):
	def __init__(self):
		super().__init__()
		self.setWindowTitle(WIN_TITLE)
		self.setGeometry( PX, PY, WIDTH, HEIGHT)
		pg.setConfigOptions(antialias=True)
		self.init_clock()
# end

	def init_clock(self):
		self.graph = self.addPlot()
		self.graph.showAxis(BOTTOM, False)
		self.graph.showAxis(LEFT, False)
		self.graph.setAspectLocked(lock=True)
		self.graph.setMouseEnabled(x=False, y=False)
		self.init_hands(self.graph)
		self.draw_circle(self.graph)
		self.draw_sec_scales(self.graph)
		self.draw_datetime_text(self.graph)
		self.draw_hour_texts(self.graph)
# end

	def init_hands(self, graph):
		pen_second = pg.mkPen(RED, width=PEN_WIDTH_SECOND_HAND)
		pen_second.setCapStyle(QtCore.Qt.RoundCap)
		self.second_hand_plot = graph.plot(pen=pen_second)
		pen_minute = pg.mkPen(GREEN, width=PEN_WIDTH_MINUTE_HAND)
		pen_minute.setCapStyle(QtCore.Qt.RoundCap)
		self.minute_hand_plot = graph.plot(pen=pen_minute)
		pen_hour = pg.mkPen(GREEN, width=PEN_WIDTH_HOUR_HAND)
		pen_hour.setCapStyle(QtCore.Qt.RoundCap)
		self.hour_hand_plot = graph.plot(pen=pen_hour)
# end

	def draw_circle(self, graph):
		inspace_circle  = np.linspace(0, 2 * np.pi, NUM_CIRCLE_POINTS)
		x = RADIUS * np.cos(inspace_circle)
		y =  RADIUS * np.sin(inspace_circle)
		graph.plot(x, y, pen=pg.mkPen(width=PEN_WIDTH_CIRCLE) )
# end

	def draw_sec_scales(self, graph):
		for second in range(MAX_SEC):
			line_length =   LINE_LENGTH_5SEC_SCALE if second % SEC_INTERVAL == 0 else  LINE_LENGTH_SEC_SCALE
			pen_width = PEN_WIDTH_5SEC_SCALE if second % SEC_INTERVAL == 0  else   PEN_WIDTH_SEC_SCALE
			rad_sec_scale = np.radians(360 * (second / 60))
			x1 = np.sin(rad_sec_scale) *  RADIUS
			x2 = np.sin(rad_sec_scale) * ( RADIUS - line_length)
			y1 = np.cos( rad_sec_scale) *  RADIUS
			y2 = np.cos(rad_sec_scale) * ( RADIUS - line_length)
			pen_sec_scale = pg.mkPen(width=pen_width)
			pen_sec_scale.setCapStyle(QtCore.Qt.RoundCap)
			graph.plot([x1, x2], [y1, y2], pen=pen_sec_scale )
# end

	def draw_datetime_text(self, graph):
		dt_now = datetime.datetime.now()
		date_str = dt_now.strftime(DATE_FORMAT)
		self.date_text = pg.TextItem(text=date_str, anchor=(0.5, 0.5))
		yo = - RADIUS / 3.5
		self.date_text.setPos(0, yo)
		font_datetime = QtGui.QFont()
		font_datetime .setPixelSize( FONT_SIZE_DATETIME )
		self.date_text.setFont(font_datetime)
		graph.addItem(self.date_text)
		self.time_text = pg.TextItem(text=TIME_TEXT, anchor=(0.5, 0.5))
		y1 = yo - (RADIUS * 0.2)
		self.time_text.setPos(0, y1)
		self.time_text.setFont(font_datetime)
		graph.addItem(self.time_text)
# end

	def draw_hour_texts(self, graph):
		font_hour_text = QtGui.QFont()
		font_hour_text.setPixelSize(FONT_SIZE_HOUR_TEXT )
		self.hour_texts = []
		for hour in range( MIN_HOUR,  MAX_HOUR, 1):
			rad_hours = np.radians( hour * HOUR_DEG )
			px = np.sin(rad_hours) * POS_HOUR_TEXT
			py = np.cos(rad_hours) * POS_HOUR_TEXT
			hour_text = pg.TextItem(text=str(hour), anchor=(0.5, 0.5))
			hour_text.setPos(px, py)
			hour_text.setFont(font_hour_text)
			graph.addItem(hour_text)
			self.hour_texts.append(hour_text)
# end

	def set_param(self, is_anime_gif):
		self.cnt = 0
		self.is_save_graph = False
		if is_anime_gif:
			self.is_save_graph = True
			os.mkdir(DIR_CLOCK)
#end
		self.start_clock()
# end

	def start_clock(self):
		update_timer = QtCore.QTimer(self)
		update_timer.timeout.connect(self.update_clock)
		update_timer.start(UPDATE_INTERVAL)
		resize_timer = QtCore.QTimer(self)
		resize_timer.timeout.connect(self.resize_text)
		resize_timer.start(RESIZE_INTERVAL)
# end

	def update_clock(self):
		dt_now = datetime.datetime.now()
		self.update_hands(dt_now)
		time_str = dt_now.strftime(TIME_FORMAT)
		self.time_text.setText(time_str)
		if self.is_save_graph:
			if self.cnt < FRAMES:
				self.cnt +=1
				self.save_plot(self.graph, self.cnt)
			elif self.cnt == FRAMES:
				self.is_save_graph = False
				create_amine_gif()
# end

	def update_hands(self, dt_now):
		hour= dt_now.hour
		minute = dt_now.minute
		second = dt_now.second
		deg_second = second * SEC_DEG
		deg_minute = int( (minute + float( float(second) / ONE_MIN_SEC) ) * MIN_DEG)
		deg_hour = int( (hour  + float( float(minute) / ONE_HOUR_MIN) ) * HOUR_DEG )
		rad_second = np.radians(deg_second)
		x_second = np.sin(rad_second) * LINE_LENGTH_SECOND_HAND
		y_second = np.cos(rad_second)  * LINE_LENGTH_SECOND_HAND
		self.second_hand_plot.setData([0, x_second], [0, y_second])
		rad_minute = np.radians(deg_minute)
		x_minute = np.sin(rad_minute) *  LINE_LENGTH_MINUTE_HAND
		y_minute = np.cos(rad_minute) *  LINE_LENGTH_MINUTE_HAND
		self.minute_hand_plot.setData([0, x_minute], [0, y_minute])
		rad_hour = np.radians(deg_hour)
		x_hour = np.sin(rad_hour) *  LINE_LENGTH_HOUR_HAND
		y_hour = np.cos(rad_hour) *  LINE_LENGTH_HOUR_HAND
		self.hour_hand_plot.setData([0, x_hour], [0, y_hour])
# end

	def resize_text(self):
		ratio_w = self.width()/  WIDTH
		ratio_h = self.height()/HEIGHT  
		ratio_min = min(ratio_w, ratio_h)
		new_font_size = int( FONT_SIZE_DATETIME * ratio_min)
		font_text = QtGui.QFont()
		font_text.setPixelSize(new_font_size )
		self.date_text.setFont(font_text)
		self.time_text.setFont(font_text)
		font_hour_text = QtGui.QFont()
		font_hour_text.setPixelSize(new_font_size)
		for hour_text in self.hour_texts:
			hour_text.setFont(font_hour_text)
# end

	def save_plot(self, graph, cnt):
		fname = FNAME_FORMAT.format(cnt)
		outfile = os.path.join(DIR_CLOCK, fname)
		graph.writeImage(outfile)
# end


def main(is_anime_gif):
	app = pg.mkQApp()
	win = Window()
	win.set_param(is_anime_gif)
	win.show()
	sys.exit(app.exec_())
# end

def usage(script):
    usage = USAGE_FORMAT.format(script)
    print(usage)
# end


# main
fpath = ""
is_anime_gif = False
is_resize = False
args = sys.argv
argc = len(args)
if argc < 2:
    usage(args[0])
elif argc >= 2:
   is_anime_gif = int(args[1])
# end
main(is_anime_gif)

  
