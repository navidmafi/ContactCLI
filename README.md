# ContactCLI

## This project has been finished on 14 June 2022

---

Simple CLI Contact app for University project, Using SQLite as database and contollers for CRUD operations.

## Build

Pre configured for building in VSCode. Make sure you have your `includePath` set correctly.

If you are not using VS Code, you can build with :

```sh
/path/to/g++ -g ./Utils.cpp ./ContactController.cpp ./DisplayController.cpp ./main.cpp -lsqlite3 -o ./build/main
```

## Features and concpets used

- SQLite Database for persistant storage
- Not using any wrapper libraries, just using SQLite directly (_PAIN_)
- Controllers and encapsulation
- File splitting
- Using template for DRY pattern in functions
- Header files and reusable methods
- static methods
- git version control and github repo
- single responsible methods
