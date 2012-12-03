/*
 * Copyright (c) 2012 Florent Tribouilloy <tribou_f AT epitech DOT net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "tclt.h"
#include "tclt_format.h"
#include "tclt_command.h"
#include "tclt_parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yajl/yajl_tree.h>

#define CONTACT1_NAME "contact1"
#define CONTACT2_NAME "contact2"
#define CONTACT3_NAME "contact3"

#define CONTACT1_RES "{\"DeleteContact\":\"contact1\"}"
#define CONTACT2_RES "{\"DeleteContact\":\"contact2\"}"
#define CONTACT3_RES "{\"DeleteContact\":\"contact3\"}"
#define EMPTY_RES "{\"DeleteContact\":\"\"}"

int
test1()
{
    if (tclt_delete_peer(NULL) == NULL)
        return 0;
    return 1;
}

int
test2()
{
    char *res = NULL;
    if ((res = tclt_delete_peer(CONTACT1_NAME)) == NULL || strcmp(res, CONTACT1_RES) != 0)
    {
        fprintf(stderr, "res[%s]\n",res);
        if (res != NULL)
            free(res);
        return 1;
    }
    free(res);
    return 0;
}

int
test3()
{
    char *res = NULL;
    if ((res = tclt_delete_peer(CONTACT2_NAME)) == NULL || strcmp(res, CONTACT2_RES) != 0)
    {
        fprintf(stderr, "res[%s]\n",res);
        if (res != NULL)
            free(res);
        return 1;
    }
    free(res);
    return 0;
}

int
test4()
{
    char *res = NULL;
    if ((res = tclt_delete_peer(CONTACT3_NAME)) == NULL || strcmp(res, CONTACT3_RES) != 0)
    {
        fprintf(stderr, "res[%s]\n",res);
        if (res != NULL)
            free(res);
        return 1;
    }
    fprintf(stderr, "res[%s]\n",res);
    free(res);
    return 0;
}

int
test5()
{
    char *res = NULL;
    if ((res = tclt_delete_peer("")) == NULL || strcmp(res, EMPTY_RES) != 0)
    {
        fprintf(stderr, "res[%s]\n",res);
        if (res != NULL)
            free(res);
        return 1;
    }
    fprintf(stderr, "res[%s]\n",res);
    free(res);
    return 0;
}

int
delete_peer_to_parse(void *f, void* intern)
{
    char *name = (char *)f;

    (void)intern;
    if (strcmp(name, CONTACT1_NAME) != 0)
    {
        fprintf(stderr, "name[%s]\n",name);
        return 1;
    }
    return 0;
}

int
test6()
{
    char *res = NULL;

    tclt_set_callback_command(DELETE_PEER_CMD, delete_peer_to_parse);
    if ((res = tclt_delete_peer(CONTACT1_NAME)) == NULL)
    {
        fprintf(stderr, "res[%s]\n",res);
        if (res != NULL)
            free(res);
        return 1;
    }
    if (tclt_dispatch_command(res, NULL) != 0)
        return 1;
    free(res);
    return 0;
}

int
main()
{
    if (test1() == 1)
        return 1;
    printf("test1 passed\n");
    if (test2() == 1)
        return 1;
    printf("test2 passed\n");
    if (test3() == 1)
        return 1;
    printf("test3 passed\n");
    if (test4() == 1)
        return 1;
    printf("test4 passed\n");
    if (test5() == 1)
        return 1;
    printf("test5 passed\n");
    if (test6() == 1)
        return 1;
    printf("test6 passed\n");
    return 0;
}
