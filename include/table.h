#ifndef byte
#include <Arduino.h>
#endif

#ifndef A
#include "led_matrix_data.h"
#endif

byte* char_to_led_data(char c) {
	byte* ret = A;
	switch (c) {
	case 'A':
		ret=A;
		break;
	case 'a':
		ret=A;
		break;
	case 'B':
		ret=B;
		break;
	case 'b':
		ret=B;
		break;
	case 'C':
		ret=C;
		break;
	case 'c':
		ret=C;
		break;
	case 'D':
		ret=D;
		break;
	case 'd':
		ret=D;
		break;
	case 'E':
		ret=E;
		break;
	case 'e':
		ret=E;
		break;
	case 'F':
		ret=F;
		break;
	case 'f':
		ret=F;
		break;
	case 'G':
		ret=G;
		break;
	case 'g':
		ret=G;
		break;
	case 'H':
		ret=H;
		break;
	case 'h':
		ret=H;
		break;
	case 'I':
		ret=I;
		break;
	case 'i':
		ret=I;
		break;
	case 'J':
		ret=J;
		break;
	case 'j':
		ret=J;
		break;
	case 'K':
		ret=K;
		break;
	case 'k':
		ret=K;
		break;
	case 'L':
		ret=L;
		break;
	case 'l':
		ret=L;
		break;
	case 'M':
		ret=M;
		break;
	case 'm':
		ret=M;
		break;
	case 'N':
		ret=N;
		break;
	case 'n':
		ret=N;
		break;
	case 'O':
		ret=O;
		break;
	case 'o':
		ret=O;
		break;
	case 'P':
		ret=P;
		break;
	case 'p':
		ret=P;
		break;
	case 'Q':
		ret=Q;
		break;
	case 'q':
		ret=Q;
		break;
	case 'R':
		ret=R;
		break;
	case 'r':
		ret=R;
		break;
	case 'S':
		ret=S;
		break;
	case 's':
		ret=S;
		break;
	case 'T':
		ret=T;
		break;
	case 't':
		ret=T;
		break;
	case 'U':
		ret=U;
		break;
	case 'u':
		ret=U;
		break;
	case 'V':
		ret=V;
		break;
	case 'v':
		ret=V;
		break;
	case 'W':
		ret=W;
		break;
	case 'w':
		ret=W;
		break;
	case 'X':
		ret=X;
		break;
	case 'x':
		ret=X;
		break;
	case 'Y':
		ret=Y;
		break;
	case 'y':
		ret=Y;
		break;
	case 'Z':
		ret=Z;
		break;
	case 'z':
		ret=Z;
		break;
	case '!':
		ret=ex_mark;
		break;
	case ' ':
		ret=space;
		break;
	default:
		break;
	}
	return ret;
}