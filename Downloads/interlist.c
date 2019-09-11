/*merge two linked lists and find intersection point */
#include<stdio.h>
#include<stdlib.h>
struct stu
{
	int data;
	struct stu *next;
};
void traversal(struct stu *p);
struct stu * create(struct stu *head);
struct stu * findintersection (struct stu *head1,struct stu *head2);
void createintersection(struct stu* head1,struct stu* head2);
int lenth,pos;
void test(int lenth1,int lenth2,int pos1);
main()
{
	int i;
	printf("enter ur testcase 1.intersect at 1st node 2.list1 is empty 3.position is graterthan lenthof list1 4.list2 empty 5.intersect at last node 6.intersect at middle 7.both lists are empty 8.position is 0 9.all 0's 10.lenth1>lenth2\n");
	scanf("%d",&i);
	switch(i)
	{
		case 1:test(5,3,1);
		       break;
		case 2:test(0,3,1);
		       break;
		case 3:test(2,3,3);
		       break;
		case 4:test(3,0,1);
		       break;
		case 5:test(3,2,3);
		       break;
		case 6:test(4,2,2);
		       break;
		case 7:test(0,0,1);
		       break;
		case 8:test(2,3,0);
		       break;
		case 9:test(0,0,0);
		       break;
		case 10:test(1,5,1);
			break;
	}
}
struct stu * create(struct stu *head)
{
	struct stu *ltemp=NULL,*p=NULL;
	while(lenth)
	{
		ltemp=(struct stu *)malloc(sizeof(struct stu));
		printf("enter data\n");
		scanf("%d",&(ltemp->data));
		ltemp->next=NULL;
		if(head==NULL)
		{
			head=ltemp;
			p=head;
		}
		else
		{
			p->next=ltemp;
			p=p->next;			
		}
		lenth--;
	}
	return head;
}
	void traversal(struct stu *p)
{if(p==NULL)
	printf("list is empty\n");
	else
	{
		while(p!=NULL)
		{
			printf("%d\n",p->data);
			p=p->next;
		}
	}
}
void createintersection(struct stu* head1,struct stu* head2)
{int i=1,n;
	if((head1==NULL)||(head2==NULL))
		printf("intersection is not possible\n");
	else{
		while((i!=pos)&&(head1->next!=NULL))
		{
			head1=head1->next;
			i++;
		}
		if(i!=pos)
			printf("intersection is not possible\n");
		else
		{
			while(head2->next!=NULL)
				head2=head2->next;
			head2->next=head1;
		}
	}
}
struct stu * findintersection (struct stu *head1,struct stu *head2)
{
	struct stu *temp2=head2,*temp1=head1;
	if(temp2==NULL)
		return temp2;
	else{
		while((temp1!=NULL))
		{
			temp2=head2;
			while((temp2!=temp1)&&(temp2!=NULL))
			{
				temp2=temp2->next;
			}
			if(temp2==temp1)
				break;
			else
				temp1=temp1->next;
		}
		return temp1;
	}
}
void test(int lenth1,int lenth2,int pos1)
{
	struct stu *head1=NULL,*head2=NULL,*temp1=NULL;
	lenth=lenth1;
	head1=create(head1);
	lenth=lenth2;
	head2=create(head2);
	pos=pos1;
	createintersection(head1,head2);
	printf("list1 afterintersection elements\n");
	traversal(head1);
	printf("list2 afterintersection elements\n");
	traversal(head2);
	temp1=findintersection(head1,head2);
	if(temp1)
		printf("node =%d\n",temp1->data);
	else
		printf("lists are not merged\n");
}
