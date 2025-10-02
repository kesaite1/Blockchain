# Blockchain

## Hash funkcijų įgyvendinimas pasitelkiant dirbtinį intelektą (DI):

### Idėja:

```Vartotojas parašo input'ą.
Inputas perskaitomas su getline().
Sukuriamas 32 baitų masyvas: unsigned char hash[32] = {0};

FOR kiekvienas simbolis input’e
    Paimti simbolio ASCII reikšmę → c
    Pasukti c bitus pagal simbolio poziciją → rotated
    Pridėti ASCII reikšmę prie hash[i mod 32] → hash[i % 32] = (hash[i % 32] + c) mod 256
    Apskaičiuoti pseudo-atsitiktinę poziciją: pos = (i * 7 + c) mod 32
    XOR rotated reikšmę su hash[pos] → hash[pos] = hash[pos] XOR rotated
    Pridėti ASCII reikšmę * 31 prie kito hash elemento → hash[(pos + 13) mod 32] = (hash[(pos + 13) mod 32] + c * 31) mod 256
END FOR

Atspausdinti hash masyvą kaip 64 simbolių ilgio hex eilutę 
```



### Testing 
- text1.txt file        -> hash: 333b032039bef039c6eb417c030c56591c782cd18c98698d18446fc3f02a7f93
- text2.txt file        -> hash: 32ab04ab717ca70af359dd70eb7f4b3a38860b6f065b290238d36667ec01e47b
- konstitucija.txt file -> hash: a68b86f57c42b9321bcbcc80c26ede09627675aa827b67b68fe4fdd06f2181fa
- text3.txt file        -> hash: cb1719b3fd6c50651a7d15513aed34a03ea506b14d461a642c8d0ac9fb49784f


