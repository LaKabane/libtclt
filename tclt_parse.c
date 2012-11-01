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
#include "tclt.h"

#include <yajl/yajl_tree.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
