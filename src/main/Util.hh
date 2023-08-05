#pragma once

/**
 * Contains random utility functions.
 */
namespace Util {
    /**
     * Takes a string and makes a copy of it.
     * @param string is the string to copy.
     * @return the copied version which you will need to manually delete.
     */
    char *copyString(char const *string);
};