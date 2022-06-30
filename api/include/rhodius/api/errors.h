#ifndef RHODIUSAPI_ERRORS_H
#define RHODIUSAPI_ERRORS_H

enum RhAPI_Error {
    RhAPI_Error_Ok = 0,
    RhAPI_Error_GenericIssue = 1,
    RhAPI_Error_AllocationFailed = 2,
    RhAPI_Error_TooSmallBuffer = 3,
    RhAPI_Error_CannotAccess = 4,
    RhAPI_Error_InvalidArgument
};

#endif
