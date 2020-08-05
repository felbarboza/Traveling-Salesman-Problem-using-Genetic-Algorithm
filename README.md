<div align="center">
  <h1> Traveling Salesman Problem using Genetic Algorithm </h1>
  <p>
    The travelling salesman problem: "Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city and returns to the origin city?"
  </p>
  <p>
    It is an NP-hard problem in combinatorial optimization, important in theoretical computer science and operations research.
    And to resolve it there are a lot of algorithms, but in this example it is used a genetic algorithm, for educational proposals.
  </p>
  
  *******
  
  
  <h3> The following graph represents the distance between each city:</h3>  
  <p align="center">
    0 29 82 46 68 52 72 42 51 55 29 74 23 72 46 <br/>
    29 0 55 46 42 43 43 23 23 31 41 51 11 52 21 <br/>
    82 55 0 68 46 55 23 43 41 29 79 21 64 31 51 <br/>
    46 46 68 0 82 15 72 31 62 42 21 51 51 43 64 <br/>
    68 42 46 82 0 74 23 52 21 46 82 58 46 65 23 <br/>
    52 43 55 15 74 0 61 23 55 31 33 37 51 29 59 <br/>
    72 43 23 72 23 61 0 42 23 31 77 37 51 46 33 <br/>
    42 23 43 31 52 23 42 0 33 15 37 33 33 31 37 <br/>
    51 23 41 62 21 55 23 33 0 29 62 46 29 51 11 <br/>
    55 31 29 42 46 31 31 15 29 0 51 21 41 23 37 <br/>
    29 41 79 21 82 33 77 37 62 51 0 65 42 59 61 <br/>
    74 51 21 51 58 37 37 33 46 21 65 0 61 11 55 <br/>
    23 11 64 51 46 51 51 33 29 41 42 61 0 62 23 <br/>
    72 52 31 43 65 29 46 31 51 23 59 11 62 0 59 <br/>
    46 21 51 64 23 59 33 37 11 37 61 55 23 59 0 <br/>
  </p>
  
  ******
  
  <h3>The Genetic Algorithm</h3>
  <p>
    In this case I've used STL vector to represent the genes and the population.
    There are 100 genes and 50 tourneaments per generation.
    The crossing percentage is 70% and multability 15% (it reproduced the best results).
    All this can be changed in the global variables.
  </p>
  <p>
    Depending on the run, this algorithm takes around 200 generations for the optimum distance.
  </p>
</div>
