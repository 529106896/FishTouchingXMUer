#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<FreeImage.h>

typedef struct{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;
}Color32;

int main(int argc, char *argv[]){

	int i,j,k;
	int ALPHA_BELOW = 0;
	char filename[256];
	FILE *fini = NULL;

	strcpy(filename,argv[0]);
	char *end = strrchr(filename,'\\'); *end = '\0';
	strcat(filename,"\\alpha_below.ini");
	if((fini = fopen(filename,"rb")) != NULL){
		while(fscanf(fini,"%x",&ALPHA_BELOW) == 1);
	}
	else{
		fini = fopen(filename,"wb");
		fprintf(fini,"%x",ALPHA_BELOW);
	}
	fclose(fini);

	FreeImage_Initialise(TRUE);
	for(k=1;k<argc;k++){
		FIBITMAP* bitmap = FreeImage_Load(FIF_PNG,argv[k],PNG_DEFAULT);
		if(bitmap == NULL){
			printf("Fail to load image.\n");
			continue;
		}
		int width = FreeImage_GetWidth(bitmap);
		int height = FreeImage_GetHeight(bitmap);
		int bytespp = FreeImage_GetLine(bitmap)/width;
		
		Color32 *matrix = (Color32*)calloc(width*height,sizeof(Color32));
		if(matrix == NULL){
			printf("Fail to apply new memery.");
			continue;
		}
		
		for(i=0;i<height;i++){
			BYTE *bitsLine = FreeImage_GetScanLine(bitmap,i);
			for(j=0;j<width;j++){
				matrix[i*width+j].r = bitsLine[FI_RGBA_RED];
				matrix[i*width+j].g = bitsLine[FI_RGBA_GREEN];
				matrix[i*width+j].b = bitsLine[FI_RGBA_BLUE];
				matrix[i*width+j].a = bitsLine[FI_RGBA_ALPHA];
				bitsLine+=bytespp;
			}
		}

		for(i=0;i<height;i++){
			BYTE *bitsLine = FreeImage_GetScanLine(bitmap,i);
			for(j=0;j<width;j++){
				if(matrix[i*width+j].a <= ALPHA_BELOW){
					bitsLine[FI_RGBA_RED] =
					bitsLine[FI_RGBA_GREEN] =
					bitsLine[FI_RGBA_BLUE] = 0xFF;
					bitsLine[FI_RGBA_ALPHA] = 0xFF;
				}
				else{
					bitsLine[FI_RGBA_RED] =
					bitsLine[FI_RGBA_GREEN] =
					bitsLine[FI_RGBA_BLUE] = 0x00;
					bitsLine[FI_RGBA_ALPHA] = 0xFF;
				}
				bitsLine+=bytespp;
			}
		}
		strcpy(filename,argv[k]);
		char *end = strrchr(filename,'.');
		
		*end = '\0';
		strcat(filename,"_mask.bmp");
		FreeImage_Save(FIF_BMP, bitmap, filename, BMP_DEFAULT);

		for(i=0;i<height;i++){
			BYTE *bitsLine = FreeImage_GetScanLine(bitmap,i);
			for(j=0;j<width;j++){
				if(matrix[i*width+j].a <= ALPHA_BELOW){
					bitsLine[FI_RGBA_RED] =
					bitsLine[FI_RGBA_GREEN] =
					bitsLine[FI_RGBA_BLUE] = 0x00;
					bitsLine[FI_RGBA_ALPHA] = 0xFF;
				}
				else{
					bitsLine[FI_RGBA_RED] = matrix[i*width+j].r;
					bitsLine[FI_RGBA_GREEN] = matrix[i*width+j].g;
					bitsLine[FI_RGBA_BLUE] = matrix[i*width+j].b;
					bitsLine[FI_RGBA_ALPHA] = 0xFF;
				}
				bitsLine+=bytespp;
			}
		}
		*end = '\0';
		strcat(filename,".bmp");
		FreeImage_Save(FIF_BMP, bitmap, filename, BMP_DEFAULT);
		free(matrix);
	}
	return 0;
}
