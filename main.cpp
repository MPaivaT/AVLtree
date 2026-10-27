#include "AVLtree.h"

using namespace std;

int main(){
    AVLtree<int> arv;
    arv.Insert(2,10);
    arv.Insert(3,40);
    arv.Insert(4,90);
    arv.Insert(1,8);
    arv.imprimir_InOrder();
    cout << arv.Search(1) << '\n';
    arv.pop(2);
    arv.imprimir_InOrder();

    return 0;
}
