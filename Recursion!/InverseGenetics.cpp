/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function : printOutCodons(string protein, string current, Map<char, Set<string> >& codons)
 *
 * Takes in the already generated list of codons and remaining protein to which new codons will be associated.
 */
void printOutCodons (string protein, string current, Map<char, Set<string> >& codons){
	if(protein.size() == 0){
		cout<<current<<endl;
	} else {
		foreach (string codon in codons[protein[0]]){
			printOutCodons(protein.substr(1, protein.size() - 1), current + codon, codons);
		}
	}
}
/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	string empty = "";
	printOutCodons(protein, empty, codons);
}

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	string str = getLine(": ");
	listAllRNAStrandsFor(str, codons);
    /* [TODO: Implement this!] */
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
