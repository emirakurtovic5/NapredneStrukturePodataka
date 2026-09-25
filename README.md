# Objektno-orijentirana implementacija naprednih struktura podataka

Projekat izrađen u okviru završnog rada na Elektrotehničkom fakultetu Univerziteta u Sarajevu, Odsjek Računarstvo i informatika.

## Opis projekta

Cilj projekta je implementacija i eksperimentalna evaluacija odabranih naprednih struktura podataka u programskom jeziku **C++14**, primjenom objektno-orijentiranog i generičkog programiranja.

Implementirane su sljedeće strukture podataka:

- **AVL stablo**
- **Red-Black stablo**
- **Hash tabela**

Za sve strukture definisan je zajednički generički interfejs `DataStructure<T>`, koji omogućava korištenje osnovnih operacija na jedinstven način.

## Implementirane funkcionalnosti

### AVL stablo

- umetanje elemenata
- brisanje elemenata
- pretraživanje elemenata
- automatsko balansiranje
- lijeve i desne rotacije
- LR i RL rotacije
- provjera ispravnosti strukture

### Red-Black stablo

- umetanje elemenata
- brisanje elemenata
- pretraživanje elemenata
- lijeve i desne rotacije
- korekcija nakon umetanja
- korekcija nakon brisanja
- provjera Red-Black pravila

### Hash tabela

- umetanje elemenata
- brisanje elemenata
- pretraživanje elemenata
- odvojeno ulančavanje za rješavanje kolizija
- automatski rehashing
- podrška za generičke tipove podataka

## Testiranje

Za provjeru ispravnosti implementacija razvijeni su jedinični testovi za sve tri strukture podataka.

Provedeno je i benchmark testiranje za različite brojeve elemenata i različite redoslijede ulaznih podataka. Dobijeni rezultati korišteni su za poređenje performansi implementiranih struktura.

Za provjeru upravljanja memorijom korišten je **Dr. Memory**.

## Struktura projekta

```text
AdvancedDataStructures/
├── src/
│   ├── DataStructure.h
│   ├── AVLNode.h
│   ├── AVLTree.h
│   ├── RedBlackNode.h
│   ├── RedBlackTree.h
│   ├── HashTable.h
│   └── main.cpp
├── tests/
│   ├── AVLTreeTests.cpp
│   ├── RedBlackTreeTests.cpp
│   └── HashTableTests.cpp
├── benchmarks/
│   ├── AVLBenchmark.cpp
│   ├── RedBlackBenchmark.cpp
│   └── HashBenchmark.cpp
├── diagrams/
├── docs/
├── CMakeLists.txt
└── README.md

# Tehnologije i alati

- **C++14** – programski jezik korišten za implementaciju
- **CMake** – sistem za konfiguraciju i izgradnju projekta
- **GCC** – kompajler
- **MSYS2** – razvojno okruženje za Windows
- **Visual Studio Code** – razvojno okruženje
- **Git** – sistem za kontrolu verzija
- **GitHub** – hosting i upravljanje repozitorijem
- **Dr. Memory** – alat za provjeru upravljanja memorijom

# Pokretanje projekta

Projekat koristi **CMake** za konfiguraciju i izgradnju.

```bash
mkdir build
cd build
cmake ..
cmake --build .

Nakon izgradnje mogu se pokrenuti testovi i benchmark programi definisani u projektu.

# Autor

**Emira Kurtović**

Elektrotehnički fakultet  
Univerzitet u Sarajevu  
Računarstvo i informatika
