# Public-Key Cryptosystem

## Public-Key Cryptography RSA (Schoolbook)
- RSA
  - RSAES (RSA-OAEP)
  - RSA-PSS (signature)
- Security
  - 2048-bit: 112-bit security
  - 3072-bit: 128-bit security


[*] Square-and-Multiply
$3 = 11_2 = M^2\cdot M$
$17=10001_2=(((M^2)^2)^2)^2\cdot M$
$65537=1000\cdots 1_2$

- private-key: decryption, generation of signature
- public-key: encryption, verification of signature

## RSAES-OAEP (against IND-CPA)
- RSA Encryption Scheme-Optimal Asymmetric Encryption Padding
  - Encryption: M ---Encoding---> M' ---Encryption---> C
  - Decryption: C ---Decryption---> M' ---Decoding---> M
