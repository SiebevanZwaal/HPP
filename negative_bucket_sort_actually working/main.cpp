#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono>
using std::cout, std::endl, std::vector, std::rand, std::string, std::to_string;

vector<vector<int> > distribution_pass(const vector<int>& vect, int div_size)
{
    vector< vector<int> > distribution_vect = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};

    for (int i : vect) {
        if (i >= 0) {
            distribution_vect[int(i / div_size) % 10 + 9].push_back(i);
        }
        else{
            distribution_vect[(- 1 * int(i / div_size)% 10) * -1 + 9].push_back(i);
        }
    }
    return distribution_vect;
}

vector<int> gathering_pass(const vector<vector<int> >& dist_vect)
{
    vector<int> vect ={};
    for (auto & i : dist_vect)
    {
        for (int j : i)
        {
            vect.push_back(j);
        }
    }
    return vect;
}

vector<int> bucket_sort(const vector<int>& vector_to_sort)
{

    auto max = std::max_element(vector_to_sort.begin(), vector_to_sort.end());
    auto min = std::min_element(vector_to_sort.begin(), vector_to_sort.end());

    int biggest;
    if (*max < std::abs(*min)) {
        biggest = *min * -1;
    }
    else{
        biggest = *max;
    }

    vector<int> return_vector = vector_to_sort;
    vector<vector<int> > distributed_vector;

    for (int i =1; i < biggest; i*=10)
    {
        distributed_vector = distribution_pass(return_vector, i);
        return_vector = gathering_pass(distributed_vector);
    }
    return return_vector;
}



int main() {
    vector<int> v = {115380};

    for (int i = 0; i < 40; i++) {
        if (i % 2 == 0){
            v.push_back(rand());
        }
        else{
            v.push_back(rand()* -1);
        }
    }


    v = bucket_sort(v);

    std::cout << "{";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if (i < v.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;


for (int vect_size = 1000; vect_size < 1000000000; vect_size*=2)
{
    auto start = std::chrono::steady_clock::now();
    vector<int> v = {};

    for (int i= 0; i <vect_size; i++)
    {
        v.push_back(rand());
    }

    v =bucket_sort(v);
    string printable_vect;
    for (int el: v)
    {
        printable_vect += to_string(el);
    }
    auto end = std::chrono::steady_clock::now();
    cout << "Elapsed time in milliseconds: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " ms, vect size : "
         << vect_size << endl;
}

    return 0;
}
