//PRIVATE
#ifndef ENV_TOOLS_H
#define ENV_TOOLS_H

#include "dllHelper.h"

// Now we use the generic helper definitions above to define HELLO_API and HELLO_API_LOCAL.
// TOOLS is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// TOOLS_LOCAL is used for non-api symbols.

#ifdef CBI_TOOLS_USE_DLL // defined if API is compiled as a DLL
#ifdef CBI_TOOLS_DLL_EXPORT // defined if we are building the API DLL (instead of using it)
#define CBI_TOOLS HELPER_DLL_EXPORT
#else
#define CBI_TOOLS HELPER_DLL_IMPORT
#endif // API_DLL__EXPORT
#define CBI_TOOLS_LOCAL HELPER_DLL_LOCAL
#else // API_DLL is not defined: this means API is a static lib.
#define CBI_TOOLS
#define CBI_TOOLS_LOCAL
#endif //

#endif /* ENV_TOOLS_H */
