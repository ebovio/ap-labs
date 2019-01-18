#Function
def test(str):
    counter = 0
    newString = [] #Creation of an empty newString to store each character
    list = [] #List to store the amount of different characters
    for i in str:
        if i not in newString:
            newString.append(i) #Adding the character in the new string
            counter = counter + 1
        else:
            newString = []
            list.append(counter) #Adding the value of the longest substring formed
            counter = 0
    list.append(counter) #Adds the last substring formed thanks to the last cycle
    answer = max(list) #Gets the maximum value stored in the list
    print(answer)

#Main Program
stringT = raw_input("Enter a string: ")
test(stringT)
