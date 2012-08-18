/*
 * Copyright (c) 2012 Florent Tribouilloy <florent.tribouilloy AT epitech DOT net>
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

#include "json_parse.h"
#include <yajl/yajl_parse.h>
#include <yajl/yajl_gen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef QT

#include <QVariant>

static QVariant createVariantSimple(elements **e, bool &ok);
static QVariant createVariantArray(elements **e, bool &ok);
static QVariant createVariantMap(elements **e, bool &ok);
static QVariant createVariantWithKey(elements **e, bool &ok);

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
	e->type = NOTHING;
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
	e->type = NULL_ELE;
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
	e->type = BOOL;
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
	e->type = INT;
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
	e->type = DOUBLE;
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
	e->type = NUMBER;
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
	e->type = STRING;
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
	e->type = START_MAP;
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
	e->type = MAP_KEY;
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
	e->type = END_MAP;
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
	e->type = START_ARRAY;
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
	e->type = END_ARRAY;
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
parse(const char *buf, size_t len)
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

#ifdef QT

eType types[] =
	{
		{START_MAP, &createVariantMap},
		{START_ARRAY, &createVariantArray},
	};

static QVariant
createVariantSimple(elements **e, bool &ok)
{
	QVariant qvar;

	if (e != 0 && *e != 0)
	{
		qvar.setValue(QString((*e)->u_value.buf));
	}
	return qvar;
}

static QVariant
createVariantMap(elements **e, bool &ok)
{
	QMap<QString, QVariant> qmap;

	if (e != 0)
	{
		while (*e != NULL && (*e)->type != NOTHING && (*e)->type != END_MAP)
		{
			if (*e != 0 && (*e)->type == MAP_KEY)
			{
				QString key((*e)->u_value.buf);
				*e = (*e)->next;
				if ((*e)->type == START_ARRAY || (*e)->type == START_MAP)
				{
					for (int i=0; i < (sizeof(types) / sizeof(eType)); ++i)
					{
						if (types[i].type == (*e)->type)
						{
							*e = (*e)->next;
							QVariant ret = types[i].fun(e, ok);
							qmap[key] = ret;
							break;
						}
					}
				}
				else if ((*e)->type != NOTHING)
				{
					QVariant ret = createVariantSimple(e, ok);
					qmap[key] = ret;
					*e = (*e)->next;
				}
				else if (*e != NULL)
					*e = (*e)->next;
			}
		}
		if (*e != NULL && (*e)->type == END_MAP)
		{
			*e = (*e)->next;
			return qmap;
		}
	}
	ok = false;
	return qmap;
}

static QVariant
createVariantArray(elements **e, bool &ok)
{
	QVariantList qlist;

	if (e != 0)
	{
		while (*e != NULL && (*e)->type != NOTHING && (*e)->type != END_ARRAY)
		{
			if ((*e)->type == START_ARRAY || (*e)->type == START_MAP)
			{
				for (int i=0; i < (sizeof(types) / sizeof(eType)); ++i)
				{
					if (types[i].type == (*e)->type)
					{
						*e = (*e)->next;
						QVariant ret = types[i].fun(e, ok);
						qlist.append(ret);
						break;
					}
				}

			}
			else
			{
				QVariant ret = createVariantSimple(e, ok);
				qlist.append(ret);
				*e = (*e)->next;
			}
		}
		if ((*e) != NULL && (*e)->type == END_ARRAY)
		{
			*e = (*e)->next;
			return qlist;
		}
	}
	ok = false;
	return qlist;
}

static QVariant*
createVariant(elements *e)
{
	QVariant *qvar = 0;
	elements *tmp = e;

	if (tmp != NULL && tmp->type != NOTHING)
	{
		if (tmp->type == START_ARRAY || tmp->type == START_MAP)
		{
			for (unsigned int i=0; i < sizeof(types)/sizeof(eType); ++i)
			{
				tmp = tmp->next;
				bool ok = true;
				QVariant ret = createVariantArray(&tmp, ok);
				if (ok == false)
				{
					fprintf(stderr, "Problem to parse the elements list\n");
					return 0;
				}
				qvar = new QVariant(ret);
				if (qvar == 0)
				{
					fprintf(stderr, "Error to allocate a new QVariant\n");
					return 0;
				}
				break;
			}
		}
	}
	if (tmp != NULL && tmp->type != NOTHING)
	{
		fprintf(stderr, "Error, buffer received not at the end\n");
		return qvar;
	}
	return qvar;
}

QVariant*
getVariant(const char *buf, size_t len)
{
	QVariant* qvar = 0;
	elements* e = parse(buf, len);

	if (e == 0)
		return 0;

	qvar = createVariant(e);
	return qvar;
}

#endif /* !QT */
