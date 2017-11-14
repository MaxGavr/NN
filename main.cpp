///////////////////////////////////////////////////////////////////
// Авторы: Каленчук Е. О , Гаврилюк М. И.
///////////////////////////////////////////////////////////////////

#include <iostream> // C++ Standard Template Library
#include "NeuralNetwork.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int n, m;
    cout << "Высота и ширина прямоугольника (n и m):" << endl;
    cin >> n >> m;

    cout << "Количество нейронов на втором слое (p):" << endl;
    int p;
    cin >> p;

    cout << "Допустимая ошибка (e):" << endl;
    double e;
    cin >> e;

    NeuralNetwork network(n, m, p, e);

    network.loadImage(argv[1]);
    network.processImage();
    network.restoreImage();

    return 0;
}
