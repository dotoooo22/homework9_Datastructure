

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

void inorderTraversal(Node* ptr);	  // ������ȸ�ϸ鼭 ���
void preorderTraversal(Node* ptr);    // ������ȸ�ϸ鼭 ���
void postorderTraversal(Node* ptr);	  //������ȸ
int insert(Node* head, int key);  //������

int freeBST(Node* head); //���޸𸮻���
Node* searchRecursive(Node* ptr, int key);  	//��ͷ� ã��
Node* searchIterative(Node* head, int key);  //��;ƴѰɷ�ã��

int deleteLeafNode(Node* head, int key);  // ������
int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;
	printf("[----- [������] [2021041021] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	if(*h != NULL)		//Ʈ���� ��������� �޸� ����
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node));		//����� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);	//���ʳ����� ���� 
		printf(" [%d] ", ptr->key);		//Ű����ϰ�
		inorderTraversal(ptr->right);	//�����ʰ���
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);	//Ű����ϰ�
		preorderTraversal(ptr->left);	//�������� ����
		preorderTraversal(ptr->right);	//���������� �ö����
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {	
		postorderTraversal(ptr->left);		//���ʳ���������
		postorderTraversal(ptr->right);		//�����ʵ� ��
		printf(" [%d] ", ptr->key);		//���
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));		//��带 �ϳ� �Ҵ�ް�
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {	//ù��° ���ʺ�������� ���ʿ� �ֱ�
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;

	Node* parentNode = NULL;	//�θ���	

	while(ptr != NULL) {	//�������

		if(ptr->key == key) return 1;	//key�� �̹� ������ �׳� ����

		parentNode = ptr;	//�θ� ptr���ְ�

		if(ptr->key < key)	//�θ�Ű���� ũ�� ���������� �ƴϸ� �������� �̵�
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if(parentNode->key > key)		//�θ��庸�� ������ ���� �ƴϸ� �����ʿ� ����
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);		//���ʵ��� �� ����
		freeNode(ptr->right);		//�����ʵ��� �� ����
		free(ptr);		//ptr����
	}
}

int freeBST(Node* head)
{

	if(head->left == head)	//��常������ ��常 �����ϰ� ����
	{
		free(head);
		return 1;
	}

	Node* p = head->left;	//���ʳְ�

	freeNode(p);	//p�������

	free(head);	//�������
	return 1;
}
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {	//�ƹ��͵���� �����ҰԾ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {	//��常�־ �����ҰԾ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;	//ptr�� ù��°���


	Node* parentNode = head;	//�θ� ���

	while(ptr != NULL) {

		if(ptr->key == key) {	//Ű��ã����
			if(ptr->left == NULL && ptr->right == NULL) {		//���ʿ����� �Ѵ� ���̸�

				if(parentNode == head)	//�θ� ���� ����(ù��°��) ��
					head->left = NULL;

				if(parentNode->left == ptr)	//�θ��� ������ ptr�̸� ������ ����
					parentNode->left = NULL;	
				else						//�ƴϸ� �������� ����
					parentNode->right = NULL;

				free(ptr);	//ptr�޸�����
			}
			else {		//key�� �߰��� �־ leaf�� �ƴ�
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}


		parentNode = ptr;		//�θ� ptr��

		
		if(ptr->key < key)		//ã��Ű�� ������Ű���� ũ����������� �ƴϸ� �������� �̵�
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}
	//Ű��ã��
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)	//ptr���̸� �� ����
		return NULL;

	if(ptr->key < key)	//ã�� Ű�� �� ũ�� ������ �� ȣ��
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	return ptr;//������ũ���� ������(������)����

}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;	//ptr�� ù���ֱ�

	while(ptr != NULL)		//������
	{
		if(ptr->key == key)	//Ű�� ���� ��� ����
			return ptr;

		if(ptr->key < key)	//ã�� Ű�� �� ũ�� ptr �� ������ �ְ� �ƴϸ� ������ ����
			ptr = ptr->right;	
		else
			ptr = ptr->left;
	}

	return NULL;		//��ã���� NULL����
}