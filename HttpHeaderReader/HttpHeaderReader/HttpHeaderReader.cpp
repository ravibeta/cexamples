// HttpHeaderReader.c : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "string.h"

static int Hash (const char * pSrc, size_t len);

int main(int argc, char* argv[])
{
	static const char filename[] = "foo.txt";

	static const int MAX_COUNT = 255;

	static int frequency[MAX_COUNT] = {0};

	FILE* fd = fopen(filename, "r");

	if ( fd != NULL )
	{
		char line[MAX_COUNT + 1];

		while ( fgets(line, sizeof line, fd) != NULL )	
		{
			char* p = strchr(line, ':');

			if (p != NULL)
			{
				printf ("%s len = %d, hash = %d\n\n", line, (size_t)(p-line), Hash(_strlwr(line), (size_t)(p-line))%255);
				
				frequency[Hash(_strlwr(line), (size_t)(p-line))%MAX_COUNT] += 1;
			}
		}

		fclose(fd);

		char header[MAX_COUNT + 1] = {0};

		printf( "Enter the header:\n " );

		scanf("%255s", header);

		header[MAX_COUNT] = '\0';

		printf( "%s occurs %d times.\n", header, frequency[Hash(_strlwr(header), strlen(_strlwr(header)))%MAX_COUNT] );
	}

	return 0;
}

static int Hash (const char * pSrc, size_t len)
{
  size_t res = 0;

  while (len--) res = (res << 1) ^ *pSrc++;
  
  return (int)res;
}

