//Kwanchak Jason ho
//Cse13s Fall 2021

#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define options "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    bool a = false;
    bool iy = false;
    bool b = false;
    bool m = false;
    bool r = false;
    bool v = false;
    bool n = false;
    bool s = false;
    bool h = false;
    double e_num = e();
    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
        case 'a': {
            a = true;
            iy = true;
            b = true;
            m = true;
            r = true;
            v = true;
            n = true;
            s = true;
            h = true;
            break;
        }
        case 'e': {
            iy = true;
            break;
        }
        case 'b': {
            b = true;
            break;
        }
        case 'm': {
            m = true;
            break;
        }
        case 'r': {
            r = true;
            break;
        }
        case 'v': {
            v = true;
            break;
        }
        case 'n': {
            n = true;
            break;
        }
        case 's': {
            s = true;
            break;
        }
        case 'h': {
            h = true;
            break;
        }
        }
    }
    if (a) {
        printf("e() = %.15f, M_E = %.15f, diff = %.15f\n", e_num, M_E, absolute(e_num - M_E));
        printf("e() terms = %d\n", e_terms());
        printf("bbp() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        printf("madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        printf("euler() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        printf("pi_euler() terms = %d\n", pi_euler_terms());
        printf("viete() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        printf("pi_viete terms() = %d\n", pi_viete_factors());
        for (double i = 0; i < 10; i += 0.1) {
            printf("sqrt_newton(%.6f) = %.15f, sqrt(%.6f) = %.15f, diff = %.15f\n sqrt_newton "
                   "terms = %d",
                i, sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)),
                sqrt_newton_iters());
        }
    } else if (iy) {
        printf("e() = %.15f, M_E = %.15f, diff = %.15f\n", e_num, M_E, absolute(e_num - M_E));
        if (s) {
            printf("e() terms = %d\n", e_terms());
        }
    } else if (b) {
        printf("bbp() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    } else if (m) {
        printf("madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    } else if (r) {
        printf("euler() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    } else if (v) {
        printf("viete() = %.15f, M_PI = %.15f, diff = %.15f\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (s) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    } else if (n) {
        for (double i = 0; i < 10; i += 0.1) {
            printf("sqrt_newton(%.6f) = %.15f, sqrt(%.6f) = %.15f, diff = %.15f\n", i,
                sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)));
        }
        if (s) {
            printf("sqrt_newton terms() = %d\n", sqrt_newton_iters());
        }
    } else if (s) {
        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvsh]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf(" -a  Runs all test.\n");
        printf(" -e  Runs e test.\n");
        printf(" -b  Runs BBP pi test.\n");
        printf(" -m  Runs Madhava pi test.\n");
        printf(" -r  Runs Euler pi test.\n");
        printf(" -v  Runs Viete pi test.\n");
        printf(" -n  Runs Newton square root test.\n");
        printf(" -s  Print verbose statistics.\n");
        printf(" -h  Displays progran synopsis and usage.\n");
    } else if (h) {
        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvsh]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf(" -a  Runs all test.\n");
        printf(" -e  Runs e test.\n");
        printf(" -b  Runs BBP pi test.\n");
        printf(" -m  Runs Madhava pi test.\n");
        printf(" -r  Runs Euler pi test.\n");
        printf(" -v  Runs Viete pi test.\n");
        printf(" -n  Runs Newton square root test.\n");
        printf(" -s  Print verbose statistics.\n");
        printf(" -h  Displays progran synopsis and usage.\n");
    }
    return 0;
}
