#include "tclt.h"

int     main(void)
{
    if (tclt_get_version() == LIB_TNETACLE_CLIENT_VERSION)
        return 0;
    return 1;
}
