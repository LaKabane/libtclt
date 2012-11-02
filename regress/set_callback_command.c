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
#include "tclt_command.h"
#include "tclt_parse.h"

#include <stdio.h>
#include <string.h>

#define TEST_CMD1  "{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"key1\",\"Ip\":\"10.0.0.1\"}}"
#define TEST_CMD2  "[{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"key1\",\"Ip\":\"10.0.0.1\"}}]"
#define TEST_CMD3  "[{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"key1\",\"Ip\":\"10.0.0.1\"}},{\"AddContact\":{\"Name\":\"contact1\",\"Key\":\"key1\",\"Ip\":\"10.0.0.1\"}}]"

#define TEST_CMD1_NAME "contact1"
#define TEST_CMD1_IP "10.0.0.1"
#define TEST_CMD1_KEY "key1"


int
test1()
{
    if (get_callback_command(ADD_PEER_CMD) == NULL)
        return 0;
    return 1;
}

int
test_func0(void *f)
{
    (void)f;
    return 0;
}

int
test_func1(void *f)
{
    (void)f;
    return 1;
}

int
test_peer_func(void *f)
{
    peer *p = (peer*)f;
    if (p == NULL)
        return 1;
    if (strcmp(p->name, TEST_CMD1_NAME) != 0)
        return 1;
    if (strcmp(p->key, TEST_CMD1_KEY) != 0)
        return 1;
    if (strcmp(p->ip, TEST_CMD1_IP) != 0)
        return 1;
    return 0;
}

int
test2()
{
    int  (*f)(void*);
    set_callback_command(ADD_PEER_CMD, &test_func0);
    set_callback_command(DELETE_PEER_CMD, &test_func1);
    f = (int(*)(void*))get_callback_command(ADD_PEER_CMD);
    if (f == NULL || f(NULL) != 0)
        return 1;
    f = (int(*)(void*))get_callback_command(DELETE_PEER_CMD);
    if (f == NULL || f(NULL) != 1)
        return 1;
    return 0;
}

int
test3()
{
    set_callback_command(ADD_PEER_CMD, &test_func1);
    if (tclt_dispatch_command(TEST_CMD1) != 1)
        return 1;
    return 0;
}

int
test4()
{
    set_callback_command(ADD_PEER_CMD, &test_func0);
    if (tclt_dispatch_command(TEST_CMD1) != 0)
        return 1;
    return 0;
}

int
test5()
{
    set_callback_command(ADD_PEER_CMD, NULL);
    if (tclt_dispatch_command(TEST_CMD1) != 1)
        return 1;
    return 0;
}

int
test6()
{
    set_callback_command(ADD_PEER_CMD, &test_func0);
    if (tclt_dispatch_command(TEST_CMD2) != 0)
        return 1;
    return 0;
}

int
test7()
{
    set_callback_command(ADD_PEER_CMD, &test_func0);
    if (tclt_dispatch_command(TEST_CMD3) != 0)
        return 1;
    return 0;
}

int
test8()
{
    set_callback_command(ADD_PEER_CMD, &test_peer_func);
    if (tclt_dispatch_command(TEST_CMD1) != 0)
        return 1;
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
    if (test7() == 1)
        return 1;
    printf("test7 passed\n");
    if (test8() == 1)
        return 1;
    printf("test8 passed\n");
    return 0;
}
