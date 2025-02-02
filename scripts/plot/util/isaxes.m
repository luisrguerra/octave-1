########################################################################
##
## Copyright (C) 2013-2022 The Octave Project Developers
##
## See the file COPYRIGHT.md in the top-level directory of this
## distribution or <https://octave.org/copyright/>.
##
## This file is part of Octave.
##
## Octave is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <https://www.gnu.org/licenses/>.
##
########################################################################

## -*- texinfo -*-
## @deftypefn {} {@var{tf} =} isaxes (@var{h})
## Return true if @var{h} is an axes graphics handle and false otherwise.
##
## If @var{h} is a matrix then return a logical array which is true where the
## elements of @var{h} are axes graphics handles and false where they are not.
## @seealso{isfigure, ishghandle, isgraphics}
## @end deftypefn

function tf = isaxes (h)

  if (nargin < 1)
    print_usage ();
  endif

  tf = ishghandle (h);

  if (any (tf))
    tf(tf) = strcmp (get (h(tf), "type"), "axes");
  endif

endfunction


%!test
%! hf = figure ("visible", "off");
%! unwind_protect
%!   hax = axes ();
%!   assert (isaxes (hax));
%!   assert (! isaxes (-hax));
%! unwind_protect_cleanup
%!   close (hf);
%! end_unwind_protect

%!test
%! hf = figure ("visible", "off");
%! unwind_protect
%!   hax = axes ();
%!   assert (isaxes ([hax NaN]), [true false]);
%! unwind_protect_cleanup
%!   close (hf);
%! end_unwind_protect

%!error <Invalid call> isaxes ()
