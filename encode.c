#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cbmp.h"

int main(int argc, char** argv)
{
    unsigned char the_string[6]={'a',' ','c','a','t','\0'};
    unsigned int bit_number;
    int i, pixel_number, character_index;
    unsigned char bit, mask;
    unsigned int x, y, width, height;
    unsigned char r, g, b;
    unsigned char r_new, g_new, b_new;
    unsigned char bit_r,bit_g,bit_b, current_bit, rgb[3];


    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Read image into BMP struct
    BMP* bmp = bopen(argv[1]);

    // Gets image width in pixels
    width = get_width(bmp);

    // Gets image height in pixels
    height = get_height(bmp);


    printf("width: %d\n", width);
    printf("height: %d\n", height);

    character_index = 0;
    mask = 0x1;

    for (x = 0; x < width; x++)
    {
        y = 0;
        while (y < height)
        {
            // Each pixel holds 3 bits of information
            if (character_index < strlen(the_string)){
                printf("%d) character: %c\n", character_index, the_string[character_index]);
               
                // Focusing on single character and retrieving 3 pixels on each iteration:
                for (pixel_number = 0 ; pixel_number < 3; ++pixel_number)
                {   
                    // Gets pixel rgb values at point (x, y)
                    get_pixel_rgb(bmp, x, y, &r, &g, &b);

                    for (int bit_num_in_rgb = 0; bit_num_in_rgb < 3; ++bit_num_in_rgb)
                    {
                        // 0100100 & 0100000
                        rgb[bit_num_in_rgb] = (the_string[character_index] & mask) > 0 ? 1 : 0; 
                        mask<<=1;
                        //printf("current_bit = %d\n", rgb[bit_num_in_rgb]);
                    }

                    r_new=(r & ~0x1) | rgb[0];
                    printf("*****************************************************************\n");
                    printf("r_bit = %d, r = %d, r_new = %d\n", rgb[0], r,r_new);
                    g_new= (g & ~0x1) | rgb[1];
                    printf("g_bit = %d, g = %d, g_new = %d\n", rgb[1], g,g_new);
                    b_new= (b & ~0x1)| rgb[2];
                    printf("b_bit = %d, b = %d, b_new = %d\n", rgb[2], b,b_new);
                    memset(rgb, '\0',3);
                    // Sets pixel rgb values at point (x, y)
                    set_pixel_rgb(bmp, x, y, r_new, g_new, b_new);
                    
                    y+=1;
                }

                // Next character:

                character_index++;
                mask = 0x1;

                } //character index
            } //y
        } //x

    // Write bmp contents to file
    bwrite(bmp, argv[2]);

    // Free memory
    bclose(bmp);

    return 0;
}
