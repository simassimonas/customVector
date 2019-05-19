# customVector

**Programos paleidimas**

Kadangi yra tik vienas main.cpp failas, tai makefile nekuriau
- `g++ -o run main.cpp`

## FUNKCIJOS

```shell
 void assign(std::size_t sz_, const T& value) {
		if (sz_ < 0) throw std::out_of_range {"Vector::assign - size negali but mazau nei 0"};
		delete[] elem;
		sz = sz_;
		cp = sz_;
		elem = new T[sz];
		std::fill_n(elem, sz, value);
	}
```
Funkcija istrina esamas Vector reiksmes ir pakeicia jas uzpildydamas konteineri nurodytu kiekiu objektu

```shell
T& operator[](std::size_t i) {
		if (i < 0 || sz <= i) throw std::out_of_range {"Vector::operator[]"};
		return elem[i];
	}
```
Funkcija grazina nurodyta elementa

```shell
void reserve(std::size_t new_cap) {
		if (cp < new_cap) {
			T *p = new T[new_cap];
			for (auto i = 0; i < sz; i++) {
				p[i] = elem[i];
			}
			delete[] elem;
			elem = p;
			cp = new_cap;
			p = nullptr;
		}
	}
```
Funkcija padidina Vectoriaus capacity. Jeigu perduotas norimas capacity yra mazesnis negu jau esantis, tada funkcija nieko nedaro

```shell
void push_back(const T& value){
		if (sz == cp) {
			reserve((sz+1)*2);
			elem[sz] = value;
			sz++;
		}
		else {
			elem[sz] = value;
			sz++;
		}
	}
```
Funkcija ideda pasirinkta objekta i Vectoriaus gala, jeigu nebera galimos vietos, tada su `reserve` funkcijos pagalba isskiria daugiau vietos

```shell
T* data() noexcept { return elem; }
```
Grazina rodykle i pirmaji vectoriaus elementa

## PUSH_BACK 

| Elementai | std::vector | Vector |
|:---:|:---:|:---:|
| 10000 | 0.000997s | 0.000698s |
| 100000 | 0.001996s | 0.000998s |
| 1000000 | 0.021938s | 0.009033s |
| 10000000 | 0.2s | 0.1s |
| 100000000 | 1.9s | 0.9s |

## ATMINTIES PERSKIRSTYMAI

Su 100000000 elementu std::vector 28 kartus, o mano customVector 26 kartus

## 3 UZDUOTIS

| Irasai | std::vector | Vector |
|:---:|:---:|:---:|
| 100000 | 4,6s | 4,65s |





