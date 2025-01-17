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
## @deftypefn {} {@var{value} =} subsasgn (@var{player}, @var{idx}, @var{rhs})
## Perform subscripted assignment on the audio player object @var{player}.
##
## Assign the value of @var{rhs} to the player property named by @var{idx}.
## @seealso{@audioplayer/audioplayer}
## @end deftypefn

function value = subsasgn (player, idx, rhs)

  if (nargin != 3)
    print_usage ();
  endif

  if (isempty (idx))
    error ("audioplayer: missing index");
  endif

  if (strcmp (idx(1).type, "."))
    field = idx.subs;
    set (player, field, rhs);
    value = player;
  else
    error ("@audioplayer/subsasgn: invalid subscript type");
  endif

endfunction


%!testif HAVE_PORTAUDIO; audiodevinfo (0) > 0
%! player = audioplayer ([-1, 1], 44100, 8);
%! player.Tag = "mytag";
%! assert (get (player, "Tag"), "mytag");

## Test input validation
%!testif HAVE_PORTAUDIO; audiodevinfo (0) > 0
%! player = audioplayer ([-1, 1], 44100, 8);
%! fail ("player(1).Tag = 5", "invalid subscript type");
%! fail ("player{1}.Tag = 5", "invalid subscript type");
