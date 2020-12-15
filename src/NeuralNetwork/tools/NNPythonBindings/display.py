#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from . import structures as s
from . import exceptions

import IPython
import numpy
from PIL import Image

def show(MMImageInstance, zoom = 3, black = (0, 0, 0), white = (255, 255, 255)):
	w = MMImageInstance.w
	h = MMImageInstance.h
	
	img = Image.new('RGB', (w * zoom, h * zoom), white)
	for x in range(w):
		for y in range(h):
			pixelIdx = y * h + x
			pixelRaw = MMImageInstance.pixelsTable[pixelIdx].pixelValue
			pixel = pixelRaw == 1.0
			color = white if pixel else black
			for i in range(x * zoom, (x + 1) * zoom):
				for j in range(y * zoom, (y + 1) * zoom):
					img.putpixel((i, j), color)
	IPython.display.display(img)
	
		