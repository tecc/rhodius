#include <errno.h>
#include <pwd.h>
#include <rhodius/_util.h>
#include <rhodius/platform.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

inline bool RhPlatform_FileExists(const char* filename) {
    if (access(filename, F_OK) == 0) {
        return true;
    }

    switch (errno) {
        case ELOOP:
            return true; // This is debatable but sure why not
        default:
            return false;
    }
}
enum RhAPI_Error RhPlatform_GetFileState(const char* filename, struct RhPlatform_FileState* out) {
    if (filename == NULL || out == NULL) {
        return RhAPI_Error_InvalidArgument;
    }

    // Reset all the values before doing anything
    out->exists = false;
    out->isDirectory = false;
    out->accessible = false;

    // Now start with the actual code

    struct stat statResult;
    int statReturnCode = stat(filename, &statResult);

    if (statReturnCode != 0) {
        switch (errno) {
            case EACCES:
                return RhAPI_Error_Ok;
            case ENOENT:
                out->accessible = true;
                out->exists = false;
                return RhAPI_Error_Ok;
            default:
                return RhAPI_Error_GenericIssue;
        }
    }

    return RhAPI_Error_Ok;
}

enum RhAPI_Error RhPlatform_MakeDirectoryRecursive(const char* directory) {
    char* actualPath = malloc(RhPATH_MAX);
    if (realpath(directory, actualPath) == NULL) {
        switch (errno) {
            case EACCES:
                return RhAPI_Error_CannotAccess;
            default:
                return RhAPI_Error_GenericIssue; // TODO(tecc): Add more errors
        }
    }
}

void RhPlatform_GetWorkingDirectory(char* out, size_t maxLength) {
    getcwd(out, maxLength);
}
enum RhAPI_Error RhPlatform_GetUserHomeDirectory(char* out, size_t maxLength) {
    const char* env = getenv("HOME");
    size_t length;
    if (env != NULL) {
        // If $HOME isn't null, use it
        length = strlen(env);
        if (length >= maxLength) { // Greater than or equals to because it has to null-terminated
            return RhAPI_Error_TooSmallBuffer;
        }

        memcpy(out, env, length);
        out[length] = '\0';

        return RhAPI_Error_Ok;
    }

    char* cbuffer = malloc(RhPlatform_BUFFER_SIZE * sizeof(char));
    if (cbuffer == NULL)
        return RhAPI_Error_AllocationFailed;

    uid_t uid = getuid();
    struct passwd* pwbuffer = malloc(sizeof(struct passwd));
    struct passwd* pw = NULL; // This is a result output
    int result = getpwuid_r(uid, pwbuffer, cbuffer, RhPlatform_BUFFER_SIZE, &pw);
    if (result != 0 || pw == NULL) {
        switch (errno) {
                // NOTE(tecc): Add more descriptive errors, perhaps
            default:
                return RhAPI_Error_GenericIssue;
        }
    }

    length = strlen(pw->pw_dir);
    if (length >= maxLength) {
        free(cbuffer); // Make sure that everything is freed
        free(pwbuffer);
        return RhAPI_Error_TooSmallBuffer;
    }
    memcpy(out, pw->pw_dir, length);

    free(cbuffer); // See the previous length >= maxLength comment
    free(pwbuffer);

    return RhAPI_Error_Ok;
}
const char* RhPlatform_GetSystemName() {
    return RhPlatform_SYSNAME_LINUX; // This is already a platform-based file, so we can just return it directly. Yay for simplicity!
}
