#include <iostream>
#include "ImageProcessor.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./NeuralNetwork path/to/image.png" << endl;
        exit(1);
    }
    srand(time(NULL));

    int n, m;
    cout << "Enter height of rectangle (n):" << endl;
    cin >> n;
    cout << "Enter width of rectangle (m):" << endl;
    cin >> m;
    cout << "Enter number of neurons for second layer (p):" << endl;
    int p;
    cin >> p;
    cout << "Enter max error (e):" << endl;
    double e;
    cin >> e;
    cout << "Enter step (a):" << endl;
    double a;
    cin >> a;

    NeuralNetwork processor(argv[1], n, m, p, e, a);
    processor.processImage();
    processor.createOutputImage();
    return 0;
}
