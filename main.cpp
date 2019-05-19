#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <limits>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <deque>
#include <list>
#include <algorithm>
#include <iomanip>

using std::cout; using std::endl; using std::cin; using std::string; using std::vector; using std::deque; using std::list;

template <typename T>
class Vector{
private:
    T* elem;        //elementai
    std::size_t sz; //size
    std::size_t cp; //capacity
public:
    /*----CONSTRUCTORS----*/
    Vector() : sz(0), cp(0), elem(nullptr) {}

    //COPY CONSTRUCTOR
    Vector(const Vector& temp) : sz(temp.sz), cp(temp.cp), elem(new T[temp.cp]){
        for (int i=0; i<sz; i++){
            elem[i] = temp.elem[i];
        }
    }

    //MOVE CONSTRUCTOR ?
    Vector(Vector&& temp) : sz(temp.sz), cp(temp.cp), elem(temp.elem){
		temp.elem = nullptr;
		temp.sz = 0;
		temp.cp = 0;
	}
	//INITIALIZER LIST
	Vector(std::initializer_list<T> temp) : sz(temp.size()), cp(temp.size()), elem(new T[temp.size()]) {
        std::copy(temp.begin(), temp.end(), elem);
	}

    //COPY ASSIGNMENT
	Vector<T>& operator=(const Vector& v)
	{
		if (&v == this)
            return *this;
		T* p = new T[v.cp];
		for (auto i = 0; i != v.sz; i++)
			p[i] = v.elem[i];
		delete[] elem;
		elem = p;
		sz = v.sz;
		cp = v.cp;
		return *this;
	}

	//MOVE ASSIGNMENT
	Vector<T>& operator=(Vector&& v)
	{
		if (&v == this)
			return *this;
		delete[] elem;
		elem = v.elem;
		sz = v.sz;
		cp = v.cp;
		v.elem = nullptr;
		v.sz = 0;
		v.cp = 0;
		return *this;
	}

    /*----DESTRUCTOR----*/
    ~Vector() { delete[] elem; }

    /*----ASSIGN----*/
    void assign(std::size_t sz_, const T& value) {
		if (sz < 0) throw std::out_of_range {"Vector::assign - size negali but mazau nei 0"};
		delete[] elem;
		sz = sz_;
		cp = sz_;
		elem = new T[sz];
		std::fill_n(elem, sz, value);
	}

	void assign(std::initializer_list<T> temp) {
		delete[] elem;
		sz = temp.size();
		cp = sz;
		elem = new T[sz];
		std::copy(temp.begin(), temp.end(), elem);
	};

	/*----ELEMENT ACCESS----*/
	T& at(std::size_t i) {
		if (i < 0 || sz < i) throw std::out_of_range {"Vector::at"};
		return elem[i];
	}

	const T& at(std::size_t i) const {
		if (i < 0 || sz < i) throw std::out_of_range {"Vector::at const"};
		return elem[i];
	}

    T& operator[](std::size_t i) {
		if (i < 0 || sz <= i) throw std::out_of_range {"Vector::operator[]"};
		return elem[i];
	}

	const T& operator[](std::size_t i) const {
		if (i < 0 || i<= i) throw std::out_of_range {"Vector::operator[] const"};
		return elem[i];
	}

    T& back() {
        if (sz == 0) throw std::logic_error("Empty container");
        return elem[sz - 1];
    }

	const T& back() const {
	    if (sz == 0) throw std::logic_error("Empty container");
        return elem[sz - 1];
    }

	T& front() {
        if (sz > 0) return elem[0];
        else throw std::logic_error("Empty container");
	}

	const T& front() const {
	    if (sz > 0) return elem[0];
        else throw std::logic_error("Empty container");
    }

	T* data() noexcept { return elem; }

	const T* data() const noexcept { return elem; }

    /*----CAPACITY----*/

    //reik cj su iteratoriais padaryt
	bool empty() const noexcept { return sz == 0; }

	std::size_t size() const noexcept { return sz; };

    std::size_t max_size() const {
        return std::numeric_limits<std::size_t>::max();
    }

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

    std::size_t capacity() const noexcept { return cp; };

    void shrink_to_fit(){
        if (sz != cp) {
			T *p = new T[sz];
			for (auto i = 0 ; i < sz; i++) {
				p[i] = elem[i];
			}
			delete[] elem;
			elem = p;
			p = nullptr;
			cp = sz;
		}
    };

    /*----MODIFIERS----*/
    void clear() noexcept {
		for(std::size_t i = 0; i<sz; i++){
            elem[i].~T();
		}
		sz=0;
	}

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

    void push_back( T&& value ){
        if (sz == cp) {
			reserve((sz+1)*2);
			elem[sz] = value;
			sz++;
		}
		else {
			elem[sz] = value; //ar std::move(value); ????????????
			sz++;
		}
    }

    void pop_back() {
        elem[sz - 1].~T();
        sz--;
    }

    void resize(std::size_t count) {
        resize(count, T());
    }

    void resize(std::size_t count, const T& value) {
        if (count < 0)
			throw std::out_of_range{"Vector::resize"};
        if (count > cp) {
            reserve(count);
            for (auto i = sz; i < count; i++) {
                elem[i] = value;
            }
            sz = count;
        }
        if (count < sz) {
            for (auto i = count; i < sz; i++) {
                elem[i].~T();
            }
            T* p = new T[count];
			sz = count;
			for (auto i = 0; i < sz; i++)
			{
				p[i] = elem[i];
			}
			delete[] elem;
			elem = p;
			p = nullptr;
        }
    }

    void swap(Vector& v) {
        std::swap(sz, v.sz);
        std::swap(cp, v.cp);
        std::swap(elem, v.elem);
    }

    T* begin() noexcept {
        return elem;
    }

    const T* begin() const noexcept {
        return elem;
    }

     T* end() noexcept {
        return elem + sz;
    }

    const T* end() const noexcept {
        return elem + sz;
    }
};

class Zmogus {
protected:
    string vardas;
    string pavarde;
    Zmogus(string v = "", string p = "") : vardas(v), pavarde(p) { }
public:
    virtual void niekoNereiskianti() = 0;
    void setVardas(string vard) { vardas = vard;}
	void setPavarde(string pav) { pavarde = pav;}
    inline string getVardas() const { return vardas;}
    inline string getPavarde() const { return pavarde;}
};

class Studentas : public Zmogus {
protected:
  vector<double> nd;
  double egz;
  double galutinis;
public:
    virtual void niekoNereiskianti(){};
    Studentas(string v = "", string p = "", double eg = 0, double gal = 0) : Zmogus(v, p), egz(eg), galutinis(gal) { nd.clear(); }  // default konstruktorius
    Studentas(Studentas&& a) : Zmogus(a.vardas, a.pavarde), egz{a.egz}, nd{std::move(a.nd)} {};
    Studentas(const Studentas& a);
    inline double getGalutinis() const { return galutinis;}
    inline double getEgz() const { return egz;}
    const vector<double>& getNd() const {return nd;}
    void pushNd(double n) {nd.push_back(n);}
    void setEgz();
    void setEgz(double a);
    void setGalutinis();
    void setGalutinis(double a);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& a);
    friend std::istream& operator>>(std::istream& in, Studentas& a);
    bool operator==(const Studentas& a);
    bool operator!=(const Studentas& a);
    Studentas& operator=(const Studentas& a);
};

//STUDENTAS KLASES FUNKCIJOS

void Studentas::setEgz(){
    egz = nd[nd.size()-1];
    nd.pop_back();
}

void Studentas::setGalutinis(){
    double vid;
    if(nd.size()==0) vid=0;
    else{
        double suma=0;
        for(double a: nd){
            suma+=a;
        }
        vid=suma/nd.size();
    }
    galutinis = 0.4*vid + 0.6*egz;
    //cout << galutinis << endl;
}

void Studentas::setGalutinis(double a){
    galutinis=a;
}

void Studentas::setEgz(double a){
    egz=a;
}

bool Studentas::operator==(const Studentas& a){
    if(egz==a.egz) return 1;
    else return 0;
}

bool Studentas::operator!=(const Studentas& a){
    if(egz!=a.egz) return 1;
    else return 0;
}

std::ostream& operator<<(std::ostream& out, const Studentas& a){
    out << a.vardas << " " << a.pavarde << " ";
    for(int i=0; i<a.nd.size(); i++){
        out << a.nd[i] << " ";
    }
    Studentas temp=a;
    temp.setGalutinis();
    out << "Egz.: " << temp.egz << " Galutinis: " << temp.galutinis;
    return out;
}

std::istream& operator>>(std::istream& in, Studentas& a){
    cout << "Iveskite varda" << endl;
    in >> a.vardas;
    cout << "Iveskite pavarde" << endl;
    in >> a.pavarde;
    cout << "Iveskite egzamino pazymi" << endl;
    in >> a.egz;
    cout << "Iveskite 10 pazymiu" << endl;
    double temp;
    for(int i=0; i<10; i++){
        in >> temp;
        a.nd.push_back(temp);
    }
    //is ivestu pazymiu paskaiciuoja galutini
    a.setGalutinis();
    return in;
}

Studentas::Studentas(const Studentas& a){
    vardas = a.vardas;
	pavarde = a.pavarde;
	egz = a.egz;
	galutinis = a.galutinis;
	nd = a.nd;
}

Studentas& Studentas::operator=(const Studentas& a)
{
	if (&a == this) return *this;

	vardas = a.vardas;
	pavarde = a.pavarde;
	egz = a.egz;
	galutinis = a.galutinis;
	nd = a.nd;
	return *this;
}

//KLASE SKIRTA LAIKO MATAVIMUI

class Timer {
 private:
  // per using sutrumpiname ilgus chrono bibliotekos tipus
  using hrClock = std::chrono::high_resolution_clock;
  using durationDouble = std::chrono::duration<double>;
  std::chrono::time_point<hrClock> start;

 public:
  Timer() : start{hrClock::now()} {}
  void reset() { start = hrClock::now(); }
  double elapsed() const {
    return durationDouble(hrClock::now() - start).count();
  }
};

//SUGENERUOJA FAILA SU RANDOM PAZYMIAIS
void generavimasFailo(int kiekIrasu){
    srand ( time ( NULL ));
    std::ofstream fout ("generatedfile.txt");
    for(int i=0; i<kiekIrasu; i++){
        fout << "Vardas" << i+1 << " " << "Pavarde" << i+1 << " ";
        for(int j=0; j<11; j++){
            fout << (int)(1 + ( double ) rand ()/ RAND_MAX * (11 - 1 )) << " ";
        }
        fout << endl;
    }

}

//PARTITION ALGORITMUI
bool isVargsiukas (const Studentas& laikinas) { return laikinas.getGalutinis() < 5.0; }

int main()
{
    //PASIRINKTI KIEK IRASU
    int kiekIrasu=100000;
    generavimasFailo(kiekIrasu);

    //LAIKO SKAICIAVIMAS
    Timer t;  // Paleisti

    Vector<Studentas> studentai;

    std::ifstream fin ("generatedfile.txt");
    string line;
    try{
        if(!fin) throw "FAILAS NEEGZISTUOJA";

        while (getline(fin, line)){
            if(line!=""){
                Studentas temp;
                int x;
                string tempString;

                std::istringstream iss(line);

                iss >> tempString;
                temp.setVardas(tempString);
                iss >> tempString;
                temp.setPavarde(tempString);

                while(!iss.eof()){
                    iss >> x;
                    if(iss.fail()) {
                        iss.clear();
                        string laikinas;
                        iss >> laikinas;
                        continue;
                        /*
                        Arba butu galima is viso sustabdyti programa:
                        cout << "Blogai ivesti duomenys" << endl;
                        exit(EXIT_FAILURE);
                        */
                    }
                    else if(x<0 || x>10){
                    continue;
                    }
                    else temp.pushNd(x);
                }
                temp.setEgz();
                temp.setGalutinis();
                studentai.push_back(temp);
            }
            else continue;
        }

    //RUSIAVIMAS SU PARTITION ALGORITMU
    auto it = std::partition(studentai.begin(), studentai.end(), isVargsiukas);

    //ISVEDIMAS I FAILUS
    std::ofstream fout ("vargsiukai.txt");
    for (auto i=studentai.begin(); i!=it; i++){
        fout << *i << endl;
    }

    std::ofstream ffout ("kietakai.txt");
    for (auto i=it; i!=studentai.end(); i++){
        ffout << *i << endl;
    }

    //LAIKO SKAICIAVIMAS
    cout << "Programos trukme: " << t.elapsed() << "s" << endl;

    }catch(const char* msg){
        cout << msg << endl;
    }

    return 0;
}
