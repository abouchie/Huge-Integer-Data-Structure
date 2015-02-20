/* 
 * Adrienne Bouchie
 * January 15, 2015
 * HugeInteger.h
 * This program defines the HugeInteger class 
 *
 */


#include <iostream>
#include <string>
using namespace std;

   class HugeInteger {
	
	friend istream &operator>> ( istream &, HugeInteger & );
	friend ostream &operator<< ( ostream &, HugeInteger & );
	
	public:
	   HugeInteger();
	   HugeInteger( int aop[]); 

	   static const int getMAXDIGITS();
 	   void displayDigits();
	   int countDigits();
	   void setSigDigits( int );
	   int getSigDigits();
	   
	   HugeInteger add( HugeInteger, HugeInteger &  );	
	   HugeInteger multiply( HugeInteger );

	   bool operator ==( HugeInteger & );
	   bool operator !=( HugeInteger & );
 	   bool operator >( HugeInteger & );
	   bool operator <( HugeInteger & );
	   bool operator >=( HugeInteger & );
	   bool operator <=( HugeInteger & );	   
	   bool operator ==( int );
	
	private:

	   static const int MAXDIGITS = 40;
           int digits[MAXDIGITS];
           int sigDigits;

	   bool isEqualTo( const HugeInteger & );
	   bool isNotEqualTo( const HugeInteger & );
	   bool isGreaterThan( const HugeInteger & );
	   bool isLessThan( const HugeInteger & );
	   bool isGreaterThanOrEqualTo( const HugeInteger & );
	   bool isLessThanOrEqualTo( const HugeInteger & );
	   bool isZero();	

};
