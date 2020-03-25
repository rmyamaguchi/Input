#include <stdio.h>
#include "InputType.h"

#ifndef UINT_MAX
#define UINT_MAX 0xffffffff
#endif /* UINT_MAX */

#define UINT_FORM 'u'
#define UINT(VAL) *(unsigned int *)(VAL)

static void uintSprintF(char *out, const char format[], void * val)
{
    sprintf(out, format, UINT(val));
}

static unsigned int uintPutKey(void * val, int key)
{
    if (key > 9 || UINT(val) > (UINT_MAX - key) / 10)
        return 0;

    UINT(val) = UINT(val) * 10 + key;
    return 1;
}

static unsigned int uintPopKey(void * val)
{
    if (UINT(val) == 0)
        return 0;

    UINT(val) /= 10;
    return 1;
}

static void configUintInput(Input input)
{
    setSprintF(input, uintSprintF);
    setPutKey(input, uintPutKey);
    setPopKey(input, uintPopKey);
}

static void CONSTRUCTOR putIntConfig(void)
{
    putConfig(UINT_FORM, configUintInput);
}