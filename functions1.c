#include "main.h"

/**
* print_unsigned - Function for printing an unsigned number
* @types: List of arguments
* @buffer: Buffer array for print handling
* @flags: Calculated active flags
* @width: Width retrieval
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed
*/
int print_unsigned(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int index = BUFF_SIZE - 2;
unsigned long int number = va_arg(types, unsigned long int);
number = convert_size_unsgnd(number, size);

if (number == 0)
buffer[index--] = '0';

buffer[BUFF_SIZE - 1] = '\0';

while (number > 0)
{
buffer[index--] = (number % 10) + '0';
number /= 10;
}

index++;

return write_unsgnd(0, index, buffer, flags, width, precision, size);
}

/**
* print_octal - Function for printing an unsigned number in octal notation
* @types: List of arguments
* @buffer: Buffer array for print handling
* @flags: Calculated active flags
* @width: Width retrieval
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed
*/
int print_octal(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int index = BUFF_SIZE - 2;
unsigned long int num = va_arg(types, unsigned long int);
unsigned long int initial_num = num;
UNUSED(width);
num = convert_size_unsgnd(num, size);

if (num == 0)
buffer[index--] = '0';

buffer[BUFF_SIZE - 1] = '\0';

while (num > 0)
{
buffer[index--] = (num % 8) + '0';
num /= 8;
}

if (flags & F_HASH && initial_num != 0)
buffer[index--] = '0';

index++;
return write_unsgnd(0, index, buffer, flags, width, precision, size);
}

/**
* print_hexadecimal - Function for printing an unsigned number in hexadecimal notation
* @types: List of arguments
* @buffer: Buffer array for print handling
* @flags: Calculated active flags
* @width: Width retrieval
* @precision: The precision specification
* @size: The size specifier
* Return: Number of characters printed
*/
int print_hexadecimal(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
return print_hexa(types, "0123456789abcdef", buffer,
flags, 'x', width, precision, size);
}

/**
* print_hexa_upper - Function for printing an unsigned number in uppercase hexadecimal notation
* @types: List of arguments
* @buffer: Buffer array for print handling
* @flags: Calculated active flags
* @width: Width retrieval
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed
*/
int print_hexa_upper(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
return print_hexa(types, "0123456789ABCDEF", buffer,
flags, 'X', width, precision, size);
}



/**
* print_hexa - Prints a hexadecimal number in lower or upper case
* @types: List of arguments
* @map_to: An array of values to map the number to
* @buffer: Buffer array for print handling
* @flags: Calculated active flags
* @flag_ch: Active flag calculation
* @width: Width retrieval
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed
*/
int print_hexa(va_list types, char map_to[], char buffer[],
int flags, char flag_ch, int width, int precision, int size)
{
int index = BUFF_SIZE - 2;
unsigned long int number = va_arg(types, unsigned long int);
unsigned long int initial_number = number;
UNUSED(width);

number = convert_size_unsgnd(number, size);

if (number == 0)
buffer[index--] = '0';

buffer[BUFF_SIZE - 1] = '\0';

buffer[index--] = map_to[number % 16];
number /= 16;

if ((flags & F_HASH) && (initial_number != 0))
{
buffer[index--] = flag_ch;
buffer[index--] = '0';
}

index++;
return write_unsgnd(0, index, buffer, flags, width, precision, size);
}

