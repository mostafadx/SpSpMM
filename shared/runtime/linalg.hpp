#pragma once

#include "boost/container/flat_map.hpp"
#include "hashmap.hpp"

template <class TYPE>
using arr_type = TYPE *;

template <class K, class V>
using boostFlatMap = boost::container::flat_map<K, V>;


template <class M, class K, class V>
inline void update(M &m, const K &k, const V &dv)
{
    // auto it = m.find( k );
    // typename M::iterator iter = it;
    auto iter = m.find(k);
    if (iter == m.end())
    {
        m.emplace(k, dv);
    }
    else
    {
        const_cast<V &>(iter->second) += dv;
    }
}

template <typename KEY, typename TYPE>
void printSpMat(arr_type<boostFlatMap<KEY, TYPE>> &M, size_t I)
{
    for (size_t i = 0; i < I; ++i)
    {
        for (auto const &kv : M[i])
        {
            std::cerr <<"( "<<i<<","<< kv.first << " ): " << kv.second << "\n";
        }
    }
}


template <typename KEY, typename TYPE>
void SpSpMM(size_t I, arr_type<boostFlatMap<KEY, TYPE>> __restrict__ &B, arr_type<boostFlatMap<KEY, TYPE>> __restrict__ &C, arr_type<boostFlatMap<KEY, TYPE>> __restrict__ &res)
{
    for (size_t ind24 = 0; ind24 < I; ++ind24)
    {
        new (&res[ind24]) boostFlatMap<int, int>();
        boostFlatMap<KEY, TYPE> temp;
        res[ind24] = temp;
    }

    

    for (size_t i = 0; i < I; ++i)
    {
        boostFlatMap<KEY, TYPE> resi;
        for (auto const &Bi_kv : B[i])
        {
            auto const k = Bi_kv.first;
            for (auto const &Ck_kv : C[k])
            {
                auto const j = Ck_kv.first;
                // TYPE resij = 0.0;
                TYPE resij = Bi_kv.second * Ck_kv.second;

                update(resi, j, resij);
            }
        }
        res[i] = resi;
    }
}

void opSpSpMM(size_t I, SPDB::HashMap &A, SPDB::HashMap &B, SPDB::HashMap &res)
{

    for (size_t i = 0; i < I; ++i){

        // TODO: use operator overloading to do smth like for  for (auto const &Ai_kv : A[i])
        for (size_t k = 0; k < A.table[i].size(); ++k){
            if(A.table[i][k]._key == -1)
                continue;
            int kkey = A.table[i][k]._key;
            // TODO: use operator overloading to do smth like for  for (auto const &Bi_kv : B[i])
            for(int j = 0; j < B.table[kkey].size();j++){
                if(B.table[kkey][j]._key == -1)
                    continue;
                int resij = A.table[i][k]._value *  B.table[kkey][j]._value;
                struct SPDB::key key;
                key.i = i;
                key.j = B.table[kkey][j]._key;
                res.put(key,resij);
            }
        }

    }
    
}

template <typename KEY, typename TYPE>
void prSpSpMM(size_t start, size_t end, arr_type<boostFlatMap<KEY, TYPE>> __restrict__ &B, arr_type<boostFlatMap<KEY, TYPE>> __restrict__ &C, arr_type<boostFlatMap<KEY, TYPE>> __restrict__ &res)
{
    for (size_t ind24 = start; ind24 < end; ++ind24)
    {
        new (&res[ind24]) boostFlatMap<int, int>();
        boostFlatMap<KEY, TYPE> temp;
        res[ind24] = temp;
    }


    for (size_t i = start; i < end; ++i)
    {
        boostFlatMap<KEY, TYPE> resi;
        for (auto const &Bi_kv : B[i])
        {
            auto const k = Bi_kv.first;
            for (auto const &Ck_kv : C[k])
            {
                auto const j = Ck_kv.first;
                // TYPE resij = 0.0;
                TYPE resij = Bi_kv.second * Ck_kv.second;

                update(resi, j, resij);
            }
        }
        res[i] = resi;
    }
}
