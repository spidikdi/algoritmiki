
#include <stdio.h>
#include <stdlib.h>

//========================= STRUCTURES =========================

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;             // <-- обязательное поле для АВЛ
};

struct Trunk {
    struct Trunk* prev;
    char* str;
};

//========================= PRINT TREE =========================

void showTrunks(struct Trunk* p) {
    if (!p) return;
    showTrunks(p->prev);
    printf("%s", p->str);
}

void printTree(struct Node* root, struct Trunk* prev, int isLeft) {
    if (!root) return;

    char* prev_str = "     ";
    struct Trunk* trunk = (struct Trunk*)malloc(sizeof(struct Trunk));
    trunk->prev = prev;
    trunk->str = prev_str;

    printTree(root->right, trunk, 1);

    if (!prev)
        trunk->str = "-----";
    else if (isLeft) {
        trunk->str = ".----";
        prev_str = "    |";
    } else {
        trunk->str = "`----";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    printf(" %d\n", root->key);

    if (prev) prev->str = prev_str;
    trunk->str = "    |";

    printTree(root->left, trunk, 0);
    free(trunk);
}

//========================= AVL HELPERS =========================

// высота NULL = 0
int getHeight(struct Node* n) {
    return n ? n->height : 0;
}

int getBalance(struct Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// пересчёт высоты узла
void updateHeight(struct Node* n) {
    int hl = getHeight(n->left);
    int hr = getHeight(n->right);
    n->height = (hl > hr ? hl : hr) + 1;
}

//========================= ROTATIONS =========================

// Правый поворот (LL-case)
struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левый поворот (RR-case)
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T = y->left;

    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}

//========================= AVL INSERT =========================

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) {
        struct Node* n = malloc(sizeof(struct Node));
        n->key = key;
        n->left = n->right = NULL;
        n->height = 1;
        return n;
    }

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;   // дубликаты игнорируем

    // обновляем высоту
    updateHeight(node);

    // считаем баланс
    int bal = getBalance(node);

    //----- 4 случая -----
    // LL
    if (bal > 1 && key < node->left->key)
        return rotateRight(node);

    // RR
    if (bal < -1 && key > node->right->key)
        return rotateLeft(node);

    // LR
    if (bal > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // RL
    if (bal < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//========================= HEIGHT FOR PRINT =========================

int height(struct Node* n) {
    return n ? n->height : 0;
}

//========================= PRINT UNBALANCED NODES =========================

void printUnbalancedNodes(struct Node* r) {
    if (!r) return;

    int hl = height(r->left);
    int hr = height(r->right);

    if (hl != hr)
        printf("Вершина %d: L=%d, R=%d\n", r->key, hl, hr);

    printUnbalancedNodes(r->left);
    printUnbalancedNodes(r->right);
}

//========================= FREE TREE =========================

void freeTree(struct Node* r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

//========================= MAIN =========================

int main() {
    struct Node* root = NULL;

    FILE* f = fopen("input.txt", "r");
    if (!f) {
        printf("Ошибка: нет input.txt\n");
        return 1;
    }
    int key;
    while (fscanf(f, "%d", &key) == 1)
        root = insert(root, key);
    fclose(f);

    printf("AVL-дерево:\n");
    printTree(root, NULL, 0);

    printf("\nВершины с разными высотами поддеревьев:\n");
    printUnbalancedNodes(root);

    freeTree(root);
    return 0;
}