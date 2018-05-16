#include <cstdio>
#include <cstdlib>

#include <faiss/IndexFlat.h>
#include <faiss/IndexIVFPQ.h>
#include <faiss/IndexLSH.h>
#include <../../cpu/timer.h>

int main(){

int d =128;

int nbits = 2 * d; 

int nb =50000;

size_t nt = 100 * 1000;

faiss::IndexLSH * lsh = new faiss::IndexLSH (d, nbits);

std::vector <float> x_train(nt * d);
        for (size_t i = 0; i < nt * d; i++) {
            x_train[i] = drand48();
}


//index.verbose = true;
//n_bits = 2 * d
//lsh = faiss.IndexLSH(d, n_bits);
lsh->train(nt,x_train.data());

std::vector<float>database (nb * d);

for (size_t i = 0; i < nb * d; i++) {
            database[i] = drand48();
}


//lsh->add(database);

int k = 4;

int i0 = 1234;
int i1 = 1243;

int nq = i1 - i0;

std::vector <float> queries;
queries.resize(nq * d);

for (int i = i0; i < i1; i++) {
  for (int j = 0; j < d; j++) {
       queries [(i - i0) * d  + j]  = database [i * d + j];
            }
        }

std::vector<faiss::Index::idx_t> I(k * nq);
std::vector<float>               D(k * nq);

lsh->add(nq, database.data());
std::cout << "lsh search:       " << std::setw(10) << benchmark([&]() { 
    lsh->search(nq, queries.data(), k,D.data(), I.data());
})<<" ms"<<std::endl;

return 0;
}
