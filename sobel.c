/*
Dan Lott
Assignment 1
Robot Vision 
Fall 2016
*/


#include <stdio.h>                          /* Sobel.c */
#include <stdlib.h>
#include <math.h>

        int pic[256][256];
        int outpicx[256][256];
        int outpicy[256][256];
        int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
        int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
        double ival[256][256],maxival;

main(argc,argv)
int argc;
char **argv;
{
        int i,j,p,q,mr,sum1,sum2;
        double loThreshold=0, hiThreshold=0;
        FILE *fo1, *fo2, *fo3, *fp1, *fopen();
        char *foobar;
		//input file name
        argc--; argv++;
        foobar = *argv;
        fp1=fopen(foobar,"rb");
	//output file name mag
	argc--; argv++;
	foobar = *argv;
	fo1=fopen(foobar,"wb");
	//output file name lo
	argc--; argv++;
	foobar = *argv;
	fo2=fopen(foobar,"wb");
	//output file name hi
	argc--; argv++;
	foobar = *argv;
	fo3=fopen(foobar,"wb");
        
	//lower threshold
    argc--; argv++;
	foobar = *argv;
	loThreshold = atof(foobar);//not working will fix
	//higher threshold
	argc--; argv++;
	foobar = *argv;
	hiThreshold = atof(foobar);//not working will fix
	
	
	loThreshold=50;//placeholder thresholds
	hiThreshold=150;
	
	
	
	

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
                {
                  pic[i][j]  =  getc (fp1);
                  pic[i][j]  &= 0377;
                }
        }

        mr = 1;
        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
             sum1 = 0;
             sum2 = 0;
             for (p=-mr;p<=mr;p++)
             {
                for (q=-mr;q<=mr;q++)
                {
                   sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
                   sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
                }
             }
             outpicx[i][j] = sum1;
             outpicy[i][j] = sum2;
          }
        }

        maxival = 0;
		
        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
             ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
                                      (outpicy[i][j]*outpicy[i][j])));
             if (ival[i][j] > maxival){
                maxival = ival[i][j];
			
			 }

           }
        }
		

			fprintf(fo1,"P5\n256 256\n255\n");
			fprintf(fo2,"P5\n256 256\n255\n");
			fprintf(fo3,"P5\n256 256\n255\n");
        for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
             ival[i][j] = (ival[i][j] / maxival) * 255;            
             fprintf(fo1,"%c",(char)((int)(ival[i][j])));
             
            }
          }
		  
		  
		  for (i=0;i<256;i++){
           for (j=0;j<256;j++){
            
				
            if(ival[i][j]>loThreshold){
				 fprintf(fo2, "%c", 255);
			}
            else{
				fprintf(fo2, "%c", 0);
			}
			if(ival[i][j]>hiThreshold){
				fprintf(fo3, "%c", 255);
			}
			else{
				fprintf(fo3, "%c", 0);
			}
			
            }
          }

}
