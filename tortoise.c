#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <libguile.h>

static const int WIDTH = 10;
static const int HEIGHT = 10;
static double x, y;
static int pendown;
static double direction;
static FILE *global_output;

static FILE *start_gnuplot ();
static void exit_gnuplot ();
static SCM tortoise_reset ();
static SCM tortoise_pendown ();
static SCM tortoise_penup ();
static SCM tortoise_turn (SCM);
static void draw_line (FILE *, double, double, double, double);
static SCM tortoise_move (SCM);

static void
inner_main (void *closure, int argc, char **argv)
{
  scm_c_define_gsubr ("tortoise-reset", 0, 0, 0, tortoise_reset);
  scm_c_define_gsubr ("tortoise-penup", 0, 0, 0, tortoise_penup);
  scm_c_define_gsubr ("tortoise-pendown", 0, 0, 0, tortoise_pendown);
  scm_c_define_gsubr ("tortoise-turn", 1, 0, 0, tortoise_turn);
  scm_c_define_gsubr ("tortoise-move", 1, 0, 0, tortoise_move);
  global_output = start_gnuplot ();
  tortoise_pendown ();
  /* preparation */
  scm_shell (argc, argv);
  /* after exit */
}

int
main (int argc, char *argv[])
{
  scm_boot_guile (argc, argv, inner_main, 0);
  return 0;			/* never reached, see inner_main */
}

static FILE *
start_gnuplot ()
{
  FILE *output;
  int pipes[2];
  pid_t pid;

  pipe (pipes);
  pid = fork ();
  if (!pid)
    {
      dup2 (pipes[0], STDIN_FILENO);
      execlp ("gnuplot", NULL);
      return;			/* never reached */
    }
  output = fdopen (pipes[1], "w");
  fprintf (output, "set multiplot\n");
  fprintf (output, "set parametric\n");
  fprintf (output, "set xrange [-%d:%d]\n", WIDTH, WIDTH);
  fprintf (output, "set yrange [-%d:%d]\n", HEIGHT, HEIGHT);
  fprintf (output, "set size ratio -1\n");
  fprintf (output, "unset xtics\n");
  fprintf (output, "unset ytics\n");
  fflush (output);
  return output;
}

static void
exit_gnuplot ()
{
  printf ("Enter any character to close gnuplot: ");
  getchar ();
  fprintf (global_output, "exit gnuplot\n");
  fflush (global_output);
  free (global_output);
}

static SCM
tortoise_reset ()
{
  x = y = 0.0;
  direction = 0.0;
  pendown = 1;
  fprintf (global_output, "clear\n");
  fflush (global_output);
  return SCM_UNSPECIFIED;
}

static SCM
tortoise_pendown ()
{
  pendown = 1;
  SCM result = scm_from_bool (pendown);
  return result;
}

static SCM
tortoise_penup ()
{
  pendown = 0;
  SCM result = scm_from_bool (pendown);
  return result;
}

static SCM
tortoise_turn (SCM degrees)
{
  const double value = scm_to_double (degrees);
  direction += M_PI / 180.0 * value;
  return scm_from_double (direction * 180.0 / M_PI);
}

static void
draw_line (FILE * output, double x1, double y1, double x2, double y2)
{
  fprintf (output, "plot [0:1] %f + %f * t, %f + %f * t notitle\n",
	   x1, x2 - x1, y1, y2 - y1);
  fflush (output);
}

static SCM
tortoise_move (SCM length)
{
  const double value = scm_to_double (length);
  double newX, newY;

  newX = x + value * cos (direction);
  newY = y + value * sin (direction);
  if (pendown)
    draw_line (global_output, x, y, newX, newY);
  x = newX;
  y = newY;
  return scm_list_2 (scm_from_double (x), scm_from_double (y));
}
