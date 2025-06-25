# class Bmp:
# 2025-04-10  K.OHWADA


FILE_HEADERSIZE = 14
INFO_HEADERSIZE = 40
BF_TYPE = b'BM'
PLANES = 1
BITCOUNT = 24


class Bmp:
    def __init__(self):
        self.bf_type = BF_TYPE #シグネチャ 'BM'
        self.bf_size =0  #ファイルサイズ
        self.reserved1=0  #予約領域1
        self.reserved2 =0  #予約領域2
        self.offbits =0 #ファイル先頭から画像データまでのオフセット[byte] ※誤った値だとアプリによっては表示失敗した
        self.bc_size = INFO_HEADERSIZE #ヘッダーサイズ
        self.width =0  #幅[dot]
        self.height =0 #高さ[dot]
        self.planes = PLANES #プレーン数 常に1
        self.bitcount = BITCOUNT #byte/1pixel(1byteを表すために必要なbit)
        self.compression =0 #圧縮形式 0 - BI_RGB（無圧縮）
        self.size_image =0 #画像データサイズ[byte]
        self.x_ppm=0 #X方向解像度[dot/m] 0の場合もある
        self.y_ppm=0 #Y方向解像度[dot/m] 0の場合もある
        self.color_used=0 #使用する色の数 ※0だとアプリによっては表示失敗した
        self.color_important=0 #重要な色の数 0の場合もある
        self.color_table = []
        self.pixels = []
# end

    def printHeader(self):
        print('bf type: ', self.bf_type)
        print('bf_size: ', self.bf_size)
        print('reserved1:', self.reserved2)
        print('reserved2:', self.reserved1)
        print('offbits: ', self.offbits)
        print('bc_size: ', self.bc_size)     
        print('width: ', self.width)
        print('height: ', self.height)
        print('planes: ', self.planes)
        print('bitcount: ',self.bitcount)
        print('compression:', self.compression)
        print('size_imag: ', self.size_image )
        print('x_ppm: ', self.x_ppm)
        print('y_ppm: ', self.y_ppm)
        print('color_used:', self.color_used)
        print('color_important:', self.color_important)
# end

    def setWriteHeader(self):
        lenOfColors = len(self.color_table)
        self.color_used = lenOfColors >> 2
        lenOfPixels = len(self.pixels)
        self.offbits = FILE_HEADERSIZE + INFO_HEADERSIZE + lenOfColors
        self.bf_size = self.offbits + self.size_image
# end

    def readFile(self, fpath):
        f =  open(fpath, 'rb')
    # BMP file header
        self.bf_type = f.read(2)
        self.bf_size = int.from_bytes(f.read(4), byteorder='little')
        self.reserved1    = int.from_bytes(f.read(2), byteorder='little')
        self.reserved2    = int.from_bytes(f.read(2), byteorder='little')
        self.offbits      = int.from_bytes(f.read(4), byteorder='little')
    # BMP information header
        self.bc_size = int.from_bytes(f.read(4), byteorder='little')
        self.width     = int.from_bytes(f.read(4), byteorder='little')   
        self.height    = int.from_bytes(f.read(4), byteorder='little')
        self.planes       = int.from_bytes(f.read(2), byteorder='little')
        self.bitcount     = int.from_bytes(f.read(2), byteorder='little')
        self.compression  = int.from_bytes(f.read(4), byteorder='little')
        self.size_image    = int.from_bytes(f.read(4), byteorder='little')
        self.x_ppm = int.from_bytes(f.read(4), byteorder='little')
        self.y_ppm = int.from_bytes(f.read(4), byteorder='little')
        self.color_used  = int.from_bytes(f.read(4), byteorder='little')
        self.color_important = int.from_bytes(f.read(4), byteorder='little')
        # self.color_table = f.read(self.color_used * 4)   
        self.pixels = f.read(self.size_image)
# end

    def writeFile(self, outfile):
        self.setWriteHeader()
        f = open(outfile, 'wb')
    #FILE_HEADER
        b = bytearray(self.bf_type)              
        b.extend(self.bf_size.to_bytes(4, 'little')) 
        b.extend( self.reserved1.to_bytes(2, 'little'))      
        b.extend( self.reserved2.to_bytes(2, 'little'))       
        b.extend( self.offbits.to_bytes(4, 'little')) 
    #INFO_HEADER
        b.extend((0x28).to_bytes(4, 'little'))      
        b.extend(self.width.to_bytes(4, 'little'))          
        b.extend(self.height.to_bytes(4, 'little'))          
        b.extend(self.planes.to_bytes(2, 'little'))         
        b.extend(self.bitcount.to_bytes(2, 'little'))         
        b.extend(self.compression.to_bytes(4, 'little'))             
        b.extend(self.size_image.to_bytes(4, 'little')) 
        b.extend(self.x_ppm.to_bytes(4, 'little'))         
        b.extend(self.y_ppm.to_bytes(4, 'little'))         
        b.extend(self.color_used.to_bytes(4, 'little')) 
        b.extend(        self.color_important.to_bytes(4, 'little'))             # b.extend(elf.color_tables)
        b.extend(self.pixels)
        f.write(b)
# end

    def check(self):
        if self.bf_type != BF_TYPE:
            print("not BM type")
            return False
        if self.bitcount != BITCOUNT:
            print("unmatch bitcount")
            return False
# end
        return True
# end


    def getPixels(self):
        line_width = int(self.size_image / self.height)
        print('line_width:', line_width)
        arr = [ [ (0, 0 ,0) for i in range(self.width) ] for j in range(self.height)]
        for y in range(self.height):
            for x in range(self.width):
                yy = (self.height - 1) - y
                index = (y * line_width) + 3*x
                b = self.pixels[index]
                g = self.pixels[index+1]
                r = self.pixels[index+2]
                arr[yy][x] = (r, g, b)
# end
        return (self.width, self.height, arr)
# end


    def setPixels(self, width, height, arr):
# data for the horizontal lines is a multiple of 4.
        line_width = 3*width + width%4
        print('line_width: ', line_width)
        self.size_image =  line_width * height
        self.width = width
        self.height = height
        self.pixels =  self.size_image * [0]
        for y in range(height):
            for x in range(width):
                yy = (height -1) - y            
                index = (y * line_width) + 3*x
                r, g, b = arr[yy][x]
                self.pixels[index] = b
                self.pixels[index+1] = g
                self.pixels[index+2] = r
# end


