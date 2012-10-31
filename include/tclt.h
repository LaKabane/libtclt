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

#ifndef TNETACLE_TCLT_H_
#define TNETACLE_TCLT_H_

#include "tclt_import.h"

struct t_peer
{
    char *name;
    char *key;
    char *ip;
};
typedef struct t_peer peer;

TCLT_EXPORT void    tclt_init(void);
TCLT_EXPORT void    tclt_destroy(void);
TCLT_EXPORT int     tclt_get_versin(void);

/*
*** Peer related
 */
TCLT_EXPORT char    *tclt_add_peers(peer *peers, unsigned int nb);
TCLT_EXPORT void    tclt_add_list_of_peers();
TCLT_EXPORT char    *tclt_add_connection();
TCLT_EXPORT void    tclt_add_tunnel();

TCLT_EXPORT void    tclt_delete_connection();
TCLT_EXPORT void    tclt_stop_tunnel();
TCLT_EXPORT void    tclt_delete_peer();
TCLT_EXPORT void    tclt_clear_peers();

TCLT_EXPORT void    tclt_edit_peer();

/*
*** Group related
*/
TCLT_EXPORT void    tclt_create_group();
TCLT_EXPORT void    tclt_destroy_group();
TCLT_EXPORT void    tclt_add_peer_to_group();
TCLT_EXPORT void    tclt_clear_group();

/*
*** Administration related
*/
TCLT_EXPORT void    tclt_edit_config();
TCLT_EXPORT void    tclt_add_public_key();
TCLT_EXPORT void    tclt_add_key_for_peer();
TCLT_EXPORT void    tclt_add_key_for_client();

#define    LIB_TNETACLE_CLIENT_VERSION 2

#define    ADD_PEER_CMD "AddContact"

#endif
