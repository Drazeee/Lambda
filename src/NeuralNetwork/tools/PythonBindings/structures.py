#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from . import display as d
from ctypes import *

class MMPixelsTable (Structure):
	_fields_ = [
		("pixelValue", c_double),
	]
	
class MMImage (Structure):
	_fields_ = [
		("pixelsTable", POINTER(MMPixelsTable)),
		("fileName", c_char_p),
		("w", c_int32),
		("h", c_int32),
		("character", c_char),
		("expectedOutput", POINTER(c_double))
	]
	
	def display(self, *args, **kwargs):
		d.show(self, *args, **kwargs)
	
	
class MMNode (Structure):
	_fields_ = [
			("weights", POINTER(c_double))
		]
	
class MMNetwork (Structure):
	_fields_ = [
			("numInputs", c_int),
			("numHiddenNodes", c_int),
			("numOutputs", c_int),
		
			("hiddenLayerBias",POINTER(c_double)),
			("outputLayerBias",POINTER(c_double)),
		
			("hiddesWeights",POINTER(MMNode)),
			("outputWeights",POINTER(MMNode)),
	]	
	
class MMGuess (Structure):
	_fields_ = [
			("character", c_char),
			("score", c_double),
			("rate", c_double)
	]
	
class MMTrainingStats (Structure):
	_fields_ = [
		("total", c_int),
		("success", c_int),
		("fails", c_int),
		("rate", c_double)
	]
	
class MMTrainingEnvironment (Structure):
	_fields_ = [
		("network", MMNetwork),
		("hiddenLayer", POINTER(c_double)),
		("outputLayer", POINTER(c_double)),
		("learningRate", c_double),
		("trainingSetSize", c_int),
		("trainingSetOrder", POINTER(c_int))
	]