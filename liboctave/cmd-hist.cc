/*

Copyright (C) 1996, 1997 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstring>

#include <string>

#include "cmd-edit.h"
#include "cmd-hist.h"
#include "lo-error.h"
#include "str-vec.h"

command_history *command_history::instance = 0;

#if defined (USE_READLINE)

#include <cstdlib>

#include <strstream>

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#ifdef HAVE_UNISTD_H
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <unistd.h>
#endif

#include <readline/history.h>

#include "file-stat.h"

class
gnu_history : public command_history
{
public:

  gnu_history (void)
    : command_history (), mark (0) { }

  ~gnu_history (void) { }

  void do_add (const string&);

  void do_remove (int);

  int do_where (void);

  int do_length (void);

  int do_max_input_history (void);

  int do_base (void);

  int do_current_number (void);

  void do_stifle (int);

  int do_unstifle (void);

  int do_is_stifled (void);

  void do_set_mark (int);

  void do_goto_mark (void);

  void do_read (const string&, bool);

  void do_read_range (const string&, int, int, bool);

  void do_write (const string&);

  void do_append (const string&);

  void do_truncate_file (const string&, int);

  string_vector do_list (int, bool);

  string do_get_entry (int);

  void do_replace_entry (int, const string&);

  void do_clean_up_and_save (const string&, int);

private:

  int mark;
};

void
gnu_history::do_add (const string& s)
{
  if (! do_ignoring_entries ())
    {
      if (s.empty ()
	  || (s.length () == 1 && (s[0] == '\r' || s[0] == '\n')))
	return;

      ::add_history (s.c_str ());

      lines_this_session++;
    }
}

void
gnu_history::do_remove (int n)
{
  HIST_ENTRY *discard = ::remove_history (n);

  if (discard)
    {
      if (discard->line)
	::free (discard->line);

      ::free (discard);
    }
}

int
gnu_history::do_where (void)
{
  return ::where_history ();
}

int
gnu_history::do_length (void)
{
  return ::history_length;
}

int
gnu_history::do_max_input_history (void)
{
  return ::max_input_history;
}

int
gnu_history::do_base (void)
{
  return ::history_base;
}

int
gnu_history::do_current_number (void)
{
  return (xsize > 0) ? do_base () + do_where () : -1;
}

void
gnu_history::do_stifle (int n)
{
  ::stifle_history (n);
}

int
gnu_history::do_unstifle (void)
{
  return ::unstifle_history ();
}

int
gnu_history::do_is_stifled (void)
{
  return ::history_is_stifled ();
}

void
gnu_history::do_set_mark (int n)
{
  mark = n;
}

void
gnu_history::do_goto_mark (void)
{
  HIST_ENTRY *h;

  if (mark)
    {
      if (history_set_pos (mark))
	{
	  h = ::current_history ();

	  if (h)
	    {
	      command_editor::insert_text (h->line);

	      command_editor::clear_undo_list ();
	    }
	}
    }

  mark = 0;

  // XXX FIXME XXX -- for operate_and_get_next.
  command_editor::restore_startup_hook ();
}

void
gnu_history::do_read (const string& f, bool must_exist)
{
  if (! f.empty ())
    {
      int status = ::read_history (f.c_str ());

      if (status != 0 && must_exist)
	error (status);
      else
	{
	  lines_in_file = do_where ();

	  ::using_history ();
	}
    }
  else
    error ("gnu_history::read: missing file name");
}

void
gnu_history::do_read_range (const string& f, int from, int to,
			    bool must_exist)
{
  if (from < 0)
    from = lines_in_file;

  if (! f.empty ())
    {
      int status = ::read_history_range (f.c_str (), from, to);

      if (status != 0 && must_exist)
	error (status);
      else
	{
	  lines_in_file = do_where ();

	  ::using_history ();
	}
    }
  else
    error ("gnu_history::read_range: missing file name");
}

void
gnu_history::do_write (const string& f_arg)
{
  string f = f_arg;

  if (f.empty ())
    f = xfile;

  if (! f.empty ())
    {
      int status = ::write_history (f.c_str ());

      if (status != 0)
	error (status);
    }
  else
    error ("gnu_history::write: missing file name");
}

void
gnu_history::do_append (const string& f_arg)
{
  if (lines_this_session)
    {
      if (lines_this_session < do_where ())
	{
	  // Create file if it doesn't already exist.

	  string f = f_arg;

	  if (f.empty ())
	    f = xfile;

	  if (! f.empty ())
	    {
	      file_stat fs (f);

	      if (! fs)
		{
		  int tem;

		  tem = open (f.c_str (), O_CREAT, 0666);
		  close (tem);
		}

	      int status = ::append_history (lines_this_session, f.c_str ());

	      if (status != 0)
		error (status);
	      else
		lines_in_file += lines_this_session;

	      lines_this_session = 0;
	    }
	  else
	    error ("gnu_history::append: missing file name");
	}
    }
}

void
gnu_history::do_truncate_file (const string& f_arg, int n)
{
  string f = f_arg;

  if (f.empty ())
    f = xfile;

  if (! f.empty ())
    ::history_truncate_file (f.c_str (), n);
  else
    error ("gnu_history::truncate_file: missing file name");
}

string_vector
gnu_history::do_list (int limit, bool number_lines)
{
  string_vector retval;

  if (limit)
    {
      HIST_ENTRY **hlist = ::history_list ();

      if (hlist)
	{
	  int end = 0;
	  while (hlist[end])
	    end++;

	  int beg = (limit < 0 || end < limit) ? 0 : (end - limit);

	  retval.resize (end - beg);

	  int k = 0;
	  for (int i = beg; i < end; i++)
	    {
	      ostrstream output_buf;

	      if (number_lines)
		output_buf.form ("%5d%c", i + do_base (),
				 hlist[i]->data ? '*' : ' '); 

	      output_buf << hlist[i]->line << ends;

	      const char *tmp = output_buf.str ();

	      retval[k++] = tmp;

	      delete [] tmp;  
	    }
	}
    }

  return retval;
}

string
gnu_history::do_get_entry (int n)
{
  string retval;

  HIST_ENTRY *entry = ::history_get (do_base () + n);

  if (entry && entry->line)
    retval = entry->line;

  return retval;
}

void
gnu_history::do_replace_entry (int which, const string& line)
{
  HIST_ENTRY *discard = ::replace_history_entry (which, line.c_str (), 0);

  if (discard)
    {
      if (discard->line)
	::free (discard->line);

      ::free (discard);
    }
}

void
gnu_history::do_clean_up_and_save (const string& f_arg, int n)
{
  string f = f_arg;

  if (f.empty ())
    f = xfile;

  if (! f.empty ())
    {
      if (n < 0)
	n = xsize;

      stifle (n);

      do_write (f.c_str ());
    }
  else
    error ("gnu_history::clean_up_and_save: missing file name");
}

#endif

bool
command_history::instance_ok (void)
{
  bool retval = true;

  if (! instance)
    make_command_history ();

  if (! instance)
    {
      (*current_liboctave_error_handler)
	("unable to create command history object!");

      retval = false;
    }

  return retval;
}

void
command_history::make_command_history (void)
{
#if defined (USE_READLINE)
  instance = new gnu_history ();
#else
  instance = new command_history ();
#endif
}

void
command_history::set_file (const string& f)
{
  if (instance_ok ())
    instance->do_set_file (f);
}

string
command_history::file (void)
{
  return (instance_ok ())
    ? instance->do_file () : string ();
}

void
command_history::set_size (int n)
{
  if (instance_ok ())
    instance->do_set_size (n);
}

int
command_history::size (void)
{
  return (instance_ok ())
    ? instance->do_size () : 0;
}

void
command_history::ignore_entries (bool flag)
{
  if (instance_ok ())
    instance->do_ignore_entries (flag);
}

bool
command_history::ignoring_entries (void)
{
  return (instance_ok ())
    ? instance->do_ignoring_entries () : false;
}

void
command_history::add (const string& s)
{
  if (instance_ok ())
    instance->do_add (s);
}

void
command_history::remove (int n)
{
  if (instance_ok ())
    instance->do_remove (n);
}

int
command_history::where (void)
{
  return (instance_ok ())
    ? instance->do_where () : 0;
}

int
command_history::length (void)
{
  return (instance_ok ())
    ? instance->do_length () : 0;
}

int
command_history::max_input_history (void)
{
  return (instance_ok ())
    ? instance->do_max_input_history () : 0;
}

int
command_history::base (void)
{
  return (instance_ok ())
    ? instance->do_base () : 0;
}

int
command_history::current_number (void)
{
  return (instance_ok ())
    ? instance->do_current_number () : 0;
}

void
command_history::stifle (int n)
{
  if (instance_ok ())
    instance->do_stifle (n);
}

int
command_history::unstifle (void)
{
  return (instance_ok ())
    ? instance->do_unstifle () : 0;
}

int
command_history::is_stifled (void)
{
  return (instance_ok ())
    ? instance->do_is_stifled () : 0;
}

void
command_history::set_mark (int n)
{
  if (instance_ok ())
    instance->do_set_mark (n);
}

int
command_history::goto_mark (...)
{
  if (instance_ok ())
    instance->do_goto_mark ();

  return 0;
}

void
command_history::read (bool must_exist)
{
  if (instance_ok ())
    instance->do_read (must_exist);
}

void
command_history::read (const string& f, bool must_exist)
{
  if (instance_ok ())
    instance->do_read (f, must_exist);
}

void
command_history::read_range (int from, int to, bool must_exist)
{
  if (instance_ok ())
    instance->do_read_range (from, to, must_exist);
}

void
command_history::read_range (const string& f, int from, int to,
			     bool must_exist) 
{
  if (instance_ok ())
    instance->do_read_range (f, from, to, must_exist);
}

void
command_history::write (const string& f)
{
  if (instance_ok ())
    instance->do_write (f);
}

void
command_history::append (const string& f)
{
  if (instance_ok ())
    instance->do_append (f);
}

void
command_history::truncate_file (const string& f, int n)
{
  if (instance_ok ())
    instance->do_truncate_file (f, n);
}

string_vector
command_history::list (int limit, bool number_lines)
{
  return (instance_ok ())
    ? instance->do_list (limit, number_lines) : string_vector ();
}

string
command_history::get_entry (int n)
{
  return (instance_ok ())
    ? instance->do_get_entry (n) : string ();
}

void
command_history::replace_entry (int which, const string& line)
{
  if (instance_ok ())
    instance->do_replace_entry (which, line);
}

void
command_history::clean_up_and_save (const string& f, int n)
{
  if (instance_ok ())
    instance->do_clean_up_and_save (f, n);
}

void
command_history::do_set_file (const string& f)
{
  xfile = f;
}

string
command_history::do_file (void)
{
  return xfile;
}

void
command_history::do_set_size (int n)
{
  xsize = n;
}

int
command_history::do_size (void)
{
  return xsize;
}

void
command_history::do_ignore_entries (bool flag)
{
  ignoring_additions = flag;
}

bool
command_history::do_ignoring_entries (void)
{
  return ignoring_additions;
}

void
command_history::do_add (const string&)
{
}

void
command_history::do_remove (int)
{
}

int
command_history::do_where (void)
{
  return 0;
}

int
command_history::do_length (void)
{
  return 0;
}

int
command_history::do_max_input_history (void)
{
  return 0;
}

int
command_history::do_base (void)
{
  return 0;
}

int
command_history::do_current_number (void)
{
  return (xsize > 0) ? do_base () + do_where () : -1;
}

void
command_history::do_stifle (int)
{
}

int
command_history::do_unstifle (void)
{
  return -1;
}

int
command_history::do_is_stifled (void)
{
  return 0;
}

void
command_history::do_set_mark (int)
{
}

void
command_history::do_goto_mark (void)
{
}

void
command_history::do_read (bool must_exist)
{
  do_read (xfile, must_exist);
}

void
command_history::do_read (const string& f, bool)
{
  if (f.empty ())
    error ("command_history::read: missing file name");
}

void
command_history::do_read_range (int from, int to, bool must_exist)
{
  do_read_range (xfile, from, to, must_exist);
}

void
command_history::do_read_range (const string& f, int, int, bool)
{
  if (f.empty ())
    error ("command_history::read_range: missing file name");
}

void
command_history::do_write (const string& f_arg)
{
  string f = f_arg;

  if (f.empty ())
    f = xfile;

  if (f.empty ())
    error ("command_history::write: missing file name");
}

void
command_history::do_append (const string& f_arg)
{
  if (lines_this_session)
    {
      if (lines_this_session < do_where ())
	{
	  // Create file if it doesn't already exist.

	  string f = f_arg;

	  if (f.empty ())
	    f = xfile;

	  if (f.empty ())
	    error ("command_history::append: missing file name");
	}
    }
}

void
command_history::do_truncate_file (const string& f_arg, int)
{
  string f = f_arg;

  if (f.empty ())
    f = xfile;

  if (f.empty ())
    error ("command_history::truncate_file: missing file name");
}

string_vector
command_history::do_list (int, bool)
{
  return string_vector ();
}

string
command_history::do_get_entry (int)
{
  return string ();
}

void
command_history::do_replace_entry (int, const string&)
{
}

void
command_history::do_clean_up_and_save (const string& f_arg, int)
{
  string f = f_arg;

  if (f.empty ())
    f = xfile;

  if (f.empty ())
    error ("command_history::clean_up_and_save: missing file name");
}

void
command_history::error (int err_num)
{
  (*current_liboctave_error_handler) ("%s", strerror (err_num));
}

void
command_history::error (const string& s)
{
  (*current_liboctave_error_handler) ("%s", s.c_str ());
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
