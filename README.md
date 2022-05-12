# hello_world

## Cloning

    git remote -v #show remotes
    git clone https://<personal_access_token>@github.com/<user_name>/<repo_name>.git
    
## Setting new remote name (origin)

    git remote -v #show remotes
    git remote set-url origin https://<token>@github.com>/miat/hello_world.git

## Adding new remote name (origin)

    git remote -v # show remotes
    git remote add origin https://<personal_access_token>@github.com/<user_name>/<repo_name>.git
    git branch -M main
    push -u origin main

## python3 execute script

    exec(open("file.py").read())

## compiler flags

    g++ $(<flags) hello.cpp -ohello 
    
(flags = local text file with compiler flag per line)

## Measuring overall code size with ARM gcc
  
    /Applications/ARM/bin/arm-none-eabi-size main.elf
    text	   data	    bss	    dec	    hex	filename
    18296	 408712	  16000	 443008	  6c280	main.elf

![A cute Maltese doggy.](https://user-images.githubusercontent.com/4535333/157773087-5f8aadc5-9f10-4ca0-a423-b0bd30f73b3a.jpeg)

--Miat  
miat@monkeeworks.com  
https://monkeeworks.com
