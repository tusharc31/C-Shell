#include "headers.h"
#include "global.h"
int history(int argc, char** argv)
{
	if(argc<1)
	{
		printf("Invalid number of arguments");
		return 1;
	}
	int n=10;
	int nn=0;
	if(argc>1)
		nn=atoi(argv[1]);
	if(nn>0)
		n=nn;
	FILE *fptr;
    char filename[100], *c;
	char *com[30];
	sprintf(filename, "%s/hist_file", HOME_DIR);
    fptr = fopen(filename, "r");
	int nread=0;
	size_t len=0;
    if (fptr == NULL)
    {
        printf("Maybe process does not exist\n");
        return 1;
    }
	int ind=0;
           while (ind< 21 && (nread = getline(&c, &len, fptr)) != -1) {
			   if(len!=0)
			{
				com[ind] = (char*)malloc(sizeof(char)*(len+3));
			   strcpy(com[ind], c);
			   ind++;
			}
           }
	if(n<ind)
		ind=n;
	for(int i=ind-1;i>=0;i--)
	{
		printf("%s", com[i]);
	}
    // Read contents from file
    fclose(fptr);
	return 0;
}
