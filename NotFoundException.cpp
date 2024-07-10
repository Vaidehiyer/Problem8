#include "NotFoundException.h"

NotFoundException::NotFoundException(const string &message)
    : logic_error("Not Found Exception: " + message)
{
}
