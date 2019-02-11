This is the code that I used to reproduce the results shown in [Tutorial Introduction to Guile](https://www.gnu.org/software/guile/docs/guile-tut/tutorial.html).

I used Guile 2.0 on Cygwin.

There were several small changes that I had to make, as per [Section 5.2.2 of the Guile Reference Manual](https://www.gnu.org/software/guile/manual/guile.html#A-Sample-Guile-Main-Program), as per the notes below.

- Note 1

In `main`, instead of having
```
scm_with_guile (&register_functions, NULL);
scm_shell (argc, argv);
```
we now have
```
scm_boot_guile (argc, argv, inner_main, 0);
```

- Note 2

We have `inner_main` function, into which we moved:
```
scm_c_define_gsubr ("tortoise-reset", 0, 0, 0, tortoise_reset);
scm_c_define_gsubr ("tortoise-penup", 0, 0, 0, tortoise_penup);
scm_c_define_gsubr ("tortoise-pendown", 0, 0, 0, tortoise_pendown);
scm_c_define_gsubr ("tortoise-turn", 1, 0, 0, tortoise_turn);
scm_c_define_gsubr ("tortoise-move", 1, 0, 0, tortoise_move);
```

- Note 3

We no longer need `register_functions` function.

Screenshot of the result is shown below.

[screenshot](/screenshot.png "Result from Guile")