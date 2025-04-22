
#include <string.h>  
#include "test.h" 
size_t
strlcpy(char *dst, const char *src, size_t dstsize)
{
    const char *osrc = src;
    size_t      nleft = dstsize;

    if (dstsize == 0)
        return strlen(src);

    while (--nleft != 0) {
        if ((*dst++ = *src++) == '\0')
            break;
    }
    if (nleft == 0) {
        *dst = '\0';
        while (*src++)
            ;
    }
    return (size_t)(src - osrc - 1);
}

size_t
strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t  dlen = strnlen(dst, dstsize);
    size_t  slen = strlen(src);

    if (dstsize == 0)
        return slen;

    if (dlen == dstsize)
        return (dstsize + slen);

    return dlen + strlcpy(dst + dlen, src, dstsize - dlen);
}

char *
strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t needle_len;

    if (*needle == '\0')
        return (char *)haystack;
    needle_len = strlen(needle);

    for (; *haystack != '\0' && len >= needle_len; haystack++, len--) {
        if (*haystack == *needle &&
            memcmp(haystack, needle, needle_len) == 0)
            return (char *)haystack;
    }
    return NULL;
}

