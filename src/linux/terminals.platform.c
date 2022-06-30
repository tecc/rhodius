#include <rhodius/platform.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Terminal Capability State
enum RhPlatform_TermCap {
    RhPlatform_TermCap_ImplicitNo,
    RhPlatform_TermCap_ExplicitNo,
    RhPlatform_TermCap_ImplicitYes,
    RhPlatform_TermCap_ExplicitYes
};

#define RhPlatform_TermCap_IsYes(cap) ((cap) == RhPlatform_TermCap_ImplicitYes || (cap) == RhPlatform_TermCap_ExplicitYes)
#define RhPlatform_TermCap_IsExplicit(cap) ((cap) == RhPlatform_TermCap_ExplicitNo || (cap) == RhPlatform_TermCap_ExplicitYes)
#define RhPlatform_CAP_MAX_LENGTH 256

bool RhPlatform_Term_IsSeparator(char c);
enum RhPlatform_TermCap RhPlatform_Term_ColourCap(const char* cap);

void RhPlatform_GetTerminalCapabilities(struct RhPlatform_TerminalCapabilities* out) {
    const char* term = getenv("TERM");
    if (term == NULL) {
    RhPlatform_Term_NoCapabilities:
        out->colours = false;
        return;
    }

    size_t terml = strlen(term);

    if (terml < 1) {
        goto RhPlatform_Term_NoCapabilities;
    }

    size_t start = 0;
    char current[RhPlatform_CAP_MAX_LENGTH];
    // Find each capability
    for (size_t i = 0; i < terml; i++) {
        // Check if the current character is a separator
        if (RhPlatform_Term_IsSeparator(term[i]) || i == terml - 1) {
            memcpy(current, term + start, i - start);
            start = i;

            enum RhPlatform_TermCap cap;
            cap = RhPlatform_Term_ColourCap(current);
            if (RhPlatform_TermCap_IsExplicit(cap)) {
                out->colours = RhPlatform_TermCap_IsYes(cap);
            }
        }
    }
}

inline enum RhPlatform_TermCap RhPlatform_Term_ColourCap(const char* cap) {
    // 256color
    if (strcmp(cap, "256color") == 0 || strcmp(cap, "256color2") == 0) {
        return RhPlatform_TermCap_ExplicitYes;
    }
    if (strcmp(cap, "16color") == 0) {
        return RhPlatform_TermCap_ExplicitYes;
    }

    return RhPlatform_TermCap_ImplicitNo;
}

inline bool RhPlatform_Term_IsSeparator(char c) {
    return c == '-' || c == '+';
}