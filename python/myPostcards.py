'''
Author: Francesca Cairoli
Date: 04 June 2019
Description: Implementation of the PostcardList class.
'''

import datetime


class PostcardList:
    '''
    Class PostcardList reads/writes postcard messages from/to a properly
    formatted file:
    date: $(DATE); from: $(SENDER); to: $(RECEIVER);
    '''

    def __init__(self):

        # Name of the file (eventually, the entire path) where postcards are stored
        self._file = ""
        # List of postcards extracted from _file.
        self._postcards = []
        # A dictionary storing postcard dates, the key is the date, the value is a list of indexes.
        self._date = {}
        # A dictionary storing postcard senders, the key is a string denoting the sender, the value is a list of indexes.
        self._from = {}
        # A dictionary storing postcard receivers, the key is a string denoting the receiver, the value is a list of indexes.
        self._to = {}

    def writeFile(self, filename):
        '''
        It writes to a file the postcards stored in self._postcards. If the file already exists, it is overwritten.
        '''
        files = open(filename,"w+") # 'w' option creates a new file named filename, the + creates a new file if it already exists
        for postcard in self._postcards:
        	files.write("%s\n" % postcard)
        files.close()
        
    def readFile(self, path_to_file):
        self._file = path_to_file
        file = open(self._file, "r")
        for line in file:
        	self._postcards.append(line)
        file.close()
        self.parsePostcards()
        
    def parsePostcards(self):
        '''
        Parses _postcards, extracts information about date, sender and receiver and stores it in the respective dictionaries: _date, 		_from, _to
        ''' 
        for ind,p in enumerate(self._postcards):
            date, sender, receiver, _ = p.split(';')

            date = date.split(':')[1]
            sender = sender.split(':')[1]
            receiver = receiver.split(':')[1]

            date = datetime.datetime.strptime(date, "%Y-%m-%d")
            if date not in self._date:
                self._date[date] = []
            self._date[date].append(ind)
            if sender not in self._from:
                self._from[sender] = []
            self._from[sender].append(ind)
            if receiver not in self._to:
                self._to[receiver] = []
            self._to[receiver].append(ind)

    def updateFile(self, new_file):
        '''
        It writes to a file the postcards stored in self._postcards. If 	the file already exists, the new content is appended to it.
        '''
        file = open(new_file,"a+") # 'a' oprion is to append lines to a given file, the + creates a new file if it already exists
        for postcard in self._postcards:
    	    file.write("%s\n" % postcard)
        file.close()

    def updateLists(self, new_file):
        '''
        Updates the _postcards list when new postcards are received
        '''
        list_new_lines = list(open(new_file,"r"))
        self._postcards + list_new_lines
        self.parsePoscards()

    def getNumberOfPostcards(self):
        '''
        Return the overall number of postcards
        '''
        return len(self._postcards)

    def getPostcardsByDateRange(self, date_range):
        '''
        Returns the postcards within a date_range
        '''
        post_by_date = []
        for i in self._date:
            if date_range[0] <= i <= date_range[1]:
                for j in self._date[i]:
                    post_by_date.append(self._postcards[j])
        return post_by_date

    def getPostcardsBySender(self, sender):
        '''
        Returns the postcards from a specific sender
        '''
        post_by_sender = []
        if sender in self._from:
            for index in self._from[sender]:
                post_by_sender.append(self._postcards[index])
        
        return post_by_sender

    def getPostcardsByReceiver(self, receiver):
        '''
        Returns the postcards to a specific receiver
        '''
        post_by_receiver = []
        
        if receiver in self._to:
            for index in self._to[receiver]:
                post_by_receiver.append(self._postcards[index])

        return post_by_receiver
