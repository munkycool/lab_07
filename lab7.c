/*-----------------------------------------------------------------------------
-					          SE 185 Lab 07 - The DS4 Equalizer
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name:
- 	Section:
-	NetID:
-	Date:
-
-   This file provides the outline for your program
-   Please implement the functions given by the prototypes below and
-   complete the main function to make the program complete.
-   You must implement the functions which are prototyped below exactly
-   as they are requested.
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>


/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
#define PI 3.141592653589

/* NO GLOBAL VARIABLES ALLOWED */


/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------
    PRE: Arguments must point to double variables or int variables as appropriate
    This function scans a line of DS4 data, and returns
    True when left button is pressed
    False Otherwise
    POST: it modifies its arguments to return values read from the input line.
------------------------------------------------------------------------------------*/
void read_input( int* time,
                double* g_x, double* g_y, double* g_z,
                int* button_T, int* button_C, int* button_X, int* button_S, int* j_LX, int* j_LY, int* j_RX, int* j_RY);

/*-----------------------------------------------------------------------------
    PRE: ~(-1.0) <= mag <= ~(1.0)
    This function scales the roll/pitch value to fit on the screen.
    Input should be capped at either -1.0 or 1.0 before the rest of your
    conversion.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/
int scaleMagForScreen(double rad);

/*-----------------------------------------------------------------------------
    PRE: -128 <= mag <= 127
    This function scales the joystick value to fit on the screen.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/
int scaleJoyForScreen(int rad);

/*----------------------------------------------------------------------------
    PRE: -39 <= number <= 39
    Uses print_chars to graph a number from -39 to 39 on the screen.
    You may assume that the screen is 80 characters wide.
----------------------------------------------------------------------------*/
void graph_line(int number);

/*-----------------------------------------------------------------------------
    PRE: num >= 0
    This function prints the character "use" to the screen "num" times
    This function is the ONLY place printf is allowed to be used
    POST: nothing is returned, but "use" has been printed "num" times
-----------------------------------------------------------------------------*/
void print_chars(int num, char use);

double roll (double x_mag);
double pitch (double y_mag);

/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
int main()
{
    double x, y, z;                     /* Values of x, y, and z axis*/
    int t;                              /* Variable to hold the time value */
    int b_Up, b_Down, b_Left, b_Right;  /* Variables to hold the button statuses */
    int j_LX, j_LY, j_RX, j_RY;         /* Variables to hold the joystick statuses */
    int scaled_pitch, scaled_roll; 	    /* Value of the roll/pitch adjusted to fit screen display */
    int scaled_joy;
    int switch_mode = 1;                  /* Value of joystick adjusted to fit screen display */
    int b_Down_pressed = 0;
    int flag;
    /* Put pre-loop preparation code here */

    plus_switch_mode:
    printf("Switch Mode by pressing square: %d\n", switch_mode);
    b_Right = 0;
    read_input(&t, &x, &y, &z, &b_Up, &b_Down, &b_Left, &b_Right, &j_LX, &j_LY, &j_RX, &j_RY);
    if (b_Right == 1) {
        switch_mode++;
        if (switch_mode > 3) {
            switch_mode = 1;
        }
    }

    do
    {
        /* Scan a line of input */
        flag = 0; 

        if (b_Right == 1) {
            flag = 1;
        }

        read_input(&t, &x, &y, &z, &b_Up, &b_Down, &b_Left, &b_Right, &j_LX, &j_LY, &j_RX, &j_RY);
        /* Calculate and scale for pitch AND roll AND joystick */

        if (flag == 1) {
            b_Right = 0;
        }

        printf("\n%d", b_Right);

        /* Switch between roll, pitch, and joystick with the up, down, and right button, respectivly */

        /* Output your graph line */

        if (switch_mode == 1) {
            scaled_pitch = scaleMagForScreen(pitch(y));
            graph_line(scaled_pitch);
            if (b_Right == 1) {
                switch_mode++;
                if (switch_mode > 3) {
                    switch_mode = 1;
                }
            }
       // printf("1");
    }
        if (switch_mode == 2) {
            scaled_roll = scaleMagForScreen(roll(x));
            graph_line(scaled_roll);
            if (b_Right == 1) {
                switch_mode++;
                if (switch_mode > 3) {
                    switch_mode = 1;
                }
        }
     //   printf("2");
    }
        if (switch_mode == 3) {
            scaled_joy = scaleJoyForScreen(j_LX);
            graph_line(scaled_joy);
            if (b_Right == 1) {
                switch_mode++;
                if (switch_mode > 3) {
                    switch_mode = 1;
                }
        }
    //    printf("3");
    }

        if (b_Left == 1) {
            exit(0);
        }

        fflush(stdout);

    } while (1 ); /* Modify to stop when left button is pressed */

    return 0;

}

void read_input( int* time,
            double* g_x, double* g_y, double* g_z,
            int* button_T, int* button_C, int* button_X, int* button_S, int* j_LX, int* j_LY, int* j_RX, int* j_RY) {
    
    scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d, %d, %d", time, g_x, g_y, g_z, button_T, button_C, button_X, button_S, j_LX, j_LY, j_RX, j_RY);
}

int scaleMagForScreen(double rad) {
    return (int) (rad * 39*PI/2);
}

int scaleJoyForScreen(int rad) {
    return (int) (rad / 3.28);
}

void graph_line(int number) {
   int i = 0;

    if (number < 0){
        i = number + 100;
        print_chars( i,  ' ');
        print_chars( -number, 'l');
    }
    else if ( number > 0) {
        print_chars( 100,  ' ');
        print_chars( number, 'r');
    }
    else if (number == NAN) {
        printf("NAN");
    }
    else{
        print_chars( 100,  ' ');
        print_chars ( 1, '0');
    }

    print_chars(1, '\n');
}

void print_chars(int num, char use) {
    for (int i = 0; i < num; i++) {
        printf("%c", use);
    }
}

double roll (double x_mag) {
    if (x_mag < -1) {
        x_mag = -1;
    }
    if (x_mag > 1) {
        x_mag = 1;
    }

    return asin(x_mag);
}
double pitch (double y_mag) {
    if (y_mag < -1) {
        y_mag = -1;
    }
    if (y_mag > 1) {
        y_mag = 1;
    }

    return asin(y_mag);
}


