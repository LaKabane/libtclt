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

#include <stdio.h>

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
    return 0;
}

int
test_func1(void *f)
{
    return 0;
}

int
test2()
{
    int  (*f)(void*);
    set_callback_command(ADD_PEER_CMD, &test_func0);
    set_callback_command(DELETE_PEER_CMD, &test_func1);
    f = get_callback_command(ADD_PEER_CMD);
    if (f == NULL || f(NULL) != 0)
        return 1;
    f = get_callback_command(DELETE_PEER_CMD);
    if (f == NULL || f(NULL) != 1)
        return 1;
    return 0;
}

int
main()
{
    if (test1() == 1)
        return 1;
    printf("test1 passed\n");
    return 0;
}
