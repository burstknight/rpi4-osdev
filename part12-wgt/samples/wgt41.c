#include "include/wgt.h"
#include "include/mem.h"
#include "include/multicore.h"

// ######## REQUIRED FUNCTIONS ########

unsigned long state0 = 1000;
unsigned long state1 = 2000;

unsigned long rand(void)
{
    unsigned long s1 = state0;
    unsigned long s0 = state1;

    state0 = s0;
    s1 ^= s1 << 23;
    s1 ^= s1 >> 17;
    s1 ^= s0;
    s1 ^= s0 >> 26;
    state1 = s1;

    return state0 + state1;
}

// ######## STUB FUNCTIONS ########

unsigned int kb = 0;

unsigned int kbhit(void) {
    kb++;
    return kb / 500;
}

void getch(void) {
    wait_msec(0x500000);
    kb = 0;
}

// ######## WGT EXAMPLES ########

void wgt41()
{
  set_clock_rate(get_max_clock());
  mem_init();
  vga256 ();			/* Initialize graphics mode */

  char *message = malloc(15);
  message[0] = 'H';
  message[1] = 'e';
  message[2] = 'l';
  message[3] = 'l';
  message[4] = 'o';
  message[5] = ' ';
  message[6] = 'w';
  message[7] = 'o';
  message[8] = 'r';
  message[9] = 'l';
  message[10] = 'd';
  message[11] = '!';
  message[12] = '\0';

  wgtfont little;
  wgtfont medium;

  extern unsigned char _binary_bin_little_wfn_start[];
  little = &(_binary_bin_little_wfn_start[0]);
  extern unsigned char _binary_bin_medium_wfn_start[];
  medium = &(_binary_bin_medium_wfn_start[0]);

  wtextcolor (vgapal[15]);
 
  wgtprintf (0, 0, NULL, "%.15s", little);
  wgtprintf (0, 8, NULL, "%.15s", medium);
  wouttextxy (0, 50, medium, "Nice to see you");
  wouttextxy (0, 100, little, "Goodbye cruel world!");

/*
  wgtprintf (0, 0, NULL, "%s", message);
  wgtprintf (0, 8, NULL, "String width : %i pixels", wgettextwidth (message, NULL));
  wgtprintf (0, 16, NULL, "String height: %i pixels", wgettextheight (message, NULL));

  wgtprintf (0, 50, medium, "%s", message);
  wgtprintf (0, 66, NULL, "String width : %i pixels", wgettextwidth (message, medium));
  wgtprintf (0, 74, NULL, "String height: %i pixels", wgettextheight (message, medium));

  wgtprintf (0, 100, little, "%s", message);
  wgtprintf (0, 116, NULL, "String width : %i pixels", wgettextwidth (message, little));
  wgtprintf (0, 124, NULL, "String height: %i pixels", wgettextheight (message, little));
*/

  getch ();
  free (message);
}

void main()
{
    wgt41();
    while (1);
}
