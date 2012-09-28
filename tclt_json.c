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

#include "tclt_json.h"
#include <yajl/yajl_parse.h>
#include <yajl/yajl_gen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if Windows
static char *
strndup(char *src, size_t size)
{
    char *tmp;

    tmp = (char *)malloc(size);
    if (tmp == NULL)
        return NULL;
    return (char *)memcpy(tmp, src, size);
}
#endif

static elements*
new_element()
{
	elements *e;
	e = (elements*)malloc(sizeof(*e));
	if (e == NULL)
		return NULL;
	e->next = NULL;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.boolean = 0;
	e->type = E_NOTHING;
	return e;
}

static int
yajl_null(void *ctx)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || (*ele) == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.boolean = 0;
	e->type = E_NULL_ELE;
	*ele = e->next;
	return 1;
}

static int
yajl_boolean(void *ctx, int boolean)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.boolean = boolean;
	e->type = E_BOOL;
	*ele = e->next;
	return 1;
}

static int
yajl_integer(void *ctx, long long val)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.integer = 0;
	e->type = E_INT;
	*ele = e->next;
	return 1;
}

static int
yajl_double(void *ctx, double val)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.floating = val;
	e->type = E_DOUBLE;
	*ele = e->next;
	return 1;
}

static int
yajl_number(void *ctx, const char* s, size_t l)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.buf = strndup(s, l);
	e->type = E_NUMBER;
	*ele = e->next;
	return 1;
}

static int
yajl_string(void *ctx, const unsigned char* s, size_t l)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.buf = strndup((const char*)s, l);
	e->type = E_STRING;
	*ele = e->next;
	return 1;
}

static int
yajl_start_map(void *ctx)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.boolean = 0;
	e->type = E_START_MAP;
	*ele = e->next;
	return 1;
}

static int
yajl_map_key(void *ctx, const unsigned char* s, size_t l)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.buf = strndup((const char *)s, l);
	e->type = E_MAP_KEY;
	*ele = e->next;
	return 1;
}

static int
yajl_end_map(void *ctx)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.boolean = 0;
	e->type = E_END_MAP;
	*ele = e->next;
	return 1;
}

static int
yajl_start_array(void *ctx)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.boolean = 0;
	e->type = E_START_ARRAY;
	*ele = e->next;
	return 1;
}

static int
yajl_end_array(void *ctx)
{
	elements **ele = (elements**)ctx;
	elements *e;

	if (ele == NULL || *ele == NULL)
		return -1;
	if ((e = new_element()) == NULL)
	  return -1;
	(*ele)->next = e;
	e = *ele;
	/* e->name = NULL; */
	/* e->len = 0; */
	e->u_value.boolean = 0;
	e->type = E_END_ARRAY;
	*ele = e->next;
	return 1;
}

static yajl_callbacks callbacks = {
	    yajl_null,
		yajl_boolean,
		yajl_integer,
		yajl_double,
		yajl_number,
		yajl_string,
		yajl_start_map,
		yajl_map_key,
		yajl_end_map,
		yajl_start_array,
		yajl_end_array
};

elements*
tclt_parse(const char *buf, size_t len)
{
	yajl_handle handler;
	yajl_status status;
	elements *e;
	elements *first;

	if ((e = new_element()) == NULL)
		return NULL;
	first = e;
	handler = yajl_alloc(&callbacks, NULL, &e);
	status = yajl_parse(handler, (const unsigned char*)buf, len);

	if (status != yajl_status_ok) {
		unsigned char * str = yajl_get_error(handler, 1, (const unsigned char*)buf, len);
		fprintf(stderr, "%s", (const char *) str);
		yajl_free_error(handler, str);
		return NULL;
	}

	status = yajl_complete_parse(handler);
	if (status != yajl_status_ok) {
		unsigned char * str = yajl_get_error(handler, 1, (const unsigned char*)buf, len);
		fprintf(stderr, "%s", (const char *) str);
		yajl_free_error(handler, str);
	}
	yajl_free(handler);
	return first;
}
