#include "structure.h"
#include <sys/time.h>
#include <sys/resource.h>


void test() {
    // printf("%li", result);
    int a = 1000;
    int b = 200;
    TREE *tree = createTree();
    TREE *tree2 = createTree();
    TREE *tree3 = createTree();
    TREE *tree4 = createTree();
    TREE *tree5 = createTree();
    treeMax(NULL);
    treeMin(NULL);
    treeMax(tree->root);
    treeMin(tree->root);


    I *iterator31 = createIterator(tree3);
    NODE *dnode = getNode(tree3, 1);
    treeMax(tree3->root);
    treeMin(tree3->root);
    treeMax(tree3->root);
    treeMin(tree3->root);
    I *iterator32 = createIterator(tree3);

    deleteNode(tree3, &dnode);
    free(iterator31);
    free(iterator32);
    free(tree3);
    srand(time(NULL));//temporary

    for (int i = 0; i < a; i++) {
        if (!addNode(tree, rand() % (b + 1 - 1) + 1)) {
            createTree();
            continue;
        }
        if (!addNode(tree2, i))
            continue;
        if (!addNode(tree4, i))
            continue;
        if (!addNode(tree5, i))
            continue;
    }
    for (int k = 0; k < b; k++) {
        getNode(tree, k);
        getNode(tree2, k);
        getNode(tree4, k);

    }
    I *iterator = createIterator(tree);
    if (iterator)
        iterator->next(NULL);
    I *iterator23 = createIterator(tree2);
    if (iterator23) {
        iterator23->current = getNode(tree2, treeMax(tree2->root)->key->key);
        iterator23->next(iterator23);
        free(iterator23);
    }
    /* iterator->current=getNode(tree, 1500);
     while (!iterator->isLast) {
         iterator->next(iterator);
     }
     iterator->current=getNode(tree, treeMin(tree)->key->key);
     iterator->isLast=0;*/
    I *iterator2 = createIterator(tree2);
    //I *iterator5 = createIterator(tree2);

    NODE *del, *del2;
    treeMax(tree->root);
    treeMin(tree->root);
    treeMax(tree2->root);
    treeMin(tree2->root);
    //deleteNode(tree, &tree->root);
    //deleteNode(tree2, tree2->root);


    /* while (!iterator->isLast) {
         del=iterator->current;
         iterator->next(iterator);
         deleteNode(tree, del);
     }*/
    for (int k = 1; k < b; k++) {
        dnode = getNode(tree4, 1);
        deleteNode(tree4, &dnode);
        dnode = getNode(tree5, 1);
        deleteNode(tree5, &dnode);
    }
    if (iterator) {
        while (!iterator->isLast) {
            del = iterator->current;
            iterator->next(iterator);
            deleteNode(tree, &del);
        }
    }
    else{
        for (int k = 1; k < b; k++) {
            dnode = getNode(tree, 1);
            deleteNode(tree, &dnode);
        }
    }
    if (iterator2){
        while (!iterator2->isLast) {
            del2 = iterator2->current;
            iterator2->next(iterator2);
            deleteNode(tree2, &del2);
        }
    }
    else{
        for (int k = 1; k < b; k++) {
            dnode = getNode(tree2, 1);
            deleteNode(tree2, &dnode);
        }
    }
    free(iterator);
    free(iterator2);
    free(tree);
    free(tree2);
    free(tree5);
}


int main() {

    test();

    struct rlimit rl;
    getrlimit (RLIMIT_AS, &rl);
    printf("\n Default value is : %lld\n", (long long int)rl.rlim_cur);
    rl.rlim_cur = 640000;
    rl.rlim_max = 640000;
    setrlimit (RLIMIT_AS, &rl);
    getrlimit (RLIMIT_AS, &rl);
    printf("\n Default value now is : %lld\n", (long long int)rl.rlim_cur);

    test();
}
