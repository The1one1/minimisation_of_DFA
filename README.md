# minimisation_of_DFA
Summary

This program that takes a deterministic finite state machine and produces an equivalent one with a minimal number of states.

For more information on deterministics FSMs, see https://en.wikipedia.org/wiki/Deterministic_finite_automaton

Algorithm Description

This program used "Myphill-Nerode Theorem"(Table filling method)" for the minimisation of DFA.

For more information on MMyphill-Nerode Theorem, see https://www.tutorialspoint.com/automata_theory/dfa_minimization.htm

Given a deterministic finite state machine A = (Q,E,q,del,F). 
This program constructs an equivalent reduced deterministic finite state machine A' = (Q', E',q',del, F').

It does not remove unreachable states from DFS.

Input/Output

Enter the number of states: 4

Enter the number of inputs: 2

Enter the states: A B C D

Enter the inputs: a b

Enter the start state: A

Enter the number of final states: 2

Enter the final states: B C

Enter the transitions:

B A  
C B 
B C 
B C

Sample input:
4
2
A B C D 
a b
A
2 B C 
B A  
C B 
B C 
B C

Sample output:

   |a   |b
--------------
A  |B   |A  
--------------
B  |C   |B  
--------------
C  |B   |C  
--------------
D  |B   |C  
--------------

-------------------------------------------
states of DFA after minimisation:: BC , A , D , 
-------------------------------------------

Transition table:
         |        a |        b | 
-------------------------------------------
       A |       BC |        A | 
-------------------------------------------
      BC |       BC |       BC | 
-------------------------------------------
       D |       BC |       BC | 
-------------------------------------------

-------------------------------------------
Final State of DFA after minimisation:: BC , 
-------------------------------------------

Make and run
This program can be compiled using g++ and does not require any third party libraries.
