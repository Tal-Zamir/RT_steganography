#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cbmp.h"

int main(int argc, char** argv)
{
    unsigned int bit_number;
    int i;
    unsigned char bit, mask;
    unsigned int x, y, width, height;
    unsigned char r, g, b;
    unsigned char r_new, g_new, b_new;
    unsigned char bit_r,bit_g,bit_b;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    // Read image into BMP struct
    BMP* bmp = bopen(argv[1]);

    // Gets image width in pixels from cbmp.h
    width = get_width(bmp);

    // Gets image height in pixels from cbmp.h
    height = get_height(bmp);


    printf("width: %d\n", width);
    printf("height: %d\n", height);

    
    i = 0;
    mask = 0x1;

    unsigned char current_char;

    int line_num = 0;

    for (x = 0; x < width; x++)
    {

        for (y = 0; y < height; y++)
        {

            // In case we have retrieved 3 pixels
            // we can print on screen the character.

            if (y % 3 == 0) {
                current_char = 0;
            }

            // Gets pixel rgb values at point (x, y)
            get_pixel_rgb(bmp, x, y, &r, &g, &b);

            bit_r = r & 0x1;
            bit_g = g & 0x1;
            bit_b = b & 0x1;

		//debugging point
            // printf("bit_r: %u\n", bit_r);
            // printf("bit_r: %u\n", bit_g);
            // printf("bit_b: %u\n", bit_b);

            current_char =  bit_r << (y % 3)*3 | current_char;
            current_char =  bit_b << (y % 3)*3 + 1 | current_char;

            if ((y % 3) != 2)
                current_char =  bit_g << (y % 3)*3 + 2 | current_char;
            
            if (y % 3 == 2)
            {
                line_num++;    
                printf("%d %c\n", line_num, current_char);
            }
        }
    }


    // Free memory
    bclose(bmp);

    return 0;
}
