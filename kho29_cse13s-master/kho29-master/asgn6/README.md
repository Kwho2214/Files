Assignment 6: Public Key Cryptography
In this assignment we are implementing the RSA algorithm to encrypt and decrypt our files. We used mpzs from the GMP library for large numbers. RSA uses a public key and private key where the public key is known to everyone, but the private key is only known to you and your receiver. The public key is used to encrypt messages, and the private key used to decrypt it. For random numbers we generate, we used the default seed time(NULL) where returns the time since January 1, 1970. Randstate.c, initializes the states and clears it when used. Numtheory.c implments the modular exponentiation, Miller-Rabin method for testing prime, and making prime numbers, modular inverses, and gcd(Greatest common divsor). RSA.c, we have making of public and private key. Reading and writing of both private and public keys. Encrypt and decrypt files, and verifying and signing signature.

Keygen:
Makes an RSA public and private key

Options:
   -h              Display program help and usage.
   -v              Display verbose program output.
   -b bits         Minimum bits needed for public key n (default: 256).
   -i confidence   Miller-Rabin iterations for testing primes (default: 50)
   -n pbfile       Public key file (default: rsa.pub).
   -d pvfile       Private key file (default: rsa.priv).
   -s seed         Random seed for testing.

Encrypt:
Encrypts files using the RSA encryption method

Options:
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to decrypt (default: stdin).
   -o outfile      Output file for decrypted data (default: stdout).
   -n pubfile       Private key file (default: rsa.pub).
 
Decrypt:
Decrypts using RSA decryption method

options:
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to decrypt (default: stdin).
   -o outfile      Output file for decrypted data (default: stdout).
   -n pvfile       Private key file (default: rsa.priv).

How to run:
Download all files needed.
In linux terminal, type make all to build all executables. 

To run:
Do ./(executable name) in your linux terminal
