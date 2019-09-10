//#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char c; 
    int in, out;
   // getchar();
    in = open("file.in", O_RDONLY);
    if (in < 0 )
    {
    write (1,"NO SUCH FILE OR DIRECTORY\n",28);
    exit(0);
    }	
 
    out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
   // getchar();
    while(read(in,&c,1) == 1)
        write(out,&c,1);

    exit(0);
}

