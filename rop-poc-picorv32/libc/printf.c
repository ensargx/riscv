#include <stdarg.h>
#include <stdint.h>

extern void print_chr(char ch);
extern void print_str(const char *p);

int printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	const char *p = format;
	while (*p) {
		if (*p == '%') {
			p++;
			if (*p == 's') {
				char *s = va_arg(ap, char*);
				print_str(s);
			} else if (*p == 'c') {
				char c = (char)va_arg(ap, int);
				print_chr(c);
			} else if (*p == '%') {
				print_chr('%');
			}
			// Add more formats here if needed
		} else {
			print_chr(*p);
		}
		p++;
	}

	va_end(ap);
	return 0;
}
