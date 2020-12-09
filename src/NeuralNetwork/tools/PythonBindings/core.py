#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from . import structures as s
from . import exceptions
from ctypes import *
import os
import sys


libPath = os.environ.get("LAMBDALIBPATH", "../lib/LambdaNeuralNetwork.so")

try:
	lib = CDLL(libPath)
except OSError:
	raise exceptions.LibNotFound("Can't find shared lib file. Ensure you have run the \"make shared\" command.")
	sys.exit(1)


LoadImageOrig = lib.LoadImage
LoadImageOrig.argtypes = [c_char_p]
LoadImageOrig.restype = s.MMImage

LoadImage = lambda s: LoadImageOrig(s.encode('utf-8'))


LoadDatasetOrig = lib.LoadDataset
LoadDatasetOrig.argtypes = [c_char_p, c_int, c_int]
LoadDatasetOrig.restype = POINTER(s.MMImage)

LoadDataset = lambda s, a, b: LoadDatasetOrig(s.encode('utf-8'), a, b)

MakeFakeData = lib.MakeFakeData
MakeFakeData.argtypes = [c_int, POINTER(c_double), c_int, POINTER(c_double)]
MakeFakeData.restype = s.MMImage


LoadNetworkOrig = lib.LoadNetwork
LoadNetworkOrig.argtypes = [c_char_p]
LoadNetworkOrig.restype = s.MMNetwork

LoadNetwork = lambda s: LoadNetworkOrig(s.encode('utf-8'))


InitNetwork = lib.InitNetwork
InitNetwork.argtypes = [c_int, c_int, c_int]
InitNetwork.restype = s.MMNetwork

InitWeightsForNetwork = lib.InitWeightsForNetwork
InitWeightsForNetwork.argtypes = [s.MMNetwork]
InitWeightsForNetwork.restype = None


Predict = lib.Predict
Predict.argtypes = [s.MMNetwork, POINTER(s.MMImage)]
Predict.restype = POINTER(c_double)



OutputCharOrig = lib.OutputChar
OutputCharOrig.argtypes = [POINTER(c_double), POINTER(s.MMContext)]
OutputCharOrig.restype = c_char

OutputChar = lambda a: OutputCharOrig(a).decode('utf-8')

HiddenLayer = lib.HiddenLayer
HiddenLayer.argtypes = [s.MMNetwork]
HiddenLayer.restype = POINTER(c_double)

OutputLayer = lib.OutputLayer
OutputLayer.argtypes = [s.MMNetwork]
OutputLayer.restype = POINTER(c_double)


Train = lib.Train
Train.argtypes = [s.MMNetwork, POINTER(s.MMImage), s.MMTrainingEnvironment, POINTER(s.MMContext)]
Train.restype = s.MMTrainingStats

TrainingEnvironment = lib.TrainingEnvironment
TrainingEnvironment.argtypes = [s.MMNetwork, c_int, c_double]
TrainingEnvironment.restype = s.MMTrainingEnvironment