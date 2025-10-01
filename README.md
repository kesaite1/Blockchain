# Blockchain

## Hash funkcijų įgyvendinimas pasitelkiant dirbtinį intelektą (DI):

### Idėja:

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


### Testing 
text1.txt file        -> hash: 570aaa6511d7b1eff3d6ca8e0854728d7a50d5278c427f0f911f44a8cf9a98f3
text2.txt file        -> hash: e5ab8fb9db4bf595bea0c72bb2072baa0707f9b70bea6ddd7f575fedadfdbb6e
konstitucija.txt file -> hash: 174f41663f42b304b882afa9d8e689607dc1c137732959fa3b920649e45b6f3f


