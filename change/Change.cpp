Change::Change() 
{ 
	SetAmount( 0.00 ); 
} 
Change::Change( double dollars ) { 
	SetAmount( dollars ); 
} 
void SetAmount( double dollars ) { 
	numTwenties = 0; 
	numTens = 0; 
	numFives = 0; 
	numOnes = 0; 
	numQuarters = 0; 
	numDimes = 0; 
	numNickels = 0; 
	numPennies = 0; 
	while( dollars >= 20.00 ) { 
		numTwenties++; dollars -= 20.00; 
	} 
	while( dollars >= 10.00 ) { 
		numTens++; dollars -= 10.00; 
	} 
	while( dollars >= 5.00 ) { 
		numFives++; dollars -= 5.00; 
	} 
	while( dollars >= 1.00 ) { 
		numOnes++; dollars -= 1.00; 
	} 
	while( dollars >= 0.25 ) { 
		numQuarters++; dollars -= 0.25; 
	} 
	while( dollars >= 0.10 ) { 
		numDimes++; dollars -= 0.10; 
	} 
	while( dollars >= 0.05 ) { 
		numNickels++; dollars -= 0.05; 
	} 
	while( dollars >= 0.01 ) { 
		numPennies++; dollars -= 0.01; 
	} 
} 
double AmountInDollars() 
{ 
	return 20.0*numTwenties + 10.0*numTens + 5.0*numFives + numOnes + 0.25*numQuarters + 0.1*numDimes + 0.05*numNickels + 0.01*numPennies; 
}