# Blockchain

## Hash funkcijų įgyvendinimas pasitelkiant dirbtinį intelektą (DI):

### Idėja:

```PRADŽIA
    Paklausia vartotojo, kokiu būdu įves input'ą: skaitant failą ar įvedant ranka?
    Jei rankinis įvedimas:
        Nuskaito input'ą su getline()
    Jei failas:
        Atidaro failą
        Nuskaito visas eilutes ir sujungia į vieną string
        Uždaro failą
    Pabaiga jei

    Inicializuoja 4 lane su skirtingais pradžios seed'ais (out[4])

    FOR kiekvienas simbolis input'e
        c = ASCII simbolio reikšmė
        lane = i mod 4

        out[lane] = out[lane] XOR (c * 0x100000001b3)
        out[lane] = pasuka bitus į kairę (i*7 mod 64)
        out[lane] = out[lane] * 0xff51afd7ed558ccd
        out[lane] = out[lane] XOR (out[lane] >> 32)

        other = (lane + 1) mod 4
        out[other] = out[other] XOR pasuka bitus (c + out[lane], i*13 mod 64)
        out[other] = out[other] * 0x9e3779b97f4a7c15
    END FOR

    FOR round = 0 to 3
        FOR j = 0 to 3
            x = out[j]
            x = x XOR pasuka bitus (out[(j+1) mod 4], j*17 + round*11)
            x = x * 0xc2b2ae3d27d4eb4f
            x = x XOR (x >> 29)
            out[j] = x
        END FOR
    END FOR

    Atspausdina out[0..3] kaip 64 simbolių ilgio hex eilutę
PABAIGA

```



### Testing 
- text1.txt file        -> hash: 333b032039bef039c6eb417c030c56591c782cd18c98698d18446fc3f02a7f93
- text2.txt file        -> hash: 32ab04ab717ca70af359dd70eb7f4b3a38860b6f065b290238d36667ec01e47b
- konstitucija.txt file -> hash: a68b86f57c42b9321bcbcc80c26ede09627675aa827b67b68fe4fdd06f2181fa
- text3.txt file        -> hash: cb1719b3fd6c50651a7d15513aed34a03ea506b14d461a642c8d0ac9fb49784f


