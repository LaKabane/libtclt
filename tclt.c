/*
 * Copyright (c) 2012 Tristan Le Guern <leguern AT medu DOT se>
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

#include <sys/types.h>
#include <yajl/yajl_tree.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tclt.h"
#include "tclt_format.h"
#include "tclt_command.h"

static void free_node(yajl_val node);

call_command commands[] =
    {
        {ADD_PEER_CMD, NULL},
        {DELETE_PEER_CMD, NULL},
        {EDIT_PEER_CMD, NULL},
        {ADD_LOG_CMD, NULL}
    };

void
tclt_init(void) {
	/* Do nothing for the moment */
}

void
tclt_destroy(void) {
	/* Do nothing for the moment */
}

int
tclt_get_version(void) {
	return LIB_TNETACLE_CLIENT_VERSION;
}

int
tclt_set_callback_command(const char *cmd, int (*f)(void*))
{
    unsigned int i;

    for (i=0; i < sizeof(commands)/sizeof(*commands); ++i)
    {
        if (strcmp(commands[i].cmd_name, cmd) == 0)
        {
            commands[i].f = f;
            return 0;
        }
    }
    return 1;
}

void*
tclt_get_callback_command(const char *cmd)
{
    unsigned int i;

    for (i=0; i < sizeof(commands)/sizeof(*commands); ++i)
    {
        if (strcmp(commands[i].cmd_name, cmd) == 0)
        {
            return (commands[i].f);
        }
    }
    return NULL;
}

static void
free_array(yajl_val node)
{
    unsigned int i;

    for (i=0; i < node->u.array.len; ++i)
    {
        free_node(node->u.array.values[i]);
    }
    free(node->u.array.values);
    free(node);
}

static void
free_object(yajl_val node)
{
    unsigned int i;

    for (i=0; i < node->u.object.len; ++i)
    {
        free_node(node->u.object.values[i]);
    }
    free(node->u.object.values);
    free(node->u.object.keys);
    free(node);
}

static void
free_string(yajl_val node)
{
    free(node->u.string);
    free(node);
}

static void
free_node(yajl_val node)
{
    if (YAJL_IS_ARRAY(node))
        free_array(node);
    else if (YAJL_IS_OBJECT(node))
        free_object(node);
    else if (YAJL_IS_STRING(node))
        free_string(node);
    else
        free(node);
}

static yajl_val
tclt_make_string_node(const char* val)
{
    yajl_val node = NULL;

    node = malloc(sizeof(*node));
    if (node == NULL)
    {
        fprintf(stderr, "tclt_make_string_node: out of memory\n");
        return NULL;
    }
    node->type = yajl_t_string;
    if (val != NULL)
        node->u.string = strdup(val);
    else
        node->u.string = strdup("");
    if (node->u.string == NULL)
    {
        fprintf(stderr, "tclt_make_string_node: out of memory\n");
        return NULL;
    }
    return node;
}

static yajl_val
tclt_make_object_node(unsigned int len)
{
    yajl_val node = NULL;

    node = malloc(sizeof(*node));
    if (node == NULL)
    {
        fprintf(stderr, "tclt_make_object_node: out of memory\n");
        return NULL;
    }
    node->type = yajl_t_object;
    node->u.object.len = len;
    node->u.object.keys = malloc(sizeof(*node->u.object.keys) * len);
    if (node->u.object.keys == NULL)
    {
        free(node);
        fprintf(stderr, "tclt_make_object_node: out of memory\n");
        return NULL;
    }
    node->u.object.values = malloc(sizeof(*node->u.object.values) * len);
    if (node->u.object.values == NULL)
    {
        free(node);
        free(node->u.object.keys);
        fprintf(stderr, "tclt_make_object_node: out of memory\n");
        return NULL;
    }
    return (node);
}

static yajl_val
tclt_make_array_node(unsigned int len)
{
    yajl_val node = NULL;

    node = malloc(sizeof(*node));
    if (node == NULL)
    {
        fprintf(stderr, "tclt_make_array_node: out of memory\n");
        return NULL;
    }
    node->type = yajl_t_array;
    node->u.array.len = len;
    node->u.array.values = malloc(sizeof(*node->u.array.values) * len);
    if (node->u.array.values == NULL)
    {
        free(node);
        fprintf(stderr, "tclt_make_array_node: out of memory\n");
        return NULL;
    }
    return (node);
}

static yajl_val
tclt_make_node_peer(peer *peer)
{
    yajl_val node = NULL;
    yajl_val ip;
    yajl_val name;
    yajl_val key;

    if ((node = tclt_make_object_node(3)) == NULL)
        return NULL;

    name = tclt_make_string_node(peer->name);
    ip = tclt_make_string_node(peer->ip);
    key = tclt_make_string_node(peer->key);
    if (name == NULL || ip == NULL || key == NULL)
    {
        free(node);
        free(node->u.object.keys);
        free(node->u.object.values);
        return NULL;
    }
    /* TODO : verify the strdup */
    node->u.object.keys[0] = "Name";
    node->u.object.values[0] = name;

    node->u.object.keys[1] = "Key";
    node->u.object.values[1] = key;

    node->u.object.keys[2] = "Ip";
    node->u.object.values[2] = ip;
    
    return node;
}

char*
tclt_add_peers(peer *peers, unsigned int nb)
{
    yajl_val    node = NULL;
    yajl_val tmp_node = NULL;
    unsigned int i;
    char    *format = NULL;

    if (nb == 0)
        return NULL;
    if ((node = tclt_make_array_node(nb)) == NULL)
        return NULL;
    for (i=0; i < nb; ++i)
    {
        if ((tmp_node = tclt_make_object_node(1)) == NULL)
            return NULL;

        tmp_node->u.object.keys[0] = ADD_PEER_CMD;
        tmp_node->u.object.values[0] = tclt_make_node_peer(&peers[i]);
        node->u.array.values[i] = tmp_node;
    }
    format = tclt_format(node);
    free_node(node);
    return format;
}

void    tclt_add_list_of_peers()
{
}

char    *tclt_add_connection()
{
    return NULL;
}

void    tclt_add_tunnel()
{
}

void    tclt_delete_connection()
{
}

void    tclt_stop_tunnel()
{
}

char*
tclt_delete_peer(const char *peer)
{
    char *res = NULL;
    yajl_val node;

    if (peer == NULL)
        return NULL;
    if ((node = tclt_make_object_node(1)) == NULL)
        return NULL;

    node->u.object.keys[0] = DELETE_PEER_CMD;
    node->u.object.values[0] = tclt_make_string_node(peer);
    res = tclt_format(node);
    free_node(node);
    return res;
}

void    tclt_clear_peers()
{
}

void    tclt_edit_peer()
{
}

void    tclt_create_group()
{
}

void    tclt_destroy_group()
{
}

void    tclt_add_peer_to_group()
{
}

void    tclt_clear_group()
{
}

void    tclt_edit_config()
{
}

void    tclt_add_public_key()
{
}

void    tclt_add_key_for_peer()
{
}

void    tclt_add_key_for_client()
{
}

char*
tclt_add_log(const char *log)
{
    yajl_val    node = NULL;
    yajl_val tmp_node = NULL;
    char    *format = NULL;

    if (log == NULL)
        return NULL;
    if ((node = tclt_make_object_node(1)) == NULL)
        return NULL;
    if ((tmp_node = tclt_make_string_node(log)) == NULL)
        return NULL;

    node->u.object.keys[0] = ADD_LOG_CMD;
    node->u.object.values[0] = tmp_node;
    format = tclt_format(node);
    free_node(node);
    return format;
}
