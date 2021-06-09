# DatalogInterpreterMain
 Datalog Interpreter compromised of three components: the Lexer, the Parser, and the Execution engine

A lexer is a program that takes as input a program file and scans the file for tokens. The
output to the lexer is a collection of tokens. These tokens can then be read by the parser.
The parser determines the meaning of the program based on the order and type of tokens.
This meaning is then given to the execution engine, which executes the program.

A parser is a program that takes as input a collection of tokens (from a lexer). The parser
then tries to parse the tokens according to the programming language grammar to determine
correctness. The parser also determines the meaning of the program based on the order and
type of tokens. This meaning is then given to the execution engine, which executes the
program.

An execution engine is a program that takes as input the “meaning” of source code (from a
parser). It executes the meaning of the program defined by the source code. For this project,
you will implement the beginning of a Datalog execution engine, the last piece you need for
the Datalog interpreter.

See e https://www.geeksforgeeks.org/compiler-vs-interpreter-2/ for
details about interpreters.
