#include<stdio.h>
#include<stdlib.h>
/*
Code Created on 26th Jan 2020 in freetime.
Author:Vivek.M.R,Just completed 3rd SEM in information science engineering at BIT(Bangalore Institue of Technology).
This code solves a sudoku.




9 x 9  matrix 'a' is the input as an unsolved sudoku.
Input can either be given here in the code itself or during run-time.
Enter 0 for blank boxes and values for the rest.
*/


int a[9][9]={
		{0,0,2,0,0,0,1,0,9},
		{1,8,4,0,0,0,0,0,0},
		{6,0,3,0,0,2,0,7,8},
		{4,0,8,0,5,0,0,3,1},
		{0,0,0,7,0,1,0,0,0},
		{0,1,0,0,8,0,5,0,6},
		{9,3,0,8,0,0,6,0,7},
		{0,0,0,0,0,0,2,9,5},
		{2,0,6,0,0,0,8,0,0}
	};
	
//Matrix v is a sparse matrix that keeps track of the constant values of the original input.This helps in Backtracking.//
int v[9][9]={0};

//valid function checks if a number 'i' is valid to be filled at a position a[m][n].//
int valid(int m,int n,int i)
{ int c,k;
	for(c=0;c<9;c++)
	{ 
        if((a[m][c]==i)||(a[c][n]==i))
		return 0;
	};//checking for repetitions in the same row & column//
	for(c=(m/3)*3;c<=(m/3)*3+2;c++)
	for(k=(n/3)*3;k<=(n/3)*3+2;k++)
	if(a[c][k]==i)
	return 0;//checking for repetitions in the mini 3x3 box//
	return 1;
}

//dis function displays the matrix(or)sudoku//
void dis()
{   int i,j,c;
 	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%d  ",a[i][j]);if((j==2)||(j==5))printf("|  ");
		};
		printf("\n");
		if((i==2)||(i==5))
		{
			for(c=0;c<33;c++)
				printf("-");
			printf("\n");
		};
	};
	printf("\n\n\n");
}

//solve function is the main logic function.It fills in the correct values and eliminates '0's in the sudoku.Uses Backtracking.

void solve()
{
	int c,i,j=0;//variables for loops//
	int y;//variable that indicates when backtracking is required.//
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(a[i][j]!=0)
			  v[i][j]=1;
		};
	};i=0;j=0;//initialising the sparse matrix 'v' and other loop variables//
	while(i<9)
	{
	    y=1;
		if(v[i][j]==0)//Non-Constant values or 0's in the original matrix//
		{
			for(c=a[i][j]+1;c<10;c++)//iterating values of c from the original value of a[i][j] to 9//
			{
				if(valid(i,j,c))//checking for validity of c at a[m][n]//
				{
					y=0;
                    a[i][j]=c;//assigning c to a[i][j]//
					if(j==8)//incrementing i,j
					{
						j=0;
						 i++;
					    }else 
					    j++;
					    break;//A value has been filled.So,No Backtracking is required//
					};
					y=1;//value isn't valid.Backtracking may be required,so changing y to 1//
				};
			if(y)//Backtracking to the previous filled position
			{   a[i][j]=0;//changing the assigned value of a[i][j] to 0 since it is wrong.//
				y=0;//changing the backtracking flag value to 0,since backtracking is being acknowledged and executed//
			    do
				{
					if(j==0)
					{
						i--;
						j=8;
					}
					else
					j--;
				}while((v[i][j])!=0);//backtracking//
			};
		}else
		if(j==8)//incrementing values of i,j in the while loop after reaching constant positions or non 0 values in the original matrix//
		{
			j=0;
			i++;
		}else j++;
	};
}//MAIN FUNCTION//
void main()
{
	int q,w,p;
	printf("Would you like to give external output?\n1.Yes\n2.No\nEnter you choice :\n");
	scanf("%d",&p);
	if(p==1)
	for(q=0;q<9;q++)
		for(w=0;w<9;w++)
			scanf("%d",&a[q][w]);//Taking External Output for solving//
	else printf("Solving the internal input...\n");
    //Calling Functions//
	solve();
	printf("SOLVED SUDOKU :\n\n");
	dis();
}