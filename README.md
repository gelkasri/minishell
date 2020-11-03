# minishell

## UNIX shell implementation in C, a 42 school project

This project was a group project, our group was: https://github.com/gelkasri + https://github.com/mle-moni

We finished this project in approx. 2 weeks

## INSTALL:

### macos:

```zsh
git clone https://github.com/mle-moni/minishell
cd minishell
make # build the project
# you will get an executable named minishell
```

## USAGE:

- launch the shell: `minishell`
- type commands

You can also use it to execute scripts: `minishell script.sh`

Like the others shells, your commands are stored in a file in your home directory: `~/.minishell_history`, this allows you to use the arrow keys to navigate through your commands history

## TESTS:

If you want to contribute to this repo, make sure to run `make test` after your modifications

If your modifs did not break anything, you should get something like:
![tests success image](https://github.com/mle-moni/minishell/blob/master/debug/tests/tests.png?raw=true)
