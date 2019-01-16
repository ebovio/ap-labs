#Function
def test(str):
    counter = 0
    newString = [] #Creation of an empty newString to store each character
    list = []
    for i in str:
        if i not in newString:
            newString.append(i) #Adding the character in the new string
            counter = counter + 1
        else:
            newString = []
            list.append(counter)
            counter = 0
    answer = max(list)
    print(answer)

#Main Program
stringT = raw_input("Enter a string: ")
test(stringT)
