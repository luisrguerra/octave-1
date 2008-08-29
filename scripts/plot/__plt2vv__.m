## Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 2000, 2003, 2005,
##               2006, 2007 John W. Eaton
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or (at
## your option) any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

## Undocumented internal function.

## Author: jwe

function retval = __plt2vv__ (h, x, y, options, properties)

  if (nargin < 3 || nargin > 5)
    print_usage ();
  endif

  if (nargin < 4 || isempty (options))
    options = __default_plot_options__ ();
  endif

  if (nargin < 5)
    properties = {};
  endif

  if (numel (options) > 1)
    options = options(1);
  endif

  [x_nr, x_nc] = size (x);
  [y_nr, y_nc] = size (y);

  if (x_nr == 1)
    x = x';
    tmp = x_nr;
    x_nr = x_nc;
    x_nc = tmp;
  endif

  if (y_nr == 1)
    y = y';
    tmp = y_nr;
    y_nr = y_nc;
    y_nc = tmp;
  endif

  if (x_nr == y_nr)
    key = options.key;
    if (! isempty (key))
      set (h, "key", "on");
    endif
    color = options.color;
    if (isempty (color))
      color = __next_line_color__ ();
    endif

    hg = hggroup ();
    retval = hg;
    properties = __add_datasource__ ("__plt2vv__", hg, {"x", "y", "z"}, 
				     properties{:});

    h = line (x, y, "keylabel", key, "color", color,
	      "linestyle", options.linestyle,
	      "marker", options.marker, "parent", hg);

    __add_line_series__ (h, hg);
    set (hg, properties{:});
  else
    error ("__plt2vv__: vector lengths must match");
  endif

endfunction
