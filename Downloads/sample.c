#include <stdio.h>
#include <malloc.h>
int main()
{
  freopen("/home/ashwini/input.txt","r", stdin);
  int T;
  scanf("%d",&T);
  while(T--){
  int N, sum = 0;
  scanf("%d", &N);
  int *arr = (int *)malloc(sizeof(int*)*N);
  for(int i=0;i<N;i++)
    scanf("%d",&arr[i]);
  for(int i=0;i<N;i++)
    sum+= arr[i];

  printf("T: %d->%d\n",T, sum);
  }
  return 0;
}
