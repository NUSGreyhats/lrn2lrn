# What is Cryptography?
If you look at the origin of the root words of cryptography (crypto and graphy), you will see that "crypto" stands for "hidden, secret", and "graphy" denotes "a process or form of drawing, writing, representing, recording, describing, etc., or an art or science concerned with such a process."

*Tldr; cryptography is the science concerned with the study of secret communication*


# What is Caesar Cipher?
The Caesar cipher, also known as a shift cipher, is one of the simplest forms of encryption. It is a substitution cipher where each letter in the original message (called the plaintext) is replaced with a letter corresponding to a certain number of letters up or down in the alphabet. (Wikipedia)

It is a simple cipher method and a good way to start learning about encryption.

# What is Substitution Cipher?
An example of Caesar Cipher.
Due to the fast computation logic in today's world, this is usually not used in practice as itself. 
However, an interesting thing to note is that ciphers are just displacements of alphabets, and English words have characteristics. Some alphabets appears more often than the others. (E and T rank highest on the list)
https://en.wikipedia.org/wiki/Letter_frequency 

Hence, to retrieve the original key, we will do frequency analysis of words. 
http://www.counton.org/explorer/codebreaking/frequency-analysis.php

# Cryptanalysis in Python
Using an example from: http://practicalcryptography.com/ciphers/simple-substitution-cipher/ 

We have prepared some easy practices!
The is interesting to try out too: https://cryptopals.com/

# Usage of tools
Online tools are useful in breaking ciphers with English words. However, automation and scripting will definitely be more efficient in CTFs and competitions. 

# Building a script
Let's take a look at this: https://inventwithpython.com/chapter14.html 
Another example can be found at: http://bt3gl.github.io/csaw-ctf-2014-cryptography-200-psifer-school.html 

# Cryptographic Primitives
Cryptographic primitives are well-established, low-level cryptographic algorithms that are frequently used to build cryptographic protocols for computer security systems. These routines include, but are not limited to, one-way hash functions and encryption functions.

Cryptographic primitives are the building blocks for cryptographic systems and they have to be reliable. If a cryptographic primitive is found to fail, almost every protocol that uses it becomes vulnerable. Since creating cryptographic routines is very hard, and testing them to be reliable takes a long time, it is essentially never sensible (nor secure) to design a new cryptographic primitive to suit the needs of a new cryptographic system.

e.g. AES, SHA-256, RSA, RC4 etc…

# Initialisation Vector (IV)
In cryptography, an initialization vector (IV) or starting variable (SV) is a fixed-size input to a cryptographic primitive that is typically required to be random or pseudorandom. Randomization is crucial for encryption schemes to achieve semantic security, a property whereby repeated usage of the scheme under the same key does not allow an attacker to infer relationships between segments of the encrypted message.
Properties of an IV depend on the cryptographic scheme used. A basic requirement is uniqueness, which means that no IV may be reused under the same key. For block ciphers, repeated IV values devolve the encryption scheme into electronic codebook mode: equal IV and equal plaintext result in equal ciphertext. In stream cipher encryption uniqueness is crucially important as plaintext may be trivially recovered otherwise.

# Wired Equivalent Privacy (WEP)
WEP was created in 1997 as part of an optional mechanism in the 802.11 standard for wireless LAN communication. Its purpose was to provide confidentiality and integrity of traffic in the WLAN. WEP is used at the two lowest layers of the OSI reference model (Data link and physical). It relies on the stream cipher RC4 for data confidentiality and CRC-32 for data integrity. It uses a symmetric key (Pre-Shared Key) to encrypt the message.

WEP | 64 bit WEP | 128 bit WEP
----|-----------|------------
Key size | 40 bits | 104 bits
IV size | 24 bits | 24 bits

# Stream Cipher
A stream cipher is a symmetric key cipher where plaintext digits are combined with a pseudorandom cipher digit stream (keystream). In a stream cipher, each plaintext digit is encrypted one at a time with the corresponding digit of the keystream, to give a digit of the ciphertext stream. Since encryption of each digit is dependent on the current state of the cipher, it is also known as state cipher. In practice, a digit is typically a bit and the combining operation an exclusive-or (XOR).

A | B | XOR
--|---|----
0|0|0
0|1|1
1|0|1
1|1|0

Stream ciphers typically execute at a higher speed than block ciphers and have lower hardware complexity. However, stream ciphers can be susceptible to serious security problems if used incorrectly (see stream cipher attacks); in particular, the same starting state (seed) must never be used twice.

######  For further reading:
https://en.wikipedia.org/wiki/Stream_cipher#Types_of_stream_ciphers

# Symmetric Key Algorithms
A symmetric key algorithm uses the same key to both encrypt and decrypt a message

Message + key -> Ciphertext
Ciphertext + key -> Message

Note: '+' is a function, e.g. XOR, ROT, etc..

# Rivest Cipher 4 (RC4)
The RC4 stream cipher used by WEP is based on two algorithms.
##### Key Scheduled Algorithm (KSA) 
A key schedule is an algorithm that, given the key, calculates the subkeys for these rounds.
KSA transforms a key of length 1 to 256 bits into a initial permutation S of the number 0 to N. The internal state of RC consists of two number I and j used a pointers to elements of S.
```
for i from 0 to 255
    S[i] := i
endfor
j := 0
for i from 0 to 255
    j := (j + S[i] + key[i mod keylength]) mod 256
    swap values of S[i] and S[j]
endfor
```
##### Pseudo Random Generation Algorithm (PRGA)
It generates a singly byte of keystream from the current internal state of RC4 and them updates the internal state. Originally, N = 255, but the algorithm can work with different values of N.
```
i := 0
j := 0
while GeneratingOutput:
    i := (i + 1) mod 256
    j := (j + S[i]) mod 256
    swap values of S[i] and S[j]
    K := S[(S[i] + S[j]) mod 256]
    output K
endwhile
```


######  Further Reading - Weakness in RC4 KSA:
http://www.crypto.com/papers/others/rc4_ksaproc.pdf


# Cyclic Redundancy Check (CRC)
CRC is a hash function used by the WEP Protocol to ensure data integrity.  The principle of CRC32 stands in a kind of polynomial division. The original message is XORed with a constant of 32 bits followed by as many 0 as necessary to reach the length of the message. The result becomes the new “message” and the operation is repeated until the length of the result is under the length of the constant.

``` python
def crc_remainder(input_bitstring, polynomial_bitstring, initial_filler):
	len_polynomial = len(polynomial_bitstring)
	range_len_polynomial = range(len_polynomial)
	len_input = len(input_bitstring)
	initial_padding = initial_filler  * (len_polynomial - 1)
	input_padded_array = list(input_bitstring + initial_padding)
	while '1' in input_padded_array[:len_input]:
		cur_shift = input_padded_array.index('1')
		for i in range_len_polynomial:
			if polynomial_bitstring[i] == input_padded_array[cur_shift + i]:
				input_padded_array[cur_shift + i] = '0'
			else:
				input_padded_array[cur_shift + i] = '1'
	return ''.join(input_padded_array)[len_input:]
```
**CRC Exercise** : Calculate the CRC-3 for 10101010 and verify it.


###### List of common CRC Standards:
https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Standards_and_common_use

# How WEP Works
The WEP protocol uses the RC4 cipher to ensure privacy and a CRC-32 checksum to ensure integrity of the data transmitted. A secret key **K** is shared between users of the network. The protocol does not specify the way the key must be shared. The key **K** is will be 40 bits or 104 bits depending on the protocol used. 

To send a message, **M**, one has to compute the integrity checksum, **c(M)** of the message and concatenate it: **M.c(M)**. RC4 stream generated by **K** and a public initialisation vector (IV) of 24bits, **V**.
Keystream = **RC4(V,K)**.

Then, one encrypts **M.c(M)** by XORing it with the keystream.
Ciphertext = **M.c(M) XOR RC4(V,K)**

The cipher text is then sent on the network. A user who knows **K** can get the message by XORing the cipher text with the keystream. **M.c(M) = Ciphertext XOR RC4(V,K)**

# Attacks on WEP
###### Small Initialisation Vector
WEP’s IV size of 24 bits provides for 16,777,216 different RC4 cipher streams for a given WEP key, for any key size. Remember that the RC4 cipher stream is XOR-ed with the original packet to give the encrypted packet which is transmitted, and the IV is sent in the clear with each packet. The problem is IV reuse. If the RC4 cipher stream for a given IV is found, an attacker can decrypt subsequent packets that were encrypted with the same IV, or, can forge packets. This means that you don’t need to know the WEP key to decrypt packets if you know what the key stream was used to encrypt that packet. They sound like similar problems, but it’s actually much easier to discover the key stream than it is to discover the WEP key.
Since there are only 16 million IV values, how the IV is chosen makes a big difference in the attacks based on IV. Unfortunately, WEP doesn’t specify how the IV is chosen or how often the IV is changed. Some implementations start the IV at zero and increase it incrementally for each packet, rolling over back to zero after 16 million packets have been sent. Some implementations choose IVs randomly. That sounds like a good idea, but it really isn't. With a randomly chosen IV, there is a 50% chance of reuse after less than 5000 packets.

###### WEP Attack Process
https://www.aircrack-ng.org/doku.php?id=simple_wep_crack

###### Further Reading (If you're good at math)
KoreK Attacks : https://lasec.epfl.ch/pub/lasec/doc/cha06.pdf

# Asymmetric Encryption
While symmetric encryption uses only 1 key for encryption and decryption, asymmetric algorithms requires 2 types of keys: Public and Private.

The public key is normally used for **Encryption**.
The private key is normally used for **Decryption**.
*The usage can be reversed and it will yield the same result*. 
The underlying explanation requries a lot of mathematical logic. Because of this, the computational costs are usually high. Most application will use asymmetric cryptography for key distribution and symmetric cryptography for encrpytion/decrpytion.

# Diffie-Hellman
###  An example of Asymmetric Encryption 
Diffie-Hellman is a key agreement protocol, meaning that if two parties (say, the SSL client and the SSL server) run this protocol, they end up with a shared secret K. However, neither client or server gets to choose the value of K; from their points of view, K looks randomly generated. 

It is secret (only them know K; eavesdroppers on the line do not) and shared (they both get the same value K), but not chosen. This is not encryption. A shared secret K is good enough, though, to process terabytes of data with a symmetric encryption algorithm (same K to encrypt on one side and decrypt on the other), and that is what happens in SSL.

*--An explanation found online*
