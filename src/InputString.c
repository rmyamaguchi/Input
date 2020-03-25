
#include <stdio.h>
#include <string.h>
#include "InputType.h"

#define STRING_FORM 's'
#define STRING(VAL) (char *)(VAL)

#define NUM_KEYS 12

static char *keyMap[NUM_KEYS] = {
    "0 ",
    "1qzQZ", "2abcABC", "3defDEF",
    "4ghiGHI", "5jklJKL", "6mnoMNO",
    "7prsPRS", "8tuvTUV", "9wxyWXY",
    "*", "#;"};

static int prevKey = NOT_A_KEY;

static void stringSprintF(char *out, const char format[], void * val)
{
    sprintf(out, format, STRING(val));
}

static unsigned int stringPutKey(void * val, int key)
{
    static char *pcMap;

    unsigned int ret;
    char *pEnd = strchr(STRING(val), '\0');

    if (key < 0 || NUM_KEYS - 1 < key)
    {
        prevKey = NOT_A_KEY;
        return 0;
    }

    if (key != prevKey)
    {
        pcMap = keyMap[key];
        *pEnd = *pcMap; /* warning: be careful to keep '\0' terminated */
        ret = 1;
    }
    else
    {
        pcMap = *(++pcMap) ? pcMap : keyMap[key];
        *(pEnd - 1) = *pcMap;
        ret = 0;
    }
    prevKey = key;
    return ret;
}

static unsigned int stringPopKey(void * val)
{
    char *pEnd = strchr(STRING(val), '\0');
    prevKey = NOT_A_KEY;

    if (pEnd == STRING(val))
        return 0;

    *pEnd = '\0';
    return 1;
}

static void configStringInput(Input input)
{
    setSprintF(input, stringSprintF);
    setPutKey(input, stringPutKey);
    setPopKey(input, stringPopKey);
}

static void CONSTRUCTOR putStringConfig(void)
{
    putConfig(STRING_FORM, configStringInput);
}