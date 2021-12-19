Summary of changes for version 2.1.x (1997-06-05 -- 2006-03-20):
---------------------------------------------------------------

  * Given a matrix, X, and a boolean index, idx, of the same shape as
    X, X(idx) and X(idx) = RHS now work no matter what the value of
    do_fortran_indexing is.

  * If you are using GNU Emacs 19.34 or earlier, you will need to add
    the following code to your ~/.emacs file in order to use Emacs
    Octave mode:

      ;; Set up the custom library.
      ;; taken from http://www.dina.kvl.dk/~abraham/custom/
      (eval-and-compile
        (condition-case ()
            (require 'custom)
          (error nil))
        (if (and (featurep 'custom) (fboundp 'custom-declare-variable))
            nil ;; We've got what we needed
          ;; We have the old custom-library, hack around it!
          (defmacro defgroup (&rest args)
            nil)
          (defmacro defcustom (var value doc &rest args)
            (` (defvar (, var) (, value) (, doc))))))

  * When `format +' is in effect, Octave uses the following symbols to
    provide more information about the values in a matrix:

      +      positive real
      -      negative real
      i      pure imaginary
      c      complex
      blank  zero

  * The ++ and -- operators now work for indexed matrices, and the
    following operators now work:

      +=, -=, *=, /=, \=, <<=, >>=, .*=, ./=, .\=, &=, |=

    These operators are currently implemented using a relatively
    inefficient brute-force method but hey, they work.

  * The built-in variable argv is now a list of strings instead of a
    string vector.

  * The value of LOADPATH set by the environment variable
    OCTAVE_PATH, the -p or --path command line options, or on the
    command line is no longer modified to include the default path.
    Instead it is left as specified.  Its default value is now ":",
    which tells Octave to search the default path, and the new
    built-in variable DEFAULT_LOADPATH contains the default list of
    directories to search.

  * The function file_in_path no longer does any special processing of
    its PATH argument.  To search LOADPATH for files, it is now
    generally better to use the new function file_in_loadpath.

  * If fread is given a skip parameter, the skip is performed after
    the read instead of before (for compatibility with Matlab).

  * The new built-in variable `crash_dumps_octave_core' controls
    whether Octave writes user variables to the file `octave-core'
    when it crashes or is killed by a signal.  The default value is 1
    (0 if you use --traditional).

  * If LOADPATH contains a doubled colon, the default path is inserted
    in its place.  This is similar to the substitution that also takes
    place for leading or trailing colons in the LOADPATH.

  * Loops of the form `for i = STRING ... endfor' are now allowed.

  * It is now possible to set the iteration limit for lsode using
    lsode_options ("step limit", N).

  * New functions:

      is_complex  -- tell whether a variable is complex
      rehash      -- re-initialize the cache of directories in LOADPATH
      graw        -- send a string to the gnuplot subprocess

  * New functions from Kurt Hornik's Octave-ci package:

    In finance (new directory):

      fv    -- future value of an investment
      fvl   -- future value of an initial lump sum investment
      irr   -- internal rate of return of an investment
      nper  -- number of payments needed for amortizing a loan
      npv   -- net present value of a series of payments
      pmt   -- amount of periodic payment needed to amortize a loan
      pv    -- present value of an investment
      pvl   -- present value of an investment that pays off at the end
      rate  -- rate of return of an investment
      vol   -- volatility of financial time series data

    In linear-algebra:

      dmult -- rescale the rows of a matrix

    In signal:

      arch_fit       -- fit an ARCH regression model
      arch_rnd       -- simulate an ARCH process
      arch_test      -- test for conditional heteroscedascity
      arma_rnd       -- simulate an ARMA process
      autocor        -- compute autocorrelations
      autocov        -- compute autocovariances
      autoreg_matrix -- design matrix for autoregressions
      bartlett       -- coefficients of the Bartlett (triangular) window
      blackman       -- coefficients of the Blackman window
      diffpara       -- estimate the fractional differencing parameter
      durbinlevinson -- perform one step of the Durbin-Levinson algorithm
      fractdiff      -- compute fractional differences
      hamming        -- coefficients of the Hamming window
      hanning        -- coefficients of the Hanning window
      hurst          -- estimate the Hurst parameter
      periodogram    -- compute the periodogram
      rectangle_lw   -- rectangular lag window
      rectangle_sw   -- rectangular spectral window
      sinetone       -- compute a sine tone
      sinewave       -- compute a sine wave
      spectral_adf   -- spectral density estimation
      spectral_xdf   -- spectral density estimation
      spencer        -- apply Spencer's 15-point MA filter
      stft           -- short-term Fourier transform
      synthesis      -- recover a signal from its short-term Fourier transform
      triangle_lw    -- triangular lag window
      triangle_sw    -- triangular spectral window
      yulewalker     -- fit AR model by Yule-Walker method

    In statistics/base (new directory):

      center     -- center by subtracting means
      cloglog    -- complementary log-log function
      cor        -- compute correlations
      cov        -- compute covariances
      cut        -- cut data into intervals
      iqr        -- interquartile range
      kendall    -- kendall's rank correlation tau
      logit      -- logit transformation
      mean       -- compute arithmetic, geometric, and harmonic mean
      meansq     -- compute mean square
      moment     -- compute moments
      ppplot     -- perform a PP-plot (probability plot)
      probit     -- probit transformation
      qqplot     -- perform a QQ-plot (quantile plot)
      range      -- compute range
      ranks      -- compute ranks
      run_count  -- count upward runs
      spearman   -- spearman's rank correlation rho
      statistics -- compute basic statistics
      studentize -- subtract mean and divide by standard deviation
      table      -- cross tabulation
      values     -- extract unique elements
      var        -- compute variance

    In statistics/distributions (new directory):

      beta_cdf           -- CDF of the Beta distribution
      beta_inv           -- Quantile function of the Beta distribution
      beta_pdf           -- PDF of the Beta distribution
      beta_rnd           -- Random deviates from the Beta distribution

      binomial_cdf       -- CDF of the binomial distribution
      binomial_inv       -- Quantile function of the binomial distribution
      binomial_pdf       -- PDF of the binomial distribution
      binomial_rnd       -- Random deviates from the binomial distribution

      cauchy_cdf         -- CDF of the Cauchy distribution
      cauchy_inv         -- Quantile function of the Cauchy distribution
      cauchy_pdf         -- PDF of the Cauchy distribution
      cauchy_rnd         -- Random deviates from the Cauchy distribution

      chisquare_cdf      -- CDF of the chi-square distribution
      chisquare_inv      -- Quantile function of the chi-square distribution
      chisquare_pdf      -- PDF of the chi-square distribution
      chisquare_rnd      -- Random deviates from the chi-square distribution

      discrete_cdf       -- CDF of a discrete distribution
      discrete_inv       -- Quantile function of a discrete distribution
      discrete_pdf       -- PDF of a discrete distribution
      discrete_rnd       -- Random deviates from a discrete distribution

      empirical_cdf      -- CDF of the empirical distribution
      empirical_inv      -- Quantile function of the empirical distribution
      empirical_pdf      -- PDF of the empirical distribution
      empirical_rnd      -- Bootstrap samples from the empirical distribution

      exponential_cdf    -- CDF of the exponential distribution
      exponential_inv    -- Quantile function of the exponential distribution
      exponential_pdf    -- PDF of the exponential distribution
      exponential_rnd    -- Random deviates from the exponential distribution

      f_cdf              -- CDF of the F distribution
      f_inv              -- Quantile function of the F distribution
      f_pdf              -- PDF of the F distribution
      f_rnd              -- Random deviates from the F distribution

      gamma_cdf          -- CDF of the Gamma distribution
      gamma_inv          -- Quantile function of the Gamma distribution
      gamma_pdf          -- PDF of the Gamma distribution
      gamma_rnd          -- Random deviates from the Gamma distribution

      geometric_cdf      -- CDF of the geometric distribution
      geometric_inv      -- Quantile function of the geometric distribution
      geometric_pdf      -- PDF of the geometric distribution
      geometric_rnd      -- Random deviates from the geometric distribution

      hypergeometric_cdf -- CDF of the hypergeometric distribution
      hypergeometric_inv -- Random deviates from hypergeometric distribution
      hypergeometric_pdf -- PDF of the hypergeometric distribution
      hypergeometric_rnd -- Random deviates from hypergeometric distribution

      kolmogorov_smirnov_cdf -- CDF of the Kolmogorov-Smirnov distribution

      laplace_cdf        -- CDF of the Laplace distribution
      laplace_inv        -- Quantile function of the Laplace distribution
      laplace_pdf        -- PDF of the Laplace distribution
      laplace_rnd        -- Random deviates from the Laplace distribution

      logistic_cdf       -- CDF of the logistic distribution
      logistic_inv       -- Quantile function of the logistic distribution
      logistic_pdf       -- PDF of the logistic distribution
      logistic_rnd       -- Random deviates from the logistic distribution

      lognormal_cdf      -- CDF of the log normal distribution
      lognormal_inv      -- Quantile function of the log normal distribution
      lognormal_pdf      -- PDF of the log normal distribution
      lognormal_rnd      -- Random deviates from the log normal distribution

      normal_cdf         -- CDF of the normal distribution
      normal_inv         -- Quantile function of the normal distribution
      normal_pdf         -- PDF of the normal distribution
      normal_rnd         -- Random deviates from the normal distribution

      pascal_cdf         -- CDF of the Pascal (negative binomial) distribution
      pascal_inv         -- Quantile function of the Pascal distribution
      pascal_pdf         -- PDF of the Pascal (negative binomial) distribution
      pascal_rnd         -- Random deviates from the Pascal distribution

      poisson_cdf        -- CDF of the Poisson distribution
      poisson_inv        -- Quantile function of the Poisson distribution
      poisson_pdf        -- PDF of the Poisson distribution
      poisson_rnd        -- Random deviates from the Poisson distribution

      stdnormal_cdf      -- CDF of the standard normal distribution
      stdnormal_inv      -- Quantile function of standard normal distribution
      stdnormal_pdf      -- PDF of the standard normal distribution
      stdnormal_rnd      -- Random deviates from standard normal distribution

      t_cdf              -- CDF of the t distribution
      t_inv              -- Quantile function of the t distribution
      t_pdf              -- PDF of the t distribution
      t_rnd              -- Random deviates from the t distribution

      uniform_cdf        -- CDF of the uniform distribution
      uniform_inv        -- Quantile function of the uniform distribution
      uniform_pdf        -- PDF of the uniform distribution
      uniform_rnd        -- Random deviates from the uniform distribution

      weibull_cdf        -- CDF of the Weibull distribution
      weibull_inv        -- Quantile function of the Weibull distribution
      weibull_pdf        -- PDF of the Weibull distribution
      weibull_rnd        -- Random deviates from the Weibull distribution

      wiener_rnd         -- Simulate a Wiener process

    In statistics/models (new directory):

      logistic_regression             -- ordinal logistic regression
      logistic_regression_derivatives -- derivates of log-likelihood
                                         in logistic regression
      logistic_regression_likelihood  -- likelihood in logistic regression

    In statistics/tests (new directory):

      anova                       -- one-way analysis of variance
      bartlett_test               -- bartlett test for homogeneity of variances
      chisquare_test_homogeneity  -- chi-square test for homogeneity
      chisquare_test_independence -- chi-square test for independence
      cor_test                    -- test for zero correlation
      f_test_regression           -- test linear hypotheses in linear
                                     regression model
      hotelling_test              -- test for mean of a multivariate normal
      hotelling_test_2            -- compare means of two multivariate normals
      kolmogorov_smirnov_test     -- one-sample Kolmogorov-Smirnov test
      kolmogorov_smirnov_test_2   -- two-sample Kolmogorov-Smirnov test
      kruskal_wallis_test         -- kruskal-Wallis test
      manova                      -- one-way multivariate analysis of variance
      mcnemar_test                -- mcnemar's test for symmetry
      prop_test_2                 -- compare two proportions
      run_test                    -- run test for independence
      sign_test                   -- sign test
      t_test                      -- student's one-sample t test
      t_test_2                    -- student's two-sample t test
      t_test_regression           -- test one linear hypothesis in linear
                                     regression model
      u_test                      -- mann-Whitney U-test
      var_test                    -- f test to compare two variances
      welch_test                  -- welch two-sample t test
      wilcoxon_test               -- wilcoxon signed-rank test
      z_test                      -- test for mean of a normal sample with
                                     known variance
      z_test_2                    -- compare means of two normal samples with
                                     known variances

  * The save command now accepts the option -append to save the
    variables at the end of the file, leaving the existing contents.

  * New command-line option --no-history (also available using the
    single character option -H) inhibits saving command history.

  * The mkoctfile script now accepts -DDEF options and passes them on
    to the C and C++ compilers.

  * Running `make check' should work now before you run `make install',
    even if you build a copy of Octave that depends on shared versions
    of the Octave libraries.

  * For matrices, x(:) now works and returns a column vector no matter
    what the value of do_fortran_indexing is.

  * New keywords __FILE__ and __LINE__ expand to the name of the file
    that is being read and the current input line number, respectively.

  * Octave's expression parser is more general and consistent.  It is
    now possible to access structure elements and index arbitrary
    values.  For example, expressions like

      my_home_dir = getpwuid (getuid ()) . dir;

    and

      svd (x) (1:5)

    now work.

  * New built-in variable `print_rhs_assign_val' controls what is
    printed when an assignment expression is evaluated.  If it is
    zero, the value of the variable on the left hand side (after the
    assignment) is printed.  If it is nonzero, the value of the right
    hand side (i.e., the result of the expression) is printed.  The
    default value of is zero, so the behavior is the same as in
    previous versions of Octave.

  * tmpnam now takes two optional arguments, DIR, and PREFIX.  For
    example, tmpnam ("/foo", "bar-") returns a file name like
    "/foo/bar-10773baa".  If DIR is omitted or empty, the value of the
    environment variable TMPDIR, or /tmp is used.  If PREFIX is
    omitted, "oct-" is used.

  * The built-in variable `PWD' has been removed.  If you need to get
    the value of the current working directory, use the pwd() function
    instead.

  * New operators.  Octave's parser now recognizes the following
    operators:  << >> += -= *= /= .+= .-= .*= ./= &= |= <<= >>=.  So
    far, there are only a few operations defined that actually use
    them (this should change before 2.1 is released).

  * New built-in data types:

    logical:

      A true value is represented by 1, and false value by 0.
      Comparison operations like <, <=, ==, >, >=, and != now return
      logical values.  Indexing operations that use zero-one style
      indexing must now use logical values.  You can use the new
      function logical() to convert a numeric value to a logical
      value.  This avoids the need for the built-in variable
      `prefer_zero_one_indexing', so it has been removed.  Logical
      values are automatically converted to numeric values where
      appropriate.

    file:

      A file object represents an open Octave stream object.  The
      fopen function now returns a file object instead of an integer.
      File objects can be converted to integers automatically, and the
      other functions that work with file ids still work with
      integers, so this change should be backward compatible.

      The binary left-shift operator `<<' has been defined to work as
      in C++ for file objects and built-in types.  For example,

        my_stream = fopen ("foo", "w");
        my_stream << "x = " << pi << " marks the spot\n";

      writes `x = 3.1416 marks the spot' in the file foo.

      The built-in variables stdin, stdout, and stderr are now also
      file objects instead of integers.

    list:

      A list is an array of Octave objects.  It can be indexed using
      the normal indexing operator.  For example,

        x = list ([1,2;3,4], 1, "foo");
        stdout << x(2) << "\n"
        1
        stdout << x;
        (
         [1] =

           1  2
           3  4

          [2] = 1
          [3] = foo
        )

      There is currently no special syntax for creating lists; you
      must use the list function.

  * Commas in global statements are no longer special.  They are now
    treated as command separators.  This removes a conflict in the
    grammar and is consistent with the way Matlab behaves.  The
    variable `warn_comma_in_global_decl' has been eliminated.

  * It is now possible to declare static variables that retain their
    values across function calls.  For example,

      function ncall = f () static n = 0; ncall = ++n; endfunction

    defines a function that returns the number of times that it has
    been called.

  * Within user-defined functions, the new automatic variable `argn'
    contains the names of the arguments that were passed to the
    function.  For example,

      function f (...)
        for i = 1:nargin
          stdout << "argn(" << i << ") = `" << deblank (argn(i,:)) \
                 << "' and its value is " << va_arg () << "\n";
        endfor
      endfunction
      f (1+2, "foo", sin (pi/2))

    prints

      argn(1) = `1 + 2' and its value is 3
      argn(2) = `"foo"' and its value is foo
      argn(3) = `sin (pi)' and its value is 1

    on the standard output stream.  If nargin is zero, argn is not defined.
  * Functions like quad, fsolve, and lsode can take either a function
    name or a simple function body as a string.  For example,

      quad ("sqrt (x)", 0, 1)

    is equivalent to

      function y = f (x) y = sqrt (x); endfunction
      quad ("f", 0, 1)

  * If the argument to eig() is symmetric, Octave uses the specialized
    Lapack subroutine for symmetric matrices for a significant
    increase in performance.

  * If the argument to lsode that names the user-supplied function is
    a 2-element string array, the second element is taken as the name
    of the Jacobian function.  The named function should have the
    following form:

      JAC = f (X, T)

    where JAC is the Jacobian matrix of partial derivatives of the
    right-hand-side functions that define the set of differential
    equations with respect to the state vector X.

  * Global variables are now initialized to the empty matrix, for
    compatibility with Matlab.

  * Explicit initialization of global variables only happens once.
    For example, after the following statements are evaluated, g still
    has the value 1.

      global g = 1
      global g = 2

    This is useful for initializing global variables that are used to
    maintain state information that is shared among several functions.

  * Structure elements completion on the command line actually works
    now.

  * The new built-in variable `fixed_point_format' controls whether
    Octave uses a scaled fixed-point format for displaying matrices.
    The default value is 0 unless you use --traditional.

  * The function sumsq now computes sum (x .* conj (x)) for complex values.

  * The new built-in variable max_recursion_depth allows you to
    prevent Octave from attempting infinite recursion.  The default
    value is 256.

  * Octave now uses kpathsea 3.2.

  * New configure option, --enable-readline.

  * New configure option, --enable-static.

Summary of changes for version 2.0.7 (1997-06-04):
-------------------------------------------------

  This is a bug-fixing release.  There are no new user-visible features.

Summary of changes for version 2.0.6 (1997-05-27):
-------------------------------------------------

  This is primarily a bug-fixing release.  There are only a few new
  user-visible features.

  * The new built-in variable default_eval_print_flag controls whether
    Octave prints the results of commands executed by eval() that do
    not end with semicolons.  The default is 1.

  * The new built-in constant OCTAVE_HOME specifies the top-level
    directory where Octave is installed.

  * Octave no longer includes functions to work with NPSOL or QPSOL,
    because they are not free software.

  * The new built-in variable called kluge_procbuf_delay specifies the
    number of microseconds to delay in the parent process after
    forking.  By default on gnu-win32 systems, it's set to 500000 (1/2
    second).  On other systems, the default value is 0.  Delaying for
    a short time in the parent after forking seems to avoid problems
    in which communicating with subprocesses via pipes would sometimes
    cause Octave to hang.  I doubt that the delay is really the right
    solution.  If anyone has a better idea, I'd love to hear it.

Summary of changes for version 2.0.5 (1997-03-01):
-------------------------------------------------

  * A `switch' statement is now available.  See the Statements chapter
    in the manual for details.

  * Commands like ls, save, and cd may now also be used as formal
    parameters for functions.

  * More tests.

Summary of changes for version 2.0.4 (1997-02-20):
-------------------------------------------------

  * It is now possible to use commands like ls, save, and cd as simple
    variable names.  They still cannot be used as formal parameters
    for functions, or as the names of structure variables.  Failed
    assignments leave them undefined (you can recover the original
    function definition using clear).

  * Is is now possible to invoke commands like ls, save, and cd as
    normal functions (for example, load ("foo", "x", "y", "z")).

Summary of changes for version 2.0.3 (1997-02-18):
-------------------------------------------------

  * The manual has been completely revised and now corresponds much
    more closely to the features of the current version.

  * The return value for assignment expressions is now the RHS since
    that is more consistent with the way other programming languages
    work.  However, Octave still prints the entire LHS value so that

      x = zeros (1, 2);
      x(2) = 1

    still prints

      x =

        0  1

    but an assignment like

      z = x(2) = 1

    sets z to 1 (not [ 0, 1 ] as in previous versions of Octave).

  * It is now much easier to make binary distributions.  See the
    Binary Distributions section of the manual for more details.

Summary of changes for version 2.0.2 (1997-01-27):
-------------------------------------------------

  * Octave now stops executing commands from a script file if an error
    is encountered.

  * The return, and break commands now cause Octave to quit executing
    commands from script files.  When used in invalid contexts, the
    break, continue, and return commands are now simply ignored
    instead of producing parse errors.

  * size ("") is now [0, 0].

  * New functions:

      sleep   -- pause execution for a specified number of seconds
      usleep  -- pause execution for a specified number of microseconds

Summary of changes for version 2.0 (1996-12-10):
-----------------------------------------------

  * The set and show commands for setting and displaying gnuplot
    parameters have been replaced by gset and gshow.  This change will
    probably break lots of things, but it is necessary to allow for
    compatibility with the Matlab graphics and GUI commands in a
    future version of Octave.  (For now, the old set and show commands
    do work, but they print an annoying warning message to try to get
    people to switch to using gset.)

  * Octave has been mostly ported to Windows NT and Windows 95 using
    the beta 17 release of the Cygnus GNU-WIN32 tools.  Not everything
    works, but it is usable.  See the file README.WINDOWS for more
    information.

  * Dynamic linking works on more systems using dlopen() and friends
    (most modern Unix systems) or shl_load() and friends (HP/UX
    systems).  A simple example is provided in examples/hello.cc.
    For this feature to work, you must configure Octave with
    --enable-shared.  You may also need to have a shared-library
    version of libg++ and libstdc++.

  * New data types can be added to Octave by writing a C++ class.  On
    systems that support dynamic linking, new data types can be added
    to an already running Octave binary.  A simple example appears in
    the file examples/make_int.cc.  Other examples are the standard
    Octave data types defined in the files src/ov*.{h,cc} and
    src/op-*.cc.

  * The configure option --enable-bounds-check turns on bounds
    checking on element references for Octave's internal array and
    matrix classes.  It's enabled by default.  To disable this
    feature, configure Octave with --disable-bounds-check.

  * The C-style I/O functions (fopen, fprintf, etc.) have been
    rewritten to be more compatible with Matlab.  The fputs function
    has also been added.  Usage of the *printf functions that was
    allowed in previous versions of Octave should still work.
    However, there is no way to make the new versions of the *scanf
    functions compatible with Matlab *and* previous versions of
    Octave.  An optional argument to the *scanf functions is now
    available to make them behave in a way that is compatible with
    previous versions of Octave.

  * Octave can now read files that contain columns of numbers only,
    with no header information.  The name of the loaded variable is
    constructed from the file name.  Each line in the file must have
    the same number of elements.

  * The interface to the pager has changed.  The new built-in variable
    `page_output_immediately' controls when Octave sends output to the
    pager.  If it is nonzero, Octave sends output to the pager as soon
    as it is available.  Otherwise, Octave buffers its output and
    waits until just before the prompt is printed to flush it to the
    pager.

  * Expressions of the form

      A(i,j) = x

    where X is a scalar and the indices i and j define a matrix of
    elements now work as you would expect rather than giving an error.
    I am told that this is how Matlab 5.0 will behave when it is
    released.

  * Indexing of character strings now works.

  * The echo command has been implemented.

  * The document command is now a regular function.

  * New method for handling errors:

      try
        BODY
      catch
        CLEANUP
      end_try_catch

    Where BODY and CLEANUP are both optional and may contain any
    Octave expressions or commands.  The statements in CLEANUP are
    only executed if an error occurs in BODY.

    No warnings or error messages are printed while BODY is
    executing.  If an error does occur during the execution of BODY,
    CLEANUP can access the text of the message that would have been
    printed in the builtin constant __error_text__.  This is the same
    as eval (TRY, CATCH) (which may now also use __error_text__) but
    it is more efficient since the commands do not need to be parsed
    each time the TRY and CATCH statements are evaluated.

  * Octave no longer parses the help command by grabbing everything
    after the keyword `help' until a newline character is read.  To
    get help for `;' or `,', now, you need to use the command
    `help semicolon' or `help comma'.

  * Octave's parser now does some simple constant folding.  This means
    that expressions like 3*i are now evaluated only once, when a
    function is compiled, and the right hand side of expressions like
    a = [1,2;3,4] are treated as true matrix constants rather than
    lists of elements which must be evaluated each time they are
    needed.

  * Built-in variables that can take values of "true" and "false" can
    now also be set to any nonzero scalar value to indicate "true",
    and 0 to indicate "false".

  * New built-in variables `history_file', `history_size', and
    `saving_history'.

  * New built-in variable `string_fill_char' specifies the character
    to fill with when creating arrays of strings.

  * If the new built-in variable `gnuplot_has_frames' is nonzero,
    Octave assumes that your copy of gnuplot includes support for
    multiple plot windows when using X11.

    If the new built-in variable `gnuplot_has_multiplot' is nonzero,
    Octave assumes that your copy of gnuplot has the multiplot support
    that is included in recent 3.6beta releases.

    The initial values of these variables are determined by configure,
    but can be changed in your startup script or at the command line
    in case configure got it wrong, or if you upgrade your gnuplot
    installation.

  * The new plot function `figure' allows multiple plot windows when
    using newer versions of gnuplot with X11.

  * Octave now notices when the plotter has exited unexpectedly.

  * New built-in variable `warn_missing_semicolon'.  If nonzero, Octave
    will warn when statements in function definitions don't end in
    semicolons.  The default value is 0.

  * Octave now attempts to continue after floating point exceptions
    or out-of-memory errors.

  * If Octave crashes, it now attempts to save all user-defined
    variables in a file named `octave-core' in the current directory
    before exiting.

  * It is now possible to get the values of individual option settings
    for the dassl, fsolve, lsode, npsol, qpsol, and quad functions
    using commands like

      dassl_reltol = dassl_options ("relative tolerance");

  * The svd() function no longer computes the left and right singular
    matrices unnecessarily.  This can significantly improve
    performance for large matrices if you are just looking for the
    singular values.

  * The filter() function is now a built-in function.

  * New function randn() returns a pseudo-random number from a normal
    distribution.  The rand() and randn() functions have separate
    seeds and generators.

  * Octave's command-line arguments are now available in the built-in
    variable `argv'.  The program name is also available in the
    variables `program_invocation_name' and `program_name'.  If
    executing a script from the command line (e.g., octave foo.m) or
    using the `#! /bin/octave' hack, the program name is set to the
    name of the script.

  * New built-in variable `completion_append_char' used as the
    character to append to successful command-line completion
    attempts.  The default is " " (a single space).

  * Octave now uses a modified copy of the readline library from
    version 1.14.5 of GNU bash.

  * In prompt strings, `\H' expands to the whole host name.

  * New built-in variable `beep_on_error'.  If nonzero, Octave will try
    to ring your terminal's bell before printing an error message.
    The default value is 0.

  * For functions defined from files, the type command now prints the
    text of the file.  You can still get the text reconstructed from
    the parse tree by using the new option -t (-transformed).

  * New command-line argument --traditional sets the following
    preference variables for compatibility with Matlab:

      PS1                           = ">> "
      PS2                           = ""
      beep_on_error                 = 1
      default_save_format           = "mat-binary"
      define_all_return_values      = 1
      do_fortran_indexing           = 1
      empty_list_elements_ok        = 1
      implicit_str_to_num_ok        = 1
      ok_to_lose_imaginary_part     = 1
      page_screen_output            = 0
      prefer_column_vectors         = 0
      prefer_zero_one_indexing      = 1
      print_empty_dimensions        = 0
      treat_neg_dim_as_zero         = 1
      warn_function_name_clash      = 0
      whitespace_in_literal_matrix  = "traditional"

  * New functions:

      readdir  -- returns names of files in directory as array of strings
      mkdir    -- create a directory
      rmdir    -- remove a directory
      rename   -- rename a file
      unlink   -- delete a file
      umask    -- set permission mask for file creation
      stat     -- get information about a file
      lstat    -- get information about a symbolic link
      glob     -- perform filename globbing
      fnmatch  -- match strings with filename globbing patterns
      more     -- turn the pager on or off
      gammaln  -- alias for lgamma

  * New audio functions from Andreas Weingessel
    <Andreas.Weingessel@ci.tuwien.ac.at>.

      lin2mu     -- linear to mu-law encoding
      loadaudio  -- load an audio file to a vector
      mu2lin     -- mu-law to linear encoding
      playaudio  -- play an audio file
      record     -- record sound and store in vector
      saveaudio  -- save a vector as an audio file
      setaudio   -- executes mixer shell command

  * New plotting functions from Vinayak Dutt.  Ones dealing with
    multiple plots on one page require features from gnuplot 3.6beta
    (or later).

      bottom_title  -- put title at the bottom of the plot
      mplot         -- multiplot version of plot
      multiplot     -- switch multiple-plot mode on or off
      oneplot       -- return to one plot per page
      plot_border   -- put a border around plots
      subplot       -- position multiple plots on a single page
      subwindow     -- set subwindow position for next plot
      top_title     -- put title at the top of the plot
      zlabel        -- put a label on the z-axis

  * New string functions

      bin2dec  -- convert a string of ones and zeros to an integer
      blanks   -- create a string of blanks
      deblank  -- delete trailing blanks
      dec2bin  -- convert an integer to a string of ones and zeros
      dec2hex  -- convert an integer to a hexadecimal string
      findstr  -- locate occurrences of one string in another
      hex2dec  -- convert a hexadecimal string to an integer
      index    -- return position of first occurrence a string in another
      rindex   -- return position of last occurrence a string in another
      split    -- divide one string into pieces separated by another
      str2mat  -- create a string matrix from a list of strings
      strrep   -- replace substrings in a string
      substr   -- extract a substring

    The following functions return a matrix of ones and zeros.
    Elements that are nonzero indicate that the condition was true for
    the corresponding character in the string array.

      isalnum   -- letter or a digit
      isalpha   -- letter
      isascii   -- ascii
      iscntrl   -- control character
      isdigit   -- digit
      isgraph   -- printable (but not space character)
      islower   -- lower case
      isprint   -- printable (including space character)
      ispunct   -- punctuation
      isspace   -- whitespace
      isupper   -- upper case
      isxdigit  -- hexadecimal digit

    These functions return new strings.

      tolower  -- convert to lower case
      toupper  -- convert to upper case

  * New function, fgetl.  Both fgetl and fgets accept an optional
    second argument that specifies a maximum number of characters to
    read, and the function fgets is now compatible with Matlab.

  * Printing in hexadecimal format now works (format hex).  It is also
    possible to print the internal bit representation of a value
    (format bit).  Note that these formats are only implemented for
    numeric values.

  * Additional structure features:

    -- Name completion now works for structures.

    -- Values and names of structure elements are now printed by
       default.  The new built-in variable `struct_levels_to_print'
       controls the depth of nested structures to print.  The default
       value is 2.

    -- New functions:

       struct_contains (S, NAME) -- returns 1 if S is a structure with
                                    element NAME; otherwise returns 0.

       struct_elements (S)       -- returns the names of all elements
                                    of structure S in an array of strings.

  * New io/subprocess functions:

      fputs    -- write a string to a file with no formatting
      popen2   -- start a subprocess with 2-way communication
      mkfifo   -- create a FIFO special file
      popen    -- open a pipe to a subprocess
      pclose   -- close a pipe from a subprocess
      waitpid  -- check the status of or wait for subprocesses

  * New time functions:

      asctime    -- format time structure according to local format
      ctime      -- equivalent to `asctime (localtime (TMSTRUCT))'
      gmtime     -- return time structure corresponding to UTC
      localtime  -- return time structure corresponding to local time zone
      strftime   -- print given time structure using specified format
      time       -- return current time

    The `clock' and `date' functions are now implemented in M-files
    using these basic functions.

  * Access to additional Unix system calls:

      dup2     -- duplicate a file descriptor
      exec     -- replace current process with a new process
      fcntl    -- control open file descriptors
      fork     -- create a copy of the current process
      getpgrp  -- return the process group id of the current process
      getpid   -- return the process id of the current process
      getppid  -- return the process id of the parent process
      getuid   -- return the real user id of the current process
      getgid   -- return the real group id of the current process
      geteuid  -- return the effective user id of the current process
      getegid  -- return the effective group id of the current process
      pipe     -- create an interprocess channel

  * Other new functions:

      commutation_matrix  -- compute special matrix form
      duplication_matrix  -- compute special matrix form
      common_size.m       -- bring arguments to a common size
      completion_matches  -- perform command completion on string
      tilde_expand        -- perform tilde expansion on string

      meshgrid  -- compatible with Matlab's meshgrid function
      tmpnam    -- replaces octave_tmp_file_name
      atexit    -- register functions to be called when Octave exits
      putenv    -- define an environment variable
      bincoeff  -- compute binomial coefficients
      nextpow2  -- compute the next power of 2 greater than a number
      detrend   -- remove a best fit polynomial from data
      erfinv    -- inverse error function
      shift     -- perform a circular shift on the elements of a matrix
      pow2      -- compute 2 .^ x
      log2      -- compute base 2 logarithms
      diff      -- compute differences of matrix elements
      vech      -- stack columns of a matrix below the diagonal
      vec       -- stack columns of a matrix to form a vector
      xor       -- compute exclusive or

  * Functions for getting info from the password database on Unix systems:

      getpwent  -- read entry from password-file stream, opening if necessary
      getpwuid  -- search for password entry with matching user ID
      getpwnam  -- search for password entry with matching username
      setpwent  -- rewind the password-file stream
      endpwent  -- close the password-file stream

  * Functions for getting info from the group database on Unix systems:

      getgrent  -- read entry from group-file stream, opening if necessary
      getgrgid  -- search for group entry with matching group ID
      getgrnam  -- search for group entry with matching group name
      setgrent  -- rewind the group-file stream
      endgrent  -- close the group-file stream

  * The New function octave_config_info returns a structure containing
    information about how Octave was configured and compiled.

  * New function getrusage returns a structure containing system
    resource usage statistics.  The `cputime' function is now defined
    in an M-file using getrusage.

  * The info reader is now a separate binary that runs as a
    subprocess.  You still need the info reader distributed with
    Octave though, because there are some new command-line arguments
    that are not yet available in the public release of Info.

  * There is a new built-in variable, INFO_PROGRAM, which is used as
    the name of the info program to run.  Its initial value is
    $OCTAVE_HOME/lib/octave/VERSION/exec/ARCH/info, but that value can
    be overridden by the environment variable OCTAVE_INFO_PROGRAM, or
    the command line argument --info-program NAME, or by setting the
    value of INFO_PROGRAM in a startup script.

  * There is a new built-in variable, EXEC_PATH, which is used as
    the list of directories to search when executing subprograms.  Its
    initial value is taken from the environment variable
    OCTAVE_EXEC_PATH (if it exists) or PATH, but that value can be
    overridden by the command line argument --exec-path PATH, or
    by setting the value of EXEC_PATH in a startup script.  If the
    EXEC_PATH begins (ends) with a colon, the directories
    $OCTAVE_HOME/lib/octave/VERSION/exec/ARCH and $OCTAVE_HOME/bin are
    prepended (appended) to EXEC_PATH (if you don't specify a value
    for EXEC_PATH explicitly, these special directories are prepended
    to your PATH).

  * If it is present, Octave will now use an `ls-R' database file to
    speed up recursive path searching.  Octave looks for a file called
    ls-R in the directory specified by the environment variable
    OCTAVE_DB_DIR.  If that is not set but the environment variable
    OCTAVE_HOME is set, Octave looks in $OCTAVE_HOME/lib/octave.
    Otherwise, Octave looks in the directory $datadir/octave (normally
    /usr/local/lib/octave).

  * New examples directory.

  * There is a new script, mkoctfile, that can be used to create .oct
    files suitable for dynamic linking.

  * Many more bug fixes.

  * ChangeLogs are now kept in each subdirectory.

See NEWS.1 for old news.