def verlaat_ploeg(naam, ploeg, dictionary):
    dictionary[ploeg].remove(naam)
    if dictionary[ploeg] == []:
        dictionary.pop(ploeg)
    return dictionary
    
def vervoegt_ploeg(naam, ploeg, dictionary):
    if ploeg in dictionary:
        dictionary[ploeg].append(naam)
    else:
        dictionary[ploeg] = [naam]
    return dictionary