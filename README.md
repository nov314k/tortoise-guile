## Notes on running the test example

https://www.gnu.org/software/guile/docs/guile-tut/tutorial.html

As per Section 5.2.2 of the Reference Manual, in main instead of

scm_with_guile (&register_functions, NULL);
scm_shell (argc, argv);

we have

  scm_boot_guile (argc, argv, inner_main, 0);

and we also have inner main into which we moved

Moved the following functions:

scm_c_define_gsubr ("tortoise-reset", 0, 0, 0, &tortoise_reset);
scm_c_define_gsubr ("tortoise-penup", 0, 0, 0, &tortoise_penup);
scm_c_define_gsubr ("tortoise-pendown", 0, 0, 0, &tortoise_pendown);
scm_c_define_gsubr ("tortoise-turn", 1, 0, 0, &tortoise_turn);
scm_c_define_gsubr ("tortoise-move", 1, 0, 0, &tortoise_move);

we have no more need for register_functions