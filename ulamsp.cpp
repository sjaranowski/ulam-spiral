#include <iostream>
#include <fstream>

using namespace std;

class ErathostenesSieve {
private:
  bool * primes;
  unsigned int size;
  
public:
  ErathostenesSieve (unsigned int N) {
    size = N + 1;
    
    primes = new bool[N + 1];
    
    primes[0] = false;
    primes[1] = false;
    for (unsigned int n = 2; n < N + 1; ++n) {
      primes[n] = true;
    }
    for (unsigned int n = 2; n * n <= N; ++n) {
      if (!primes[n])
	continue;
      unsigned int k = n + n;
      while (k <= N) {
	primes[k] = false;
	k += n;
      }
    }
  }
  void print (void) {
    for (unsigned int i = 0; i < size; ++i)
      cout << " " << primes[i];
    cout << endl;
  }
  bool isPrime(unsigned int n) {
    return primes[n];
  }
};

class Direction {
private:
  pair<unsigned int, unsigned int> * cycle;
  unsigned int idx;

public:
  Direction (void) {
    cycle = new pair<unsigned int, unsigned int> [4];

    // Standard cycle of directions
    cycle[0] = make_pair(-1, 0);
    cycle[1] = make_pair(0, -1);
    cycle[2] = make_pair(1, 0);
    cycle[3] = make_pair(0, 1);
    idx = 3;
  }
  
  ~Direction (void) {
    //delete[] cycle;
  }

  unsigned int getI (void) {
    return cycle[idx].first;
  }

  unsigned int getJ (void) {
    return cycle[idx].second;
  }

  void update(void) {
    ++idx;
    
    if (idx == 4)
      idx = 0;
  }
};

class Position {
public:
  Position (unsigned int i, unsigned int j) {
    this->i = i;
    this->j = j;
  }

  // Matrix is considered to be A x B
  unsigned int get(unsigned int B) {
    return i * B + j;
  }
  
  void update (Direction& direction) {
    i += direction.getI();
    j += direction.getJ();
  }

  void print (void) {
    cout << "(" << i << ", " << j << ")" << endl;
  }
private:
  unsigned int i;
  unsigned int j;
};

class UlamSpiral {
public:
  UlamSpiral (unsigned int K) {
    compute(K);
  }
  ~UlamSpiral () {
    //delete[] spiral;
  }

  void print () {
    unsigned int c = 0;
    for (unsigned int i = 0; i < A; ++i) {
      for (unsigned int j = 0; j < B; ++j) {
	cout << " " << spiral[c++];
      }
      cout << endl;
    }
    //cout << endl;
  }

  void write (void) {
    ofstream fout;
    fout.open("out.ppm", ios::binary | ios::out);

    // Tri-color
    char c1[3] = {0xF1, 0xB9, 0x2B};
    char c2[3] = {0x2E, 0xB8, 0x21};
    char c3[3] = {0x00, 0x91, 0xEA};

    char fg[3] = {0x1D, 0x7F, 0xAF};
    char bg[3] = {0xFF, 0xFF, 0xFF};

    unsigned int count = 0;
    for (unsigned int i = 0; i < A * B; ++i) {
      
      if (spiral[i]) {
        fout.write((char*) &fg, sizeof(bg));	
      /*
	count++;
	switch (count % 3) {
	case 0:
	  fout.write((char*) &c1, 3);
	  break;
	case 1:
	  fout.write((char*) &c2, 3);
	  break;
	case 2:
	  fout.write((char*) &c3, 3);
	  break;
	}
      */
    }
      else
	fout.write((char*) &bg, sizeof(bg));
    }
    fout.close();
  }

private:
bool * spiral;
  unsigned int A, B;
  
  void compute(unsigned int K) {
    A = 2 * K + 1;
    B = A;

    unsigned int N = A * A;
    
    spiral = new (nothrow) bool [N];

    ErathostenesSieve sieve (N);
    
    // A starting point (right in the center)
    Position position (K, K);
    unsigned int k = 0;
    unsigned int d = 2 * k + 1;

    Direction direction, base;
    
    for (unsigned int n = 1; n <= N; ++n) {
      spiral[position.get(B)] = sieve.isPrime(n);

      if (n == d * d) {
	position.update (base);
	direction.update ();
	k++;
	d = 2 * k + 1;
	continue;
      }

      if (n  % (d - 1) == 1)
	direction.update();
      position.update (direction);
    }
  }
};

int main (int argc, char** argv)
{
  // Simple argument parser
  if (arg != 2)
    cerr << "ulamsp: wrong number of arguments, only one expected"

  int N
  UlamSpiral ulam (2000);
  ulam.write();
}
