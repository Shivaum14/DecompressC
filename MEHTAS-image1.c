#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* simply to read run length data and print image */

struct run_length{		/* creats a structure to easily handel the charecters and lengths stored in the encoded files */
	int pix;
	int len;
};

struct run_length add_pixel(void){		/* function to read input from stdin and add it to array for easy use and itteration */
	struct run_length sample;
	fscanf(stdin, "%d", &sample.pix);
	fscanf(stdin, "%d", &sample.len);
	return sample;
}

void initialise(char* A, char* B, char* C, char* D, int levels){		/* function to set the value of variables depending on the value of grey levels */
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
			break;		/* function will not return any values, but instead will change the variables at their memory address */
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
	initialise(&A, &B, &C, &D, levels);		/* sets the charecter set to use in images */

	for (j = 0; j < (2*width*height); j++){
		pixels[j] = add_pixel();		/* adds pixels to array inclusing their value and length */
	}

	int values[height][width], count = 0;
	char img[height][width];

	for (k = 0; k < ((width*height))/2; k++){		/* for loop that creates a 2d array of ints that can later be directly converted to an image */
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
		if (line >= width*height){		/* checks if total size is exceeded */
			break;
		}
	}

	for (h = 0; h < height; h++){		/* creates a char array called img according to the int array created earlier, this array is in the form of the image */
		for (w = 0; w < width; w++){
			if (values[h][w] == 0){
				img[h][w] = A;
			} else if (values[h][w] == 1){
				img[h][w] = B;
			} else if (values[h][w] == 2){
				img[h][w] = C;
			} else if (values[h][w] == 3){
				img[h][w] = D;
			}
		}
	}

	for (h = 0; h < height-1; h++){		/* prints the img 2d array in the correct format */
		for (w = 0; w < width-1; w++){
			printf("%c",img[h][w]);
		}
		printf("\n");
	}
	return 0;
}
