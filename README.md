# Blockchain

## Hash funkcijų įgyvendinimas pasitelkiant dirbtinį intelektą (DI):

# Idėja:

``` Vartotojas parašo input'ą.
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

Atspausdinti hash masyvą kaip 64 simbolių ilgio hex eilutę ```


