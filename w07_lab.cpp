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
   // long number = 111111;
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
   
   // cout << "\ta stack address:  " << &number           << endl;
   // cout << "\ta code address:   " << (void *)main  << endl;
   // cout << "\ta heap address:   " << (const void *)passMessage       << endl;
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
      cout << left   // left justify all values in their fields.
           << setw(5) << i              // offset is 8 bytes
           << setw(16) << &bow + i      // ADDRESS at offset;
           << setw(20) << *(&pLong + i +1) // the contents at address
                                           //(pLong + offset) HEXIDECIMAL
           << setw(19) << *(&bow + i)   // '<<' matches to the type, DECIMAL,
                                        // a long, is 8 bytes. 
                                        //  << setw(20) << hex << *(&bow + i)
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
   /// MARK'S THOUGHTS: I'm not liking this fixed offest approach.
   /// if it's what we need to do, ok. What other ways might this
   /// be done? Searching for the location of 11868464746679594 (*MAIN**)
   /// and then changing it? Same with the others that use hard offsets.
   /// Ex.:
   // keep bow's value where it is:
   int iBow;
   for (iBow = 1; *(&bow + iBow) != 11868464746679594; iBow++)
      ;
   *(&bow + iBow) = 11868602724609322;
   /// CAN YOU DO THE REST TANNER IF YOU AGREE THIS IS MORE ROBUST?
   //*(&bow + 32) = static_cast<long>("*main**");
   // *(&bow + 28) = 11868602724609322; // Set the decimal value to the value of "*main**"

   // change number in main() to 654321
   // This DOES work, but its hard coded to 30 indexes after bow. If something is added or deleted from the 
   // program, the stack would be different and this would not change the correct address's data
   *(&bow + 26) = 654321;

   // change pointerFunction in main() to point to pass
   // TANNER'S THOUGHTS: I know that the "pointerMessage" address is at bow + 29 (index 29), but I
   // don't know how to change it to point to the pointer "pass"
   /// MARK'S THOUGHTS: If we declare a new long pointer it will 
   /// be at the "top" of the stack.
   long *pBow;
   /// through pointer arithmetic we can jump between addresses just
   /// like we did above with bow above, but we search for fail. 
   /// (it is a long, just a void *() long).
   for (pBow = (long *)&pBow; *pBow != (long)fail; pBow++)
      // this is an empty for loop
      ;
   /// verify
   assert(*pBow == (long)fail);
   /// Now that we have the right address, change it.
   *pBow = (long)pass;

   // change message in main() to point to passMessage
   // TANNER'S THOUGHTS: I know that the "message" address is at bow + 28 (index 28),
   // but I don't know how to change it to point to "passMessage"
   /// MARK'S THOUGHTS: The pointer is a constant in this case, only 
   /// points to one address, but the contents there can change.
   // cout << "Bow + 28: "<< (&bow + 28) << endl;
   // cout << "passMessage: "<< (const void *)passMessage << endl;
   // *(&bow + 28) = (const void *)passMessage;
   /// going for a (long) casting of a (long *) of a (const void *)
   *(&bow + 24) = (long)(long *)passMessage;
   //
   ////////////////////////////////////////////////
}
