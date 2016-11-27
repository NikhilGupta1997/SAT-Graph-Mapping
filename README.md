# SAT-Graph-Mapping

## Steps to Run
### Using Script
*Run* using `boot.sh G1_nodes G1_edges G2_nodes G2_edges`

### Without Script
*Compile* using `compile.sh`  
*Generate* a graphs using `generate.py G1_nodes G1_edges G2_nodes G2_edges > 'filename.graphs'`  
*Run* clause generator using `run1.sh filename`  
*Invoke* **MINISAT** using `minisat 'filename.satinput' 'filename.satoutput'`  
*Obtain* mapping using `run2.sh filename`  
*Check* correctness using `check.py 'filename.graphs' 'filename.mapping'`

## Authors
* [Nikhil Gupta](https://github.com/NikhilGupta1997)
* [Shardul Tripathi](https://github.com/Shardul-Tripathi)

Course Project under [**Prof. Mausam**](http://homes.cs.washington.edu/~mausam)

