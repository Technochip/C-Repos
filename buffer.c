// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

int
main ()
{

  char str[10];
  int pass = 0;

  printf ("Enter the password:");

  gets (str);

  int len = strlen (str);
  printf ("length of password: %d\n", len);

  printf ("Your enterd password");
  puts (str);

  if (strcmp (str, "wizard"))
    {
      puts ( "Wrong Password!" );
    }
  else
    {
      puts ( "Correct Password!!" );
      pass = 1;
    }

  if (pass)
    {
      /* Now Give root or admin rights to user */
      puts ( "Root privileges given to the user" );
    }

  return 0;


}
