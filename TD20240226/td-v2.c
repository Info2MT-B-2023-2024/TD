// files and directories organisation
// file types (text, binary)
// filename and path (relative, absolute)
// file access modes (read, write, append)
// access mechanisms (open, close, read, write, seek, tell)
// always check errors

#include <stdio.h>
#include <stdlib.h>

#define NUM_POINTS 20000
#define MIN_VALUE -1.
#define MAX_VALUE 1.

double my_rand(const double val_min, const double val_max)
{
	return val_min + (val_max - val_min) * (rand() / (double)RAND_MAX);
}

int create_file(const char *filename)
{
	FILE *f = NULL;
	size_t index = 0;
	double x = 0.;
	double y = 0.;
	double sum_x = 0.;
	double sum_y = 0.;
	double mean_x = 0.;
	double mean_y = 0.;

	srand(0);

	f = fopen(filename, "w");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}

	for (index = 0; index < NUM_POINTS; index++)
	{
		x = my_rand(MIN_VALUE, MAX_VALUE);
		y = my_rand(MIN_VALUE, MAX_VALUE);
		sum_x += x;
		sum_y += y;

		fprintf(f, "%+6.3lf %+6.3lf\n", x, y);
	}
	mean_x = sum_x / NUM_POINTS;
	mean_y = sum_y / NUM_POINTS;

	printf("mean_x = %+.15lf\n", mean_x);
	printf("mean_y = %+.15lf\n", mean_y);

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}

	return 0;
}

int process_file(const char *filename)
{
	FILE *f = NULL;
	double x = 0.;
	double y = 0.;
	int ret = 0;

	f = fopen(filename, "r");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}

	// lecture des toutes les lignes du fichier
	// à l'aide d'une boucle et de la fonction feof
	// calcul de la valeur moyenne des éléments par colonne
	// affichage avec 15 chiffres après la virgule
	// comparez avec les valeurs moyennes calculées lors de la
	// création du fichier
	// Q: que proposez-vous pour améliorer la précision des calculs ? (en conservant un fichier txt)

	ret = fscanf(f, "%lf %lf", &x, &y);
	if (2 != ret)
	{
		fprintf(stderr, "error while reading %s.\n", filename);
		return 1;
	}
	printf("%+6.3lf %+6.3lf\n", x, y);

	ret = fscanf(f, "%lf %lf", &x, &y);
	if (2 != ret)
	{
		fprintf(stderr, "error while reading %s.\n", filename);
		return 1;
	}
	printf("%+6.3lf %+6.3lf\n", x, y);

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}

	return 0;
}

int main(int argc, const char *argv[])
{

	const char *filename = "data/points2D.txt";
	int ret = 0;

	ret = create_file(filename);
	if (ret != 0)
	{
		return ret;
	}
	ret = process_file(filename);
	if (ret != 0)
	{
		return ret;
	}
	return 0;
}