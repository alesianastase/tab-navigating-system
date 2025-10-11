Data Structures
-> tabLink and tabsList
The tabLink structure is used to navigate between browser tabs.


All tabs are stored in a doubly linked list (tabsList).


A sentinel node (santi) connects the tabsList and tabLink structures, simplifying traversal and ensuring consistent behavior at the list boundaries.


-> stackLink
Each tab has two stacks: one for backward navigation and one for forward navigation.


The head of a stack represents the most recently added element (LIFO).


The stackLink structure allows navigation between pages within these stacks.

Implemented Functions
Initialization
CREATE_SANTI() – Creates the sentinel node used to manage the tab list.


CREATE_PAGE_IMP() – Creates the default (implicit) page.


CREATE_TAB_ZERO() – Creates tab 0, initializes its default page, and links it to the sentinel.


NEW_TAB() – Allocates memory for a new tab, assigns it a unique ID (incremented each time a new tab is created), and sets its current page to the default page created by CREATE_PAGE_IMP().


Memory Management
FREE_STACK() – Frees dynamically allocated memory for all elements in a stack and for the stack itself.


CLOSE() – Removes a tab (except tab 0, which cannot be closed).
 Traverses the tab list, relinks neighboring tabs to maintain list integrity, and frees the memory used by the closed tab.


Navigation and Operations
OPEN_ID() – Searches for a tab with the specified ID.
 If found, sets it as the current tab; otherwise, prints an error message.


NEXT() – Moves to the next tab in the list.
 Skips over the sentinel if necessary. Updates the current tab to the one after the current.


PREV() – Moves to the previous tab in the list.
 Updates the current tab to the one before the current.


PAGE_ID() – Searches for a page by ID.
 If found, creates a copy to assign as the new current page, adds the previous page to the backward stack, clears the forward stack, and updates the current page.


Backward/Forward Navigation
BACKWARD() – Moves one step backward in history.
 Saves the current page to the forward stack, pops the top page from the backward stack, and sets it as the new current page.


FORWARD() – Moves one step forward in history.
 Saves the current page to the backward stack, pops the top page from the forward stack, and sets it as the new current page.


Printing
RECURSIVE_PRINT() – Recursively prints the elements of a stack starting from the first page added.


PRINT_HISTORY_ID() – Searches for a tab by ID and prints its entire history:
 the forward stack (in order), the current page, and then the backward stack.


PRINT() – Displays the IDs of all open tabs in a circular manner starting from the current tab and prints the description of the current page.
 Skips the sentinel when encountered, continuing with tab 0.
main Function Overview
Initializes variables and opens the input/output files.


Creates the vector of pages, the sentinel, and tab 0 using the initialization functions above.


Sets the current tab to tab 0.


Reads the number of pages and loads each page into memory.


Reads and executes the sequence of commands from the input file:


Each command is processed by comparing it to known commands and calling the corresponding function.


Trailing newlines from input are removed using fgets.


At the end, frees all dynamically allocated memory.



