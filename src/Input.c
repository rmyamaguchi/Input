
#include <stdlib.h>
#include <string.h>
#include "Input.h"
#include "InputType.h"

static ConfigInputFun configInputFun[INDEX('z') + 1] = {};

struct InputDeref
{
    unsigned int cursor;
    const char *format;
    void *val;
    SprintFFun sprintF;
    PutKeyFun putKey;
    DelKeyFun delKey;
};

/**
 * @brief Check the first format in a printf formatted string.
 * 
 * @param[in] format String
 * @return char Which represents the variable to be put in place.
 */
static char getFormat(const char format[])
{
    char *pc;
    pc = strchr(format, '%');
    if (pc == NULL)
        return 0;

    do /* Skip other formating parameters */
        pc++;
    while (*pc != '\0' &&
           (*pc == '-' || *pc == '*' || *pc == '.' ||
            (*pc >= '0' && *pc <= '9')));
    return *pc;
}

/**
 * @brief Create an Input object
 */
Input createInput(const char format[], void *val)
{
    int type;
    Input input;

    type = getFormat(format);
    if (type < 'A' || 'z' < type || 
        configInputFun[INDEX(type)] == NULL)
        return NULL;

    input = malloc(sizeof(*input));
    if (input != NULL) {
        input->cursor = 0;
        input->format = format;
        input->val = val;

        configInputFun[INDEX(type)](input);
    }
    return input;
}

/**
 * @brief Delete an Input object
 */
void deleteInput(Input input)
{
    free(input);
}

/**
 * @brief Run the configured sprintF function.
 */
void runSprintF(Input input, char *out)
{
    if (input != NULL)
        input->sprintF(out, input->format, input->val);
}

/**
 * @brief Run the configured putKey function.
 * @warning For strings, pass strlen - 1 (keep '\0' in the end)
 */
void runPutKey(Input input, int key, size_t len)
{
    if (input != NULL && input->cursor < len)
        input->cursor += input->putKey(input->val, key);
}

/**
 * @brief Run the configured delKey function.
 */
void runDelKey(Input input)
{
    if (input != NULL && input->cursor > 0)
        input->cursor -= input->delKey(input->val);
}

/**
 * @brief Set Input configs
 */
void setSprintF(Input input, SprintFFun sprintF)
{
    if (input != NULL)
        input->sprintF = sprintF;
}
void setPutKey(Input input, PutKeyFun putKey)
{
    if (input != NULL)
        input->putKey = putKey;
}
void setDelKey(Input input, DelKeyFun delKey)
{
    if (input != NULL)
        input->delKey = delKey;
}

/**
 * @brief Put the configuration to be called when creating Input
 */
void putConfig(int type, ConfigInputFun configFun)
{
    configInputFun[INDEX(type)] = configFun;
}