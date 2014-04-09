#include "wincompat.h"

int vasprintf (char **buf, const char *format, va_list ap) {
	int len;
	len = vsnprintf (NULL, 0, format, ap);  /* get needed size */
	if(len < 0) return len;
	*buf = talloc (len + 1);  /* reserve 1 byte for trailing \0 */
	if(!*buf) return 0;
	return vsnprintf (*buf, len + 1, format, ap);
}

char* strndup (const char *s, size_t n) {
	char *result;
	size_t len = strlen (s);

	if(n < len)
		len = n;

	result = (char *)talloc (len + 1);
	if(!result)
		return 0;

	result[len] = '\0';
	return (char *)memcpy (result, s, len);
}
