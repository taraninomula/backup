#include<stdio.h>
int main() 
{
    int N;
    scanf("%d",&N);
    int h[N];
    
    for(int i=0;i<N;i++){
        scanf("%d",&h[i]);}
    
    int prev,next,s,max=0;
    for(int i=0;i<N;i++)
    {
        s=h[i];
        
        prev=i-1;
        while(prev>=0 && h[prev]>=h[i]){
            s+=h[i];
            prev--;
        }
        
        next=i+1;
        while(next<N && h[next]>=h[i]){
            s+=h[i];
            next++;
        }
        
        if(s>max)
            max=s;
    }
    
    printf("%d\n",max);
    return 0;
}

