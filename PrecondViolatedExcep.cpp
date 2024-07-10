/** @file PrecondViolatedExcep.cpp */
#include "PrecondViolatedExcep.h"

PrecondViolatedExcep ::PrecondViolatedExcep(const string &message) : logic_error("Precondition Violated Exception: " + message)
{
} // end constructor