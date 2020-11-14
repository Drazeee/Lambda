//
//  Macros.h
//  DigitsLearning
//
//  Created by Maxime on 10/10/2020.
//

#ifndef Macros_h
#define Macros_h


#define ORDER "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?-%()&$\":;/+=@#"
#define NO_CHARACTERS 78



// Following content concerns execution on programs on my computers
// by defining preproc flags for each execution purpose.

#if defined(XCODE) && __APPLE__ // Program is running on Xcode: no dealing with cmd lines etc
#	if __arm64__
#		define XCODE_DTK // Program is running on the DTK
#	else
#		define XCODE_MBP // Program is running on the MacBook Pro
#	endif
#endif


#ifdef XCODE_MBP
#	define DATASET_PATH "/Users/maxime/dataset/"
#	define NETWORK_PATH "/Users/maxime/IAC/"
#endif

#ifdef XCODE_DTK
#	define DATASET_PATH "/Users/maxime/Desktop/OCR/dataset/"
#	define NETWORK_PATH "/Users/maxime/Desktop/OCR/IAC/"
#endif


#endif /* Macros_h */
