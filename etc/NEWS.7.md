Summary of important user-visible changes for version 7 (2022-01-05)
--------------------------------------------------------------------

### General improvements

- Many functions in Octave can be called in a command form---no
parentheses for invocation and no return argument assignment---or in a
functional form---parentheses and '=' for assignment of return values.

    **Command Form Example**

    `mkdir new_directory`

    **Function Form Example**

    `status = mkdir ("new_directory")`

    Octave now handles errors that occur in a consistent manner.  If
    called in command form and there is a failure, an error is thrown
    and a message printed.  If called in functional form, no error or
    message is printed and the failure is communicated to the programmer
    via the output status variable.

    The following list of functions have been modified.

    * `copyfile`
    * `fcntl`
    * `fileattrib`
    * `kill`
    * `link`
    * `mkfifo`
    * `movefile`
    * `rename`
    * `rmdir`
    * `symlink`
    * `unlink`

- Calling a user-defined function with too many inputs or outputs is now
an error.  The interpreter makes this check automatically.  If a
function uses varargin then the check is skipped for function inputs,
and if a function uses varargout then the check is skipped for function
outputs.  Input validation for functions typically begins with checking
that the number of inputs and outputs match expectations.  Existing code
can be simplified by removing these checks which are now done by the
interpreter.  Typically, code blocks like the following can simply be
deleted.

        ## Checking number of inputs
        if (nargin > 2)
          print_usage ();
        endif

        ## Checking number of outputs
        if (nargout > 1)
          print_usage ();
        endif

- Binary and hexadecimal constants like `0b101` and `0xDEADBEEF` now
create integers (unsigned by default) with sizes determined from the
number of digits present.  For example, `0xff` creates a `uint8` value
and `0xDEADBEEF` creates a `uint64` value.  You may also use a suffix of
the form `u8`, `u16`, `u32`, `u64`, `s8`, `s16`, `s32`, or `s64` to
explicitly specify the data type to use (`u` or `s` to indicate unsigned
or signed and the number to indicate the integer size).

    Binary constants are limited to 64 binary digits and hexadecimal
constants are limited to 16 hexadecimal digits with no automatic
rounding or conversion to floating point values.  Note that this may
cause problems in existing code.  For example, an expression like
`[0x1; 0x100; 0x10000]` will be uint8 (because of the rules of
concatenating integers of different sizes) with the larger values
truncated (because of the saturation semantics of integer values).  To
avoid these kinds of problems either: 1) declare the first integer to be
of the desired size such as `[0x1u32; 0x100; 0x10000]`, or 2) pad
constants in array expressions with leading zeros so that they use the
same number of digits for each value such as
`[0x00_00_01; 0x00_01_00; 0x01_00_00]`.

- The increment and decrement operators `++` and `--` must "hug" their
corresponding variables.  In previous versions of Octave, whitespaces
between these operators and the variable they affect were allowed.  That
is no longer the case.

- The `mldivide` function (i.e., the `\` operator) now uses an LU
decomposition to solve nearly singular full square matrices.  This is
Matlab-compatible and yields results which more nearly minimize `norm
(A*x - b)`.  Previously, Octave computed a minimum-norm solution.

- The `factor` function has been overhauled for speed.  For large
inputs > 1e14, it can be up to 10,000 times faster.

- The `isprime` function uses a new primality testing algorithm
that is up to 50,000 times faster for inputs > 1e14.

- The `betainc` function now calculates an exact output for the
important special cases where a or b are 1.

- The `whos` function now displays an additional attribute 's' when
the variable is a sparse type.

- As part of GSoC 2020, Abdallah K. Elshamy implemented the
`jsondecode` and `jsonencode` functions to read and write JSON data.

- As part of GSoC 2021, Abdallah K. Elshamy implemented the
`jupyter_notebook` classdef class.  This class supports running and
filling Jupyter Notebooks using the Octave language kernel from Octave
itself.  Making the evaluation of long-running Jupyter Notebooks on a
computing server without permanent browser connection possible.

- By default, the history file is now located at $DATA/octave/history,
where $DATA is a platform dependent location for (roaming) user data
files (e.g., ${XDG_DATA_HOME} or, if that is not set, ~/.local/share on
Unix-like operating systems or %APPDATA% on Windows).

- For Octave on Windows OS, the minimum required version of the Windows
API is now 6.1 (Windows 7 or newer).

- The non-re-entrant version of the QHull library "libqhull" was
deprecated upstream.  Octave now (optionally) requires the re-entrant
version of that library "libqhull_r" instead.

- Octave's build system no longer appends "++" to the end of the
"magick++" library name (set with the `--with-magick=` configure flag).
The real name of the "magick++" library (including any potentially
trailing "++") needs to be set in that option now.

- The `pkg update` command now accepts options that are passed to `pkg
install` for each updated package.  Specifying @option{-local} or
@option{-global} will restrict update checks to local or global
installed packages, respectively.

### Graphical User Interface

- The graphical user interface is now available in Hungarian and
Turkish.

- In debug mode, symbol values are now shown in tooltips when hovering
variables in the editor panel.

- The "Disable global shortcuts when Command Window has focus" GUI
preference under the Shortcuts tab is now disabled by default.  This
option disables keyboard shortcuts to avoid interference with readline
key strokes in the Command Window.  Unlike versions prior to Octave 7,
this preference now also affects the Ctrl-C/V shortcuts for copy/paste.

- In command line mode, i.e. when Octave is started without the --gui option,
the doc command now opens the GUI documentation browser as a standalone widget,
provided that Octave was compiled with GUI support.

### Graphics backend

- Support for Qt4 for both graphics and the GUI has been removed.

- If a working LaTeX tool chain is found on the path, including `latex`,
`dvipng`, and `dvisvgm` binaries, then text strings can now be rendered
properly when using the `"latex"` value for the text objects'
`"interpreter"` property and axes objects' `"ticklabelinterpreter"`.
Type `doc "latex interpreter"` for further info.

- The `"Marker"` property for plot objects now accepts `|` which draws
a vertical line or `_` which draws a horizontal line.

- The `FMT` format argument for plot commands now accepts long forms for
color names which may be more understandable than the existing
one-letter codes.  For example, the RGB value `[0 0 0]` can now be
specified by `"black"` in addition to `"k"`.

- The color graphics properties, for example `"EdgeColor"` or
`"FaceColor"`, now accept HTML specifications.  An HTML specification is
a string that begins with the character '#' and is followed by either 3
or 6 hexadecimal digits.  For example, magenta which is 100% red and
blue values can specified by `"#FF00FF"` or `"#F0F"`.

- The additional property `"contextmenu"` has been added to all graphics
objects.  It is equivalent to the previously used `"uicontextmenu"`
property which is hidden now.

- `uicontrol` objects now fully implement the `"Off"` and `"Inactive"`
values of the `"Enable"` property.  When the value is `"Off"`, no
interaction with the object occurs and the `uicontrol` changes color
(typically to gray) to indicate it is disabled.  When the value is
`"Inactive"`, the object appears normally (no change in color), but it
is not possible to change the value of the object (such as modifying
text in an `Edit` box or clicking on a `RadioButton`).

- The `"ListBoxTop"` property for `uicontrol` objects has been
implemented for `set` commands.

- The `Title` property for print formats such as PDF or SVG is now set
to the title displayed on the figure window which contains the plot.

- Additional properties have been added to the `axes` graphics object:
    * `"alphamap"` (not yet implemented)
    * `"alphascale"` (not yet implemented)
    * `"colorscale"` (not yet implemented)
    * `"fontsizemode"` (not yet implemented)
    * `"innerposition"` (equivalent to `"position"`)
    * `"interactions"` (not yet implemented)
    * `"layout"` (not yet implemented)
    * `"legend"` (not yet implemented)
    * `"nextseriesindex"` (read-only, used by `scatter`
      graphics objects)
    * `"positionconstraint"` (replacement for `"activepositionproperty"`
      which is now a hidden property.  No plans for removal.)
    * `"toolbar"` (not yet implemented)
    * `"xaxis"` (not yet implemented)
    * `"yaxis"` (not yet implemented)
    * `"zaxis"` (not yet implemented)

### Matlab compatibility

- The function `griddata` now implements the `"v4"` Biharmonic Spline
Interpolation method.  In adddition, the function now accepts 3-D inputs
by passing the data to `griddata3`.

- Coordinate transformation functions `cart2sph`, `sph2cart`,
`cart2pol`, and `pol2cart` now accept either row or column vectors for
coordinate inputs.  A single coordinate matrix with one variable per
column can still be used as function input, but a single output variable
will now contain just the first output coordinate, and will no longer
return the full output coordinate matrix.  Output size matches the size
of input vectors, or in the case of an input matrix will be column
vectors with rows corresponding to the input coordinate matrix.

- The function `dec2bin` and `dec2hex` now support negative numbers.

- The function `factor` now supports uint64 inputs larger than
`flintmax`.

- The function `primes` now supports char inputs.

- The functions `quantile` and `prctile` now permit operating on
dimensions greater than `ndims (x)`.

- The function `iqr` now uses Matlab compatible interpolation for
quantile values.  The dimension input now allows a vector, "all", and
dimensions greater than `ndims (x)`.  The function also handles
`Inf` and `NaN` input values in a Matlab-compatible manner.

- The function `importdata` now produces more compatible results when
the file contains a 2-D text matrix.

- The file functions `copyfile`, `mkdir`, `movefile`, `rmdir` now return
a logical value (true/false) rather than a numeric value (1/0).

- `uimenu` now accepts property `"Text"` which is identical to
`"Label"`.  Matlab recommends using `"Text"` in new code, although there
is no announced date for deprecating `"Label"`.

- The functions `scatter` and `scatter3` now return a handle to a
scatter graphics object.  For compatibility, they return an `hggroup` of
patch graphics objects when the `"gnuplot"` graphics toolkit is used.  In
previous versions of Octave, these functions returned an `hggroup` of
patch graphics objects for all graphics toolkits.

- The functions `bar` and `barh` now handle stacked negative bar values
in a Matlab-compatible manner.  Negative values now stack below the zero
axis independently of a positive value bars in the same stack.
Previously the negative bars could overlap positive bars depending on
drawing order.

- The functions `bar` and `barh` now use colors from the `"ColorOrder"`
axes property rather than the `"Colormap"` figure property unless one
of the histogram options (@qcode{"hist"}, @qcode{"histc"} was specified.

- The function `saveas` now defaults to saving in Octave figure format
(.ofig) rather than PDF (.pdf).

- A new warning ID (`"Octave:unimplemented-matlab-functionality"`) has
been added which prints a warning when Octave's parser recognizes valid
Matlab code, but for which Octave does not yet implement the
functionality.  By default, this warning is enabled.

- When Octave is started with the `--traditional` option for maximum
compatibility the `print_struct_array_contents` internal variable is set
to true.

- The function `repelem` now produces a row vector output when the input is
a scalar.

- The functions `var` and `std` now accept a weight vector as input and
compute the weigthed variance.  Dimension input now allows a vector and
the keyword "all".

### Alphabetical list of new functions added in Octave 7

* `cospi`
* `getpixelposition`
* `endsWith`
* `fill3`
* `jsondecode`
* `jsonencode`
* `jupyter_notebook`
* `listfonts`
* `matlab.net.base64decode`
* `matlab.net.base64encode`
* `memory`
* `ordqz`
* `rng`
* `sinpi`
* `startsWith`
* `streamribbon`
* `turbo`
* `uniquetol`
* `xtickangle`
* `ytickangle`
* `ztickangle`

### Deprecated functions and operators

The following functions and operators have been deprecated in Octave 7
and will be removed from Octave 9 (or whatever version is the second
major release after 7):

- Functions

  Function                     | Replacement
  ---------------------------- |----------------------------
  `disable_diagonal_matrix`    | `optimize_diagonal_matrix`
  `disable_permutation_matrix` | `optimize_permutation_matrix`
  `disable_range`              | `optimize_range`

- Operators

  Operator | Replacement | Description
  ---------|-------------|------------
  `**`     | `^`         | Matrix exponent
  `.**`    | `.^`        | Element-by-element exponent
  `.+`     | `+`         | Element-by-element addition
  `.-`     | `-`         | Element-by-element subtraction

- Interpreter

    * The use of `'...'` for line continuations *inside* double-quoted
    strings has been deprecated.  Use `'\'` for line continuations
    inside strings instead.

    * The use of `'\'` as a line continuation *outside* of double-quoted
    strings has been deprecated.  Use `'...'` for line continuations
    instead.

    * Any trailing whitespace after a `'\'` line continuation has been
    deprecated.  Delete unnecessary trailing whitespace.


The following functions were deprecated in Octave 6 and will be removed
from Octave 8 (or whatever version is the second major release after 6):

- Functions

  Function               | Replacement
  -----------------------|------------------
  `runtests`             | `oruntests`

- The environment variable used by `mkoctfile` for linker flags is now
  `LDFLAGS` rather than `LFLAGS`.  `LFLAGS` was deprecated in Octave 6,
  and a warning is now emitted if it is used, but it will continue to
  work.


### Removed functions, properties, and features

The following functions and properties were deprecated in Octave 5
and have been removed from Octave 7.

- Functions

  Function                 | Replacement
  -------------------------|------------------
  `output_max_field_width` | `output_precision`
  `is_keyword`             | `iskeyword`

- Properties

  Object           | Property      | Value
  -----------------|---------------|------------
  `text`           | `fontangle`   | `"oblique"`
  `uibuttongroup`  | `fontangle`   | `"oblique"`
  `uicontrol`      | `fontangle`   | `"oblique"`
  `uipanel`        | `fontangle`   | `"oblique"`
  `uitable`        | `fontangle`   | `"oblique"`

- The prototype JIT compiler has been removed from Octave.  Since it was
first added as part of a Google Summer of Code project in 2012, no one
has ever seriously taken on further development of it and it still does
nothing significant.  It is out of date with the default interpreter
that walks the parse tree.  Even though we have fixed the configure
script to disable it by default, people still ask questions about how to
build it, but it doesn’t seem that they are doing that to work on it but
because they think it will make Octave code run faster (it never did,
except for some extremely simple bits of code as examples for
demonstration purposes only).  The following functions related to the
JIT compiler have also been removed: `debug_jit`, `jit_enable`,
`jit_failcnt`, and `jit_startcnt`.

### Old release news

- [Octave 6.x](etc/NEWS.6)
- [Octave 5.x](etc/NEWS.5)
- [Octave 4.x](etc/NEWS.4)
- [Octave 3.x](etc/NEWS.3)
- [Octave 2.x](etc/NEWS.2)
- [Octave 1.x](etc/NEWS.1)
