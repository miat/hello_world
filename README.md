# hello_world

## Visual Studio Code and Personal Access Token

1. Get personal access token from https://github.com/settings/tokens
2. Save access token. Can begin with something like ghp_pVC**.
3. In Visual Studio Code terminal,
4.      git remote set-url origin https://<personal_access_token>@github.com/<user_name>/<repo_name>.git
  
That's it. Publishing to github should work.


![A cute Maltese doggy.](https://user-images.githubusercontent.com/4535333/157773087-5f8aadc5-9f10-4ca0-a423-b0bd30f73b3a.jpeg)

--Miat  
miat@monkeeworks.com  
https://monkeeworks.com

## Creating N-element constexpr array in C++

(source: https://www.educative.io/edpresso/how-to-create-an-n-element-constexpr-array-in-cpp)

#include <iostream>
const int ARRAY_SIZE=10;

    template <int size>
    struct BigConstant {
        int big_array[size];

        constexpr BigConstant() : big_array() {
            for (int n=0; n<size; ++n) big_array[n] = n;
        }

        void print() const {
            for(int n=0; n<size; ++n) std::cout << big_array[n] << std::endl;
        }
    };

        BigConstant<ARRAY_SIZE> my_const;

    int main () {
        my_const.print();
        return 69;
    }

## Measuring overall code size with ARM gcc
  
    /Applications/ARM/bin/arm-none-eabi-size main.elf
    text	   data	    bss	    dec	    hex	filename
    18296	 408712	  16000	 443008	  6c280	main.elf
