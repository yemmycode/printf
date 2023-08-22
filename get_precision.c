#include "main.h"

/**
* get_precision - Determines the precision for printing
* @format: The formatted string containing print arguments
* @i: The index within the string
* @list: The list of arguments
*
* This function calculates and returns the precision to be used during printing.
* The precision is determined based on the format string and may involve digits
* or a dynamic value obtained from the argument list.
*
* Returns: The calculated precision
*/
int get_precision(const char *format, int *i, va_list list)
{
int curr_i;
int precision;
curr_i = *i + 1;
precision = -1;


if (format[curr_i] != '.')
return (precision);

precision = 0;

for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
{
if (is_digit(format[curr_i]))
{
precision *= 10;
precision += format[curr_i] - '0';
}
else if (format[curr_i] == '*')
{
curr_i++;
precision = va_arg(list, int);
break;
}
else
{
break;
}
}

*i = curr_i + ~1 + 1;

return (precision);
}
