struct test {
	int a;
	char b;
};

main ()
{

//struct test xyz;
struct test abc = {10,'A'};
struct test *ptr;
ptr = &abc; 
//xyz.a = 4;
printf ("abc.a:%d abc.b:%c\n",abc.a,abc.b);
printf ("abc.a:%d abc.b:%c\n",ptr->a,ptr->b);
}








