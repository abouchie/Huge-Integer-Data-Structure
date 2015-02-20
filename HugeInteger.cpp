/*
 * Adrienne Bouchie
 * January 15, 2015
 * HugeInteger.cpp
 * This program implements the HugeInteger class 
 *
 */

#include "HugeInteger.h"
#include <cstdlib>
#include <cstdio>  
#include <string>


// Friend function that overloads the cin operator to allow the user to input a number up to 40 integers long and stores it in an object of HugeInteger
   istream &operator>> ( istream &input, HugeInteger &op ) {

	string numberEntered;
	char charDigits;
	int digit = 0;  
	int sigDigits = 0;

	do {
		cout << "Enter a digit up to 40 characters long:" << endl;
		cin >> numberEntered;

		if ( numberEntered.length() > 40 ) {
			cout << "Error! The number entered is larger than 40 characters. Try again!" << endl;
		}
	
	} while ( numberEntered.length() >= 40 );
		
	
	for ( int i = numberEntered.length()-1, j = HugeInteger::getMAXDIGITS()-1; i >= 0 && j >= 0; i--, j-- ) {
		charDigits = numberEntered[i];
		digit = atoi( &charDigits );
		op.digits[j] = digit;
	}

	sigDigits = op.countDigits();
	op.setSigDigits( sigDigits );	 	


	return( input );
   }


// Friend function that overloads the cout operator to display the digits in the object of HugeInteger
   ostream &operator<< ( ostream &output, HugeInteger &op ) {

	op.displayDigits();

   	return( output ); // do i need to return output? displayDigits is a void function
   }

// Constructor that initializes each element in the digits array to 0
   HugeInteger::HugeInteger() {
	for ( int i=0; i < MAXDIGITS; i++ ) {
		digits[i] = 0;
	}
   }

	
// add int numEntered for number of digits entered -- && i < numEntered; i ++    
   HugeInteger::HugeInteger( int aop[] ) {
	for ( int i=0; i < MAXDIGITS; i++ ) {
		digits[i] = aop[i];	
	}
	sigDigits = countDigits();
   }


// Function that returns the static const MAXDIGITS	 
  const int HugeInteger::getMAXDIGITS() {
	return( MAXDIGITS );
   }	

 
// Function that displays the digits in the HugeInteger object
   void HugeInteger::displayDigits() {
			
	int firstDigit = MAXDIGITS - sigDigits;

	for ( int i = firstDigit; i < MAXDIGITS; i++ ) {
                cout << digits[i];
	}
	cout << endl;
   } 


// Function that counts the number of digits in an integer
   int HugeInteger::countDigits() {
	int zeroCounter = 0;
	int sigDig = 0;
	
	for ( int i =0; i < MAXDIGITS; i++ ) {
		if ( digits[i] != 0 ) {
			break;
		}
		else
			zeroCounter++;
	}
   
	sigDig = MAXDIGITS - zeroCounter; 	// to calculate sigDigits subtract the amount of zero's from MAXDIGITS

	return ( sigDig );	
   }

 
// Function that sets the significant digits for each object instantiated
   void HugeInteger::setSigDigits( int digitsEntered ) {

  	sigDigits = digitsEntered;

   }


// Function that returns the significant digits of the object it is called on
   int HugeInteger::getSigDigits() {

	return( sigDigits );
   }


// Function that adds the object passed to the object the function is called on and stores the result in a third object, which is then returned to the driver
    HugeInteger HugeInteger::add( HugeInteger op2, HugeInteger &result ) {
	
	bool full = false;
	int tempVar = 0;	
	int carry = 0;
	int numberOfDigits = 0;

	
	// to check which object has the greatst sigDigits to use in the loop
	if ( sigDigits >= op2.sigDigits && sigDigits >= result.sigDigits ) {
		numberOfDigits = sigDigits;
	}
	else if ( op2.sigDigits >= sigDigits && op2.sigDigits >= result.sigDigits ) {
		numberOfDigits = op2.sigDigits;
	}
	else {
		numberOfDigits = result.sigDigits;
	}
	
	for (int i = MAXDIGITS-1, n=0; i >= 0 && n <= numberOfDigits; i--, n++ ) {    
           	tempVar = digits[i] + op2.digits[i] + carry;
               	
		if ( tempVar >= 10 ) {
			carry = 1;
			tempVar -= 10;
		}
		
		else {
			carry = 0;
		}
               
		// to check if there is carry after it loops through the last sigDigit 	
		if ( n ==  numberOfDigits && carry > 0 ) {
                        result.digits[i-1] = carry;
		}
		
		// to check if there is overflow when the entire array is full
		if ( i == 0 && carry > 0 ) {
			cout << "ERROR: Result is greater than 40 integers" << endl;
			break;
		}
		
	
		result.digits[i] = tempVar;     // store tempVar in result object
	}
	  

	return( result );	
   } 	


// Function that takes in an object, multiplies it by the object it was called on and stores it in a third object called result, which is returned to the driver
   HugeInteger HugeInteger::multiply( HugeInteger op2 ) {
	
	int tempVar = 0;
	int carry = 0;
	int digitsCounter = 0;
	int numberOfDigits = 0;
	HugeInteger tempResult;
	HugeInteger result;	
	bool isFull = false;

	// to check which object has more sigDigits for the loop
	if ( sigDigits >= op2.sigDigits ) {
                numberOfDigits = sigDigits;
        }	
        else {
                numberOfDigits = op2.sigDigits;
        } 	
	
	for ( int i = getMAXDIGITS()-1, k = 0; i >= 0 && k < numberOfDigits; i--, k++ ) {   		// outer loop = op1
		for ( int j = getMAXDIGITS()-1, n = 0; j >= 0 && n <= numberOfDigits; j--, n++ ) {	// inner loop = op2
			tempVar= ( digits[i] * op2.digits[j] ) + carry;
			carry = 0;
	
			tempResult.digits[j-k] = tempVar % 10;
			carry = tempVar / 10;
	
			// to check if there is carry after loop ends
			if ( n == numberOfDigits && carry > 0 ) {	
				tempResult.digits[j-n] = carry;	
			}
			
			// to check if there is any overflow after the entire array has been filled
			if ( i == 0 && carry > 0  ) {
				cout << "ERROR: Result is larger than 40 integers" << endl;
				break;
			}
		 
		
		} // end of inner loop
		

		digitsCounter = tempResult.countDigits(); // count sigDigits of tempResult
		tempResult.setSigDigits( digitsCounter ); // store sigDigits in object tempResult
			
		
		result = result.add( tempResult, result ); // call add() to add tempResult to result and store it in result
			
		// to set tempResult to 0 for the next iteration
		for ( int m = getMAXDIGITS()-1; m >= 0; m-- ) {
			tempResult.digits[m] = 0;
		}
	
	} // end of outer loop		
	
	return( result );
   }


// Function that overloads the == operator to see if one object is equal to another object of HugeInteger
   bool HugeInteger::operator ==( HugeInteger &op2 ) {

	return( isEqualTo( op2 ));

   }


// Function that overloads the != operator to see if one object is not equal to another object of HugeInteger
   bool HugeInteger::operator !=( HugeInteger &op2 ) {
           
	return( isNotEqualTo( op2 ));
       
   }


// Function that overloads the > operator to see if one object is greater than another object of HugeInteger
   bool HugeInteger::operator >( HugeInteger &op2 ) {
           
        return( isGreaterThan( op2 ));
      
   }                

// Function that overloads the < operator to see if one object is less than another object of HugeInteger
   bool HugeInteger::operator <( HugeInteger &op2 ) {

	return( isLessThan ( op2 ));

   }

// Function that overloads the <= operator to see if one object is greater than or equal to another object of HugeInteger
   bool HugeInteger::operator >=( HugeInteger &op2 ) {

        return( isGreaterThanOrEqualTo ( op2 ));

   }

// Function that overloads the <= operator to see if one object is less than or equal to another object of HugeInteger
    bool HugeInteger::operator <=( HugeInteger &op2 ) {

        return( isLessThanOrEqualTo ( op2 ));

   }

// Function that overloads the == operator to see if the object it is called on is equal to zero
   bool HugeInteger::operator ==( int zero ) {

        return( isZero());

   }


// Function that checks to see if two object of HugeInteger are equal and returns a boolean variable 
   bool HugeInteger::isEqualTo( const HugeInteger &op2 ) {
  	bool isEqual = true;
    	int count = 0;

	for ( int i = MAXDIGITS-1; i >= 0; i -- ) {
		if ( digits[i] == op2.digits[i] ) {
			count++;
		}
	} 
	
	if ( count == sigDigits && count == op2.sigDigits ) {
		isEqual = true;	
	}
	else {
		isEqual = false;
	}

	return( isEqual );
   }


// Function that checks to see if two objects of HugeInteger are not equal and returns a boolean variable
   bool HugeInteger::isNotEqualTo( const HugeInteger &op2 ) {

	bool isEqual = true;
	int count = 0;

	for ( int i = MAXDIGITS-1; i >= 0; i-- ) {
		if ( digits[i] == op2.digits[i] ) {
			count++;
		}
	}	

	if ( count == sigDigits && count == op2.sigDigits ) 
		isEqual = true;
	else
		isEqual = false;
  	 
	
	return( isEqual );
   }


// Function that checks to see if an object of HugeInteger is greater than another object of HugeInteger
   bool HugeInteger::isGreaterThan( const HugeInteger &op2 ) {
	
	bool isGreaterThan = false;
	int op1SigDig = 0;
	int op2SigDig = 0;


	if ( sigDigits > op2.sigDigits ) {
		isGreaterThan = true;
	}
	else if ( sigDigits < op2.sigDigits ) {
		isGreaterThan = false;
	}
	
	else {
		for ( int i = MAXDIGITS-1, n = 0; i >= 0, n <= sigDigits; i--, n++ ) {
                        if ( n == sigDigits && digits[i] > op2.digits[i] ) {
                                isGreaterThan = true;
                        }
                        else {
                                isGreaterThan = false;
                        }

                }
	
	
		cout << "There is an error " << endl;
		isGreaterThan = false;
	}

   return( isGreaterThan );
   }


// Function that checks if an object of HugeInteger is less than the object passed to it
   bool HugeInteger::isLessThan( const HugeInteger &op2 ) {

        bool isLessThan = true;

        if ( sigDigits < op2.sigDigits ) {
                isLessThan = true;
        }
        
        if ( sigDigits > op2.sigDigits ) {
                isLessThan = false;
        }

        else {
                for ( int i = MAXDIGITS, n = 0; i >= 0, n <= sigDigits; i--, n++ ) {
                        if ( n == sigDigits && digits[i] > op2.digits[i] ) {
                                isLessThan = false;
                        }
                        else if ( n == sigDigits && digits[i] < op2.digits[i] ) {
                                isLessThan = true;
                        }

                }

        }

   return( isLessThan );
   
   }


// Function that checks to see if an object of HugeInteger is greater than or equal to another object of HugeInteger
   bool HugeInteger::isGreaterThanOrEqualTo( const HugeInteger &op2 ) {

	bool isGreaterThanOrEqualTo = true;
        int count = 0;

        
	if ( sigDigits > op2.sigDigits ) { 
                isGreaterThanOrEqualTo = true;
	}
	else if ( sigDigits < op2.sigDigits ) {
		isGreaterThanOrEqualTo = false;
	}
        else {
		for ( int i = MAXDIGITS, n = 0; i >= 0, n <= sigDigits; i--, n++ ) {	
			if ( n == sigDigits && digits[i] >= op2.digits[i] ) {
				isGreaterThanOrEqualTo = true;
			}
			else if ( n == sigDigits && digits[i] < op2.digits[i] ) {
				isGreaterThanOrEqualTo = false;
			}
		
		}

	}  
        
        return( isGreaterThanOrEqualTo );
   }


// Function that checks to see if the object of HugeInteger is greater than or equal to the object being passed to it
   bool HugeInteger::isLessThanOrEqualTo( const HugeInteger &op2 ) {

   	bool isLessThanOrEqualTo = true;
        
        if ( sigDigits < op2.sigDigits ) {
                isLessThanOrEqualTo = true;
        }
        else if ( sigDigits > op2.sigDigits ) {
                isLessThanOrEqualTo = false;
        }
        else {
                for ( int i = MAXDIGITS-1, n = 0; i >= 0, n <= sigDigits; i--, n++ ) {  
                        if ( n == sigDigits && digits[i] <= op2.digits[i] ) {
                                isLessThanOrEqualTo = true;
                        }
                        else if ( n == sigDigits && digits[i] > op2.digits[i] ) {
                                isLessThanOrEqualTo = false;
                        }
                        
                }

        }

        return( isLessThanOrEqualTo );

}


// Function that checks if the object passed to it is zero 
   bool HugeInteger::isZero() {
 
	bool isZero = true;

   	for ( int i = MAXDIGITS-1, n = 0; i >= 0, n <= sigDigits; i--, n++ ) {
		if ( digits[i] !=0 ) {
			isZero = false;
			break;
		}
		else {
			isZero = true;
		}
	}

	return ( isZero );
   }

