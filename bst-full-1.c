

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

void inorderTraversal(Node* ptr);	  // 중위순회하면서 출력
void preorderTraversal(Node* ptr);    // 전위순회하면서 출력
void postorderTraversal(Node* ptr);	  //후위순회
int insert(Node* head, int key);  //노드삽입

int freeBST(Node* head); //모든메모리삭제
Node* searchRecursive(Node* ptr, int key);  	//재귀로 찾기
Node* searchIterative(Node* head, int key);  //재귀아닌걸로찾기

int deleteLeafNode(Node* head, int key);  // 노드삭제
int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;

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

	if(*h != NULL)		//트리가 비어있으면 메모리 해제
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node));		//헤드노드 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);	//왼쪽끝까지 가서 
		printf(" [%d] ", ptr->key);		//키출력하고
		inorderTraversal(ptr->right);	//오른쪽가고
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);	//키출력하고
		preorderTraversal(ptr->left);	//왼쪽으로 계쏙들어감
		preorderTraversal(ptr->right);	//오른쪽으로 올라오기
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {	
		postorderTraversal(ptr->left);		//왼쪽끝가지가서
		postorderTraversal(ptr->right);		//오른쪽도 들어가
		printf(" [%d] ", ptr->key);		//출력
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));		//노드를 하나 할당받고
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {	//첫번째 왼쪽비어있으면 왼쪽에 넣기
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;

	Node* parentNode = NULL;	//부모노드	

	while(ptr != NULL) {	//빈곳까지

		if(ptr->key == key) return 1;	//key가 이미 있으면 그냥 리턴

		parentNode = ptr;	//부모에 ptr을넣고

		if(ptr->key < key)	//부모키보다 크면 오른쪽으로 아니면 왼쪽으로 이동
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if(parentNode->key > key)		//부모노드보다 작으면 왼쪽 아니면 오른쪽에 삽입
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);		//왼쪽들어가서 다 해제
		freeNode(ptr->right);		//오른쪽들어가서 다 해제
		free(ptr);		//ptr해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head)	//헤드만있으면 헤드만 해제하고 리턴
	{
		free(head);
		return 1;
	}

	Node* p = head->left;	//왼쪽넣고

	freeNode(p);	//p노드해제

	free(head);	//헤드해제
	return 1;
}
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {	//아무것도없어서 삭제할게없음
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {	//헤드만있어서 삭제할게없음
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;	//ptr에 첫번째노드


	Node* parentNode = head;	//부모에 헤드

	while(ptr != NULL) {

		if(ptr->key == key) {	//키값찾으면
			if(ptr->left == NULL && ptr->right == NULL) {		//왼쪽오른쪽 둘다 널이면

				if(parentNode == head)	//부모가 헤드면 왼쪽(첫번째거) 널
					head->left = NULL;

				if(parentNode->left == ptr)	//부모의 왼쪽이 ptr이면 왼쪽을 끊고
					parentNode->left = NULL;	
				else						//아니면 오른쪽을 끊기
					parentNode->right = NULL;

				free(ptr);	//ptr메모리해제
			}
			else {		//key가 중간에 있어서 leaf가 아님
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}


		parentNode = ptr;		//부모를 ptr로

		
		if(ptr->key < key)		//찾는키가 현재노드키보다 크면오른쪽으로 아니면 왼쪽으로 이동
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}
	//키못찾음
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	

}
Node* searchIterative(Node* head, int key)
{
	
}