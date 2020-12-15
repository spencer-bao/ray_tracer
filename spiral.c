#include <stdio.h>
#include <math.h>
#define PI 3.14159265

int main(void)
{
    double x, y, z, a, b, r;
    double prev_x, prev_y, prev_z;
    double step = 0.1;
    double loops = 10;
    double theta = 0.0;

    a = 2;
    b = 2;
    r = a;
    prev_x = r*cos(theta);
    prev_y = r*sin(theta);
    prev_z = 30;
    double ball_size = 0.1;

    while (theta < (2 * loops * PI))
    {
        theta += 0.25;
        r = a + b*theta;
        // Draw pixels, but remember to convert to Cartesian:
        x = r*cos(theta);
        y = r*sin(theta);
        prev_z -= .1;
        ball_size += 0.002;

        printf("%f %f %f\n", prev_x/30, prev_y/30, prev_z);
        printf("%f\n", ball_size);
        printf("1.0 0.0 0.9\n\n");

        printf("%f %f %f\n", prev_x/30, prev_y/30, prev_z - 2);
        printf("%f\n", ball_size);
        printf("0.0 1.0 1.0\n\n");

        prev_x = x;
        prev_y = y;
    }

    return 0;
}