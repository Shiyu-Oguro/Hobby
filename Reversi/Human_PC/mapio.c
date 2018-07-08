#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_map_file(
	const char* fname,
	char map[10][10]
){
	int x,y;
	char buf[81];
	FILE *fp;

	if((fp = fopen(fname, "r" )) == NULL) return 0;
	fgets(buf, sizeof(buf), fp);
	for(y=0;y<10; ++y){
		fgets(buf,sizeof(buf),fp);
		map[y][0] = atoi(strtok(buf, ","));
		for( x=1; x<10 ;++x)
			map[y][x] = atoi(strtok(NULL, ","));
	}
	fclose(fp);
	return 1;
}
