#include "AVLtree.h"

using namespace std;

int main(){
    AVLtree<int> arv;
    arv.Insert(1,10);
    arv.Insert(2,40);
    arv.Insert(7,90);
    arv.Insert(90,8);
    arv.imprimir_InOrder();
    cout << arv.Search(90) << '\n';
    arv.pop(2);
    arv.imprimir_InOrder();


    return 0;
}
