# Input

A configurable structure to assist in getting a multi character input from generic keyboards.

## Examples

`InputUint.c` and `InputString.c` show examples of input types being implemented. Note that they rely on [GCC function attributes](https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html).

When using the structure to get a generic input, the following example should illustrate a concise way of doing so:

```c++
#include "Input.h"
/* ... */
#define MAXLENGTH 42

int getInput(const char format[], void *val, size_t len)
{
    char msg[MAXLENGTH] = {};
    int key;
    Input input = createInput(format, val);

    do {
        runSprintF(input, msg);
        showMessage(msg);        /* Display the value */
        key = getNumericalKey(); /* Get key as a number */

        switch (key)
        {
        case KBD_KEY_CANCEL:     /* Cancel */
        case KBD_KEY_ENTER:      /* Confirm */
            deleteInput(input);
            return key;
        case KBD_KEY_CLEAR:      /* Backspace */
            runDelKey(input);
            break;
        default:
            runPutKey(input, key, len);
            break;
        }
    } while (1);
}
```