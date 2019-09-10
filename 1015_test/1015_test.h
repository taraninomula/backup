typedef struct node
{
	int data;
	struct node *ptr_next;
	struct node *ptr_next_next;
}node;
struct node* createnode();
void print_LL(node *root);
void swap_node(node *ptr);
void insert_node(node *ptr);
void delete_node(node *ptr);

