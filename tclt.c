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

static void
free_node(yajl_val node)
{
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
tclt_make_node_peer(peer *peer)
{
    yajl_val node = NULL;
    yajl_val ip;
    yajl_val name;
    yajl_val key;

    node = malloc(sizeof(*node));
    if (node == NULL)
    {
        fprintf(stderr, "tclt_make_node_peer: out of memory\n");
        return NULL;
    }
    node->type = yajl_t_object;
    node->u.object.len = 3;
    node->u.object.keys = malloc(sizeof(*node->u.object.keys) * 3);
    if (node->u.object.keys == NULL)
    {
        free(node);
        fprintf(stderr, "tclt_make_node_peer: out of memory\n");
        return NULL;
    }

    node->u.object.values = malloc(sizeof(*node->u.object.values) * 3);
    if (node->u.object.values == NULL)
    {
        free(node);
        free(node->u.object.keys);
        fprintf(stderr, "tclt_make_node_peer: out of memory\n");
        return NULL;
    }

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
    char    *tmp_key = NULL;

    if (nb == 0)
        return NULL;
    node = malloc(sizeof(*node));
    if (node == NULL)
    {
        fprintf(stderr, "tclt_add_peers: out of memory\n");
        return NULL;
    }
    node->type = yajl_t_array;
    node->u.array.len = nb;
    node->u.array.values = malloc(sizeof(*node->u.array.values) * nb);
    if (node->u.array.values == NULL)
    {
        fprintf(stderr, "tclt_add_peers: out of memory\n");
        return NULL;
    }
    for (i=0; i < nb; ++i)
    {
        tmp_node = malloc(sizeof(*tmp_node));
        if (tmp_node == NULL)
        {
            fprintf(stderr, "tclt_add_peers: out of memory\n");
            return NULL;
        }
        tmp_node->type = yajl_t_object;
        tmp_key = strdup(ADD_PEER_CMD);
        if (tmp_key == NULL)
        {
            fprintf(stderr, "tclt_add_peers: out of memory\n");
            return NULL;
        }
        tmp_node->u.object.len = 1;
        tmp_node->u.object.keys = &tmp_key;
        yajl_val *tmp = malloc(sizeof(*tmp));
        if (tmp == NULL)
        {
            fprintf(stderr, "tclt_add_peers: out of memory\n");
            return NULL;
        }
        tmp[0] = tclt_make_node_peer(&peers[i]);
        tmp_node->u.object.values = tmp;
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

void    tclt_delete_peer()
{
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
