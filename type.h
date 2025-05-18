#ifndef TYPE_H
#define TYPE_H

typedef unsigned int uint;//unsiged int - uint

typedef enum
{
    e_success,
    e_failure 
} Status_e;

typedef enum
{
    e_encode,
    e_decode,
    e_unsupported
} OperationType;

typedef enum
{
    d_success,
    d_failure
} Status_d;

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;33m"
#define YELLOW  "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

#endif 