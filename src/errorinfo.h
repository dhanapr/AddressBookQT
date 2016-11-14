#ifndef CORE_ERRORINFO_H
#define CORE_ERRORINFO_H

#include <string>

/***********************************************************************
    Class: ErrorInfo

    Author: Phil Grohe

    Error status structure.  Holds an ErrorCode and a string describing
    the error.
***********************************************************************/

enum ErrorCode
{
    ERR_OK,
    ERR_CONTACT_NOT_VALID,
    ERR_CONTACT_NOT_FOUND,
    ERR_DATASOURCE_ERROR,
    ERR_UNKNOWN_ERROR
};

class ErrorInfo
{
    public: 
        ErrorCode code;
        std::string msg;

        ErrorInfo() : code(ERR_OK), msg("") {};
        ErrorInfo(ErrorCode code, std::string msg) : code(code), msg(msg) {};

};
#endif
