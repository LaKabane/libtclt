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

#include "tclt_parse.h"
#include "tclt_command.h"
#include "tclt.h"

#include <yajl/yajl_tree.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int no_arg_dispatch(void *ptr);

static call_command dispatch_cmd [] =
    {
        {ADD_PEER_CMD, no_arg_dispatch},
        {DELETE_PEER_CMD, no_arg_dispatch},
        {EDIT_PEER_CMD, no_arg_dispatch},
        {ADD_LOG_CMD, no_arg_dispatch}
    };

yajl_val   tclt_parse(const char *str)
{
    yajl_val node;
    char    errbuf[BUFF_LEN];

    errbuf[0] = 0;
    node = yajl_tree_parse(str, errbuf, sizeof(errbuf));

    if (node == NULL)
    {
        fprintf(stderr, "parse_error: ");
        if (strlen(errbuf))
            fprintf(stderr, " %s\n", errbuf);
        else
            fprintf(stderr, "unknown error\n");
        return NULL;
    }
    return node;
}

static int
no_arg_dispatch(void *ptr)
{
    fun_args *args = ptr;
    int  (*f)(void*);

    f = get_callback_command(args->name);
    if (f == NULL)
    {
        fprintf(stderr, "Command not found : %s\n", args->name);
        return 1;
    }
    return (f(NULL));
}

int
tclt_dispatch_object_command(yajl_val node)
{
    unsigned int i;
    unsigned int j;
    fun_args tmp;
    int     res = 1;

    for (i=0; i < YAJL_GET_OBJECT(node)->len; ++i)
    {
        tmp.name = YAJL_GET_OBJECT(node)->keys[i];
        tmp.node = YAJL_GET_OBJECT(node)->values[i];
        for (j=0; j < sizeof(dispatch_cmd) / sizeof(*dispatch_cmd); ++j)
        {
            if (strcmp(dispatch_cmd[j].cmd_name, tmp.name) == 0)
            {
                res = dispatch_cmd[j].f(&tmp);
            }
        }
    }
    return res;
}

int
tclt_dispatch_array_command(yajl_val node)
{
    unsigned int i;
    int     res = 1;

    for (i=0; i < YAJL_GET_ARRAY(node)->len; ++i)
    {
        if (YAJL_IS_OBJECT(YAJL_GET_ARRAY(node)->values[i]))
            res = tclt_dispatch_object_command(YAJL_GET_ARRAY(node)->values[i]);
        else
            return 1;
    }
    return res;
}

int
tclt_dispatch_command(const char *str)
{
    yajl_val node;
    int    res = 1;

    node = tclt_parse(str);
    if (str == NULL || node == NULL)
    {
        fprintf(stderr, "tclt_dispatch_command : command unknown [%s]\n", str);
        return 1;
    }
    if (YAJL_IS_ARRAY(node))
    {
        res = tclt_dispatch_array_command(node);
    }
    if (YAJL_IS_OBJECT(node))
    {
        res = tclt_dispatch_object_command(node);
    }
    free(node);
    return res;
}
