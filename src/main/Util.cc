#include "Util.hh"
#include <string.h>

char *Util::copyString(char const *string) {
    int length = strlen(string);
    char *newString = new char[length + 1];
    for (int i = 0; i <= length; i++) newString[i] = string[i];
    return newString;
}