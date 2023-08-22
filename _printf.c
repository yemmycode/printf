#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/*
* _printf - Function for printing formatted output
* @format: The format string specifying how to print
* Return: Number of characters printed
*/

int _printf(const char *format, ...)
{
int i;
int printed = 0;
int printed_chars = 0;
int flags;
int width;
int precision;
int size;
int buff_ind = 0;
va_list list;
char buffer[BUFF_SIZE];

if (format == NULL)
return (-1);

va_list list;
va_start(list, format);

for (i = 0; format && format[i] != '\0'; i++)
{
if (format[i] != '%')
{
buffer[buff_ind] = format[i];
buff_ind++;

if (buff_ind >= BUFF_SIZE)
print_buffer(buffer, &buff_ind);

printed_chars += 1;
}
else
{
print_buffer(buffer, &buff_ind);
flags = calculate_flags(format, &i);
width = calculate_width(format, &i, list);
precision = calculate_precision(format, &i, list);
size = calculate_size(format, &i);
++i;
printed = handle_print(format, &i, list, buffer,
flags, width, precision, size);
if (printed == -1)
return (-1);
printed_chars = printed_chars + printed;
}
}

print_buffer(buffer, &buff_ind);
va_end(list);
return (printed_chars);
}

/*
* print_buffer - Outputs the buffer's content if it exists
* @buffer: An array of characters
* @buff_ind: The index for the next character and also the length
*/

void print_buffer(char buffer[], int *buff_ind)
{
if (*buff_ind != 0)
*buff_ind = 0;
}
