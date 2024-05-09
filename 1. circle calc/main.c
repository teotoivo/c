#include <stdio.h>
#include <math.h>

int main()
{
	const double PI = 3.14159;

	double radius;

	printf("Radius? ");
	scanf("%lf", &radius);

	printf("\nCircumference: %.5lf", (double) (2*PI*radius));

	printf("\nArea: %lf", (double) (PI*radius*radius));

	return 0;
}