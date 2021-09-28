# To implement the Left most derivation removal algorithm.

no_of_productions = int(input("Enter the number of productions: "))

productions = {}

print("Enter the Productions: ")
for _ in range(no_of_productions):
    splited = input().split("->")
    if splited[0].strip() not in productions.keys():
        productions[splited[0].strip()] = set()
    productions[splited[0].strip()] = productions[splited[0].strip()] | set(map(lambda x: x.strip(),splited[1].split("|")))

for key, value in productions.items():
    productions[key] = list(value)

keys = list(productions.keys())

def indirectCall(lookInto, lookFor):
    for rhs in productions[keys[lookInto]]:
        if rhs.startswith(keys[lookFor]):
            return True
    return False

for index in range(len(keys)):
    for index2 in range(index):
        if indirectCall(index, index2) and indirectCall(index2, index):
            for rhs in productions[keys[index]]:
                if rhs.startswith(keys[index2]):
                    for rhs2 in productions[keys[index2]]:
                        productions[keys[index]].append(rhs.replace(keys[index2], rhs2))
                    productions[keys[index]].remove(rhs)

    print(productions)
    immidiate = []
    non_immidiate = []

    for rhs in productions[keys[index]]:
        if rhs.startswith(keys[index]):
            immidiate.append(rhs)
        else:
            non_immidiate.append(rhs)
        
    if immidiate:
        newNonTerminal = keys[index]+"'"
        productions[keys[index]] = set(map(lambda x: x+newNonTerminal, non_immidiate))

        immidiate = list(map(lambda x: x+newNonTerminal, immidiate))
        immidiate = list(map(lambda x: x.replace(keys[index],"",1),immidiate))
        immidiate.append("@")
        productions[newNonTerminal] = set(immidiate)

print("Answer: \n=====================")
for key, values in productions.items():
    print(key,"->", "|".join(values))
