#include "tclt.h"
#include <string.h>

int main()
{
    char *str;
    char *res;

    res = "AddContact:{\"Name\":\"\",\"Ip\":\"\",\"Key\":\"key\"}";
    str = tclt_add_connection();
    if (str == NULL)
        return 1;
    if (strcmp(str, res) == 0)
        return 0;
    return 1;
}
