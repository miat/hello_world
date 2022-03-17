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

    template <int size>
    struct BigConstArray {
        int m_big_array[size];

        constexpr BigConstArray() : m_big_array() {
            for (int n=0; n<size; ++n) m_big_array[n] = n;
        }

        const int& operator[](std::size_t idx) const {return m_big_array[idx];}
    };
    const int ARRAY_SIZE=100;

    BigConstArray<ARRAY_SIZE> big_const_array;

    int main () {
    
        for(int i; i < ARRAY_SIZE; ++i)
        std::cout << big_const_array[i] << std::endl;
        return 69;
    }

## Measuring overall code size with ARM gcc
  
    /Applications/ARM/bin/arm-none-eabi-size main.elf
    text	   data	    bss	    dec	    hex	filename
    18296	 408712	  16000	 443008	  6c280	main.elf
