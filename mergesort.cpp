#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std::chrono;
using std::vector, std::min, std::copy, std::thread;

void merge_sort(vector<int>& xs, int start_index, int end_index)
{

    int unit = 1;
    while (unit <= end_index - start_index)
    {
        for (int h = start_index; h < end_index; h = h + unit * 2)
        {
            int l = h;
            int r;
            r = min(end_index, h + 2 * unit);
            int mid = h + unit;
            int p = l;
            int q = mid;
            while (p < mid and q < r) {
                if (xs[p] <= xs[q]) {
                    p += 1;
                }else {
                    int tmp = xs[q];
                    copy(xs.begin() + p, xs.begin()+ q, xs.begin() + p + 1);
                    xs[p] = tmp;
                    p+= 1;
                    mid +=1;
                    q += 1;
                }

            }
        }
        unit *= 2;

    }
}
vector<int> merge(vector<int> v, vector<int> indexes)
{

    vector<int> new_v (v.size());
    int i = 0;
    int i_new = 0;
    int index_h = 0;

    while (i < indexes.size() - 1)
    {
        if (i > 0)
        {
            index_h = indexes[i - 1];
        }
        int index_i = indexes[i];
        while (index_h < indexes[i] and index_i < indexes[i+1])
        {
            if (v[index_h] < v[index_i])
            {
                new_v[i_new] = (v[index_h]);
                index_h++;
                i_new++;
            }else
            {
                new_v[i_new] = (v[index_i]);
                index_i++;
                i_new++;
            }
        }
        // collecting the leftover numbers
        if (index_h < indexes[i])
        {
            for (;index_h < indexes[i]; index_h++)
            {
                new_v[i_new] = v[index_h];
                i_new++;
            }
        }else
        {
            for (;index_i < indexes[i+1]; index_i++)
            {
                new_v[i_new] = v[index_i];
                i_new++;
            }
        }

        i+=2;
    }

    return new_v;
}

void multithreaded_merge_sort(vector<int>& v, int num_threads){

    vector<thread> threads;
    int start_index = 0;
    int end_index = v.size() / num_threads;
    int elevation = v.size() / num_threads;
    vector<int> index_vect;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back(merge_sort, std::ref(v), start_index, end_index);
        start_index = end_index;
        index_vect.push_back(start_index);
        end_index += elevation;
    }
    for (auto& t : threads)
    {
        t.join();
    }

    // mergen
    while (index_vect.size() > 1){
        v = merge(v, index_vect);
        vector<int> new_index_vect ((int)index_vect.size()/2);

        int new_index_vect_i = 0;
        for (int index_i = 0; index_i < index_vect.size(); index_i++)
        {
            if (index_i % 2 == 1)
            {
                new_index_vect[new_index_vect_i] = index_vect[index_i];
                new_index_vect_i++;
            }
        }
        index_vect = new_index_vect;
    }



}

int main() {
    int max_vec_size = 253953;
    long total_runtime = 0;
    int runs = 0;
    int num_threads = 16;
    for (int vec_size = 8192; vec_size < max_vec_size; vec_size += 8192)
    {

        auto start = high_resolution_clock::now();
        vector<int> v(vec_size);
        std::generate(v.begin(), v.end(), std::rand);
        multithreaded_merge_sort(v, num_threads);
        auto stop = high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = duration_cast<microseconds>(stop - start);
//        ::duration<long, std::micro> int_usec = duration;
        runs++;
        total_runtime += duration.count();
        std::cout << "vector of size " << vec_size << " took " << duration.count() << " ms " << std::endl;
    }

    std::cout << total_runtime / runs << std::endl;
//    std::cout << "v" << std::endl;
//    std::cout << "{" ;
//    for (int i: v) {
//        std::cout << i << ",";
//    }
//    std::cout << "}" << std::endl;

    return 0;
}