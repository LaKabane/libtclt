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

#ifndef TCLT_PARSE_H_
# define TCLT_PARSE_H_

#include <yajl/yajl_tree.h>
#include <stddef.h>

#include "tclt.h"
#include "tclt_import.h"

# ifdef __cplusplus
extern "C" {
# endif

struct t_fun_args
{
    yajl_val node;
    const char *name;
};
    typedef struct t_fun_args fun_args;

    yajl_val   tclt_parse(const char *str);
    TCLT_EXPORT int    tclt_dispatch_command(const char *str, void *intern);

#define BUFF_LEN 4096
#define TCLT_KEY   "Key"
#define TCLT_IP   "Ip"
#define TCLT_NAME   "Name"

# ifdef __cplusplus
}
# endif

#endif
