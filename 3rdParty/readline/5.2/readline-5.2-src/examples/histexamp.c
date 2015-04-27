/* Copyright (C) 1987-2002 Free Software Foundation, Inc.

   This file is part of the GNU Readline Library, a library for
   reading lines of text with interactive input and history editing.

   The GNU Readline Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   The GNU Readline Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   The GNU General Public License is often shipped with GNU software, and
   is generally kept in a file called COPYING or LICENSE.  If you do not
   have a copy of the license, write to the Free Software Foundation,
   59 Temple Place, Suite 330, Boston, MA 02111 USA. */

#include <stdio.h>

#ifdef READLINE_LIBRARY
#  include "history.h"
#else
#  include <readline/history.h>
#endif

#include <string.h>

main (argc, argv)
     int argc;
     char **argv;
{
  char line[1024], *t;
  int len, done;

  line[0] = 0;
  done = 0;

  using_history ();
  while (!done)
    {
      printf ("history$ ");
      fflush (stdout);
      t = fgets (line, sizeof (line) - 1, stdin);
      if (t && *t)
	{
	  len = strlen (t);
	  if (t[len - 1] == '\n')
	    t[len - 1] = '\0';
	}

      if (!t)
	strcpy (line, "quit");

      if (line[0])
	{
	  char *expansion;
	  int result;

	  using_history ();

	  result = history_expand (line, &expansion);
	  if (result)
	    fprintf (stderr, "%s\n", expansion);

	  if (result < 0 || result == 2)
	    {
	      rl_free (expansion);
	      continue;
	    }

	  add_history (expansion);
	  strncpy (line, expansion, sizeof (line) - 1);
	  rl_free (expansion);
	}

      if (strcmp (line, "quit") == 0)
	done = 1;
      else if (strcmp (line, "save") == 0)
	write_history ("history_file");
      else if (strcmp (line, "read") == 0)
	read_history ("history_file");
      else if (strcmp (line, "list") == 0)
	{
	  register HIST_ENTRY **the_list;
	  register int i;
	  time_t tt;
	  char timestr[128];

	  the_list = history_list ();
	  if (the_list)
	    for (i = 0; the_list[i]; i++)
	      {
	      	tt = history_get_time (the_list[i]);
		if (tt)
		  strftime (timestr, sizeof (timestr), "%a %R", localtime(&tt));
		else
		  strcpy (timestr, "??");
	        printf ("%d: %s: %s\n", i + history_base, timestr, the_list[i]->line);
	      }
	}
      else if (strncmp (line, "delete", 6) == 0)
	{
	  int which;
	  if ((sscanf (line + 6, "%d", &which)) == 1)
	    {
	      HIST_ENTRY *entry = remove_history (which);
	      if (!entry)
		fprintf (stderr, "No such entry %d\n", which);
	      else
		{
		  rl_free (entry->line);
		  rl_free (entry);
		}
	    }
	  else
	    {
	      fprintf (stderr, "non-numeric arg given to `delete'\n");
	    }
	}
    }
}