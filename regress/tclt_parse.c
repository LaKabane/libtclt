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

#include <stdio.h>
#include <string.h>
#include <yajl/yajl_tree.h>
#include "tclt_parse.h"
#include "tclt.h"

#define TEST_EMPTY  ""
#define TEST_ERROR  "[{\"key\":\"value\"}"
#define TEST_SIMPLE_OBJECT  "{\"key\":\"value\"}"
#define TEST_SIMPLE_ARRAY  "[\"value\"]"
#define KEY "key"
#define VALUE "value"


int
testAddContact(void *data)
{
    peer* p = (peer*)data;

    printf("data[%s] [%s] [%s]\n", p->name, p->ip, p->key);
    return 0;
}

int
test1()
{
    yajl_val node = tclt_parse(TEST_EMPTY);
    if (node != NULL)
        return 1;
    return 0;
}

int
test2()
{
    yajl_val node = tclt_parse(TEST_ERROR);
    if (node != NULL)
        return 1;
    return 0;
}

int
test3()
{
    yajl_val node = tclt_parse(TEST_SIMPLE_OBJECT);

    if (YAJL_GET_OBJECT(node) != NULL && YAJL_GET_OBJECT(node)->len == 1 && YAJL_IS_STRING(YAJL_GET_OBJECT(node)->values[0])
        && strcmp(YAJL_GET_OBJECT(node)->keys[0], KEY) == 0)
    {
        char *str = YAJL_GET_STRING(YAJL_GET_OBJECT(node)->values[0]);
        if (strcmp(str, VALUE) == 0)
            return 0;
    }
    return 1;
}

int
test4()
{
    yajl_val node = tclt_parse(TEST_SIMPLE_ARRAY);

    if (YAJL_GET_ARRAY(node) != NULL && YAJL_GET_ARRAY(node)->len == 1 && YAJL_IS_STRING(YAJL_GET_ARRAY(node)->values[0]))
    {
        char *str = YAJL_GET_STRING(YAJL_GET_ARRAY(node)->values[0]);
        if (strcmp(str, VALUE) == 0)
            return 0;
    }
    return 1;
}

int
main()
{
    if (test1() == 1)
        return 1;
    if (test2() == 1)
        return 1;
    if (test3() == 1)
        return 1;
    if (test4() == 1)
        return 1;
    return 0;
}
