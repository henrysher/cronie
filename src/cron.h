/* Copyright 1988,1990,1993,1994 by Paul Vixie
 * All rights reserved
 */

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1997,2000 by Internet Software Consortium, Inc.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* cron.h - header for vixie's cron
 *
 * $Id: cron.h,v 1.6 2004/01/23 18:56:42 vixie Exp $
 *
 * vix 14nov88 [rest of log is in RCS]
 * vix 14jan87 [0 or 7 can be sunday; thanks, mwm@berkeley]
 * vix 30dec86 [written]
 */

#include "../config.h"
#include "externs.h"

#ifdef WITH_SELINUX
#include <selinux/selinux.h>
#endif

#ifdef WITH_PAM
#include <security/pam_appl.h>
#endif

#ifdef WITH_INOTIFY
#include <sys/inotify.h>
#endif

#include "pathnames.h"
#include "macros.h"
#include "structs.h"
#include "funcs.h"
#include "globals.h"

#ifdef WITH_PAM
static pam_handle_t *pamh = NULL;
static int pam_session_opened = 0;  //global for open session
static const struct pam_conv conv = {
    NULL
};

#define PAM_FAIL_CHECK if (retcode != PAM_SUCCESS) { \
    fprintf(stderr,"\n%s\n",pam_strerror(pamh, retcode)); \
    if (pamh != NULL) { \
        if (pam_session_opened != 0) \
            pam_close_session(pamh, PAM_SILENT); \
        pam_end(pamh, retcode); \
    } \
        return(retcode);    }
#endif

