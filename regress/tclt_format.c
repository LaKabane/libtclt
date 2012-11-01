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

#include <yajl/yajl_tree.h>
#include "tclt_format.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_KEY    "key"
#define TEST_VALUE    "value"
#define TEST_KEY2    "key2"
#define TEST_VALUE2    "value2"
#define TEST_RES    "{\"key\":\"value\"}"
#define TEST_RES_ARRAY    "[\"value\"]"
#define TEST_RES2    "[{\"key\":\"value\"},{\"key2\":\"value2\"}]"
#define TEST_LEN    15

/*
 * Test NULL input
 */
static int test1()
{
    if (tclt_format(NULL))
    {
        fprintf(stderr, "Test1 failed\n");
        return 1;
    }
    return 0;
}

static int test2()
{
    yajl_val    node_key;
    yajl_val    node_string;
    const char    *key = TEST_KEY;
    int    ok = 0;

    node_key = malloc(sizeof(*node_key));
    node_string = malloc(sizeof(*node_string));
    if (node_key == NULL || node_string == NULL)
    {
        fprintf(stderr, "Test2 failed, due to memory\n");
        return 1;
    }
    node_key->type = yajl_t_object;
    node_key->u.object.keys = &key;
    node_key->u.object.values = &node_string;
    node_key->u.object.len = 1;

    node_string->type = yajl_t_string;
    node_string->u.string = TEST_VALUE;
    if (tclt_get_size(node_key, &ok) != TEST_LEN)
    {
        free(node_key);
        free(node_string);
        fprintf(stderr, "Test2 failed\n");
        return 1;
    }
    free(node_key);
    free(node_string);
    return 0;
}

/*
 * Test Simple case
 */
static int test3()
{
    yajl_val    node_key;
    yajl_val    node_string;
    char    *res;
    const char    *key = TEST_KEY;

    node_key = malloc(sizeof(*node_key));
    node_string = malloc(sizeof(*node_string));
    if (node_key == NULL || node_string == NULL)
    {
        fprintf(stderr, "Test3 failed, due to memory\n");
        return 1;
    }

    node_string->type = yajl_t_string;
    node_string->u.string = TEST_VALUE;

    node_key->type = yajl_t_object;
    node_key->u.object.keys = &key;
    node_key->u.object.values = &node_string;
    node_key->u.object.len = 1;

    res = tclt_format(node_key);
    if (res == NULL || strcmp(res, TEST_RES) != 0)
    {
        fprintf(stderr, "Test3 failed : %s\n", res);
        free(node_key);
        free(node_string);
        if (res == NULL)
            free(res);
        return 1;
    }
    free(res);
    free(node_key);
    free(node_string);
    return 0;
}

static int test4()
{
    yajl_val    node_key;
    yajl_val    node_string;
    char    *res;

    node_key = malloc(sizeof(*node_key));
    node_string = malloc(sizeof(*node_string));
    if (node_key == NULL || node_string == NULL)
    {
        fprintf(stderr, "Test4 failed, due to memory\n");
        return 1;
    }

    node_string->type = yajl_t_string;
    node_string->u.string = TEST_VALUE;

    node_key->type = yajl_t_array;
    node_key->u.array.values = &node_string;
    node_key->u.array.len = 1;

    res = tclt_format(node_key);
    if (res == NULL || strcmp(res, TEST_RES_ARRAY) != 0)
    {
        fprintf(stderr, "Test4 failed : %s\n", res);
        if (res == NULL)
            free(res);
        free(node_key);
        free(node_string);
        return 1;
    }
    free(res);
    free(node_key);
    free(node_string);
    return 0;
}

static int test5()
{
    yajl_val    node_array;
    yajl_val    node_key;
    yajl_val    node_string;
    yajl_val    node_key2;
    yajl_val    node_string2;
    char    *res;
    const char    *key = TEST_KEY;
    const char    *key2 = TEST_KEY2;

    node_key = malloc(sizeof(*node_key));
    node_string = malloc(sizeof(*node_string));
    node_key2 = malloc(sizeof(*node_key2));
    node_string2 = malloc(sizeof(*node_string2));
    node_array = malloc(sizeof(*node_array));
    node_array->u.array.values = malloc(sizeof(*node_array->u.array.values) * 2);
    if (node_key == NULL || node_string == NULL || node_string2 == NULL || node_key2 == NULL || node_array == NULL || node_array->u.array.values == NULL)
    {
        fprintf(stderr, "Test4 failed, due to memory\n");
        return 1;
    }

    node_string->type = yajl_t_string;
    node_string->u.string = TEST_VALUE;
    node_string2->type = yajl_t_string;
    node_string2->u.string = TEST_VALUE2;

    node_key->type = yajl_t_object;
    node_key->u.object.keys = &key;
    node_key->u.object.values = &node_string;
    node_key->u.object.len = 1;

    node_key2->type = yajl_t_object;
    node_key2->u.object.keys = &key2;
    node_key2->u.object.values = &node_string2;
    node_key2->u.object.len = 1;

    node_array->type = yajl_t_array;
    node_array->u.array.len = 2;
    node_array->u.array.values[0] = node_key;
    node_array->u.array.values[1] = node_key2;

    res = tclt_format(node_array);
    if (res == NULL || strcmp(res, TEST_RES2) != 0)
    {
        fprintf(stderr, "Test4 failed : %s\n", res);
        free(node_key);
        free(node_string);
        free(node_key2);
        free(node_string2);
        free(node_array->u.array.values);
        free(node_array);
        if (res == NULL)
            free(res);
        return 1;
    }
    free(res);
    free(node_key);
    free(node_string);
    free(node_key2);
    free(node_string2);
    free(node_array->u.array.values);
    free(node_array);
    return 0;
}

int main()
{
    if (test1() == 1)
        return 1;
    if (test2() == 1)
        return 1;
    if (test3() == 1)
        return 1;
    if (test4() == 1)
        return 1;
    if (test5() == 1)
        return 1;
    return 0;
}
