class Change { 
	private: 
		int numTwenties; 
		int numTens; 
		int numFives; 
		int numOnes; 
		int numQuarters; 
		int numDimes; 
		int numNickels; 
		int numPennies; 
	public: 
		Change(); 
		Change( double dollars ); 
		Change( int twenties, int tens, int fives, int ones, int quarters, int dimes, int nickels, int pennies ); 
		double AmountInDollars(); 
		void SetAmount( double dollars ); 
		// I would probably add a method for setting/getting each of the twenties/tens/etc. 
		void SetTwenties( int twenties ); 
		int GetTwenties(); 
}; 