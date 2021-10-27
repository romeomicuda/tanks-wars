#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>

int random(int start, int end)
{
	return (rand() % end) + start;
}
void wrap()
{
	for (int i = 70; i > 0; i--)
	{
		printf("==");
	}
}

void startGame()
{
	wrap();
	printf("\n\nWar of Tanks\n\n");
	wrap();
}
void ground()
{
	printf("\n");
	for (int i = 1; i <=70; i++) {
		printf("~~");
	}
	printf("\n");
}
void life(int life1, int life2)
{
	if (life1 <= life2) {
		for (int i = life1; i > 0; i--) {
			printf("%s", "O");
		}
		for (int i = 140-life1-life2; i > 0; i--)
		{
			printf(" ");
		}
		for (int i = life2; i > 0; i--) {
			printf("%s", "O");
		}
	}
	else
	{
		for (int i = life2; i > 0; i--) {
			printf("%s", "O");
		}
		for (int i = 140-life1-life2; i > 0; i--)
		{
			printf(" ");
		}
		for (int i = life1; i > 0; i--) {
			printf("%s", "O");
		}
	}
}
void tanks(int t1, int t2,int bomb)
{
	for (int i = 1; i <=70; i++) {
		if (i == bomb) {
			printf("* ");
			Beep(1600, 250);
		}
		else if (i == t1)
			printf("1 ");
		else if (i == t2)
			printf("2 ");
		else
			printf("  ");
	}
}
void printGame(int t1,int t2, int bomb, int life1, int life2) // poziacia tanku t1,t2 a bomby
{
	ground();
	life(life1,life2);
	printf("\n\n\n\n\n");
	tanks(t1, t2, bomb);
	ground();
}
int bang(double alpha, double velocity)
{
	double res;
	res = (velocity / 3.6) * (velocity / 3.6) * sin((2 * alpha * M_PI) / 180) / (9.81 * 1000);
	return res;
}
int HumanTurn()
{
	double alpha;
	double velocity;
	double res;
	printf("\nYOUR TURN\n");
	printf("ANGLE [DEGREE]  :");
	scanf("%lf", &alpha);
	printf("VELOCITY [KM/H] :");
	scanf("%lf", &velocity);
	res = bang(alpha, velocity);
	return round(res);

}

int checkGame(int t, int bomb)
{
	int dx = abs(t - bomb);
	if (dx = 0)
		return 1;
	else
		return 0;
}
int PcTurn(int t1)
{
	printf("\nPC TURN\n");
	return random(t1-5, t1+5);
}

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds);
}

void gameOverSound()
{
	for (int i = 1800; i > 600; i -= 200) {
		Beep(i, 400);
	}
}


void winSound()
{
	for (int i = 300; i < 1800; i += 200) {
		Beep(i, 300);
	}
}

void end(int winner)
{
	if (winner == 1) {
		printf("\n_____%s______\n", "You win.");
		winSound();
	}
	else
	{
		printf("\n_____%s______\n", "Game over.");
		gameOverSound();
	}
}

int game(int t1, int t2)
{
	int life1 = 3;
	int life2 = 3;
	int x;
	int hit;
	printGame(t1, t2, 0, life1, life2);
	while (1) {
		x = HumanTurn();
		hit = checkGame(t2, t1 + x);
		if (hit)
			life2 -= 1;

		int selfhit = checkGame(t1, t1 + x);
		if (selfhit == 0)
			life1 -= 1;

		delay(1.3);
		printGame(t1, t2, t1 - x, life1, life2);

		if (life1 == 0)
			return 2;
		if (life2 == 0)
			return 1;


		int bomb = PcTurn(t1);
		hit = checkGame(t1, t2 + x);
		if (hit)
			life1 -= 1;
		delay(1.3);
		printGame(t1, t2, bomb , life1, life2);

		if (life1 == 0)
			return 2;

	}

}

int main()
{
	int t1, t2;
	srand(time(0));
	t1 = random(1,70);
	t2 = random(1,70);
	startGame();
	int winner = game(t1, t2);
	printf("%d", winner);
	return 0;
}
