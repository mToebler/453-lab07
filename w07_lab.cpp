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
   
   cout << "\ta stack address:  " << &number           << endl;
   cout << "\ta code address:   " << (void *)main  << endl;
   cout << "\ta heap address:   " << (const void *)passMessage       << endl;
   // call the other functions
   one(number + 111111);     // 222222

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
void one(long number)               // 222222
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 3333333
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 333333
{
   // start your display of the stack from this point
   long bow = number + 111111;     // 444444
   char text[8] = "**TWO**";
   long * pLong = NULL;
   // double * pLong = NULL;
   char * pChar = NULL;
   //TODO: remove this line and next 2
   long bow2 = bow + 111111;     // 555555
   long bow3 = bow2 + 111111; // 666666
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
   long bow4 = bow3 + 111111; // 777777
   for (long i = 35; i >= -30; i--)
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      // formatting tips used from: 
      // http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html
      cout << left   // left justify all values in their fields.
           << setw(5) << i              // offset is 8 bytes
           << setw(16) << &bow + i      // address at offset;
           << setw(20) << *(&pLong + i +1) // the contents of mem at address
                                           //(pLong + offset) HEXIDECIMAL
           << setw(19) << *(&bow + i)   // '<<' matches to the type, DECIMAL,
                                        // a long, is 8 bytes.  double would 
                                        // have worked here as well
                                        //  << setw(20) << hex << *(&bow + i)
                                        // chars are 1 byte, 2 lines it up. 
           << setw(18) << displayCharArray(text + (i * 8) - (2 * 8)) // CHARS
           << endl;
      //
      ////////////////////////////////////////////////
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()

   // change text in main() to "*main**"
   
   //*(&bow + 32) = static_cast<long>("*main**");
   *(&bow + 32) = 11868602724609322; // Set the decimal value to the value of "*main**"

   // change number in main() to 654321
   // This DOES work, but its hard coded to 30 indexes after bow. If something is added or deleted from the 
   // program, the stack would be different and this would not change the correct address's data
   *(&bow + 30) = 654321;

   // change pointerFunction in main() to point to pass
   // TANNER'S THOUGHTS: I know that the "pointerMessage" address is at bow + 29 (index 29), but I
   // don't know how to change it to point to the pointer "pass"
    

   // change message in main() to point to passMessage
   // TANNER'S THOUGHTS: I know that the "message" address is at bow + 28 (index 28),
   // but I don't know how to change it to point to "passMessage"
   
   //
   ////////////////////////////////////////////////
}
