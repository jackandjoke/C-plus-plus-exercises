#include<vector>
#include<numeric>
#include<iostream>



int main(){
    std::vector<int> vect{1,2,3,4,5,6,7,8,9,10};
    std::cout <<"sum of vect is "<< std::accumulate(vect.cbegin(),vect.cend(),0) << std::endl;
    return 0;
}
