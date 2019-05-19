# customVector

**Programos paleidimas**
Kadangi yra tik vienas main.cpp failas, tai makefile nekuriau
- `g++ -o run main.cpp`

## FUNKCIJOS

## PUSH_BACK 

| Elementai | std::vector | Vector |
|:---:|:---:|:---:|
| 10000 | 0.000997s | 0.000698s |
| 100000 | 0.001996s | 0.000998s |
| 1000000 | 0.021938s | 0.009033s |
| 10000000 | 0.2s | 0.1s |
| 100000000 | 1.9s | 0.9s |

## ATMINTIES PERSKIRSTYMAI

Su 100000000 elementu std::vector 28 kartus, o mano cusutomVector 26 kartus

## 3 UZDUOTIS

| Irasai | std::vector | Vector |
|:---:|:---:|:---:|
| 100000 | 4,6s | 4,65s |





