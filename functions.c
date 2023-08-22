#include "main.h"

/**
* print_char - Outputs a single character
* @types: List of arguments
* @buffer: Buffer array for printing
* @flags: Calculated active flags
* @width: Width parameter
* @precision: The precision specification
* @size: The size specifier
* Return: Count of characters printed
*/
int print_char(va_list types, char buffer[], int flags,
int width, int precision, int size)
{
char c = (char)va_arg(types, int);
return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
* print_string - Displays a string
* @types: Argument list
* @buffer: Buffer array for printing
* @flags: Active flag calculations
* @width: Width retrieval
* @precision: Precision specification
* @size: Size indication
* Return: Count of printed characters
*/

int print_string(va_list types, char buffer[],
int flags, int width,
int precision, int size)
{
int length = 0;
int i;
char *str;
str = va_arg(types, char *);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

if (!str)
{
str = "(null)";
if (precision >= 6)
str = " ";
}

while (*(str + length) != '\0')
length++;

if ((precision >= 0) && (precision < length))
length = precision;

if (width > length)
{
if (flags & F_MINUS)
{
write(1, str, length);
for (i = width - length; i > 0; i--)
write(1, " ", 1);
return (width);
}
else
{
for (i = width - length; i > 0; i--)
write(1, " ", 1);
write(1, str, length);
return (width);
}
}
return write(1, str, length);
}

/**
* print_percent - Function for printing a percent sign
* @types: List of arguments
* @buffer: Buffer array for print handling
* @flags: Calculated active flags
* @width: Width specification
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed
*/
int print_percent(va_list types, char buffer[], int flags,
int width, int precision, int size)
{
UNUSED(types);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
return write(1, "%%", 1);
}

/**
* print_int - Function to print an integer
* @types: List of arguments
* @buffer: Buffer array for print handling
* @flags: Active flags calculation
* @width: Width retrieval
* @precision: Precision specification
* @size: Size specification
* Return: Number of printed characters
*/
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int index = BUFF_SIZE - 2;
int isNegative = 0;
long int number = va_arg(types, long int);
unsigned long int value;
number = convert_size_number(number, size);

if (number == 0)
buffer[index--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
value = (unsigned long int)number;

if (number < 0)
{
value = (unsigned long int)(-number);
isNegative = 1;
}

while (value > 0)
{
buffer[index--] = (value % 10) + '0';
value /= 10;
}
index++;
return write_number(isNegative, index, buffer, flags, width, precision, size);
}

/**
* print_binary - Prints an unsigned number in binary format
* @types: List of arguments
* @buffer: Buffer array for print handling
* @flags: Calculated active flags
* @width: Width value
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed
*/

int print_binary(va_list types, char buffer[], int flags,
int width, int precision, int size)
{
unsigned int n = va_arg(types, unsigned int);
unsigned int m = 2147483648; // 2 ^ 31
unsigned int a[32];
int count;

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

a[0] = n >> 31;

for (unsigned int i = 1; i < 32; i++)
{
m >>= 1;
a[i] = (n >> (31 - i)) & 1;
}

for (unsigned int i = 0, sum = 0; i < 32; i++)
{
sum += a[i];
if (sum != 0 || i == 31)
{
char z = a[i] + '0';
write(1, &z, 1);
count++;
}
}

