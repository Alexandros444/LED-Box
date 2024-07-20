import string



# byte* char_to_led_data(char c) {
# 	byte* ret = A;
# 	switch (c) {
# 	case 'A':
# 		ret = A;
# 		break;
# 	case 'a':
# 		ret = A;
# 		break;
# 	default:
# 		break;
# 	}
# 	return ret;
# }

#ifndef TABLE_H
#define TABLE_H

#include <Arduino.h>
#include "led_matrix_data.h"

lines = ""
lines += "#include \"table.h\"\n"

lines += f"byte* char_to_led_data(char c) "+"{\n"
lines += f"\tbyte* ret = space;\n"
lines += f"\tswitch (c) "+"{\n"

for i in range(0,len(string.ascii_lowercase)):
    char_up =  string.ascii_uppercase[i]
    char_low = string.ascii_lowercase[i]
    lines += f"\tcase \'{char_up}\':\n\t\tret={char_up};\n\t\tbreak;\n"
    lines += f"\tcase \'{char_low}\':\n\t\tret={char_up};\n\t\tbreak;\n"

for i in range(0,10):
    lines += f"\tcase \'{i}\':\n\t\tret=num{i};\n\t\tbreak;\n"

lines += f"\tcase '\\x84':\n\t\tret=AE;\n\t\tbreak;\n"
lines += f"\tcase '\\x8e':\n\t\tret=AE;\n\t\tbreak;\n"
lines += f"\tcase '\\x9a':\n\t\tret=UE;\n\t\tbreak;\n"
lines += f"\tcase '\\x81':\n\t\tret=UE;\n\t\tbreak;\n"
lines += f"\tcase '\\x94':\n\t\tret=OE;\n\t\tbreak;\n"
lines += f"\tcase '\\x99':\n\t\tret=OE;\n\t\tbreak;\n"
lines += f"\tcase '\\xel':\n\t\tret=SZ;\n\t\tbreak;\n"

# ä \x84
# Ä \x8e
# Ü \x9a
# ü \x81
# ö \x94
# Ö \x99
# ß \xe1
lines += f"\tcase \':\':\n\t\tret=dotdot;\n\t\tbreak;\n"
lines += f"\tcase \'?\':\n\t\tret=q_mark;\n\t\tbreak;\n"
lines += f"\tcase \'!\':\n\t\tret=ex_mark;\n\t\tbreak;\n"
lines += f"\tcase \'.\':\n\t\tret=dot;\n\t\tbreak;\n"
lines += f"\tcase \' \':\n\t\tret=space;\n\t\tbreak;\n"
lines += f"\tdefault:\n\t\tbreak;\n\t"+"}\n\treturn ret;\n}\n"

with open("src/table.cpp","wt") as out:
    out.write(lines)