# Shell

I developed a stripped down version of Bash shell: 

* Multiple proccess programming
* Following POSIX standards 
* Kernel signals handling 
* Environment variables handling
* Errors and return codes handling

---

### System Requirements

- Linux (Ubuntu)
- gcc
- make
- GNU Readline

You may install the required dependencies with: 
```bash
sudo apt update;
sudo apt install libreadline-dev;
```

---

### Build

```bash
git https://github.com/romolog/C__cli__minishell_2025 minishell;
cd minishell;
make;
```

### Run
```bash
./minishell;
```