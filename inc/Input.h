#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>

#define INDEX(C) (C) - 'A'

#define NOT_A_KEY -1

typedef struct InputDeref *Input;

/**
 * @brief Create an Input object
 * 
 * @param[in] format String to display
 * @param[in,out] val Pointer to where the input value should be stored
 * @return Input object
 */
Input createInput(const char format[], void *val);

/**
 * @brief Delete an Input object
 * 
 * @param[in] input To be destroyed
 */
void deleteInput(Input input);

/**
 * @brief Call the configured SprintF function
 * 
 * @param[in] input Object with the function 
 * @param[out] out String to store the output
 */
void runSprintF(Input input, char *out);

/**
 * @brief Call the configured PutKey function
 * @warning For strings, pass strlen - 1 (keep '\0' in the end)
 * 
 * @param[in,out] input Object to store the key
 * @param[in] key Numerical value to be translated and stored
 * @param[in] len Maximum length (in characters) of the value to be stored
 */
void runPutKey(Input input, int key, size_t len);

/**
 * @brief Call the configured PopKey function
 * 
 * @param[in,out] input Object from which the last character inserted is deleted
 */
void runPopKey(Input input);

#endif /* INPUT_H */
