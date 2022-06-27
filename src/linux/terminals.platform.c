#include <rhodius/_platform.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool RhPlatform_Term_IsSeparator(char c);

bool RhPlatform_TerminalSupportsColour() {
    const char* term = getenv("TERM");
    if (term == NULL) {
        return false;
    }

    size_t terml = strlen(term);

    if (terml < 1) {
        return false;
    }

    bool started;
    size_t separatorPos;
    // Find the separator
    for (size_t i = 0; i < terml; i++) {
        if (RhPlatform_Term_IsSeparator(term[i]) || i == terml - 1) {
            separatorPos = i;

        }
    }

    return false;
}

inline bool RhPlatform_Term_IsSeparator(char c) {
    return c == '-' || c == '+';
}