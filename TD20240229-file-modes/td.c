#include <stdio.h>
#include <stdlib.h>

int create_file(const char *filename)
{

	const char *mode = "w";
	FILE *f = NULL;

	f = fopen(filename, mode);
	if (NULL == f)
	{
		printf("[create_file] error, unable to create file %s\n", filename);
		return 1;
	}

	fprintf(f, "ABCDEFG");
	if (ferror(f))
	{
		printf("[create_file] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}
	if (0 != fclose(f))
	{
		printf("[create_file] error, unable to close file %s\n", filename);
		return 1;
	}
	return 0;
}

// mode "r" :
// - read anywhere from the file
// - write impossible
int process_file_r(const char *filename)
{
	const char *mode = "r";
	FILE *f = NULL;

	puts("\nprocess_file_r");
	f = fopen(filename, mode);
	if (NULL == f)
	{
		printf("[process_file_r] error, unable to open file %s\n", filename);
		return 1;
	}

	printf("[process_file_r] trying to read char at offset 0...\n");
	fseek(f, 0, SEEK_SET);
	char c = fgetc(f);
	if (ferror(f))
	{
		clearerr(f);
		printf("[create_file] error with fgetc at line %d\n", __LINE__);
	}
	else
		printf("[process_file_r] char at offset 0 = [%c]\n", c);

	printf("[process_file_r] trying to read char at offset 1...\n");
	fseek(f, +1, SEEK_SET);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_r] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_r] char at offset 1 = [%c]\n", c);

	printf("[process_file_r] trying to read char end of file...\n");
	fseek(f, -1, SEEK_END);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_r] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_r] char at end of file = [%c]\n", c);

	printf("[process_file_r] trying to write a char 'X' at offset 3\n");
	fseek(f, +3, SEEK_SET);
	fprintf(f, "X");
	if (ferror(f))
	{
		printf("[process_file_r] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_r] trying to read char at offset 3...\n");
	fseek(f, +3, SEEK_SET);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_r] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_r] read char at offset 3 = [%c]\n", c);

	if (0 != fclose(f))
	{
		printf("[process_file_r] error, unable to close file %s\n", filename);
		return 1;
	}
	return 0;
}

// mode "r+" :
// - read anywhere from the file
// - write anywhere into the file
int process_file_r_plus(const char *filename)
{
	const char *mode = "r+";
	FILE *f = NULL;

	puts("\nprocess_file_r_plus");
	f = fopen(filename, mode);
	if (NULL == f)
	{
		printf("[process_file_r_plus] error, unable to open file %s\n", filename);
		return 1;
	}

	printf("[process_file_r_plus] trying to read char at offset 0...\n");
	fseek(f, 0, SEEK_SET);
	char c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_r_plus] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_r_plus] char at offset= [%c]\n", c);

	printf("[process_file_r_plus] trying to read char at offset 1...\n");
	fseek(f, +1, SEEK_SET);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_r_plus] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_r_plus] read second char = [%c]\n", c);

	printf("[process_file_r] trying to read char end of file...\n");
	fseek(f, -1, SEEK_END);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[create_file] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_r_plus] char end of file = [%c]\n", c);

	printf("[process_file_r_plus] trying to write a char 'X' at offset 3\n");
	fseek(f, +3, SEEK_SET);
	fprintf(f, "X");
	if (ferror(f))
	{
		printf("[create_file] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_r_plus] trying to read char at offset 3...\n");
	fseek(f, +3, SEEK_SET);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[create_file] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_r_plus] read char at position 3 = [%c]\n", c);

	if (0 != fclose(f))
	{
		printf("[process_file_r_plus] error, unable to close file %s\n", filename);
		return 1;
	}
	return 0;
}

// mode "a" :
// - create the file if it does not exist
// - keep the file content if it exists
// - impossible to read from the file
// - write only at the end of the file
int process_file_a(const char *filename)
{
	const char *mode = "a";
	FILE *f = NULL;

	puts("\nprocess_file_a");
	f = fopen(filename, mode);
	if (NULL == f)
	{
		printf("[process_file_a] error, unable to open file %s\n", filename);
		return 1;
	}

	printf("[process_file_a] trying to read char at offset 0...\n");
	fseek(f, 0, SEEK_SET);
	char c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_a] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_a] read char at offset 0 = [%c]\n", c);

	printf("[process_file_a] trying to read char at offset 1...\n");
	fseek(f, +1, SEEK_SET);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_a] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_a] read char at offset 1 = [%c]\n", c);

	printf("[process_file_a] trying to read char end of file...\n");
	fseek(f, -1, SEEK_END);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_a] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_a] read char end of file = [%c]\n", c);

	// in 'a' mode, all written data will be done at the end of the file
	// doing a fseek before does not generate an error, but the fseek is ignored for the write
	printf("[process_file_a] write a char 'X' at position 3\n");
	fseek(f, +3, SEEK_SET);
	fprintf(f, "X");
	if (ferror(f))
	{
		printf("[process_file_a] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_a] trying to read char at offset 3...\n");
	fseek(f, +3, SEEK_SET);
	c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_a] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_a] read char at offset 3 = [%c]\n", c);

	printf("[process_file_a] trying to read char end of file...\n");
	fseek(f, -1, SEEK_END);
	c = fgetc(f);
	printf("[process_file_a] read last char = [%c]\n", c);
	if (ferror(f))
	{
		printf("[process_file_a] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_a] read char end of file = [%c]\n", c);

	if (0 != fclose(f))
	{
		printf("[process_file_a] error, unable to close file %s\n", filename);
		return 1;
	}
	return 0;
}

// mode "a+" :
// - create the file if it does not exist
// - keep the file content if it exists
// - read anywhere from the file
// - write only at the end of the file
int process_file_a_plus(const char *filename)
{
	const char *mode = "a+";
	FILE *f = NULL;

	puts("\nprocess_file_a_plus");
	f = fopen(filename, mode);
	if (NULL == f)
	{
		printf("[process_file_a_plus] error, unable to open file %s\n", filename);
		return 1;
	}

	printf("[nprocess_file_a_plus] trying to write a char 'Z' just after opening\n");
	fprintf(f, "Z");
	if (ferror(f))
	{
		printf("[nprocess_file_a_plus] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}
	printf("[nprocess_file_a_plus] trying to write again a char 'T'\n");
	fprintf(f, "T");
	if (ferror(f))
	{
		printf("[nprocess_file_a_plus] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[nprocess_file_a_plus] trying to read char at offset 0...\n");
	fseek(f, 0, SEEK_SET);
	char c = fgetc(f);
	if (ferror(f))
	{
		printf("[nprocess_file_a_plus] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[nprocess_file_a_plus] read char at offset 0 = [%c]\n", c);

	if (0 != fclose(f))
	{
		printf("[process_file_a_plus] error, unable to close file %s\n", filename);
		return 1;
	}
	return 0;
}

// mode "w" :
// - create the file if it does not exist
// - suppress the file content if it exists
// - impossible to read from the file
// - write anywhere into the file
int process_file_w(const char *filename)
{
	const char *mode = "w";
	FILE *f = NULL;

	puts("\nprocess_file_w");
	f = fopen(filename, mode);
	if (NULL == f)
	{
		printf("[process_file_w] error, unable to open file %s\n", filename);
		return 1;
	}

	printf("[process_file_w] trying to write a char '1' \n");
	fprintf(f, "1");
	if (ferror(f))
	{
		printf("[process_file_w] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_w] trying to write a char '2' \n");
	fprintf(f, "2");
	if (ferror(f))
	{
		printf("[process_file_w] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_w] trying to write a char '4' at offset 0 \n");
	fseek(f, 0, SEEK_SET);
	fprintf(f, "4");
	if (ferror(f))
	{
		printf("[process_file_w] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_w] trying to read char at offset 0...\n");
	fseek(f, 0, SEEK_SET);
	char c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_w] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_w] read char at offset 0 = [%c]\n", c);

	if (0 != fclose(f))
	{
		printf("[process_file_w] error, unable to close file %s\n", filename);
		return 1;
	}
	return 0;
}

// mode "w+" :
// - create the file if it does not exist
// - suppress the file content if it exists
// - impossible to read from the file
// - write anywhere into the file
int process_file_w_plus(const char *filename)
{
	const char *mode = "w+";
	FILE *f = NULL;

	puts("\nprocess_file_w_plus");
	f = fopen(filename, mode);
	if (NULL == f)
	{
		printf("[process_file_w_plus] error, unable to open file %s\n", filename);
		return 1;
	}

	printf("[process_file_w_plus] trying to write a char '1' \n");
	fprintf(f, "1");
	if (ferror(f))
	{
		printf("[process_file_w_plus] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_w_plus] trying to write a char '2' \n");
	fprintf(f, "2");
	if (ferror(f))
	{
		printf("[process_file_w_plus] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_w_plus] trying to write a char at offset 0 \n");
	fseek(f, 0, SEEK_SET);
	fprintf(f, "4");
	if (ferror(f))
	{
		printf("[process_file_w_plus] error with fprintf at line %d\n", __LINE__);
		clearerr(f);
	}

	printf("[process_file_w_plus] trying to read char at offset 0...\n");
	fseek(f, 0, SEEK_SET);
	char c = fgetc(f);
	if (ferror(f))
	{
		printf("[process_file_w_plus] error with fgetc at line %d\n", __LINE__);
		clearerr(f);
	}
	else
		printf("[process_file_w_plus] read char at offset 0 = [%c]\n", c);

	if (0 != fclose(f))
	{
		printf("[process_file_w_plus] error, unable to close file %s\n", filename);
		return 1;
	}
	return 0;
}

int main(int argc, const char *argv[])
{
	const char *filename = "./data/data.txt";

#if 1
	if (0 != create_file(filename))
	{
		printf("Error, unable to create file %s\n", filename);
		return 1;
	}
	if (0 != process_file_r(filename))
	{
		printf("Error, unable to process file %s\n", filename);
		return 1;
	}
#endif
#if 1
	if (0 != create_file(filename))
	{
		printf("Error, unable to create file %s\n", filename);
		return 1;
	}
	if (0 != process_file_r_plus(filename))
	{
		printf("Error, unable to process file %s\n", filename);
		return 1;
	}
#endif
#if 1
	if (0 != create_file(filename))
	{
		printf("Error, unable to create file %s\n", filename);
		return 1;
	}
	if (0 != process_file_a(filename))
	{
		printf("Error, unable to process file %s\n", filename);
		return 1;
	}
#endif
#if 1
	if (0 != create_file(filename))
	{
		printf("Error, unable to create file %s\n", filename);
		return 1;
	}
	if (0 != process_file_a_plus(filename))
	{
		printf("Error, unable to process file %s\n", filename);
		return 1;
	}
#endif
#if 1
	if (0 != create_file(filename))
	{
		printf("Error, unable to create file %s\n", filename);
		return 1;
	}
	if (0 != process_file_w(filename))
	{
		printf("Error, unable to process file %s\n", filename);
		return 1;
	}
#endif
#if 1
	if (0 != create_file(filename))
	{
		printf("Error, unable to create file %s\n", filename);
		return 1;
	}
	if (0 != process_file_w_plus(filename))
	{
		printf("Error, unable to process file %s\n", filename);
		return 1;
	}
#endif
	return 0;
}
