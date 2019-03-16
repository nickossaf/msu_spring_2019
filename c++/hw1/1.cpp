#include<iostream>
#include<cstdlib>
#include"numbers.dat"

bool isPrime(int x){
    if(x == 1) return false;
    for(int i = 2; i * i <= x; i++){
        if(x % i == 0) return false;
    }
    return true;
}

int binSearch(int x, const int arr[], const int n, char type = 'l'){
/*type maybe 'r' or 'l' and if we have got plenty matching
elements we return the rightest one or leftest; */
    int l = 0, r = n - 1;
    int m = (l + r) / 2;

    while(l < r && x != arr[m]){
        if(type == 'l'){
            if(x < arr[m]) r = m - 1;
            else l = m + 1;
        } else{
            if(x > arr[m]) l = m + 1;
            else r = m - 1;
        }

        m = (l + r) / 2;
    }

    if(x == arr[m]) return m;
    else return -1;
}

int main(int argc, char* argv[])
{
    if(argc % 2 == 0 || argc == 1) return -1;

    int top_l = -1;
    int down_r = Size + 1;

    for (int i = 1; i < argc - 1; i+=2){
        int l = binSearch(std::atoi(argv[i]), Data, Size);
        int r = binSearch(std::atoi(argv[i + 1]), Data, Size, 'r');
        if(l == -1 || r == -1){
            std::cout << 0 << std::endl;
            return 0;
        }

        int counter = 0;

        for(int j = l; j <= r; j++){
            if(isPrime(Data[j])) counter++;
        }

        std::cout << counter << std::endl;

    }

    return 0;
}
