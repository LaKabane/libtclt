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

#define REAL_LOG    "this is a real log test"

#define RES_NOLOG   "{\"AddLog\":\"\"}"
#define RES_REAL_LOG    "{\"AddLog\":\"this is a real log test\"}"


int
test1()
{
    if (tclt_add_log(NULL) == NULL)
        return 0;
    return 1;
}

int
test2()
{
    char *res = NULL;

    res = tclt_add_log("");
    if (res == NULL || strcmp(res, RES_NOLOG) != 0)
    {
        printf("%s\n", res);
        return 1;
    }
    return 0;
}

int
test3()
{
    char *res = NULL;

    res = tclt_add_log(REAL_LOG);
    if (res == NULL || strcmp(res, RES_REAL_LOG) != 0)
    {
        printf("%s\n", res);
        return 1;
    }
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
    return 0;
}
