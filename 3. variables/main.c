#include <stdio.h>

int main() {
  
  int currentYear = 2024;
	int birthYear = 2005;

	int age = currentYear - birthYear;

	float some = 2.05;

	char gender = "m";

	char name[] = "Teo";
	char surName[] = "Maximilien";

	printf("Your name is %s %s and you are %d years old.\n", name, surName, age);

  return 0;
}