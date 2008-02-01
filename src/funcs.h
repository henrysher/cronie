/*
 * $Id: funcs.h,v 1.9 2004/01/23 18:56:42 vixie Exp $
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

/* Notes:
 *	This file has to be included by cron.h after data structure defs.
 *	We should reorg this into sections by module.
 */

void		set_cron_uid(void),
		set_cron_cwd(void),
		open_logfile(void),
		sigpipe_func(void),
		job_add(entry *, user *),
		do_command(entry *, user *),
		link_user(cron_db *, user *),
		unlink_user(cron_db *, user *),
		free_user(user *),
		env_free(char **),
		unget_char(int, FILE *),
		free_entry(entry *),
		acquire_daemonlock(int),
		skip_comments(FILE *),
		log_it(const char *, int, const char *, const char *),
		log_close(void);
#if defined WITH_INOTIFY
		void load_inotify_database(cron_db *, int fd, int no),
		set_cron_watched(int fd),
		set_cron_unwatched(int fd);
#else
		void load_database(cron_db *);
#endif

int		job_runqueue(void),
		set_debug_flags(const char *),
		get_char(FILE *),
		get_string(char *, int, FILE *, char *),
		swap_uids(void),
		swap_uids_back(void),
		load_env(char *, FILE *),
		cron_pclose(FILE *),
		glue_strings(char *, size_t, const char *, const char *, char),
		strcmp_until(const char *, const char *, char),
		allowed(const char * ,const char * ,const char *),
		strdtb(char *);

size_t		strlens(const char *, ...);

char		*env_get(char *, char **),
		*arpadate(time_t *),
		*mkprints(unsigned char *, unsigned int),
		*first_word(char *, char *),
		**env_init(void),
		**env_copy(char **),
		**env_set(char **, char *);

user		*load_user(int, struct passwd *, const char *, const char *, const char *),
		*find_user(cron_db *, const char *, const char *);

entry		*load_entry(FILE *, void (*)(), struct passwd *, char **);

FILE		*cron_popen(char *, const char *, struct passwd *);

struct passwd	*pw_dup(const struct passwd *);

#ifndef HAVE_TM_GMTOFF
long		get_gmtoff(time_t *, struct tm *);
#endif

/* Red Hat security stuff (security.c): 
 */
void cron_restore_default_security_context( void );

int cron_set_job_security_context( entry *e, user *u, char ***jobenvp );

int cron_open_security_session( struct passwd *pw );

void cron_close_security_session( void );

int cron_change_user( struct passwd *pw, char *homedir );

int cron_get_job_context( user *u, void *scontextp, void *file_contextp, char **envp );

int cron_change_selinux_context( user *, void *scontext, void *file_context );

int get_security_context(const char *name, 
			 int crontab_fd, 
			 security_context_t *rcontext, 
			 const char *tabname
                        );

void free_security_context( security_context_t *scontext );

int crontab_security_access(void);

/* PAM */
int cron_start_pam(struct passwd *pw);
void cron_close_pam(void);
