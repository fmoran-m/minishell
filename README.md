## **Minishell**
> As beautiful as a Shell

### **Aim**
The objective of this project is for you to create a simple Shell. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.

### **Documentation and Development**
Our working shell (mishell), was a beast of a project tackled and developed by both myself and my minishell partner [nvillalt](https://github.com/nvillalt).
The first and most relevant point was setting a clear basis of how we were going to structure the project and setting the boundaries of what our shell would and would not contemplate, something which came from reading plenty of Bash documentation and talking to our peers in 42 to properly grasp how shells should work. Here are some useful links:
  - [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
  - [Writing your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
  - [Shell Syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
  - [Maia De Graaf's Minishell Guide](https://github.com/maiadegraaf/minishell)

After getting some ground work done we decided on the following structures to create our project:
  - Tokenising the input by saving in a linked node list each "word" or "symbol" sent to the readline function.
  - Expanding the $COMMAND symbols encountered after reading the nodes
  - Adding each of the "tokens" in our token list to a process list (organise whatever we got between pipes in the following manner, to afterwards send to the executor/processes part of the program)
    - A linked node list containing commands/builtins and their arguments with another linked node list contained within in order to handle all redirections
  - Properly handle all status responses to print and expand with $?
  - Properly handle exit errors, memory allocations and de-allocations, truly one of the most difficult parts of the project.
  
### **Aftermath**
Minishell's scope is so huge and you truly need to define the project in such a way (set boundaries of the scope of what you will handle, coordinate with another developer, set clear basis for both of you to work...) that makes it the most challenging and useful project to date in the 42 Cursus Common Core. You truly learn a lot not only about bash's innards, but also about how to clean code, organisation, teamwork and project definition and execution.
Good luck with your shell! It truly is as beautiful as a shell!

