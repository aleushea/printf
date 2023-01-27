#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @design: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *design, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	design_t design_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; design_types[i].design != '\0'; i++)
		if (design[*ind] == design_types[i].design)
			return (design_types[i].fn(list, buffer, flags, width, precision, size));

	if (design_types[i].design == '\0')
	{
		if (design[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (design[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (design[*ind] != ' ' && design[*ind] != '%')
				--(*ind);
			if (design[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &design[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
