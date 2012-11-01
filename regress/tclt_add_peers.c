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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yajl/yajl_tree.h>

#define CONTACT1_NAME "contact1"
#define CONTACT2_NAME "contact2"
#define CONTACT3_NAME "contact3"

#define CONTACT1_KEY "key1"
#define CONTACT2_KEY "key2"
#define CONTACT3_KEY "key3"

#define CONTACT1_IP "10.0.0.1"
#define CONTACT2_IP "10.0.0.2"
#define CONTACT3_IP "10.0.0.3"

#define RES_SIMPLE    "[{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"key1\",\"Ip\":\"10.0.0.1\"}}]"
#define RES_TRIPLE    "[{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"key1\",\"Ip\":\"10.0.0.1\"}},{\"AddContact\":{\"Name\":\"contact2\",\"Key\":\"key2\",\"Ip\":\"10.0.0.2\"}},{\"AddContact\":{\"Name\":\"contact3\",\"Key\":\"key3\",\"Ip\":\"10.0.0.3\"}}]"
#define RES_SIMPLE_WT_KEY    "[{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"\",\"Ip\":\"10.0.0.1\"}}]"
#define RES_SIMPLE_WT_IP    "[{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"key1\",\"Ip\":\"\"}}]"
#define RES_SIMPLE_WT_NAME    "[{\"AddContact\":{\"Name\":\"\",\"Key\":\"key1\",\"Ip\":\"10.0.0.1\"}}]"

int
test1()
{
    if (tclt_add_peers(NULL, 0) == NULL)
        return 0;
    return 1;
}

int
test2()
{
    peer p;
    char *res = NULL;

    p.name = CONTACT1_NAME;
    p.key = CONTACT1_KEY;
    p.ip = CONTACT1_IP;
    res = tclt_add_peers(&p, 1);
    if (res == NULL || strcmp(res, RES_SIMPLE) != 0)
    {
        fprintf(stderr, "res=[%s]\n", res);
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
    peer p[3];
    char *res = NULL;

    p[0].name = CONTACT1_NAME;
    p[0].key = CONTACT1_KEY;
    p[0].ip = CONTACT1_IP;

    p[1].name = CONTACT2_NAME;
    p[1].key = CONTACT2_KEY;
    p[1].ip = CONTACT2_IP;

    p[2].name = CONTACT3_NAME;
    p[2].key = CONTACT3_KEY;
    p[2].ip = CONTACT3_IP;
    res = tclt_add_peers(&p[0], 3);
    if (res == NULL || strcmp(res, RES_TRIPLE) != 0)
    {
        if (res != NULL)
            free(res);
        fprintf(stderr, "res=[%s]\n", res);
        return 1;
    }
    free(res);
    return 0;
}

int
test4()
{
    peer p;
    char *res = NULL;

    p.name = CONTACT1_NAME;
    p.key = NULL;
    p.ip = CONTACT1_IP;
    res = tclt_add_peers(&p, 1);
    if (res == NULL || strcmp(res, RES_SIMPLE_WT_KEY) != 0)
        {
        if (res != NULL)
            free(res);
        fprintf(stderr, "res=[%s]\n", res);
        return 1;
    }
    free(res);
    return 0;
}

int
test5()
{
    peer p;
    char *res = NULL;

    p.name = CONTACT1_NAME;
    p.key = CONTACT1_KEY;
    p.ip = NULL;
    res = tclt_add_peers(&p, 1);
    if (res == NULL || strcmp(res, RES_SIMPLE_WT_IP) != 0)
    {
        if (res != NULL)
            free(res);
        fprintf(stderr, "res=[%s]\n", res);
        return 1;
    }
    free(res);
    return 0;
}

int
test6()
{
    peer p;
    char *res = NULL;

    p.name = NULL;
    p.key = CONTACT1_KEY;
    p.ip = CONTACT1_IP;
    res = tclt_add_peers(&p, 1);
    if (res == NULL || strcmp(res, RES_SIMPLE_WT_NAME) != 0)
    {
        if (res != NULL)
            free(res);
        fprintf(stderr, "res=[%s]\n", res);
        return 1;
    }
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
