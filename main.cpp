#include "AVLtree.h"

using namespace std;

int main(){
    AVLtree<int> arv;
    arv.Insert(2,10);
    arv.Insert(3,40);
    arv.Insert(4,90);
    arv.Insert(1,8);
    if(arv.pop(1))cout << "Deu Certo\n";
    arv.print_Order(0);
    arv.foreach([](int& x){x = x/10;});
    arv.print_Order(0);

    return 0;
}
