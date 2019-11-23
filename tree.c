#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct TreeNode TreeNode;

typedef struct TreeNode
{
    int Value;
    TreeNode *Left;
    TreeNode *Right;
}TreeNode;

TreeNode *CreateNode(int value)
{
    TreeNode *newNode = malloc(sizeof(TreeNode));
    newNode->Left = NULL;
    newNode->Right = NULL;
    newNode->Value = value;
    return newNode;
}

TreeNode *SearchForNodePosition(TreeNode *rootNode, int value)
{
    //Returns the last node for the given value
    TreeNode *currentNode = rootNode;
    int found = 0;
    while (!found)
    {
        if (currentNode->Value > value)
        {
            if (currentNode->Left != NULL)
            {
                currentNode = currentNode->Left;
            }
            else
            {
                found = 1;
                return currentNode;
            }    
        }
        else
        {
            if (currentNode->Right != NULL)
            {
                currentNode = currentNode->Right;
            }
            else
            {
                found = 1;
                return currentNode;
            }
        } 
    }
}

void AssignNodeToTree(TreeNode *rootNode, TreeNode *newNode)
{
    TreeNode *parentNode = SearchForNodePosition(rootNode, newNode->Value);
    if (parentNode->Value > newNode->Value)
    {
        parentNode->Left = newNode;
    }
    else
    {
        parentNode->Right = newNode;  
    }  
}

void PrintInOrder(TreeNode *rootNode)
{
    if (rootNode->Left != NULL)
    {
        PrintInOrder(rootNode->Left);
    }
    printf("%d\n", rootNode->Value);
    if (rootNode->Right != NULL)
    {
        PrintInOrder(rootNode->Right);
    } 
}

void PrintPreOrder(TreeNode *rootNode)
{
    printf("%d\n", rootNode->Value);
    if (rootNode->Left != NULL)
    {
        PrintPreOrder(rootNode->Left);
    }
    if (rootNode->Right != NULL)
    {
        PrintPreOrder(rootNode->Right);
    } 
}

void PrintPostOrder(TreeNode *rootNode)
{
    if (rootNode->Left != NULL)
    {
        PrintPostOrder(rootNode->Left);
    }
    if (rootNode->Right != NULL)
    {
        PrintPostOrder(rootNode->Right);
    }
    printf("%d\n", rootNode->Value);
}

void GetElementsInTree(TreeNode *rootNode, int *numberOfElements)
{
    if (rootNode->Left != NULL)
    {
        GetElementsInTree(rootNode->Left, numberOfElements);
    }
    (*numberOfElements)++;
    if (rootNode->Right != NULL)
    {
        GetElementsInTree(rootNode->Right, numberOfElements);
    } 
    
}


int CalculateSubTreeHeight(TreeNode *rootNode, int goRight)
{
    //if goRight is 1 then right subtree, else left subtree
    int lengthOfTree = 0;

    if (goRight)
    {
        if (rootNode->Right != NULL)
        {
            GetElementsInTree(rootNode->Right, &lengthOfTree);
        }
    }
    else
    {
        if (rootNode->Left != NULL)
        {
            GetElementsInTree(rootNode->Left, &lengthOfTree);
        }
    }
    return lengthOfTree;
}

int TreeIsImbalanced(TreeNode *rootNode)
{
    //If tree heights differ by more than 1 then it's imbalanced
    int lengthOfRight = CalculateSubTreeHeight(rootNode, 1);
    int lengthOfLeft = CalculateSubTreeHeight(rootNode, 0);
    if (lengthOfRight - lengthOfLeft < -1 || lengthOfRight - lengthOfLeft > 1)
    {
       return 1;
    }
    return 0;
}


void AddTreeElementsToArray(TreeNode *rootNode, int treeArray[], int *currentIndex)
{
    if (rootNode->Left != NULL)
    {
        AddTreeElementsToArray(rootNode->Left, treeArray, currentIndex);
    }
    treeArray[*currentIndex] = rootNode->Value;
    (*currentIndex)++;
    if (rootNode->Right != NULL)
    {
        AddTreeElementsToArray(rootNode->Right, treeArray, currentIndex);
    } 
}

void FreeTree(TreeNode *rootNode)
{
    if (rootNode->Left != NULL)
    {
        FreeTree(rootNode->Left);
    }
    if (rootNode->Right != NULL)
    {
        FreeTree(rootNode->Right);
    }
    free(rootNode);
}

int *CreateTreeArray(TreeNode *rootNode)
{
    int elementsInTree = 0;
    int currentIndex = 0;
    GetElementsInTree(rootNode, &elementsInTree);
    int *treeArray = malloc(sizeof(int) *elementsInTree);
    AddTreeElementsToArray(rootNode, treeArray, &currentIndex);
    
    return treeArray;
}

TreeNode *BalanceTree(TreeNode *rootNode)
{
    int *treeArray = CreateTreeArray(rootNode);
    int lengthOfArray = 0;
    GetElementsInTree(rootNode, &lengthOfArray);
    TreeNode *newRoot = CreateNode(treeArray[lengthOfArray/2]);
    for (int i = 0; i < lengthOfArray; i++)
    {
        if (i != lengthOfArray/2)
        {
            TreeNode *newNode = CreateNode(treeArray[i]);
            AssignNodeToTree(newRoot, newNode);
        } 
    }
    free(treeArray);
    return newRoot;
}

int main()
{
    int input;
    printf("Enter the node value: ");
    scanf("%d", &input);
    TreeNode *rootNode = CreateNode(input);
    do
    {
        printf("Enter the node value: ");
        scanf("%d", &input);
        if (input != -1)
        {
            AssignNodeToTree(rootNode, CreateNode(input));
        }
        
    }while (input != -1);
    if (TreeIsImbalanced(rootNode))
    {
        rootNode = BalanceTree(rootNode);
    }
    PrintInOrder(rootNode);
    printf("New Root: %d\n", rootNode->Value);
}