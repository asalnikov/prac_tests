#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc,char **argv)
{
    unsigned char byte;
    int symbol;

    FILE *inp,*outp;
 
    int cursor=0;
    size_t counter_read=0;
    size_t counter_write=0;
    size_t counter_bytes=0;
 
    if(argc<3)
    {
        printf("This program converts text with bits to binary file.\n");
        printf("Where bytes corresponds to sequence of symbols '0' and '1'\n");
        printf("All white space symbols in source file will skip\n\n");
        printf("You should present as first parameter of program input file with bits\n");
        printf("and as second parameter output binary file\nFor example\n");
        printf("\t%s inp.txt outp.bin\n\n",argv[0]);

        return 1;
    }

    inp=fopen(argv[1],"r");
    if(inp == NULL)
    {
        fprintf(stderr,"Can't open '%s' for read\n",argv[1]);
        return 2;
    }

    outp=fopen(argv[2],"w");
    if(outp == NULL)
    {
        fprintf(stderr,"Can't open '%s' for write\n",argv[2]);
        return 2;
    }

    printf("convert:\n\tfrom: '%s'\n\tto: '%s'\n\n",argv[1],argv[2]);

    printf("read 0 (bytes), write 0 (bits), write 0 (bytes)");
    fflush(stdout);

    while((symbol=fgetc(inp))!=EOF)
    {

        counter_read++;
        
        if(counter_read%100 == 0)
        {
            printf("\rread %lu (bytes), write %lu (bits), write %lu (bytes)",
                    (unsigned long)counter_read,
                    (unsigned long)counter_write,
                    (unsigned long)counter_bytes
                  );
            fflush(stdout);
        }

        if(isspace(symbol))
        {
            continue;
        }

        if((symbol == '0') || (symbol == '1'))
        {
            if(cursor == 8)
            {
                if(fwrite(&byte,1,1,outp)!=1)
                {
                    fprintf(stderr,"\nOutput truncated\n");
                    fclose(inp);
                    fclose(outp);
                    return 3;
                }
                counter_bytes++;
                cursor=0;
                byte=0;
            }

            byte |= ((unsigned char)(symbol-'0')) << (7-cursor);
            cursor++;

            counter_write++;
        }
        else
        {
            fprintf(stderr,"\nWrong format at byte %lu\n",(unsigned long)counter_read);
            fclose(inp);
            fclose(outp);
            return 4;
        }       
    }
    
    if(cursor!=0)
    {
        if(fwrite(&byte,1,1,outp)!=1)
        {
            fprintf(stderr,"\nOutput truncated\n");
            fclose(inp);
            fclose(outp);
            return 3;
        }
        counter_bytes++;
    }
    
    fclose(inp);
    fclose(outp);

    printf("\rread %lu (bytes), write %lu (bits), write %lu (bytes)",
                    (unsigned long)counter_read,
                    (unsigned long)counter_write,
                    (unsigned long)counter_bytes
          );
    fflush(stdout);
    printf("\nDone\n");

    return 0;
}
