#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std::chrono;
using std::vector, std::min, std::copy, std::thread;

void merge_sort(vector<int>& xs)
{

    int unit = 1;
    while (unit <= xs.size())
    {
        for (int h = 0; h < xs.size(); h = h + unit * 2)
        {
            int l = h;
            int r;
            r = min((int)xs.size(), h + 2 * unit);
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

int main() {
    vector<int> v ={9,8,7,6,5,4,3,2,1,0};
    merge_sort(v);
    std::cout << "{";
    for (int el: v){
        std::cout << el << ",";
    }
    std::cout << "}" << std::endl;
    return 0;
}
