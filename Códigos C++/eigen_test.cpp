#include <stdio.h>
#include <eigen3/Eigen/Sparse>

using namespace Eigen;
using namespace std;
Eigen::SparseMatrix<double> sparse_matrix(864,5);

void printNonZeros(SparseMatrix<double> &sparse_matrix);
void checkElementAt(SparseMatrix<double> &sparse_matrix, int row, int col);
double getElementAt(SparseMatrix<double> &sparse_matrix, int row, int col);
void insertElementAt(SparseMatrix<double> &sparse_matrix, int row, int col, double value);
int getStateNumber(int dist_d, int ang_d, int alt_d, bool object_pickect, bool folded);
void getStateFromNumber(int number, int &dist_d, int &ang_d, int &alt_d, bool &object_pickect, bool &folded);

int main(int argc, char const *argv[])
{
    /*
    //Insert element
    sparse_matrix.insert(3,4) = 20.0; // sparse_matrix.coeffRef(3,4) += 20.0
    printf("Inserting 20.0...\n");
    sparse_matrix.insert(1,4) = 3.0;
    printf("Inserting 3.0...\n");

    // Check number of non-zero elements
    int nonzeros = sparse_matrix.nonZeros();
    printf("Non-zeros elements: %d\n\n", nonzeros);

    // Print non-zero elements
    for(int k=0; k<sparse_matrix.outerSize(); ++k){
        for (SparseMatrix<double>::InnerIterator it(sparse_matrix, k); it; ++it){
            printf("Value %.2f\n",it.value());
            printf("Row %d\n", it.row());
            printf("Col %d\n",it.col());
            printf("Index %d\n",it.index());
        }
    }

    // Get an element of the sparse matrix
    printf("\nValue at (0,0): %.2f\n",sparse_matrix.coeffRef(0,0));
    nonzeros = sparse_matrix.nonZeros();
    printf("Non-zeros elements after accesing a 0 element: %d\n", nonzeros);

    // Pruning for not counting the 0 element
    sparse_matrix.prune(0.0);
    nonzeros = sparse_matrix.nonZeros();
    printf("Non-zeros elements after pruning: %d\n", nonzeros);

    // Getting elements
    double elem = getElementAt(sparse_matrix, 0, 0);
    printf("\n%.2f",elem);

    elem = getElementAt(sparse_matrix, 3, 4);
    printf("\n%.2f\n",elem);

    nonzeros = sparse_matrix.nonZeros();
    printf("Non-zeros elements after getting two elements: %d\n\n", nonzeros);

    // Inserting elements by function
    insertElementAt(sparse_matrix, 0, 0, 225.0);
    checkElementAt(sparse_matrix, 0, 0);
    */
    int dist_d; int ang_d; int alt_d; bool object_picked; bool folded;
    //int number = getStateNumber(-1, -1, -1, false, true);
    int number = 736;
    getStateFromNumber(number, dist_d, ang_d, alt_d, object_picked, folded);
    printf("number: %d\ndist_d: %d\nang_d: %d\nalt_d: %d\npicked: %d\nfolded: %d\n",
            number, dist_d, ang_d, alt_d, object_picked, folded);

    return 0;
}

void printNonZeros(SparseMatrix<double> &sparse_matrix){
    for(int k=0; k<sparse_matrix.outerSize(); ++k){
        for (SparseMatrix<double>::InnerIterator it(sparse_matrix, k); it; ++it){
            printf("Value %.2f\n",it.value());
            printf("Row %d\n", it.row());
            printf("Col %d\n",it.col());
            printf("Index %d\n",it.index());
        }
    }
}

void checkElementAt(SparseMatrix<double> &sparse_matrix, int row, int col){
    printf("Value at sparse_matrix[%d,%d]: %.2f\n", row, col, sparse_matrix.coeffRef(row, col));
    sparse_matrix.prune(0.0);
}

double getElementAt(SparseMatrix<double> &sparse_matrix, int row, int col){
    double element = sparse_matrix.coeffRef(row, col);
    sparse_matrix.prune(0.0);
    return element;
}

void insertElementAt(SparseMatrix<double> &sparse_matrix, int row, int col, double value){
    sparse_matrix.insert(row, col) = value;
    printf("Inserted value %.2f into sparse_matrix(%d,%d)\n", value, row, col);
}

int getStateNumber(int dist_d, int ang_d, int alt_d, bool object_picked, bool folded){
    return (dist_d) * pow(6,2) * pow(2,2) +
            (ang_d) * 6 * pow(2,2) +
            (alt_d) * pow(2,2) +
            object_picked * 2 +
            folded; // 6 = discr_lvl + 1
}

void getStateFromNumber(int number, int &dist_d, int &ang_d, int &alt_d, bool &object_picked, bool &folded){
    dist_d = ((int)number / (int)(pow(6,2) * pow(2,2)));
    ang_d = ((number % (int)(pow(6,2) * pow(2,2))) / (int)(6 * pow(2,2)));
    alt_d = ((number % (int)(pow(6,2) * pow(2,2)) % (int)(6 * pow(2,2))) / (int)pow(2,2));
    object_picked = ((number % (int)(pow(6,2) * pow(2,2)) % (int)(6 * pow(2,2)) % (int)pow(2,2)) / 2);
    folded = ((number % (int)(pow(6,2) * pow(2,2)) % (int)(6 * pow(2,2)) % (int)pow(2,2) % 2));
}