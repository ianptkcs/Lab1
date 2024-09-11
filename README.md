# Airport Control Tower Simulator

## Description

This C program simulates an airport control tower managing flight landings. It processes incoming flight requests, manages a landing queue, and handles emergency situations. The program reads commands from an input file and generates an output file with landing authorizations and the final queue status.

## Features

-   Processes incoming flight landing requests
-   Manages a dynamic landing queue using a linked list
-   Handles emergency landing requests with priority
-   Outputs landing authorizations as they occur
-   Provides a final status of the remaining queue

## Technical Details

-   Language: C
-   Compilation: Tested with Visual Studio Code 1.92.2
-   Data Structure: Singly linked list for queue management

## File Structure

-   `control_tower.cpp`: Main source code
-   `entrada1.txt`: Input file with flight commands
-   `saida1.txt`: Output file for landing authorizations and queue status

## Usage

1. Compile the program:

    ```
    g++ control_tower.cpp -o control_tower
    ```

2. Run the executable:

    ```
    ./control_tower
    ```

3. Check the output in `saida1.txt`

## Input File Format

The input file (`entrada1.txt`) should contain the following commands:

-   `INICIO`: Marks the beginning of commands
-   `pede_pouso [FLIGHT] [ORIGIN]`: Request landing for a flight
-   `pista_liberada`: Indicates the runway is clear for the next landing
-   `URGENCIA [FLIGHT]`: Emergency landing request for a specific flight
-   `FIM`: Marks the end of commands

Example:

```
Joseloid International Airport
Torre de controle: mensagens recebidas
Bla
Bla
=========================================
MESSAGE           FLIGHT  FROM

INICIO              0000  -
pede_pouso          1234  Amsterdam
pista_liberada      0000  -
pista_liberada      0000  -
pede_pouso          8086  San Francisco
pede_pouso          4444  Londres
pede_pouso          0055  Paris
pede_pouso          2552  Tokyo
pista_liberada      0000  -
URGENCIA            0055  -
pede_pouso          6161  Hong Kong
pista_liberada      0000  -
pista_liberada      0000  -
FIM                 0000  -
```

## Output Format

The output file (`saida1.txt`) contains:

1. Header information
2. Landing authorizations as they occur
3. Final queue status

Example:

```
Bla bla bla
Ble
AUTORIZACOES DE POUSO
=========================================
FLIGHT  FROM

1234    Amsterdam
0000    Nenhum aviao pousando
8086    San Francisco
0055    Paris
4444    Londres

Situacao da fila

2552    Tokyo
6161    Hong Kong
```

## Functions

-   `iniciarVariaveis()`: Initializes variables and opens files
-   `lerLinhas()`: Reads and processes input file lines
-   `gerenciarComandos()`: Manages different types of commands
-   `pedePouso()`: Handles landing requests
-   `pistaLiberada()`: Processes runway clearance
-   `urgencia()`: Manages emergency landing requests
-   `escreverELiberar()`: Writes final queue status and frees memory

## Error Handling

The program includes basic error handling for file operations and memory allocation.

## Author

Ian Patrick da Costa Soares

## License

This project is licensed under the [MIT License](LICENSE).
