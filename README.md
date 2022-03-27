# hello_world

## Syncing local with github

1. Get personal access token from https://github.com/settings/tokens
2. Save access token. Can begin with something like ghp_pVC**.
3. In Visual Studio Code terminal,
4.      git remote set-url origin https://<personal_access_token>@github.com/<user_name>/<repo_name>.git
  

## Pushing existing new repo to github

1.    git remote add origin https://<personal_access_token>@github.com/<user_name>/<repo_name>.git
2.    git branch -M main
3.    push -u origin main


![A cute Maltese doggy.](https://user-images.githubusercontent.com/4535333/157773087-5f8aadc5-9f10-4ca0-a423-b0bd30f73b3a.jpeg)

--Miat  
miat@monkeeworks.com  
https://monkeeworks.com


## Measuring overall code size with ARM gcc
  
    /Applications/ARM/bin/arm-none-eabi-size main.elf
    text	   data	    bss	    dec	    hex	filename
    18296	 408712	  16000	 443008	  6c280	main.elf
