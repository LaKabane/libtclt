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

#include <stdlib.h>
#include <string.h>

#include "tclt.h"

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

void    tclt_add_peer()
{
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
