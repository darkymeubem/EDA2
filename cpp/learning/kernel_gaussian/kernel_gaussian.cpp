#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <vector>




using namespace std;
double gaussianFunction(double x, double y, double sigma) {
    return (1.0 / (2 * M_PI * pow(sigma, 2))) *
            exp(-(pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2)));
}

class Kernel{
    private:
        int SIZE;
        vector<vector<double>> mat;
        double sigma;

    public:
        Kernel(double sigma) {
            this->sigma = sigma;
            SIZE = 2 * ceil(3 * sigma) + 1;
            mat = vector<vector<double>>(SIZE, vector<double>(SIZE, 0.0));
        }
        void createKernel(){
            int center = SIZE / 2;
            int x,y;
            for(int i = 0; i < SIZE; i++ ){
                for(int j = 0; j < SIZE; j++){
                    x = j - center;
                    y = i - center;

                    mat[i][j] = gaussianFunction(x, y, sigma);
                }

            }
        }
        void printMatrix(){
            for(int i= 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    cout << fixed << setprecision(6) << setw(8) << mat[i][j] << " ";

                }
                printf("\n");
            }
        }
        
        double sum(){
            double count = 0.0;
            for(int i= 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    count+=mat[i][j];
                }
            }
            return count;
        }
};

int main(){
    double sigma = 1;
    Kernel k(1);
    k.createKernel();
    k.printMatrix();
    double soma = k.sum();

    cout << soma << endl;
}