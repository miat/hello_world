# Git with GitHub

    git clone https:://<token>@github.com/miat/hello_world.git
    git remote
Configured remote servers; origin = default name you cloned from.
  
    git remote -v
URLS for reading from/writing remote

    git remote add gh https://<token>@github.com/miat/hello_world.git
    git fetch gh
Fetch URL shortcut. Have all branches locally. 

    git origin push master
Push your master branch to your origin server.

    git remote show origin


    git tag -a v1.0 -m "my first v1.0 tag"
    git show v1.0
    git push origin v1.0
Annotated Tag. Explicitly sharing tag.

    
