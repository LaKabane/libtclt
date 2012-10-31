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

#include "tclt_format.h"

#include <yajl/yajl_tree.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t    tclt_get_size(yajl_val node, int *ok)
{
    size_t    len = 0;
    int    i = 0;

    if (node == NULL)
    {
        *ok = 1;
        return len;
    }
    if (node->type == yajl_t_string)
    {
        len = 2; /* for '{' and '}' */
        len += strlen(node->u.string);
    }
    else if (node->type == yajl_t_object)
    {
        len = 2; /* for '{' and '}' */
        for (i = 0; i < node->u.object.len; ++i)
        {
            len += 3; /* for the double quote of the key and the semicolon*/
            len += strlen(node->u.object.keys[i]);
            len += tclt_get_size(node->u.object.values[i], ok);
        }
    }
    else if (node->type == yajl_t_array)
    {
        len = 2; /* for '[' and ']' */
        for (i = 0; i < node->u.array.len; ++i)
        {
            len += tclt_get_size(node->u.array.values[i], ok);
            if (i + 1 != node->u.array.len)
                len += 1; /* for the ',' */
        }
    }
    else
    {
        *ok = 1;
    }
    return len;
}

void    make_string(yajl_val node, char *str, size_t len)
{
    int    i;

    if (node->type == yajl_t_string)
    {
        strncat(str, "\"", 1);
        strncat(str, node->u.string, strlen(node->u.string));
        strncat(str, "\"", 1);
        len += strlen(node->u.string) + 2;
    }
    else if (node->type == yajl_t_object)
    {
        strncat(str, "{", 1);
        for (i = 0; i < node->u.object.len; ++i)
        {
            strncat(str, "\"", 1);
            strncat(str, node->u.object.keys[i], strlen(node->u.object.keys[i]));
            strncat(str, "\":", 2);
            make_string(node->u.object.values[i], str, len);
            if (i + 1 != node->u.object.len)
                strncat(str, ",", 1);
        }
        strncat(str, "}", 1);
        len += 2;
    }
    else if (node->type == yajl_t_array)
    {
        strncat(str, "[", 1);
        for (i = 0; i < node->u.array.len; ++i)
        {
            make_string(node->u.array.values[i], str, len);
            if (i + 1 != node->u.array.len)
                strncat(str, ",", 1);
        }
        strncat(str, "]", 1);
        len += 2;
    }
}

char    *tclt_format(yajl_val node)
{
    size_t    len = 1;
    char    *str_made = NULL;
    int    ok = 0;

    if (node == NULL)
        return NULL;
    len += tclt_get_size(node, &ok);
    if (ok == 1)
    {
        fprintf(stderr, "tclt_format: error in the type node\n");
        return NULL;
    }
    str_made = malloc(len * sizeof(*str_made));
    str_made[0] = '\0';
    if (str_made == NULL)
    {
        fprintf(stderr, "tclt_format: not enough memory\n");
        return str_made;
    }
    make_string(node, str_made, 0);
    return str_made;
}
