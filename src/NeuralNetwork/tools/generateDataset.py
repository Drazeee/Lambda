#!/usr/bin/env python3
# -*- coding: utf-8 -*-

global outputDir, noImagesPerChar, fonts_basepath, fonts, chars, imgSize, tolerence # Bouhh des globals cépabo


outputDir = "/Users/maxime/datasetWC" # Dossier de sortie du dataset (ne doit pas déjà exister)

noImagesPerChar = 2000 # Combien d'images par caractères

fonts_basepath = "/System/Library/Fonts/" # Chemin ou sont les fonts sur l'ordi (par défaut pour macOS)

fonts = ["Helvetica.ttc","Courier.dfont","Menlo.ttc","Supplemental/Comic Sans MS.ttf","Supplemental/Courier New Italic.ttf","Supplemental/Impact.ttf","Times.ttc","Monaco.dfont","AppleSDGothicNeo.ttc","Avenir Next Condensed.ttc","Geneva.dfont","MarkerFelt.ttc","NewYork.ttf","Noteworthy.ttc","Palatino.ttc","Optima.ttc","SFNSDisplayCondensed-Black.otf","Supplemental/AmericanTypewriter.ttc","Supplemental/Apple Chancery.ttf","Supplemental/Athelas.ttc","Supplemental/Bradley Hand Bold.ttf","Supplemental/Chalkboard.ttc","Supplemental/Copperplate.ttc","Supplemental/Didot.ttc","Supplemental/Futura.ttc","Supplemental/Georgia Bold Italic.ttf","Supplemental/Kefa.ttc","Supplemental/Krungthep.ttf","Supplemental/Luminari.ttf","Supplemental/PTSans.ttc","Supplemental/PTSerif.ttc","Supplemental/Rockwell.ttc","Supplemental/Silom.ttf","Supplemental/STIXGeneral.otf","Supplemental/SuperClarendon.ttc","Supplemental/Telugu MN.ttc"] # Listes des polices à utiliser pour les images


multithreading = True # Utilise plusieurs processus & threads pour générer les images: bcp plus rapide mais bouffe tout le CPU.



import sys
import os
import random
import multiprocessing
import time


try:
	from PIL import Image
	from PIL import ImageFont
	from PIL import ImageDraw
except ModuleNotFoundError:
	print ("PIL/Pillow n'est pas installé.")
	print ("https://pillow.readthedocs.io/en/stable/installation.html")
	sys.exit(1)
	
	
# Ne pas changer les paramètres qui suivent

chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabdefghijklmnqrt0123456789.!?-%()&$\":;/+*=@#€àâäéèêëîïôöùüûÀÂÄÉÈÊËÎÏÔÖÙÜÛçÇ" # Characters list and order (no lowercased)
merged = "COPSUVWXYZ" # Characters that look too similar between upper & lower

imgSize = 32 # Image width & height
tolerence = 200 # Tolerence of pixel detection when moving text to 0,0


class ImgGeneratorThread(multiprocessing.Process): # Generator thread
	def __init__(self, char, idx):
		global outputDir, noImagesPerChar, fonts_basepath, fonts, chars, imgSize, tolerence
		multiprocessing.Process.__init__(self)
		self.char = char
		self.idx = idx
		self.isMerged = char in merged
		
	def run(self):
		for j in range(noImagesPerChar): # Generate specific image
			# Random Color
			r = random.randint(0, 100)
			g = random.randint(0, 100)
			b = random.randint(0, 100)
			
			# Default position
			y = 0
			x = 0
			
			#Random font & font size
			size = random.randint(10,30)
			font = random.choice(fonts)
			
			t = self.char
			if self.isMerged:
				if random.randint(0,1):
					t = self.char.lower()
			
			img = Image.new("RGB", size = (imgSize, imgSize), color="white")
			draw = ImageDraw.Draw(img)
			fontpath = os.path.join(fonts_basepath, font)
			try:
				font = ImageFont.truetype(fontpath, size)
			except: # Invalid font
				print ("Police invalide: \"%s\"" % fontpath)
				sys.exit(3)
				

			# Draw text on initial image
			draw.text((x, y), self.char, (r,g,b), font=font)
			
			
			# Crop image to edge text on 0,0
			shouldBreak = False
			for topPadding in range(imgSize):
				for a in range(imgSize):
					rc, gc, bc = img.getpixel((a,topPadding))
					moy = (rc + gc + bc) * 0.33
					if moy < tolerence:
						shouldBreak = True
						break
				if shouldBreak:
					break
					
			shouldBreak = False
			for leftPadding in range(imgSize):
				for a in range(topPadding, imgSize):
					rc, gc, bc = img.getpixel((leftPadding,a))
					moy = (rc + gc + bc) * 0.33
					if moy < tolerence:
						shouldBreak = True
						break
				if shouldBreak:
					break
			
			
			# Resize cropped text
			imCrop = img.crop((leftPadding, topPadding, imgSize, imgSize))
			img = Image.new("RGB", size = (imgSize, imgSize), color="white")
			img.paste(imCrop, (0,0))
			
			# Save image
			img.save(os.path.join(outputDir, str(self.idx), '%s.bmp'%j))
			
			
t0 = time.time()

threads = [] # List of existing threads

# Test if dir already exists
if os.path.isdir(outputDir) or os.path.isfile(outputDir):
	print ("Le dossier de sortie existe déjà")
	sys.exit(2)

# Generate images
idx = 0
for i in chars:
	
	os.makedirs(os.path.join(outputDir, str(idx))) # Make character directory
	print ("Generating %i images for character \"%s\"" % (noImagesPerChar, i))

	t = ImgGeneratorThread(i, idx)
	threads.append(t)
	
	if multithreading:
		t.start()
	else:
		t.run()

	idx += 1
	

if multithreading: # If multithreading is enabled: wait for all threads to end
	for t in threads:
		t.join()
	
t1 = time.time()
print ("Images generated in %is" % (t1 - t0))
