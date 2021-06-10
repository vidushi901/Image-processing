//PROJECT :: IMAGE PROCESSING BY :-
//VIDUSHI TIWARI-191210057

#include<stdio.h>
#include<stdlib.h>
#define BRIGHTNESS_FACTOR 50
#define DARKENING_FACTOR 50

void read_grayscale_image(FILE *image)
{

    //A BMP Image has a 54 byte header file, 1024 byte color table and image (pixel) data.
    //Image width is found @ 18th byte in header file ,image height @ 22nd byte and bitdepth @28th byte
    //(2^8 nos can be used or 256 colors, each color shown by a integer carrying 4 bytes each,therefore taking color table storage to 256*4=1024 bytes)
    if(image==NULL) exit(0);
    unsigned char header[54],colortable[1024];       //Color table exists if bitdepth <=8
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);         //Reading the header file and storing in a character array
    int image_width=*(int*)&header[18];              //Type Casting from char to int
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    //Pixel data will be stored in a new array of size width*height
    unsigned char pixel_information[image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    //Now for copying an image into a new file
    FILE *copy_grayscale_image=fopen("C:\\Users\\hp\\Desktop\\grayscale_image_COPY.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,copy_grayscale_image);      //copying header file onto copy image
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,copy_grayscale_image);     //Copying color table
    fwrite(pixel_information,sizeof(unsigned char),(image_width*image_height),copy_grayscale_image); //Copying Image Information
    fclose(copy_grayscale_image);
}

void readImage2 (FILE *image)
{
    unsigned char header[54],colortable[1024];
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    unsigned char pixel_information[image_height*image_width*3];
    fread(pixel_information,sizeof(unsigned char),(image_height*image_width*3),image);
    FILE *copy_image=fopen("C:\\Users\\hp\\Desktop\\coloured_image_1_Copy.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,copy_image);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,copy_image);
    fwrite(pixel_information,sizeof(unsigned char),(image_width*image_height*3),copy_image);
    fclose(copy_image);
}

void negative_of_Image(FILE *image)
{
    if(image==NULL) exit(0);
    unsigned char header[54],colortable[1024];
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    FILE *negative=fopen("C:\\Users\\hp\\Desktop\\grayscale_image_NEGATIVE.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,negative);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,negative);
    unsigned char modified_pixel_information[image_width*image_height];
    for(i=0;i<(image_width*image_height);i++) modified_pixel_information[i]=255-pixel_information[i];        //Negative means new pixel data = 255-old pixel data
    fwrite(modified_pixel_information,sizeof(unsigned char),(image_width*image_height),negative);
    fclose(negative);
}

void brightness(FILE *image)
{
    if(image==NULL) exit(0);
    unsigned char header[54],colortable[1024];
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    unsigned char modified_pixel_information[image_width*image_height];
    for(i=0;i<(image_width*image_height);i++)
    {
        modified_pixel_information[i]=pixel_information[i]+BRIGHTNESS_FACTOR;                      //INCREASING BRIGHTNESS MEANS INCREASING PIXEL VALUE
        if(modified_pixel_information[i]>255) modified_pixel_information[i]=255;
    }
    FILE *bright_image=fopen("C:\\Users\\hp\\Desktop\\BRIGHT IMAGE.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,bright_image);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,bright_image);
    fwrite(modified_pixel_information,sizeof(unsigned char),(image_width*image_height),bright_image);
    fclose(bright_image);
}

void rgb_2_grayscale(FILE *image)
{

    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    FILE* grayscale=fopen("C:\\Users\\hp\\Desktop\\RGB_2_Grayscale.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,grayscale);
    if(bit_depth<=8) fwrite(color_table,sizeof(unsigned char),1024,grayscale);
    unsigned char pixel_information[image_height*image_width][3];
    int i,grayscale_value;
    for(i=0;i<image_height*image_width;i++)
    {
        pixel_information[i][2]=getc(image);
        pixel_information[i][1]=getc(image);
        pixel_information[i][0]=getc(image);//CONVERSION FORMULA
        putc(grayscale_value,grayscale);
		putc(grayscale_value,grayscale);
		putc(grayscale_value,grayscale);
    }
    fclose(grayscale);
}

void blurrimage(FILE *image)
{
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height][3],new_pixel_information[image_width*image_height][3];
    int i,j;
    for(i=0;i<image_height*image_width;i++)
	{
		new_pixel_information[i][2]=pixel_information[i][2]=getc(image);					// blue
		new_pixel_information[i][1]=pixel_information[i][1]=getc(image);					// green
		new_pixel_information[i][0]=pixel_information[i][0]=getc(image);					// red
	}
	float v=1.0 / 9.0;
	float kernel[3][3]={{v,v,v},                        // initialize the blurrring kernel
						{v,v,v},
						{v,v,v}};
    int x,y;
    for(x=1;x<image_height-1;x++)
	{
		for(y=1;y<image_width-1;y++)
		{
			float sum0= 0.0;
			float sum1= 0.0;
			float sum2= 0.0;
			for(i=-1;i<=1;++i)
			{
				for(j=-1;j<=1;++j)
				{
					// matrix multiplication with kernel with every color plane
					sum0=sum0+kernel[i+1][j+1]*pixel_information[(x+i)*image_width+(y+j)][0];
					sum1=sum1+kernel[i+1][j+1]*pixel_information[(x+i)*image_width+(y+j)][1];
					sum2=sum2+kernel[i+1][j+1]*pixel_information[(x+i)*image_width+(y+j)][2];
				}
			}
			new_pixel_information[(x)*image_width+(y)][0]=sum0;
			new_pixel_information[(x)*image_width+(y)][1]=sum1;
			new_pixel_information[(x)*image_width+(y)][2]=sum2;
		}
	}
    FILE *blurred_rgb=fopen("C:\\Users\\hp\\Desktop\\BLURRED RGB.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,blurred_rgb);
    if(bit_depth<=8) fwrite(color_table,sizeof(unsigned char),1024,blurred_rgb);
    for(i=0;i<image_height*image_width;i++)						//write image data back to the file
	{
		putc(new_pixel_information[i][2],blurred_rgb);
		putc(new_pixel_information[i][1],blurred_rgb);
		putc(new_pixel_information[i][0],blurred_rgb);
	}
    fclose(blurred_rgb);
}

void horizontal_reflection(FILE *image)
{
    unsigned char header[54],colortable[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height],modified_pixel_information[image_height*image_width];
    fread(pixel_information,sizeof(unsigned char),(image_height*image_width),image);
    int i,j;
    for(i=0;i<image_height;i++)
    {
        for(j=0;j<image_width;j++)
        {
            modified_pixel_information[i*image_width+j]=pixel_information[((i+1)*image_width)-(j+1)];
        }
    }
    FILE *horizontal_reflection=fopen("C:\\Users\\hp\\Desktop\\horizontal_reflection.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,horizontal_reflection);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,horizontal_reflection);
    fwrite(modified_pixel_information,sizeof(unsigned char),(image_height*image_width),horizontal_reflection);
    fclose(horizontal_reflection);
}

void vertical_reflection(FILE *image)
{
    unsigned char header[54],colortable[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height],modified_pixel_information[image_height*image_width];
    fread(pixel_information,sizeof(unsigned char),(image_height*image_width),image);
    int i,j;
    for(i=0;i<image_height;i++)
    {
        for(j=0;j<image_width;j++)
        {
            modified_pixel_information[i*image_width+j]=pixel_information[((image_height-1-i)*image_width)+j];
        }
    }
    FILE *vertical_reflection=fopen("C:\\Users\\hp\\Desktop\\vertical_reflection.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,vertical_reflection);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,vertical_reflection);
    fwrite(modified_pixel_information,sizeof(unsigned char),(image_height*image_width),vertical_reflection);
    fclose(vertical_reflection);
}

void darken(FILE *image)
{
     if(image==NULL) exit(0);
    unsigned char header[54],colortable[1024];
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height],modified_pixel_information[image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    for(i=0;i<(image_width*image_height);i++)
    {
        modified_pixel_information[i]=pixel_information[i]-DARKENING_FACTOR;                      //DARKENING MEANS REDUCING THE PIXEL VALUE
        if(modified_pixel_information[i]<0) modified_pixel_information[i]=0;
    }
    FILE *dark_image=fopen("C:\\Users\\hp\\Desktop\\DARK IMAGE.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,dark_image);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,dark_image);
    fwrite(pixel_information,sizeof(unsigned char),(image_width*image_height),dark_image);
    fclose(dark_image);
}

void deviation (FILE *image)
{

  //FILE *image=fopen("image.bmp","rb");
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information [image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    FILE *image2=fopen("C:\\Users\\hp\\Desktop\\Blurred Image.bmp","rb");
    unsigned char header2[54],color_table2[1024];
    fread(header2,sizeof(unsigned char),54,image2);
    int image_width2=*(int*)&header2[18];
    int image_height2=*(int*)&header2[22];
    int bit_depth2=*(int*)&header2[28];
    if(bit_depth2<=8) fread(color_table2,sizeof(unsigned char),1024,image2);
    unsigned char pixel_information2[image_width2*image_height2];
    fread(pixel_information2,sizeof(unsigned char),(image_width2*image_height2),image2);
    FILE *image3=fopen("C:\\Users\\hp\\Desktop\\grayscale_image_COPY.bmp","rb");
    unsigned char header3[54],color_table3[1024];
    fread(header3,sizeof(unsigned char),54,image3);
    int image_width3=*(int*)&header3[18];
    int image_height3=*(int*)&header3[22];
    int bit_depth3=*(int*)&header3[28];
    if(bit_depth3<=8) fread(color_table3,sizeof(unsigned char),1024,image3);
    unsigned char pixel_information3[image_width3*image_height3];
    fread(pixel_information3,sizeof(unsigned char),(image_width3*image_height3),image3);
    int i;
    float cnt=0,cnt1=0;
    for(i=0;i<image_height*image_width;i++)
    {
        int c =pixel_information2[i]-pixel_information[i];
        if(c==0) cnt++;
        int d =pixel_information3[i]-pixel_information[i];
        if(d==0) cnt1++;
    }
    int size=image_height*image_width;
    float similarity1=(cnt*100)/size;
    float similarity2=(cnt1*100)/size;
    float deviation1=100-similarity1;
    float deviation2=100-similarity2;
    printf("DEVIATION OBSERVED FROM BLURRED IMAGE  ::  %f\n\n",deviation1);
    printf("DEVIATION OBSERVED FROM IMAGE COPY  ::  %f\n\n",deviation2);
    fclose(image2);
    fclose(image3);
}

void metamorphosis (FILE *image)
{
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information [image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    FILE *image2=fopen("C:\\Users\\hp\\Desktop\\DARK IMAGE.bmp","rb");
    unsigned char header2[54],color_table2[1024];
    fread(header2,sizeof(unsigned char),54,image2);
    int image_width2=*(int*)&header2[18];
    int image_height2=*(int*)&header2[22];
    int bit_depth2=*(int*)&header2[28];
    if(bit_depth2<=8) fread(color_table2,sizeof(unsigned char),1024,image2);
    unsigned char pixel_information2[image_width2*image_height2];
    fread(pixel_information2,sizeof(unsigned char),(image_width2*image_height2),image2);
    unsigned char pixel_information3[image_width*image_height];
    int i;
    for(i=0;i<image_height*image_width;i++)
    {
        pixel_information3[i]=pixel_information[i]+pixel_information2[i];
        if(pixel_information3[i]>255) pixel_information3[i]=255;
    }
    FILE *image3=fopen("C:\\Users\\hp\\Desktop\\sum_image.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,image3);
    if(bit_depth<=8) fwrite(color_table,sizeof(unsigned char),1024,image3);
    fwrite(pixel_information3,sizeof(unsigned char),(image_height*image_width),image3);
    fclose(image2);
    fclose(image3);
}

void rotation (FILE *image)
{
    unsigned char header[54],colortable[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width][image_height];
    fread(pixel_information,sizeof(unsigned char),(image_height*image_width),image);
    FILE *rotate=fopen("C:\\Users\\hp\\Desktop\\90_rotate.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,rotate);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,rotate);
    unsigned char pixel_information2[image_height][image_width];
    int x,y;
    for(x=0;x<image_height/2;x++)
    {
        for(y=x;y<image_height-x-1;y++)
        {
            pixel_information2[x][y]=pixel_information[y][image_height-x-1];
            pixel_information2[y][image_height-x-1]=pixel_information[image_height-x-1][image_height-y-1];
            pixel_information2[image_height-x-1][image_height-y-1]=pixel_information[image_height-y-1][x];
            pixel_information2[image_height-y-1][x]=pixel_information[x][y];
        }
    }
    fwrite(pixel_information2,sizeof(unsigned char),(image_height*image_width),rotate);
    fclose(rotate);
}

void apply_sepia_filter(FILE* image)
{
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18],image_height=*(int*)&header[22],bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information [image_height*image_width][3];
    unsigned char modified_pixel_information [image_height*image_width][3];
    fread(pixel_information,sizeof(unsigned char),image_height*image_width*3,image);
    int i;
    for(i=0;i<image_height*image_width;i++)
    {
        int new_blue=(pixel_information[i][2]*0.272)+(pixel_information[i][1]*0.534)+(pixel_information[i][0]*0.189);
        int new_green=(pixel_information[i][2]*0.349)+(pixel_information[i][1]*0.686)+(pixel_information[i][0]*0.168);
        int new_red=(pixel_information[i][2]*0.393)+(pixel_information[i][1]*0.769)+(pixel_information[i][0]*0.131);
        if(new_blue>255) new_blue=255;
        if(new_green>255) new_green=255;
        if(new_red>255) new_red=255;
        modified_pixel_information[i][0]=new_blue;
        modified_pixel_information[i][1]=new_green;
        modified_pixel_information[i][2]=new_red;
    }
    FILE* sepia=fopen("C:\\Users\\hp\\Desktop\\lena_sepia.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,sepia);
    if(bit_depth<=8) fwrite(color_table,sizeof(unsigned char),1024,sepia);
    fwrite(modified_pixel_information,sizeof(unsigned char),image_height*image_width*3,sepia);
    fclose(sepia);
}

void blur_grayscale(FILE* image)
{
    if(image==NULL) exit(0);
    unsigned char header[54],colortable[1024];
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    unsigned char modified_pixel_information[image_width*image_height];
    for(i=0;i<(image_height*image_width);i++) modified_pixel_information[i]=pixel_information[i];
    /*FOR BLURRING AN IMAGE A KERNEL(N*N MATRIX WHERE N IS ODD NUMBER) IS DECLARED
    THE CENTRE OF THE KERNEL IS THE PIXEL IN ACTION
    THE KERNEL PROVIDES THE AVERAGE OF THE N PIXEL VALUES(N-1 SURROUNDING + 1 ITSELF) TO THE PIXEL IN ACTION
    AND HAS VALUE OF EACH ELEMENT AS 1/N
    A 3*3 KERNEL(THE FIRST MATRIX) PROVIDES A BLURRED IMAGE WITH MOST RESOLUTION*/
    int x,y,j;
    float a=1.0 / 9.0;
	float kernel[3][3]={{a,a,a},								//initialize the blurrring kernel
						{a,a,a},
						{a,a,a}};
    for(x=1;x<image_height-1;x++)
	{
		for(y=1;y<image_width-1;y++)
		{
			float sum= 0.0;
			for(i=-1;i<=1;++i)
			{
				for(j=-1;j<=1;++j)
				{
					sum=sum+kernel[i+1][j+1]*pixel_information[(x+i)*image_width+(y+j)];	//this process is called convolution
				}
			}
			modified_pixel_information[(x)*image_width+(y)]=sum;                            //as blurring an image would give less resolution than the original image so we let the outer pixels remain same as original
		}
	}
	FILE *blurred_image=fopen("C:\\Users\\hp\\Desktop\\Blurred Image.bmp","wb");
	fwrite(header,sizeof(unsigned char),54,blurred_image);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,blurred_image);
    fwrite(modified_pixel_information,sizeof(unsigned char),(image_width*image_height),blurred_image);
    fclose(blurred_image);
}

void convert_2_BnW(FILE* image)
{
    if(image==NULL) exit(0);
    unsigned char header[54],colortable[1024];
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(colortable,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_width*image_height];
    fread(pixel_information,sizeof(unsigned char),(image_width*image_height),image);
    for(i=0;i<(image_width*image_height);i++) pixel_information[i]=(pixel_information[i]>127)?255:0;
    FILE *black_n_white=fopen("C:\\Users\\hp\\Desktop\\B&W IMAGE.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,black_n_white);
    if(bit_depth<=8) fwrite(colortable,sizeof(unsigned char),1024,black_n_white);
    fwrite(pixel_information,sizeof(unsigned char),(image_width*image_height),black_n_white);
    fclose(image);
    fclose(black_n_white);
}

void get_detail(FILE* image)
{
    if(image==NULL) exit(0);
    unsigned char header[54];
    int i;
    for(i=0;i<54;i++) header[i]=getc(image);
    printf("IMAGE WIDTH :: %d\n",*(int*)&header[18]);
    printf("IMAGE HEIGHT :: %d\n",*(int*)&header[22]);
    printf("BIT DEPTH :: %d\n\n",*(int*)&header[28]);
}

void get_pixel_value(FILE* image,int y,int x)
{
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_height*image_width];
    fread(pixel_information,sizeof(unsigned char),image_height*image_width,image);
    printf("PIXEL VALUE AT (%d,%d) :: %d\n",y,x,pixel_information[y*image_width+x]);
}

void set_pixel_value(FILE* image,int y,int x,int value)
{
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_height*image_width];
    fread(pixel_information,sizeof(unsigned char),image_height*image_width,image);
    pixel_information[y*image_width+x]=value;
    FILE *new_pixel_grayscale_image=fopen("C:\\Users\\hp\\Desktop\\grayscale_image_NEW PIXEL.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,new_pixel_grayscale_image);
    if(bit_depth<=8) fwrite(color_table,sizeof(unsigned char),1024,new_pixel_grayscale_image);
    fwrite(pixel_information,sizeof(unsigned char),(image_width*image_height),new_pixel_grayscale_image);
    fclose(new_pixel_grayscale_image);
}

void average_gray_level(FILE* image)
{
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18];
    int image_height=*(int*)&header[22];
    int bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information[image_height*image_width];
    fread(pixel_information,sizeof(unsigned char),image_height*image_width,image);
    int i;
    float sum=0;
    for(i=0;i<image_height*image_width;i++)
    {
        sum=sum+pixel_information[i];
    }
    float image_size=image_height*image_width;
    printf("AVERAGE GRAY LEVEL OF IMAGE :: %f\n\n",(sum)/image_size);
}

void crop_image(FILE* image)
{
    unsigned char header[54],color_table[1024];
    fread(header,sizeof(unsigned char),54,image);
    int image_width=*(int*)&header[18],image_height=*(int*)&header[22],bit_depth=*(int*)&header[28];
    if(bit_depth<=8) fread(color_table,sizeof(unsigned char),1024,image);
    unsigned char pixel_information [image_height*image_width][3];
    fread(pixel_information,sizeof(unsigned char),image_height*image_width*3,image);
    printf("MAX HEIGHT OF IMAGE :: %d\nMAX WIDTH OF IMAGE :: %d\n",image_height,image_width);
    printf("\nENTER CO-ORDINATES OF UPPER LEFT ROW AND COLUMN\n");
    int ULr,ULc,LRr,LRc;
    scanf("%d %d",&ULr,&ULc);
    printf("\nENTER CO-ORDINATES OF LOWER RIGHT ROW AND COLUMN\n");
    scanf("%d %d",&LRr,&LRc);
    printf("%d  %d  %d  %d",ULr,ULc,LRr,LRc);
    if(ULr>=LRr||ULc>=LRc||LRr>=image_height||LRc>=image_width)
    {
        printf("\nINVALID INPUT\n");
        return;
    }
    unsigned char modified_header[54];
    int i;
    int modified_height=(LRr-ULr)+1;
    int modified_width=(LRc-ULc)+1;
    //*(int*)&header[18]=modified_width;
    //*(int*)&header[22]=modified_height;
    for(i=0;i<54;i++)
    {
        if(i==18)
        {
            modified_header[i]=(modified_width)-256*(modified_width>>8);
            i++;
            modified_header[i]=(modified_width>>8)-256*(modified_width>>16);
            i++;
            modified_header[i]=(modified_width>>16)-256*(modified_width>>24);
            i++;
            modified_header[i]=(modified_width>>24);
            i++;
            modified_header[i]=(modified_height)-256*(modified_height>>8);
            i++;
            modified_header[i]=(modified_height>>8)-256*(modified_height>>16);
            i++;
            modified_header[i]=(modified_height>>16)-256*(modified_height>>24);
            i++;
            modified_header[i]=(modified_height>>24);
            i++;
        }
        modified_header[i]=header[i];
    }
    FILE* crop=fopen("C:\\Users\\hp\\Desktop\\CROPPED_IMAGE.bmp","wb");
    fwrite(header,sizeof(unsigned char),54,crop);
    if(bit_depth<=8) fwrite(color_table,sizeof(unsigned char),1024,crop);
    unsigned char modified_pixel_information[modified_height*modified_width][3];
    int j=0,cnt,k;
    for(k=(image_width*ULr)+ULc;k<=LRr*image_width+ULc;k=k+(image_width-modified_width))
    {
        for(i=k,cnt=0;cnt<modified_width;i++,j++,cnt++)
        {
            modified_pixel_information[j][0]=pixel_information[i][0];
            modified_pixel_information[j][1]=pixel_information[i][1];
            modified_pixel_information[j][2]=pixel_information[i][2];
        }
    }
    fwrite(modified_pixel_information,sizeof(unsigned char),modified_height*modified_width*3,crop);
    fclose(crop);
}

int main()
{
    int a;
    while (1)
    {
        printf("Enter your choice:\n\n1. Read and Copy a Grayscale Image\n2. Read and Copy a Coloured Image\n3. Get the negative of an image\n4. Blur a Grayscale Image\n5. Increase the brightness\n");
        printf ("6. Convert RGB Image to Grayscale\n7. Blur a coloured image\n8. Horizontal reflection of an image\n9. Vertical Reflection of an image\n");
        printf ("10. Darken an image\n11. Detecting deviation from an image\n12. Image Morphing\n13. Rotate an image\n");
        printf ("14. To apply Sepia Filter\n15. To apply B&W Filter\n16. Get details of image\n17. Get pixel Value at (r,c)\n18. Set the pixel value at(r,c)\n19. Compute average gray level\n20. Crop a Image\n21. To exit\n\n");
        scanf ("%d", &a);
        FILE *image=fopen("C:\\Users\\hp\\Desktop\\image.bmp","rb");       // grayscale image
        FILE *ci1=fopen("C:\\Users\\hp\\Desktop\\coloured_image_1.bmp", "rb");       // coloured image 1
        FILE *ci2=fopen("C:\\Users\\hp\\Desktop\\lena_color.bmp", "rb");             // coloured image 3
        switch (a)
        {
            case 1:
                read_grayscale_image(image);
                printf("\nImage has been read\n\n");
                break;
            case 2:
                readImage2 (ci1);
                printf("\nImage has been read\n\n");
                break;
            case 3:
                negative_of_Image(image);
                printf ("Negative of the image has been created\n\n");
                break;
            case 4:
                blur_grayscale(image);
                printf("The grayscale image has been blurred");
                break;
            case 5:
                brightness(image);
                printf("The brightness of the image has been enhanced by a factor of 50\n\n");
                break;
            case 6:
                rgb_2_grayscale(ci1);
                printf ("Grayscale image of RGB has been created\n\n");
                break;
            case 7:
                blurrimage(ci1);
                printf ("The coloured image has been blurred\n\n");
                break;
            case 8:
                horizontal_reflection(image);
                printf ("Horizontal Reflection is obtained\n\n");
                break;
            case 9:
                vertical_reflection(image);
                printf ("Vertical Reflection is obtained\n\n");
                break;
            case 10:
                darken(image);
                printf("The image has been darkened by a factor of 50\n\n");
                break;
            case 11:
                deviation(image);
                printf ("\n\n");
                break;
            case 12:
                metamorphosis(image);
                printf ("The final combination of the images has been generated\n\n");
                break;
            case 13:
                rotation(image);
                printf("Image has been rotated\n\n");
                break;
            case 14:
                apply_sepia_filter(ci2);
                printf("Sepia Filter applied\n\n");
                break;
            case 15:
                convert_2_BnW(image);
                printf("Black and white filter has been applied\n\n");
                break;
            case 16:
                get_detail(image);
                break;
            case 17:
                printf("Enter the co-ordinates\n");
                int r,c;
                scanf("%d %d",&r,&c);
                get_pixel_value(image,r,c);
                break;
            case 18:
                printf("Enter the co-ordinates\n");
                scanf("%d %d",&r,&c);
                int value;
                printf("\nEnter the new pixel value\n");
                scanf("%d",&value);
                set_pixel_value(image,r,c,value);
                printf("\nNew pixel value has been set\n\n");
                break;
            case 19:
                average_gray_level(image);
                break;
            case 20:
                crop_image(ci1);
                printf("Image has been cropped.\n\n");
                break;
            case 21:
                exit(1);
                break;
            default:
                printf("Invalid Input\n\n");
                exit(1);
        }
    }
    return 0;
}
