This is the code that I used to reproduce the results of the [Tutorial Introduction to Guile](https://www.gnu.org/software/guile/docs/guile-tut/tutorial.html). I used Guile 2.0 on Cygwin. I had to make some small changes in the tutorial code, as per the notes below.

*Note 1*

In the `main` function, instead of having
```
scm_with_guile (&register_functions, NULL);
scm_shell (argc, argv);
```
I had
```
scm_boot_guile (argc, argv, inner_main, 0);
```

See [Section 5.2.2 of the Guile Reference Manual](https://www.gnu.org/software/guile/manual/guile.html#A-Sample-Guile-Main-Program) for details. Also see [simple-guile example](/simple-guile) in this repository.

*Note 2*

I also had an `inner_main` function, which in it had
```
scm_c_define_gsubr ("tortoise-reset", 0, 0, 0, tortoise_reset);
scm_c_define_gsubr ("tortoise-penup", 0, 0, 0, tortoise_penup);
scm_c_define_gsubr ("tortoise-pendown", 0, 0, 0, tortoise_pendown);
scm_c_define_gsubr ("tortoise-turn", 1, 0, 0, tortoise_turn);
scm_c_define_gsubr ("tortoise-move", 1, 0, 0, tortoise_move);
```

*Note 3*

I no longer needed the `register_functions` function.

Screenshot of the result is shown below.

![screenshot](/screenshot.png "Result from Guile")

Packages that I have installed:

- guile2.0: GNU Scheme interpreter library (2.0.14-3)
- libguile2.0_22: GNU Scheme interpreter library (2.0.14-3)
- libguile2.0-devel: GNU Scheme interpreter library (2.0.14-3)
- gmp: Library for arbitrary precision arithmetic
- libgmp10: Library for arbitrary precision arithmetic (C runtime)
- libgmp-devel: Library for arbitrary precision arithmetic (development)

