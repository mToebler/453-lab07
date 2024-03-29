#include <iostream>
#include <iomanip>
#include <string>
#include <assert.h>

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
void one(long number)            // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);         // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)            // 345678
{
   // start your display of the stack from this point
   long bow = number + 111111;   // 456789
   char text[8] = "**TWO**";
   long * pLong = NULL;
   char * pChar = NULL;

   // header for our table. Use these setw() offsets in your table
   cout << '[' << setw(1) << 'i' << ']'
        << setw(16) << "address"
        << setw(18) << "hexadecimal"
        << setw(21) << "decimal"
        << setw(18) << "characters"
        << endl;
   cout << "--+"
        << "----------------+"
        << "-----------------+"
        << "--------------------+"
        << "-----------------+\n";       
   for (long i = 35; i >= -10; i--)
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      // formatting tips used from: 
      // http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node83.html  
      // reinterpret_cast: compiler directive
      // https://en.cppreference.com/w/cpp/language/reinterpret_cast    
      char * charArray = reinterpret_cast <char *> (&bow + i);
      cout << left << right << dec // right justify all values in their fields.
           << setw(3)  << i                // offset is 8 bytes
           << setw(16) << &bow + i         // ADDRESS at offset;
      //   << setw(20) << *(&pLong + i +1) // the contents at address
           << setw(18) << hex << *(&bow + i)                                            
                                             // (pLong + offset) HEXIDECIMAL
           << setw(21) << dec << *(&bow + i) // DECIMAL,
                                           // a long, is 8 bytes. 
                                           // chars are 1 byte, 2 lines it up. 
                                           // on my macOS.
           << setw(18) << displayCharArray(charArray) // CHARS
      //   << setw(18) << displayCharArray(text + (i * 8) - (2 * 8)) // CHARS
           << endl;
      //
      ////////////////////////////////////////////////
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()

   // change text in main() to "*main**"
   // Originally we used bow's offsets explicity, e.g., *(&bow + 28)
   // but the hardcoded values fell apart when more was piled/removed
   // from the stack. 
   int iBow;
   int * pHeap = NULL;
   // Loop through the offsets from "bow" until you find "*MAIN**"
   // Find the current value and store the offset in iBow.
   for (iBow = 1; *(&bow + iBow) != 11868464746679594 || iBow == 100; iBow++)
      ; // An empty loop. Sets the value of iBow to the right offset
   // The decimal version of "*main**". This overwrites the char * in
   // main() with lowercase values
   *(&bow + iBow) = 11868602724609322;

   // change number in main() to 654321
   // Loop through the offsets from "bow" until you find the decimal 
   // value "123456"
   for (iBow = 1; *(&bow + iBow) != 123456 || iBow == 100; iBow++)
      ; // An empty loop. Sets the value of iBow to the right offset
   *(&bow + iBow) = 654321; // Change the value to "654321"


   // change pointerFunction in main() to point to pass
   
   // through pointer arithmetic we can jump between addresses just
   // like we did above with bow, but we search for fail. 
   // (it is a long, just a void *() long).
   for (iBow = 1; *(&bow + iBow) != (long)fail || iBow == 100; iBow++)
      ; // An empty loop. Sets the value of iBow to the right offset
   // verify
   assert(*(&bow + iBow) == (long)fail);
   // Now that we have the right address, change it.
   *(&bow + iBow) = (long)pass;

   // change message in main() to point to passMessage
   // going for a (long) casting of a (long *) of a (const void *)
   for (iBow = 1;
        *(&bow + iBow) != (long)(long *)failMessage || iBow == 200;
        iBow++)
      ;

   *(&bow + iBow) = (long)(long *)passMessage;


   // Display the different types of aaddresses
   pHeap = new int(1);
   cout << "\n\tA Stack Address: " << &number      << endl
        << "\tA Code Address:  " << (void *) main  << endl
        << "\tA Heap Address:  " << (void *) pHeap << endl 
        << endl;
   delete (pHeap);
   pHeap = NULL;
   //
   ////////////////////////////////////////////////
}
