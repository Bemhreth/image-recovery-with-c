#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{

    char raw_file[20];
    FILE *inptr=NULL;

    printf("enter the raw data here(for this case please enter card.raw): " );
  scanf("%s",raw_file);

    // open input file

inptr = fopen(raw_file, "r");

    if (inptr == NULL)
    {
        printf("Could not open %s\n",raw_file);
        return 1;
    }

    // counter
    int count = 0;
    int count1 = 0;

    /* a block of 512 bytes (Different datatypes have different size here we explicitly
       need a datatype which stroes each element in a BYTE) */
    uint8_t block[512];

    // output file
    FILE* outptr = NULL;

    do
    {
        fread(block, 512, 1, inptr);

        // are we at the start of a JPG ?
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            // if already exist, then close file
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // what file should we put data into
            char FILENAME[8];
            char file[10]="%03d.jpg";
            sprintf(FILENAME, file, count);
            outptr = fopen(FILENAME, "w");
            count++;
            count1++;
            fwrite(block, sizeof(block), 1, outptr);

        }
        else if (count > 0)
        {
            // put jpg into outptr
            fwrite(block, sizeof(block), 1, outptr);
        }

    }while(!feof(inptr));

printf("%d files recovered\n",count1 );


    // close infile

    fclose(inptr);


    fclose(outptr);


    return 0;
}
