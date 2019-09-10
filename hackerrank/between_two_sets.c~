int main(){
    int n,i,min,max,j,c=0,f; 
    int m; 
    scanf("%d %d",&n,&m);
    int *a = malloc(sizeof(int) * n);
    for(int a_i = 0; a_i < n; a_i++){
       scanf("%d",&a[a_i]);
    }
    int *b = malloc(sizeof(int) * m);
    for(int b_i = 0; b_i < m; b_i++){
       scanf("%d",&b[b_i]);
    }
    max=a[0];
    for(i=0;i<n;i++)
        {
        if(a[i]>max)
            max=a[i];
    }
    min=b[0];
    for(i=0;i<m;i++)
        {
        if(b[i]<min)
            min=b[i];
    }
    for(i=max;i<=min;i++)
        {
        f=0;
        for(j=0;j<n;j++)
            {
            if(i%a[j]!=0)
                {
                f=1;
                break;
            }
        }
        if(f==0)
            {
            for(j=0;j<m;j++)
                {
                if(b[j]%i!=0)
                    {
                    f=1;
                    break;
                }
            }
        }
        if(f==0)
            c++;
    }
    printf("%d",c);
    return 0;
}
