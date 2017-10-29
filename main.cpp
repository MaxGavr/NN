#include <iostream>
#include <vector>
#include <armadillo>

#include "Rectangle.h"
#include "ImageProcessor.h"
#include "Matrix.h"

using namespace std;
using namespace arma;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Usage: ./NeuralNetwork path/to/image.png" << endl;
        exit(1);
    }

    int n , m;
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

    ImageProcessor processor(argv[1], n, m, p, e, a);
    processor.run();
    processor.createOutputImage();
    return 0;
}
