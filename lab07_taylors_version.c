#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int read_input(double x, double y, double z, int* up, int* down, int* left, int* right, int* l_x, int* l_y, int* r_x, int* r_y);
int scaleMagForScreen(double rad);
int scaleJoyForScreen(int rad);
double roll(double x_mag);
double pitch(double y_mag);
void graph_line(int number);
void print_chars(int num, char use);

int main () {
    double x, y, z;
    int up, down, left, right;
    int l_x, l_y, r_x, r_y;
    int scaled_pitch;
    int scaled_roll;
    int scaled_joy;
    double roll_rad, pitch_rad;

    do {

        read_input(x, y, z, &up, &down, &left, &right, &l_x, &l_y, &r_x, &r_y);

        roll_rad = roll(x);
        pitch_rad = pitch(y);

        scaled_roll = scaleMagForScreen(roll_rad);
        graph_line(scaled_roll);


        fflush(stdout);

    }while (1);
}

int read_input(double x, double y, double z, int* up, int* down, int* left, int* right, int* l_x, int* l_y, int* r_x, int* r_y) {
    scanf("%lf %lf %lf %d %d %d %d %d %d %d %d", &x, &y, &z, up, down, left, right, l_x, l_y, r_x, r_y);
    return 0;
}

int scaleMagForScreen(double rad) {
    return (int) (rad * 39);
}

int scaleJoyForScreen(int rad) {
    return (int) (rad / 3.28);
}

double roll(double x_mag) {
    if (x_mag < -1) {
        x_mag = -1;
    }
    if (x_mag > 1) {
        x_mag = 1;
    }
    return asin(x_mag);
}

double pitch(double y_mag) {
    if (y_mag < -1) {
        y_mag = -1;
    }
    if (y_mag > 1) {
        y_mag = 1;
    }
    return asin(y_mag);
}

void print_chars(int num, char use) {
    for (int i = 0; i < num; i++) {
        printf("%c", use);
    }
}

void graph_line(int number) {
    int i = 0;

    if (number < 0){
        i = number + 40;
        print_chars( i,  ' ');
        print_chars( -number, 'l');
    }
    else if ( number > 0) {
        print_chars( 40,  ' ');
        print_chars( number, 'r');
    }
    else{
        print_chars( 40,  ' ');
        print_chars ( 1, '0');
    }

    print_chars(1, '\n');
}