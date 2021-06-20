//ADA project 171310132055-056-057
//Analysis of Knapsack problen using different methods
/*Knapsack is a problem in which we will be given items with different weight and value and a bag with weight
limit and we have to select items for bag such that we can get maximum value from the elements selected*/

#include<iostream>
#include<bits\stdc++.h>
using namespace std;

//Function to solve the knapsack problem using 0-1 method
//In this method the items will be selected as per the value. The highest value item would be selected first.
void knap_int(int n, int w[], int v[], int max)
{
	int i,j,temp,find,tw=0, max_w=0, max_v=0,d[n];
	
	//Creating duplicate array for values of elements
	for(i=0;i<n;i++)
		d[i]=v[i];
		
	//Sorting data of duplicate array in descending order	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(d[j]<d[j+1])
			{
				temp=d[j];
				d[j]=d[j+1];
				d[j+1]=temp;
			}
		}
	}
	
	//logic to select items for bag
	i=0;
	while(max_w<=max&&i<n)
	{
		//selecting item with highest value i.e. selecting item from duplicate array which is reverse sorted
		j=0;
		find=d[i];
		
		//logic to find the index of the first element from duplicate array to original array
		while(v[j]!=find)
		{
			j++;
		}
		
		//adding weight of the element to temporary variable and checking if weight exceeds limit	
		tw+=w[j];
		if(tw<=max)
		{
			max_w+=w[j];
			max_v+=v[j];
			
			//Printing the selected items number
			cout<<"\nThe item selected is "<<j+1<<"\n";
		}
		else
		//if weight exceeds it will remove the current item and selecting next elememt
			tw-=w[j];	
		i++;
	}
	
	//Printing the final value of total available weight and value of bag
	cout<<"\nThe total value is "<<max_v;
	cout<<"\nThe total weight is "<<max_w<<"\n\n";
}

//Function to solve the knapsack problem using greedy method
//In this method items would be selected as per the ratio of the weight to value of item.
//here also element with highest ratio will be selected first
void knap_gr_int(int n, int w[], int v[], int max)
{
	int i,j,in=0, tw=0, max_w=0, max_v=0;
	float find,temp,d[n],du[n];
	
	//creating duplicate array for ratio of the weight to value
	for(i=0;i<n;i++)
		du[i]=d[i]=((float)v[i]/w[i]);
		
	//sorting the duplicate array for ratio of the weight to value in descending order
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(du[j]<du[j+1])
			{
				temp=du[j];
				du[j]=du[j+1];
				du[j+1]=temp;
			}
		}
	}
	
	//logic to select items for bag
	i=0;
	while(max_w<=max&&i<n)
	{
		
		//selecting item with highest value i.e. selecting item from duplicate array which is reverse sorted
		j=0;
		find=du[i];
		
		//logic to find the index of the first element from duplicate array to original array
		while(d[j]!=find)
		{
			j++;
		}
		
		//adding weight of the element to temporary variable and checking if weight exceeds limit
		tw+=w[j];
		if(tw<=max)
		{
			max_w+=w[j];
			max_v+=v[j];
			
			//Printing the selected items number
			cout<<"\nThe item selected is "<<j+1<<"\n";
		}
		else
		//if weight exceeds it will remove the current item and selecting next elememt
			tw-=w[j];
		i++;
	}
	
	//Printing the final value of total available weight and value of bag
	cout<<"\nThe total value is "<<max_v;
	cout<<"\nThe total weight is "<<max_w<<"\n\n";
}

//Function to solve knapsack using greedy method (fractional)
/*This method is similar to greedy integer method but if the bag could not be filled completely because of
uneven weight the bag is made to be filled with required weight and fraction that value and add it 
to final answer and bag is completely filled.*/ 
void knap_gr_fr(int n, int w[], int v[], int max)
{
	int i,j,in=0, tw=0;
	float find,temp,d[n],du[n],max_w=0, max_v=0,rem=0;
	
	//creating duplicate array for ratio of the weight to value
	for(i=0;i<n;i++)
		du[i]=d[i]=((float)v[i]/w[i]);
		
	//sorting the duplicate array for ratio of the weight to value in descending order	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(du[j]<du[j+1])
			{
				temp=du[j];
				du[j]=du[j+1];
				du[j+1]=temp;
			}
		}
	}
	
	//logic to select items for bag
	for(i=0;i<n;i++)
	{
		
		//selecting item with highest value i.e. selecting item from duplicate array which is reverse sorted
		j=0;
		find=du[i];
		
		//selecting item with highest value i.e. selecting item from duplicate array which is reverse sorted
		while(d[j]!=find)
		{
			j++;
		}
		
		//adding weight of the element to temporary variable and checking if weight exceeds limit
		tw+=w[j];
		if(tw>max)
		{
			tw-=w[j];
			break;
		}
		else
		{
			max_w+=w[j];
			max_v+=v[j];
			
			//Printing the selected items number
			cout<<"\nThe item selected is "<<j+1<<"\n";
		}
	}
	
	//remaining weight 
	rem=max-tw;
	max_w+=rem;
	
	//adding fractional value of element to the final value
	max_v+=(d[j]*rem);
	
	//Printing the final value of total available weight and value of bag
	cout<<"\nThe item selected is "<<j+1<<"\n";
	cout<<"\nThe total value is "<<max_v;
	cout<<"\nThe total weight is "<<max_w<<"\n\n";
	
}

//Function to solve knapsack using dynamic programming
/*In dynamic method all the possible solution of the problem is finded recursively and most optimal solution
is selected out of it*/
void dynamic(int W, int wt[], int val[], int n) 
{ 
    int i, w,max_w; 
    
    //Temporary array which will contain solutions
    int K[n + 1][W + 1]; 
    
    //Build table K[][] in bottom up manner and add possible solutions 
    for (i = 0; i <= n; i++) 
	{ 
        for (w = 0; w <= W; w++) 
		{ 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
                
            //if total weight is less than bag limit add next possible element
            else if (wt[i - 1] <= w) 
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]); 
            else
                K[i][w] = K[i - 1][w]; 
        } 
    } 
    
    //Printing temporary array
    for(int j=0;j<n+1;j++)
	{
		for(int l=0; l<W+1;l++)
			cout<<K[j][l]<<"\t";
		cout<<"\n";
	}
	
	//Printing the optimal solution
    int res = K[n][W];     
    cout << "Total value is " << res << endl;
    w = W; 
    for (i = n; i > 0 && res > 0; i--) 
	{            
        if (res == K[i - 1][w])  
            continue;         
        else 
		{ 
            cout << "item selected is " << i << endl;
            max_w += wt[i-1]; 
            res = res - val[i - 1]; 
            w = w - wt[i - 1]; 
        } 
    } 
    cout << " Total weight is " << max_w << endl;
} 

//Driver program for all above functions
int main()
{
	int n,ch=0;
	
	cout<<"Enter number of elements: ";
	cin>>n;
	
	//Array containing weight of available elements
	int w[n];
	
	//Array containing value of available elements
	int v[n];
	
	for(int i=0;i<n;i++)
	{
		cout<<"Enter the weight and value of item "<<i+1<<": ";
		cin>>w[i];
		cin>>v[i];
	}
	
	//Display available elements weight and value
	cout<<"\nThe weight and values are \n";
	cout<<"Weight:";
	for(int i=0;i<n;i++)
		cout<<"\t"<<w[i];
	cout<<"\nValue: ";
	for(int i=0;i<n;i++)
		cout<<"\t"<<v[i];
	
	//Variable containing maximum capacity of the bag
	int max=0;
	
	cout<<"\n\nEnter the weight capacity of bag: ";
	cin>>max;
	
	//Loop to solve knapsack with one specific method
	while(ch!=5)
	{
		cout<<"\n1. Knapsack using 0-1 method";
		cout<<"\n2. Knapsack using greedy method (Integer method)";
		cout<<"\n3. Knapsack using greedy method (Fractional method)";
		cout<<"\n4. Knapsack using dynamic method 0-1";
		cout<<"\n5. Exit\n";
		cout<<"Enter your choice: ";
		cin>>ch;
		switch(ch)
		{
			
			//Function to solve knapsack using 0-1 Method
			case 1: knap_int(n,w,v,max);
				break;
				
			//Function to solve knapsack using greedy method
			case 2: knap_gr_int(n,w,v,max);
				break;
				
			//Function to solve knapsack using greedy method (Fractional)
			case 3: knap_gr_fr(n,w,v,max);
				break;
				
			//Function to solve knapsack using dynamic method
			case 4: dynamic(max,w,v,n);
				break;
				
			case 5: break;
			
			default: cout<<"\nEnter a valid choice\n";
		}
	}
	return 0;
}
