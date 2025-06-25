# Python: Class Pixels
# 2x2  Color Matrix Pixels
# 3x3  Color Matrix Pixels
# 4x4  Color Matrix Pixels
# Checker Board Pattern Pixels
# Static method
 # createColorMatrixPixels()
 # createCheckerBoardPixels()
# dumpPixels()
 # 2025-04-10 K.OHWADA
 
# Color
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (200, 200, 200)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

COLOR_MATRIX_PIXELS_2x2 = [ 
    [ (255,   0,   0),  # Red
    ( 0, 255,   0) ] , # Green
    [ (0,   0, 255) , # Blue
    (255, 255,   0) ]  # Yellow
]

COLOR_MATRIX_PIXELS_3x3 = [
    [ (255,   0,   0) , # Red
    (0, 255,  0) , # Lime
    (0,  0, 255) ], # Blue
    [(255, 0, 255),  # Fuchsia
    (0,  0,  0),  # Black
    (255, 255,  0) ],  # Yellow
    [ (0,   0, 128), # Navy
    (0, 128,  0), # Green
    (128,  0,   0) ] # Maroon
]

COLOR_MATRIX_PIXELS_4x4 = [
    [ (255,   0,  0), # Red
    (0, 255,  0), # Lime
    (255,  255,  255),  # White
    (0,   0, 255) ], # Blue
    [ (0, 128,   0), # Green
    (192,  192, 192), # Silver
    (0,  255, 255), # Aqua
    (128,  0, 128) ], # Purple
    [ (128,   0,  0), # Maroon
    (128,  128, 0), # Olive 
    (128,  128, 128), # Gray
    (0,  0, 128) ], # Navy
    [ (0,  128, 128), # Teal
    (255, 0, 255),  # Fuchsia
    (0,  0,  0),  # Black
    (255, 255,  0) ] # Yellow
]

class Pixels:

    @classmethod
    def createColorMatrixPixels(cls, num, scale):
        matrix = cls.getColorMatrixPixels(cls, num)
        return cls.scalePixels(cls, matrix, num, num, scale)
# end

    @classmethod
    def createCheckerBoardPixels(cls, size, scale): 
        matrix = cls.createCheckerBoardPixels_color(cls, size, size)
        return cls.scalePixels(cls, matrix, size, size, scale)
# end

    @classmethod
    def dumpPixels(cls, pixels, width,  height):
        print()
        for j in range(height):
            for i in range(width):
                rgb = pixels[j][i]
                print(j, i, rgb)
# end
        print()
# end

    def getColorMatrixPixels(self, num):
        matrix = COLOR_MATRIX_PIXELS_2x2
        if num == 3:
            matrix = COLOR_MATRIX_PIXELS_3x3
        elif num == 4:
            matrix = COLOR_MATRIX_PIXELS_4x4
# end
        return matrix
# end


    def scalePixels(self, src,  src_width, src_height, scale):
        buf_width = scale * src_width
        buf_height = scale * src_height
        buf = [ [ [255, 255, 255] for i in range(buf_width)] for j in range(buf_height)]
        for y in range(src_height):
            for x in range(src_width):
                rgb =  src[y][x]
                for j in range(scale):
                    for i in range(scale):
                        yy = y*scale + j
                        xx = x*scale + i
                        buf[yy][xx] = rgb
# end
        return buf
# end

    def createCheckerBoardPixels_color(self, width, height, color1= GRAY, color2=BLACK):  
        buf = [ [ WHITE for i in range(width)] for j in range(height)]
        is_width_even = (width%2 == 0)
        cnt=0
        for y in range(height):
            if is_width_even: cnt += 1 
            for x in range(width):
                cnt+=1
                color = color1 if (cnt%2 == 0 ) else color2
                buf[y][x] = color
# for end
        return buf
# end


