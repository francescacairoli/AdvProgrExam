# Python - PostcardList

## Introduction

The purpose of the assigned project is to implement a PostcardList class. 
This class should read/write Postcard messages from/to a properly formatted
file, in which each line is a Postcard.
The Postcard format is "date:$(DATE); from:$(SENDER); to:$(RECEIVER);".

The class implementation must satisfy the provided tests, defined in unittest.

The file myPostcards.py contains the PostcardsList class;

The main.py file contains the unittest specifications.
In addidition, ten properly formatted files were provided with the assignment.

## Implementation 
The class PostcardList has the following attributes: 
- _file, 
- _postcards, 
- _date, 
- _from, 
- _to. 

The **readFile** method is used to read line by line the content of a file
and to store it in the list self._postcards.
For subsequent readings, we should use the **updateList** method, which appends the new lines read from a file to the existing ones already stored in the postcards list. 

Everytime we read or update, we should also call **parsePostcards**, which parses the list and sets accordingly the three dictionaries _date, _from and _to. 
In particular, the dictionaries are useful to retrieve information about all the postcards respectively sent by a given sender (by means of the function **getPostcardsBySender**), 
received by a given receiver (**getPostcardsByReceiver**), 
sent within a given date range (**getPostcardsByDateRange**). 

In addition, we can use **writeFile** to write the content of _postcards list into a file, while with **updateFile** we can append to the file the content of _postcards.

We verified that our class PostcardList satisfies the tests.

```
Ran 5 tests in 0.006s

OK
```
