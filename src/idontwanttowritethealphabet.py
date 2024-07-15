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

lines = ""
lines += "#ifndef byte\n#include <Arduino.h>\n#endif\n\n"
lines += "#ifndef A\n#include \"led_matrix_data.h\"\n#endif\n\n"
lines += f"byte* char_to_led_data(char c) "+"{\n"
lines += f"\tbyte* ret = A;\n"
lines += f"\tswitch (c) "+"{\n"

for i in range(0,len(string.ascii_lowercase)):
    char_up =  string.ascii_uppercase[i]
    char_low = string.ascii_lowercase[i]
    lines += f"\tcase \'{char_up}\':\n\t\tret={char_up};\n\t\tbreak;\n"
    lines += f"\tcase \'{char_low}\':\n\t\tret={char_up};\n\t\tbreak;\n"

for i in range(0,10):
    lines += f"\tcase \'{i}\':\n\t\tret=num{i};\n\t\tbreak;\n"

lines += f"\tcase \'!\':\n\t\tret=ex_mark;\n\t\tbreak;\n"
lines += f"\tcase \'.\':\n\t\tret=dot;\n\t\tbreak;\n"
lines += f"\tcase \' \':\n\t\tret=space;\n\t\tbreak;\n"
lines += f"\tdefault:\n\t\tbreak;\n\t"+"}\n\treturn ret;\n}"



with open("include/table.h","wt") as out:
    out.write(lines)