#include <iostream>
#include "Binary_tree_implementation.hpp"
using namespace std;


int main()
{

    BinaryTreeScope::BinaryTree<int> myTree;
    cout <<myTree.empty() << endl;

    /*myTree.insert(3);
    myTree.insert(1);
    myTree.insert(2);
    myTree.insert(0);
    myTree.insert(-1);*/

    myTree.insert(14);
    myTree.insert(13);
    myTree.insert(12);
    myTree.insert(11);
    myTree.insert(10);
    myTree.insert(9);
    myTree.insert(8);
    myTree.insert(7);
    myTree.insert(6);
    myTree.insert(5);
    myTree.insert(4);
    myTree.insert(3);
    myTree.insert(2);
    myTree.insert(1);

    /*myTree.insert(8);
    myTree.insert(11);
    myTree.insert(10);*/
    myTree.toString();

    // BinaryTreeScope::Node<int>* root = myTree.find(8);  //left 6
    // cout << root->key << " brawlhala" << endl;
    //
    // //myTree.rotateRight(root);
    //
    // BinaryTreeScope::Node<int>* a = myTree.find(6);
    // cout << root->key << " brawlhala" << endl;

    //myTree.dRotateLeft(root);


    myTree.toString();


    //
    //
    // myTree.display();





    //myTree.rotateRight(root);

    /*myTree.insert(5);
    myTree.insert(4);
    myTree.insert(7);
    myTree.insert(6);
    myTree.insert(3);*/

/*    myTree.insert(5);
    myTree.insert(7);
    myTree.insert(6);*/

    //myTree.remove(10);


    myTree.remove(7);
    myTree.remove(14);
    myTree.remove(13);

    myTree.toString();

    myTree.remove(12);
    myTree.remove(1);

    myTree.toString();
    myTree.remove(2);


    // root = myTree.find(11)->left;
    // cout << root->key << " brawlhala" << endl;

    //myTree.toString();
    //myTree.remove(9);
    //myTree.remove(10);

    myTree.toString();


    //myTree.remove(7);

    //cout << "Successor of 5: " << s->key << endl;

    //myTree.toString();

    /*BinaryTreeScope::Node<int> *root = myTree.find(5);
    int valor = myTree.balFactOfNode(root);
    cout << valor << endl;*/


/*    myTree.insert(7);
    myTree.insert(5);
    myTree.insert(4);
    myTree.insert(1);
*/
/*    BinaryTreeScope::Node<int>* hola = myTree.find(3);
    cout << "Altura: " << myTree.height_Node(hola) << endl;*/


    return 0;
}
