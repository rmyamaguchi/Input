#ifndef INPUTTYPE_H
#define INPUTTYPE_H

#include "Input.h"

#define NOT_A_KEY -1

#define CONSTRUCTOR __attribute__((constructor))

typedef void (*SprintFFun)(char *, const char[], void *);
typedef unsigned int (*PutKeyFun)(void *, int);
typedef unsigned int (*DelKeyFun)(void *);

typedef void (*ConfigInputFun)(Input);

/**
 * @brief Set the SprintF function to be used
 * @note To be used by Input type implementations
 * 
 * @param[in,out] input Object to be edited
 * @param[in] sprintF Function to be addressed
 */
void setSprintF(Input input, SprintFFun sprintF);

/**
 * @brief Set the PutKey function to be used
 * @note To be used by Input type implementations
 * 
 * @param[in,out] input Object to be edited
 * @param[in] sprintF Function to be addressed
 */
void setPutKey(Input input, PutKeyFun putKey);

/**
 * @brief Set the DelKey function to be used
 * @note To be used by Input type implementations
 * 
 * @param[in,out] input Object to be edited
 * @param[in] sprintF Function to be addressed
 */
void setDelKey(Input input, DelKeyFun delKey);

/**
 * @brief Saves a configuration type for the Input to use
 * @note To be used by Input type implementations
 * @note The configFun should be declared with the CONSTRUCTOR attribute
 * 
 * @param[in] type 
 * @param[in] configFun 
 */
extern void putConfig(int type, ConfigInputFun configFun);

#endif /* INPUTTYPE_H */