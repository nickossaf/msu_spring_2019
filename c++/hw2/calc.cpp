#include<iostream>
#include<cstdlib>
#include<string>
#include <stdexcept>

class Calculator{
private:
    std::string buffer;
    int pntr = 0;
    int buffer_len;

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
            throw std::invalid_argument("Missed operator");
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
        int number = 0;
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

            tab();
        }

        return ans;
    }
    int getMultiplication(){
        int number = 1;
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
                if(number == 0) throw std::invalid_argument("Division by zero");
                ans /= number;
            }

            tab();
        }

        return ans;
    }

public:

    int parser(std::string const& buff){
        buffer = buff;
        pntr = 0;
        buffer_len = buffer.length();
        int ans = 0;

        tab();
        ans = getAddition();

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

    try {
        calc.parser(argv[1]);
    } catch(const std::invalid_argument& e){
        std::cout << "error";
        return 1;
    }

    return 0;

}
