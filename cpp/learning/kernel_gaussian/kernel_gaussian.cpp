#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

class Kernel {

private:

    int SIZE;
    double sigma;

    vector<double> mat;

    int index(int x, int y) const {
        return y * SIZE + x;
    }

    double gaussianFunction(int x, int y) const {

        double sigma2 = sigma * sigma;

        double exponent =
        -((x * x) + (y * y)) / (2.0 * sigma2);

        double coefficient =
        1.0 / (2.0 * M_PI * sigma2);

        return coefficient * exp(exponent);
    }

public:

    Kernel(double sigma) {

        this->sigma = sigma;

        SIZE = 2 * ceil(3 * sigma) + 1;

        mat.resize(SIZE * SIZE, 0.0);
    }

    void createKernel() {

        int center = SIZE / 2;

        for(int y = 0; y < SIZE; y++) {

            for(int x = 0; x < SIZE; x++) {

                int relativeX = x - center;
                int relativeY = y - center;

                mat[index(x, y)] =
                gaussianFunction(relativeX, relativeY);
            }
        }

        normalize();
    }

    void normalize() {

        double s = sum();

        for(double& value : mat) {

            value /= s;
        }
    }

    double sum() const {

        double total = 0.0;

        for(const double& value : mat) {

            total += value;
        }

        return total;
    }

    void printMatrix() const {

        for(int y = 0; y < SIZE; y++) {

            for(int x = 0; x < SIZE; x++) {

                cout
                << fixed
                << setprecision(6)
                << setw(10)
                << mat[index(x, y)]
                << " ";
            }

            cout << '\n';
        }
    }
};

int main() {

    Kernel k(1.0);

    k.createKernel();

    k.printMatrix();

    cout << "\nSoma: "
         << k.sum()
         << endl;

    return 0;
}