//
//  Context.h
//  DigitsLearning
//
//  Created by Maxime on 04/12/2020.
//

#ifndef Context_h
#define Context_h

typedef struct MMContext {
	char* classes;
	int nb_classes;
} MMContext;

static MMContext CHARS_CTX = {"ABDEFGHJLMNQRTabcdefghijklmnopqrstuvwxyz0123456789.!?-%()&$\":;/+*=@#", 68};
static MMContext ACC_CTX = {"\x00\x01\x02\x03\x04", 5};

#endif /* Context_h */
