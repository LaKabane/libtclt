#include <yajl/yajl_tree.h>
#include "tclt_format.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_KEY    "test"
#define TEST_VALUE    "test"
#define TEST_RES    "{\"test\":\"test\"}"
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
    char    *res;
    const char    *key = TEST_KEY;

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
    if (tclt_get_size(node_key) != TEST_LEN)
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
    node_key->type = yajl_t_object;
    node_key->u.object.keys = &key;
    node_key->u.object.values = &node_string;
    node_key->u.object.len = 1;

    node_string->type = yajl_t_string;
    node_string->u.string = TEST_VALUE;
    res = tclt_format(node_key);
    if (res == NULL || strcmp(res, TEST_RES) != 0)
    {
        fprintf(stderr, "Test3 failed : %s\n", res);
        free(node_key);
        free(node_string);
        return 1;
    }
    free(node_key);
    free(node_string);
    return 0;
}

static int test4()
{
    if (0)
    {
        fprintf(stderr, "Test4 failed\n");
        return 1;
    }
    return 0;
}

static int test5()
{
    if (0)
    {
        fprintf(stderr, "Test5 failed\n");
        return 1;
    }
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
