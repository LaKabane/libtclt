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

#ifdef Windows

#include "import.h"

TCLT_EXPORT void		tnt_tclt_init(void);
TCLT_EXPORT void		tnt_tclt_destroy(void);
TCLT_EXPORT int		tnt_tclt_get_version(void);

#else

void		tnt_tclt_init(void);
void		tnt_tclt_destroy(void);
int		tnt_tclt_get_version(void);

#endif

#define		LIB_TNETACLE_CLIENT_VERSION 1

#endif
