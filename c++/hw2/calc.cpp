#include<iostream>
#include<cstdlib>
#include<string>

class Calculator{
private:
    int ERROR_KEY = 2147483647;

    void tab(){
        while(pntr < buffer_len){
            if(buffer[pntr] == ' ') pntr++;
            else return;
        }
    }
    int getNumber(){
        int ans = 0;
        int sign = 1;
        tab();

        if(buffer[pntr] == '-'){
            sign = -1;
            pntr++;
        }

        tab();

        if(buffer[pntr] <= '0' || buffer[pntr] >= '9'){
            return ERROR_KEY;
        }

        while(buffer[pntr] >= '0' && buffer[pntr] <= '9'){
            if(buffer[pntr] >= '0' && buffer[pntr] <= '9') {
                ans *= 10;
                ans += buffer[pntr] - '0';
                pntr++;
            }
        }

        return ans * sign;
    }
    int getAddition(){
        int number = ERROR_KEY;
        int ans = getMultiplication();
        tab();

        while(buffer[pntr] == '+' || buffer[pntr] == '-'){
            if(buffer[pntr] == '+'){
                pntr++;
                number = getMultiplication();
                ans += number;
            } else if(buffer[pntr == '-']){
                pntr++;
                number = getMultiplication();
                ans -= number;
            }

            if(number == ERROR_KEY) return ERROR_KEY;
            tab();
        }

        return ans;
    }
    int getMultiplication(){
        int number = ERROR_KEY;
        int ans = getNumber();
        tab();

        while(buffer[pntr] == '*' || buffer[pntr] == '/'){
            if(buffer[pntr] == '*'){
                pntr++;
                number = getNumber();
                ans *= number;
            } else if(buffer[pntr] == '/'){
                pntr++;
                number = getNumber();
                if(number == 0) return ERROR_KEY;
                ans /= number;
            }

            if(number == ERROR_KEY) return ERROR_KEY;
            tab();
        }

        return ans;
    }

public:

    std::string buffer;
    int pntr;
    int buffer_len;

    int parser(){
        int ans = 0;
        buffer_len = buffer.length();

        tab();
        ans = getAddition();

        if(ans == ERROR_KEY){
            std::cout << "error";
            return 1;
        }

        std::cout << ans;
        return 0;
    }
};

int main(int argc, char* argv[]){
    if(argc != 2) {
        std::cout << "error";
        return 1;
    }

    Calculator calc;
    calc.buffer = argv[1];;
    calc.pntr = 0;

    return calc.parser();

}
