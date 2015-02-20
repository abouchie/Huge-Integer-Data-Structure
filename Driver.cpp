
/* Adrienne Bouchie
 * January 13th, 2015
 * Driver.cpp
 * 
 */


#include "HugeInteger.h"
#include <iostream>
using namespace std;


main() {

   HugeInteger op1;
   HugeInteger op2;
   HugeInteger results;
      		
   cin >> op1; 
   cin >> op2;

   cout << "op1 = " << op1 << endl;
   cout << "op2 = " << op2 << endl;


   results = op1.add( op2, results );
   int resultDigits = results.countDigits();
   results.setSigDigits( resultDigits );
   cout << "op1 + op2 = " << results << endl;
 
  
   results = op1.multiply( op2 );
   resultDigits = results.countDigits();
   results.setSigDigits( resultDigits );
   cout << "op1 * op2 = " << results << endl;
  

   if ( op1 == op2 ) {
	cout << "op1 is Equal to op2" << endl;
   } 
   else { 
	cout << "op1 is not equal to op2" << endl;
   }
   if ( op1 < op2 ) {
	cout << "op1 is less than op2" << endl;
   }
   else {	
	cout << "op1 is greater than op2" << endl;
   }

   if ( op1 == 0 ) {
	cout << "op1 is zero" << endl;
   }
   else {
	cout << "op1 is not equal to zero" << endl;
   }
  
   if ( op2 == 0 ) {
	cout << "op2 is zero" << endl;
   }
   else {
	cout << "op2 is not equal to zero" << endl;
   }

}
