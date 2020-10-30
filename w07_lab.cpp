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
   long number = 123456;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();
   
   // cout << "\tpassMessage address:  " << (const void *)passMessage  << endl;
   // cout << "\tfailMessage address:  " << (const void *)failMessage  << endl;
   // cout << "\tpass address:   " << (void *)pass  << endl;
   // cout << "\tfail address:   " << (void *)fail  << endl;
   
   // call the other functions
   one(number + 111111);

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
void one(long number)
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)
{
   // start your display of the stack from this point
   long bow = number + 111111;
   char text[8] = "**TWO**";
   long * pLong = NULL;
   char * pChar = NULL;

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
   for (long i = 35; i >= -10; i--)
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      // formatting tips used from: 
      // http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html
      cout << left                         // left justify all values in their fields.
           << setw(5) << i                 // offset is 8 bytes
           << setw(16) << &bow + i         // ADDRESS at offset;
           << setw(20) << *(&pLong + i +1) // the contents at address
                                           // (pLong + offset) HEXIDECIMAL
           << setw(19) << *(&bow + i)      // '<<' matches to the type, DECIMAL,
                                           // a long, is 8 bytes. 
                                           // << setw(20) << hex << *(&bow + i)
                                           // chars are 1 byte, 2 lines it up. 
                                           // on my macOS.
           << setw(18) << displayCharArray(text + (i * 8) - (2 * 8)) // CHARS
           << endl;
      //
      ////////////////////////////////////////////////
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()

   // change text in main() to "*main**"
   int iBow;

   // Loop through the offsets from "bow" until you find "*MAIN**"
   for (iBow = 1; *(&bow + iBow) != 11868464746679594 || iBow == 100; iBow++)
      // An empty loop. This just sets the value of iBow to get the offset
      ;
   // The decimal version of "*main**". This makes the char array in main() lowercase
   *(&bow + iBow) = 11868602724609322;


   // change number in main() to 654321
   // Loop through the offsets of "bow" until you find the decimal value "123456"
   for (iBow = 1; *(&bow + iBow) != 123456 || iBow == 100; iBow++)
      // An empty loop. This just sets the value of iBow to get the offset
      ;
   *(&bow + iBow) = 654321; // Change the value to "654321"


   // change pointerFunction in main() to point to pass
   long *pBow;
   // through pointer arithmetic we can jump between addresses just
   // like we did above with bow, but we search for fail. 
   // (it is a long, just a void *() long).
   for (pBow = (long *)&pBow; *pBow != (long)fail; pBow++)
      ;
   /// verify
   assert(*pBow == (long)fail);
   // Now that we have the right address, change it.
   *pBow = (long)pass;

   // change message in main() to point to passMessage
   /// going for a (long) casting of a (long *) of a (const void *)
   *(&bow + 24) = (long)(long *)passMessage;


   // Display the different types of aaddresses
   cout << "\n\tA Stack Address: " << &number                   << endl;
   cout << "\tA Code Address:  " << (void *)main              << endl;
   cout << "\tA Heap Address:  " << (const void *)passMessage << endl << endl;
   //
   ////////////////////////////////////////////////
}
