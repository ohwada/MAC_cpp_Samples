/**
 * matrix.cpp
 * 2022-06-01 K.OHWADA
 */

// matrix multiplication
// reference : https://qiita.com/t--k/items/69c43a667a1283578012

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <cblas.h>


/**
 * main
 */
int main(void)
{
    const int m = 1000, k = 2000, n = 3000;

    std::vector<double> a(m * k);
    std::vector<double> b(k * n);
    std::vector<double> c_blas(m * n);
    std::vector<double> c_loop(m * n);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> dist(0.0, 10.0);

    for (double& d : a) {
        d = dist(mt);
    }
    for (double& d : b) {
        d = dist(mt);
    }

// Multiply matrices in normal loop
    std::cout << "Loop:" << std::endl;
    auto begin = std::chrono::high_resolution_clock::now();

#pragma omp parallel for
    for (int i = 0; i < m; i++) {
        for (int t = 0; t < k; t++) {
            for (int j = 0; j < n; j++) {
                c_loop[i * n + j] += a[i * k + t] * b[t * n + j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "  elapsed time: " << elapsed / 1000.0 << " sec." << std::endl;

// Multiply matrices in OpenBLAS
    std::cout << "BLAS:" << std::endl;
    begin = std::chrono::high_resolution_clock::now();

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, a.data(), k, b.data(), n, 0.0, c_blas.data(), n);

    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "  elapsed time: " << elapsed / 1000.0 << " sec." << std::endl;    


// Just in case, check if the requested answer is roughly the same.
// To do so, first subtract c_loop from c_blas.
    cblas_daxpy(c_blas.size(), -1.0, c_loop.data(), 1, c_blas.data(), 1);


// Next, sum the absolute values ​​of the subtracted elements.
    auto diff = cblas_dasum(c_blas.size(), c_blas.data(), 1);
    std::cout << "Diff: " << diff << std::endl;

    return 0;
}



// Loop:
 //  elapsed time: 53.289 sec.
// BLAS:
  // elapsed time: 0.288 sec
