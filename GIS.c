#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Symbolic Constants
#define LINEAR 1
#define STOCK 1 
#define FORM 0
#define CHECKOUT 0
#define MAX_ITEM_NO 21	
#define DATAFILE "inventory.dat"
#define MAX_Quantity 999
#define SKU_MAX 999
#define SKU_MIN 100

//Structure for the grocery items
struct Item {
  double price;
  int sku;
  int isTaxed;
  int quantity;
  int minQuantity;
  char name[21];
};

//Global Variable
const double TAX = 0.13;

//Milestone 1 Function Headers
void printWelcome(void);
void printGoodBye(void);
void printTitle(void);
void printFooter(double gTotal);
void clearKeyboard(void);
void pause(void);
int getInteger(void);
double getDouble(void);
int getIntLimited(int, int);
double getDoubleLimited(double, double);

//Milestone 2 Function Headers
bool getYesOrNo(void);
int getMenuChoice(void);
void runInventorySystem(void);

//Milestone 3 Function Headers
double totalAfterTax(struct Item item);
bool isQuantityLow(struct Item * item);
struct Item enterItem(int sku);
void displayItem(struct Item * item, int linear);
void listItems(struct Item[], int NoOfItems);
bool locateItem(struct Item item[], int NoOfRecs, int sku, int * index);

//Milestone 4 Function Headers
void search(struct Item item[], int NoOfRecs);
void updateItem(struct Item * itemPointer);

//Milestone 5 Function Headers
int loadItems(struct Item * item, char fileName[], int * NoOfRecsPtr);

//Main Function
int main(void) {
    printWelcome();
    runInventorySystem();
    printGoodBye();
  }

//Milestones 1 function Prototypes
//Prints the Title of the Inventory System
void printWelcome(void) {
    printf("---===Welcome To Sanket's Grocery Inventory System ===---\n\n");
  }
//Prints the footer at the end of the program
void printGoodBye(void) {
    printf("Sanket Kasote");
  }
//Prints a table that consists of the item information
void printTitle(void) {
    printf("Row |SKU| Name               | Price  |Taxed| Quantity | Min |   Total    |Atn\n");
    printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
  }
//Prints the end of the table that consists 
void printFooter(double gTotal) {
    printf("--------------------------------------------------------+----------------\n");
    if (gTotal > 0)
      printf("                                            Grand Total: |     1234.57   \n");
  }
//
void clearKeyboard(void) {
    char get_character;
    do {
      scanf("%c", & get_character);
    }
    while (strncmp( & get_character, "\n", 1) != 0);
  }
  //
void pause(void) {
    printf("Press <ENTER> to continue...");
    clearKeyboard();
  }
  //Function checks if the user entered a integer and pressed entered
int getInteger(void) {
    int get_integer;
    char get_character;
    scanf("%d%c", & get_integer, & get_character);
    while (strncmp( & get_character, "\n", 1) != 0) {
      clearKeyboard();
      printf("Invalid integer, please try again: ");
      scanf("%d%c", & get_integer, & get_character);
    }
    return get_integer;
  }
  //Function checks if the user has entered a double and pressed enter
double getDouble(void) {
    double get_double;
    char get_character;
    scanf("%lf%c", & get_double, & get_character);
    while (strncmp( & get_character, "\n", 1) != 0) {
      clearKeyboard();
      printf("Invalid number, please try again: ");
      scanf("%lf%c", & get_double, & get_character);
    }
    return get_double;
  }
  //Function 
int getIntLimited(int lowerLimit, int upperLimit) {
  int intlimited;
  intlimited = getInteger();
  while (intlimited < lowerLimit || intlimited > upperLimit) {
    printf("Invalid value, %d <= value <= %d: ", lowerLimit, upperLimit);
    intlimited = getInteger();
  }
  return intlimited;
}

double getDoubleLimited(double lowerLimit, double upperLimit) {
    double dblelimited;
    dblelimited = getDouble();
    while (dblelimited < lowerLimit || dblelimited > upperLimit) {
      printf("Invalid value, %lf <= value <= %lf: ", lowerLimit, upperLimit);
      dblelimited = getDouble();
    }
    return dblelimited;
  }
  /**************************************************************/
  //Milestones 2 function Prototypes
  //Recieves the user input and checks if the user input matches Y or N
bool getYesOrNo(void) {
  char ch = 'x';
  int RET = 0;

  do {
    ch = getchar();

    if (!(ch == 'Y' || ch == 'y') && !(ch == 'N' || ch == 'n')) { //invalid input
      printf("Only (Y)es or (N)o are acceptable: ");
    }
    clearKeyboard(); //because they enter something regardless
    //while the user didnt enter upper or lowercase y or n
  } while (!(ch == 'Y' || ch == 'y') && !(ch == 'N' || ch == 'n'));

  //Returns 1 if the character input matches "Y" or "y"
  if (ch == 'Y' || ch == 'y') {
    RET = 1;
  }
  //Returns 0 if the character input matches "Y" or "y"
  if (ch == 'n' || ch == 'N') {
    RET = 0;
  }
  return RET;
}

// Prints Menu for User to select an option
int getMenuChoice(void) {
    int value = 0;
    printf("1- List all items\n");
    printf("2- Search by SKU\n");
    printf("3- Checkout an item\n");
    printf("4- Stock an item\n");
    printf("5- Update Item\n");
    printf("6- Delete item\n");
    printf("7- Search by name\n");
    printf("0- Exit program\n");
    printf("> ");
    value = getInteger();
    while (value < 0 || value > 7) {
      printf("Invalid value, 0 <= value <= 7: ");
      value = getInteger();
    }
    return value;
  }
  // Function runs series of different option depe
void runInventorySystem(void) {
    int skuFound;
    int sku;
    int index;
    int call;
    struct Item inventory[MAX_ITEM_NO];
    int value = 0, done = 0;
    printf("Loading inventory data...\n");
    call = loadItems(inventory, DATAFILE, & index);
    if (call == 0)
      printf("Cannot open inventory.dat.\n");
    else {
      pause();

      while (!done) {

        value = getMenuChoice();
        switch (value) {
        case 1:
          printf("List!\n");
          listItems(inventory, MAX_ITEM_NO);
          clearKeyboard();
          break;
        case 2:
          printf("Search!\n");
          search(inventory, MAX_ITEM_NO);
          clearKeyboard();
          break;
        case 3:
          printf("Checkout: NOT IMPLEMENTED\n");
          clearKeyboard();
          break;
        case 4:
          printf("Stock: NOT IMPLEMENTED\n");
          clearKeyboard();
          break;
          //case 5 Updates the items in the inventory based on 
          //the new information entered by the user
        case 5:
          printf("Update Item!\n");
          printf("Please enter the SKU: ");
          sku = getIntLimited(SKU_MIN, SKU_MAX);
          skuFound = locateItem(inventory, 21, sku, & index);
          if (skuFound) {
            displayItem( & inventory[index], LINEAR);
            updateItem( & inventory[index]);
          } else printf("Item not found!\n");
          pause();
          clearKeyboard();
          break;
        case 6:
          printf("Delete: NOT IMPLEMENTED\n");
          pause();
          clearKeyboard();
          break;
        case 7:
          printf("Search: NOT IMPLEMENTED\n");
          pause();
          clearKeyboard();
          break;
        case 0:
          printf("Exit the program? (Y)es/(N)o:");
          done = getYesOrNo();
          break;
        }
      }
    }
  }
  /**************************************************************/
  //Milestones 3 function Prototypes
  //Function checks if the Item has been taxed or not
  //Adds tax to non taxed items 
double totalAfterTax(struct Item item) {
    double tax;
    tax = 0;
    if (item.isTaxed == 1) {
      tax = (item.price * item.quantity) + ((item.price * item.quantity) * TAX);
    } else if (item.isTaxed == 0) {
      tax = item.quantity * item.price;
    }
    return tax;
  }
  //Function return 1 or 0 depending 
  //on if the quantity is lower than the minuantity
bool isQuantityLow(struct Item * item) {
  if (item -> quantity < item -> minQuantity) {
    return 1;
  } else {
    return 0;
  }
}

struct Item enterItem(int sku) {
    struct Item entry;

    printf("        SKU: %d\n", sku);
    entry.sku = sku;

    printf("       Name: ");
    scanf(" %20[^\n]", entry.name);
    clearKeyboard();

    printf("      Price: ");
    scanf("%lf", & entry.price);

    printf("   Quantity: ");
    scanf(" %d", & entry.quantity);

    printf("Minimum Quantity: ");
    scanf(" %d", & entry.minQuantity);

    printf("   Is Taxed: ");
    entry.isTaxed = getYesOrNo();

    return entry;
  }
  //Prints a item in two different formats - Linear & Form
  //
void displayItem(struct Item * item, int linear) {
  double totalprice;
  totalprice = totalAfterTax( * item);
  if (linear == 1) {
    if (item -> isTaxed == 1) {
      printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|\n",
        item -> sku, item -> name, item -> price, item -> quantity, item -> minQuantity, totalprice);
    } else if (item -> isTaxed == 0) {
      printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|\n",
        item ->sku, item -> name, item -> price, item -> quantity, item -> minQuantity, totalprice);
    } else if (item -> quantity >= item ->minQuantity)
      printf("\n");
    else if (item -> quantity < item -> minQuantity)
      printf("***\n");

  } else {
    printf("                 SKU: %d\n", item -> sku);
    printf("                Name: %s\n", item -> name);
    printf("               Price: %.2f\n", item -> price);
    printf("            Quantity: %d\n", item -> quantity);
    printf("    Minimum Quantity: %d\n", item -> minQuantity);
    if (item -> isTaxed == 1)
      printf("            Is Taxed: Yes\n");
    else
      printf("            Is Taxed: No\n");
    if (item -> quantity <= item -> minQuantity)
      printf("WARNING: Quantity low, please order ASAP!!!\n");
  }
}
//Lists all the items in the inventory 
void listItems(struct Item item[], int NoOfItems) {
    int i = 0;
    float grandtotal = 0;
    printTitle();
    for (i = 0; i < NoOfItems; i++) {
      printf("%-4d", i + 1);
      displayItem( & item[i], 1);
      grandtotal = totalAfterTax(item[i]);
    }
    printFooter(grandtotal);
  }
// Receives an SKU integer for the user and searches for the item array
bool locateItem(struct Item item[], int NoOfRecs, int sku, int * index) {
  int temp = 0;
  int i;
  for (i = 0; i < NoOfRecs; i++) {
    if (sku == item[i].sku) { * index = i;
      temp = 1;
    }
  }

  return temp;
}

/**************************************************************/
//Milestones 4 function Prototypes
//Searches for a item in the inventory by using the sku code inputted by the user
void search(struct Item item[], int NoOfRecs) {
  int skuFound;
  int index;
  int sku;
  printf("Please enter the SKU: ");
  sku = getIntLimited(SKU_MIN, SKU_MAX);

  skuFound = locateItem(item, NoOfRecs, sku, & index);
  if (skuFound) {
    displayItem( & item[index], FORM);
  } else {
    printf("Item not found!\n");
  }
}

struct Item itemEntry(int sku) {
  struct Item item;
  item.sku = sku;

  printf("        SKU: %d\n", item.sku);
  printf("       Name: ");
  scanf("%20[^\n]", item.name);
  printf("      Price: ");
  scanf("%lf", & item.price);
  printf("   Quantity: ");
  scanf("%d", & item.quantity);
  printf("Minimum Qty: ");
  scanf("%d", & item.minQuantity);
  printf("   Is Taxed: ");
  scanf("%d", & item.isTaxed);
  item.isTaxed = (getYesOrNo());

  return item;
}

void updateItem(struct Item * itemPointer) {
  struct Item buffer;
  int dataOverWrite;
  printf("Enter new data:\n");
  buffer = itemEntry(itemPointer -> sku);
  printf("Overwrite old data? (Y)es/(N)o: ");

  dataOverWrite = getYesOrNo();

  if (dataOverWrite) {
    printf("--== Updated! ==--\n"); * (itemPointer) = buffer;
  } else {
    printf("--== Aborted! ==--\n");
  }
}

/**************************************************************/
//Milestones 5 function Prototypes
//Load Items Function opens a external file and reads the data
//LoadItems Functions uses this data for the function to operate
int loadItems(struct Item * item, char fileName[], int * NoOfRecsPtr) {
  int i;
  int FILE_OPENED;
  FILE * dataFile;
  dataFile = fopen(fileName, "r");

  if (dataFile != NULL) //if file opened
  {
    FILE_OPENED = 1;
    for (i = 0; i < MAX_ITEM_NO; i++) {
      fscanf(dataFile, "%d,%[^,],%lf,%d,%d,%d", & item[i].sku, item[i].name, & item[i].price, & item[i].isTaxed, & item[i].quantity, & item[i].minQuantity);
    }
  } else {
    FILE_OPENED = 0;
  }

  fclose(dataFile);
  return FILE_OPENED;
}
