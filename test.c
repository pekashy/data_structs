#include "structure.h"

int main() {
    int a=10000;
    int b=2000;

    TREE *tree = createTree();
    TREE *tree2 = createTree();


    srand(time(NULL));//temporary
    for (int i = 0; i < a; i++) {
        if(!addNode(tree, rand() % (b + 1 - 1) + 1))
            return -1;
        if(!addNode(tree2, i) )
            return -1;
    }
    for(int k=0; k<b; k++){
        getNode(tree, k);
        getNode(tree2, k);
    }
 //   deleteNode(tree, tree->root);
    //deleteNode(tree2, tree2->root);

    I *iterator = createIterator(tree);
    I *iterator2 = createIterator(tree2);
    NODE* del, *del2;
    treeMax(tree->root);
    treeMin(tree->root);
    treeMax(tree2->root);
    treeMin(tree2->root);

    while (!iterator->isLast) {
        del=iterator->current;
        iterator->next(iterator);
        //deleteNode(tree2, del2);
    }
    /*for(int k=1; k<b; k++){
        deleteNode(tree, getNode(tree,k));
        deleteNode(tree2, getNode(tree2,k));
    }*/
    while (!iterator->isLast) {
        del=iterator->current;
        iterator->next(iterator);
        deleteNode(tree, del);
    }
    while (!iterator2->isLast) {
        del2=iterator2->current;
        iterator2->next(iterator2);
        deleteNode(tree2, del2);
    }
    free(iterator);
    free(iterator2);

    // iterator = createIterator(tree);
   // free(iterator);
    free(tree);
    free(tree2);

}
