#include <stdio.h>
int main(){
	double x = 100, y = 100;
	double vx = 7, vy = 5;
	double dt = 1;

	while(x < 1000 && y < 1000){
		printf("before: x = %lf, y = %lf\n", x, y);
		x = x + vx * dt;
		y = y + vy * dt;
		printf("after:  x = %lf, y = %lf\n\n\n", x, y);
	}
}
