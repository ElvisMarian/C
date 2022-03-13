#define MAX 100

typedef struct node {
	char data[MAX];
	struct node *next;
} stack;
	//operatia de pus in stiva
stack *push(stack *head, char *data)
{
	stack *tmp = (stack *)malloc(sizeof(stack));

	strcpy(tmp->data, data);
	tmp->next = head;
	head = tmp;
	return head;
}
	//operatia de scos din stiva
stack *pop(stack **head)
{
	stack *tmp = *head;
	*head = (*head)->next;
	free(tmp);
	return *head;
}
	//testez daca stiva e goala
int empty(stack *head)
{
	return head == NULL;
}
void stack_free(stack **stack_command)
{
	while (!empty(*stack_command))
		*stack_command = pop(stack_command);
}
