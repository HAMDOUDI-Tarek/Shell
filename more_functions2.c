#include "shell.h"

/**
 * erroratoi - converts a string to an integer.
 * @input_string: string.
 * Return: 0 or 1.
 */

int erroratoi(char *input_string)
{
	int index;
	unsigned long int result_value = 0;

	if (*input_string == '-')
	{
		input_string++;
		while (*input_string == '0')
			input_string++;
	}

	for (index = 0; input_string[index] != '\0'; index++)
	{
		if (input_string[index] >= '0' && input_string[index] <= '9')
		{
			result_value *= 10;
			result_value += (input_string[index] - '0');

			if (result_value > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}

	return ((*input_string == '-') ? -(int)result_value : (int)result_value);
}

/**
 * error_print - prints an error message.
 * @info: info struct.
 * @error_string: error type.
 * Return: 0 or 1.
 */
void error_print(info_t *info, char *error_string)
{
	_eputs(info->fname);
	_eputs(": ");
	decint_print(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
 * decint_print - prints a decimal int.
 * @input_number: input
 * @file_descriptor: where to write to.
 * Return: chars.
 */
int decint_print(int input_number, int file_descriptor)
{
	int (*output_function)(char) = _putchar;
	int divisor, digit_count = 0;
	unsigned int absolute_value, current_digit;

	if (file_descriptor == STDERR_FILENO)
		output_function = _eputchar;

	if (input_number < 0)
	{
		absolute_value = -input_number;
		output_function('-');
		digit_count++;
	}
	else
	{
		absolute_value = input_number;
	}

	current_digit = absolute_value;

	for (divisor = 1000000000; divisor > 1; divisor /= 10)
	{
		if (absolute_value / divisor)
		{
			output_function('0' + current_digit / divisor);
			digit_count++;
		}
		current_digit %= divisor;
	}

	output_function('0' + current_digit);
	digit_count++;

	return (digit_count);
}

/**
 * num_conv - conversion function.
 * @input_num: number
 * @base: base
 * @conversion_flags: argument flags.
 * Return: string
 */
char *num_conv(long int input_num, int base, int conversion_flags)
{
	static char result_buffer[50];
	char *character_set;
	char sign_indicator = 0;
	char *result_ptr;
	unsigned long absolute_value = input_num;

	if (!(conversion_flags & CONVERT_UNSIGNED) && input_num < 0)
	{
		absolute_value = -input_num;
		sign_indicator = '-';
	}
	const char *character_set = (conversion_flags & CONVERT_LOWERCASE)
		? "0123456789abcdef"
		: "0123456789ABCDEF";
	result_ptr = &result_buffer[49];
	*result_ptr = '\0';

	while (absolute_value != 0)
	{
		*--result_ptr = character_set[absolute_value % base];
		absolute_value /= base;
	}

	if (sign_indicator)
		*--result_ptr = sign_indicator;

	return (result_ptr);
}

/**
 * rmcomments - function replaces first instance of '#' with '\0'
 * @buffer: string.
 * Return: Always 0;
 */
void rmcomments(char *buffer)
{
	int index = 0;

	while (buffer[index])
	{
		if (buffer[index] == '#' && (index == 0 || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
		index++;
	}
}
