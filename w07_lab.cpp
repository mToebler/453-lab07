#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   // long number = 123456;
   long number = 111111;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
// string displayCharArray(const char * p)
string displayCharArray(const char * p) 
{
   string output;
   for (int i = 0; i < 8; i++)
      output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 345678
{
   // start your display of the stack from this point
   long bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * pLong = NULL;
   // double * pLong = NULL;
   char * pChar = NULL;
   //TODO: remove this line and next 2
   long bow2 = bow + 111111;     // 544444
   long bow3 = bow2 + 111111; // 544444
   // header for our table. Use these setw() offsets in your table
   cout << '[' << setw(2) << 'i' << ']'
        << setw(15) << "address"
        << setw(20) << "hexadecimal"
        << setw(20) << "decimal"
        << setw(18) << "characters"
        << endl;
   cout << "----+"
        << "---------------+"
        << "-------------------+"
        << "-------------------+"
        << "-----------------+\n";
   for (long i = 30; i >= -30; i--)   // You may need to change 24 to another number
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      // for formatting tips see: 
      // http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html
      cout << left   // left justify all values in their fields.
           << setw(5) << i              // offset is 8 bytes
           << setw(15) << &bow + i      // address at offset;
           << setw(21) << *(&pLong + i +1) // the contents of mem at address(pLong + offset)
           << setw(22) << *(&bow + i)   // << outputs to the type
                                        // a long is 8 bytes.  double would work here as well
                                        //   << setw(20) << hex << *(&bow + i)
           << setw(18) << displayCharArray(text + (i * 8)) // to get to the base of text //
      << endl;
      ; // hexadecimal
      //
      ////////////////////////////////////////////////
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()
                                                                                
   // change text in main() to "*main**"

   // change number in main() to 654321

   // change pointerFunction in main() to point to pass

   // change message in main() to point to passMessage

   //
   ////////////////////////////////////////////////
}
