//
//  Macros.h
//  DigitsLearning
//
//  Created by Maxime on 10/10/2020.
//

#ifndef Macros_h
#define Macros_h


#define ORDER "ABCDEFGHIJKLMNOPQRSTUVWXYZabdefghijklmnqrt0123456789.!?-%()&$\":;/+*=@#€\x88\x89\x90\x8e\x8f\x90\x91\x94\x95\x99\x9a\x9d\x9f\x9e\xcb\xe5\x80\x83\xe9\xe6\xe8\xeb\xec\xef\x85\xf4\x86\xf3\x8d\x82"
#define NO_CHARACTERS 101



// Following content concerns execution on programs on my computers
// by defining preproc flags for each execution purpose.

#if defined(XCODE) && __APPLE__ // Program is running on Xcode: no dealing with cmd lines etc
#    if __arm64__
#        define XCODE_DTK // Program is running on the DTK
#    else
#        define XCODE_MBP // Program is running on the MacBook Pro
#    endif
#endif


#ifdef XCODE_MBP
#    define DATASET_PATH "/Users/maxime/datasetWC/"
#    define NETWORK_PATH "/Users/maxime/IA-WC/"
#    define NEW_NETWORK 1
#endif

#ifdef XCODE_DTK
#    define DATASET_PATH "/Users/maxime/OCR/dataset-WC/"
#    define NETWORK_PATH "/Users/maxime/OCR/IA-WC-1200/"
#    define NEW_NETWORK 0
#endif


#endif /* Macros_h */
