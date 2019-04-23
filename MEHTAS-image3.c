#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* simply to read run length data and print image */

struct run_length{      /* creats a structure to easily handel the charecters and lengths stored in the encoded files */
   int pix;
   int len;
};

struct run_length add_pixel(void){     /* function to read input from stdin and add it to array for easy use and itteration */
   struct run_length sample;
   fscanf(stdin, "%d", &sample.pix);
   fscanf(stdin, "%d", &sample.len);
   return sample;
}

void initialise(char* A, char* B, char* C, char* D, int levels){     /* function to set the value of variables depending on the value of grey levels */
   switch(levels){
      case 2 :
         *A = '#';
         *B = ' ';
         break;
      case 3 :
         *A = '#';
         *B = '.';
         *C = ' ';
         break;
      case 4 :
         *A = '#';
         *B = ':';
         *C = '.';
         *D = ' ';
         break;      /* function will not return any values, but instead will change the variables at their memory address */
   }  
}

int main(int argc, char const *argv[]){

   int j, k, l, width, height, levels, line = 0, h, w;
   struct run_length pixels[10000];
   char A, B, C, D;

   if ((fscanf(stdin, "%d", &width) + fscanf(stdin, "%d", &height) + fscanf(stdin, "%d", &levels)) != 3){
   /* scans in the width, height and grey levels while checking for errors */
      fprintf(stderr, "Invalid input\n");
      return 0;
   }
   initialise(&A, &B, &C, &D, levels);    /* sets the charecter set to use in images */

   for (j = 0; j < (2*width*height); j++){
      pixels[j] = add_pixel();      /* adds pixels to array inclusing their value and length */
   }

   int values[height][width], count = 0;

   for (k = 0; k < ((width*height))/2; k++){    /* for loop that creates a 2d array of ints that can later be directly converted to an image */
      if (pixels[k].pix == 0){
         for (l = 0; l < pixels[k].len; l++){
            values[0][count] = 0;
            count++;
            line++;
         }
      } else if (pixels[k].pix == 1){
         for (l = 0; l < pixels[k].len; l++){
            values[0][count] = 1;
            count++;
            line++;
         }
      } else if (pixels[k].pix == 2){
         for (l = 0; l < pixels[k].len; l++){
            values[0][count] = 2;
            count++;
            line++;
         }
      } else if (pixels[k].pix == 3){
         for (l = 0; l < pixels[k].len; l++){
            values[0][count] = 3;
            count++;
            line++;
         }
      }
      if (line >= width*height){    /* checks if total size is exceeded */
         break;
      }
   }

   int x2 = 0, y2 = 0;
   int temp_values[(height*2)][(width*2)], final_values[(height*2)][(width*2)], aa_values[(height*2)][(width*2)];
   char new_img[(height*2)][(width*2)];
   int new_levels = levels*2;

   initialise(&A, &B, &C, &D, new_levels);      /* sets the new charecter values for double the grey levels */

   for (h = 0; h < height; h++){    /* flips the values of 1s and 3s in the array */
      for (w = 0; w < width; w++){
         if (values[h][w] == 1){
            values[h][w] = 3;
         } else if (values[h][w] == 3){
            values[h][w] = 1;
         }
      }
   }

   for (h = 0; h < height; h++){    /* coppies the previous array with a 1 pixel space around each charecter in the form of a 9 */
      for (w = 0; w < width; w++){
         temp_values[y2][x2] = values[h][w];
         temp_values[y2+1][x2++] = 9;
         temp_values[y2][x2] = 9;
         temp_values[y2+1][x2++] = 9;
      }
      y2++;
   }

   for (h = 0; h < (height*2); h++){      /* coppies temp_values to final_values to create two identical arrays */
      for (w = 0; w < (width*2); w++){
         final_values[h][w] = temp_values[h][w];
      }
   }

   /* scaling */
   for (h = 0; h < (height*2); h++){      /* fills in the spaceing between charecters with the average of its non-nine surrounding pixels */
      for (w = 0; w < (width*2); w++){
         if ((temp_values[h][w] == 9) && (temp_values[h][w+1] != 9) && (temp_values[h][w-1] != 9)){
            final_values[h][w] = ((temp_values[h][w-1] + temp_values[h][w+1])/2);
         } else if ((temp_values[h][w] == 9) && (temp_values[h+1][w] != 9) && (temp_values[h-1][w] != 9)){
            final_values[h][w] = ((temp_values[h-1][w] + temp_values[h+1][w])/2);
         } else if ((temp_values[h][w] == 9) && (temp_values[h+1][w+1] != 9) && (temp_values[h-1][w-1] != 9) && (temp_values[h+1][w-1] != 9) && (temp_values[h-1][w+1] != 9)){
            final_values[h][w] = ((temp_values[h-1][w-1] + temp_values[h-1][w+1] + temp_values[h+1][w-1] + temp_values[h+1][w+1] + 1)/4);
         }
      }
   }

   /*  Antialiasing, smoothing */
   for (j = 0; j < 3; j++){      /* repeatedly smooths the image by changing each pixels value to the weighted average of its surrounding pixels */
      for (h = 0; h < ((height*2)); h++){
         for (w = 0; w < ((width*2)); w++){
            if (h == 0 || h == (height*2)-1 || h == (height*2)-2 || w == 0 || w == (width*2)-1 || w == (width*2)-2 ){
               aa_values[h][w] = final_values[h][w];
            } else {
               aa_values[h][w] = (
                  final_values[h-1][w-1]+(2*final_values[h-1][w])+final_values[h-1][w+1]+
                  (2*final_values[h][w-1])+(4*final_values[h][w])+(2*final_values[h][w+1])+
                  final_values[h+1][w-1]+(2*final_values[h+1][w])+final_values[h+1][w+1]+7)/16;
            }
         }
      }
      for (h = 0; h < ((height*2)); h++){
         for (w = 0; w < ((width*2)); w++){
            final_values[h][w] = aa_values[h][w];
         }
      }
   }


   for (h = 0; h < height*2; h++){    /* creates a char array called img according to the int array created earlier, this array is in the form of the image */
      for (w = 0; w < width*2; w++){
         if (final_values[h][w] == 0){
            new_img[h][w] = A;
         } else if (final_values[h][w] == 1){
            new_img[h][w] = B;
         } else if (final_values[h][w] == 2){
            new_img[h][w] = C;
         } else if (final_values[h][w] == 3){
            new_img[h][w] = D;
         }
      }
   }

   for (h = 0; h < (height*2)-1; h++){     /* prints the img 2d array in the correct format */
      for (w = 0; w < (width*2)-1; w++){
         printf("%c",new_img[h][w]);
      }
      printf("\n");
   }
   return 0;
}
