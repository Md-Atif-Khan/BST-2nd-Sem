#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int val;
    struct tree *left;
    struct tree *right;
};

struct tree *create_node(int n)
{
    struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
    temp->val = n;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct tree *insert(struct tree *root, int n)
{
    if (root == NULL)
        return create_node(n);
    else if (n > root->val)
        root->right = insert(root->right, n);
    else if (n < root->val)
        root->left = insert(root->left, n);
    else
    {
        printf("Similar element is already present in the tree\n");
        return root;
    }
}

void search(struct tree *root, int n)
{
    if (root == NULL)
        printf("Given element doesn't exist\n");
    else if (root->val == n)
        printf("Given element exist\n");
    else if (root->val < n)
        search(root->right, n);
    else
        search(root->left, n);
    return;
}

int maximum_element(struct tree *root)
{
    if (root->right == NULL)
        return root->val;
    else
        return maximum_element(root->right);
}

int minimum_element(struct tree *root)
{
    if (root->left == NULL)
        return root->val;
    else
        return minimum_element(root->left);
}

int total_nodes(struct tree *root)
{
    if (root == NULL)
        return 0;
    else
        return (total_nodes(root->left) + total_nodes(root->right) + 1);
}

int total_leaf_nodes(struct tree *root)
{
    if (root == NULL)
        return 0;
    else if (root->left == NULL && root->right == NULL)
        return 1;
    else
        return (total_leaf_nodes(root->left) + total_leaf_nodes(root->right));
}

int total_internal_nodes(struct tree *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    else
        return (total_internal_nodes(root->left) + total_internal_nodes(root->right) + 1);
}

int tree_height(struct tree *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int left_height, right_height;
        left_height = tree_height(root->left);
        right_height = tree_height(root->right);
        if (left_height > right_height)
            return (left_height + 1);
        else
            return (right_height + 1);
    }
}
// // DOUBT--> DELETE NODE FUNCTION IS NOT WORKING WHEN MIRRORED
struct tree *mirror_tree(struct tree *root)
{
    struct tree *temp; // here, root->left is a pointer, hence we used a pointer of same type
    if (root != NULL)
    {
        mirror_tree(root->left);
        mirror_tree(root->right);
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

struct tree *inorder_predecessor(struct tree *root)
{
    if (root == NULL || root->right == NULL)
        return root;
    else
        return inorder_predecessor(root->right);
}

struct tree *inorder_sucessor(struct tree *root)
{
    if (root == NULL || root->left == NULL)
        return root;
    else
        return inorder_sucessor(root->left);
}

struct tree *delete_node(struct tree *root, int n)
{
    if (root == NULL)
    {
        printf("Given element doesn't exist\n");
        return root;
    }
    else if (n < root->val)
        root->left = delete_node(root->left, n);
    else if (n > root->val)
        root->right = delete_node(root->right, n);
    // ROOT TO BE DELETED IS FOUND AND NONE OF ITS CHILDREN ARE NULL
    else if (root->left != NULL && root->right != NULL)
    {
        // *****DELETING BY THE PROCESS OF INORDER PREDECESSOR*****
        // struct tree *temp = inorder_predecessor(root->left);
        // root->val = temp->val;
        // root->left = delete_node(root->left, root->val);
        // return root;

        // *****DELETING BY THE PROCESS OF INORDER SUCESSOR*****
        struct tree *temp = inorder_sucessor(root->right);
        root->val = temp->val;
        root->right = delete_node(root->right, root->val);
    }
    // ROOT TO BE DELETED IS FOUND AND EITHER ONE OR BOTH OF ITS CHILDREN ARE NULL
    else if (root->left == NULL)
    {
        struct tree *temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL)
    {
        struct tree *temp = root->left;
        free(root);
        return temp;
    }
    return root;
}

//*****DOUBT******
struct tree *delete_tree(struct tree *root)
{
    if (root != NULL)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

void preorder_display(struct tree *root)
{
    if (root != NULL)
    {
        printf("%d ", root->val);
        preorder_display(root->left);
        preorder_display(root->right);
    }
}

void inorder_display(struct tree *root)
{
    if (root != NULL)
    {
        inorder_display(root->left);
        printf("%d ", root->val);
        inorder_display(root->right);
    }
}

void postorder_display(struct tree *root)
{
    if (root != NULL)
    {
        postorder_display(root->left);
        postorder_display(root->right);
        printf("%d ", root->val);
    }
}

int main()
{
    struct tree *root = NULL;
    int n, choice;
    while (1)
    {
        printf("***MENU***\n");
        printf("1-Insert a element\n");
        printf("2-Check if element exist\n");
        printf("3-Delete a node\n");
        printf("4-Preorder Display\n");
        printf("5-Inorder Display\n");
        printf("6-Postorder Display\n");
        printf("7-Display Minimum element\n");
        printf("8-Display Maximum element\n");
        printf("9-Count total nodes\n");
        printf("10-Count total leaf/external nodes\n");
        printf("11-Count total internal nodes\n");
        printf("12-Height of tree\n");
        printf("13-Mirror the tree\n");
        printf("14-Delete whole tree\n");
        printf("15-Exit\n");
        printf("Choose from above option\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the value to be inserted in the BST\n");
            scanf("%d", &n);
            if (root == NULL)
                root = create_node(n);
            else
                root = insert(root, n);
            break;

        case 2:
            if (root == NULL)
                printf("No elements present\n");
            else
            {
                printf("Enter the element to be searched\n");
                scanf("%d", &n);
                search(root, n);
            }
            break;

        case 3:
            printf("Enter the element to be deleted\n");
            scanf("%d", &n);
            root = delete_node(root, n);
            break;

        case 4:
            if (root == NULL)
                printf("No elements present\n");
            else
            {
                preorder_display(root);
                printf("\n");
            }
            break;

        case 5:
            if (root == NULL)
                printf("No elements present\n");
            else
            {
                inorder_display(root);
                printf("\n");
            }
            break;

        case 6:
            if (root == NULL)
                printf("No elements present\n");
            else
            {
                postorder_display(root);
                printf("\n");
            }
            break;

        case 7:
            if (root == NULL)
                printf("No elements present\n");
            else
            {
                printf("Minimum element in BST is %d\n", minimum_element(root));
            }
            break;

        case 8:
            if (root == NULL)
                printf("No elements present\n");
            else
            {
                printf("Maximum element in BST is %d\n", maximum_element(root));
            }
            break;

        case 9:
            printf("Total no. of nodes: %d\n", total_nodes(root));
            break;

        case 10:
            printf("Total no. of leaf/external nodes: %d\n", total_leaf_nodes(root));
            break;

        case 11:
            printf("Total no. of internal nodes: %d\n", total_internal_nodes(root));
            break;

        case 12:
            printf("Height of BST is %d\n", tree_height(root));
            break;

        case 13:
            root = mirror_tree(root);
            break;

        case 14:
            root = delete_tree(root);
            break;

        case 15:
            exit(0);
            break;

        default:
            printf("Choose a correct option\n");
            break;
        }
    }
}