> [!NOTE]
> - What cryptography is about
> - Theoretical versus real-world cryptography
> - What you'll learn throughout this adventure

*Cryptography* is the ancient discipline of securing situations that are troubled with malicious characters. 

## 1.1 Cryptography is about securing protocols
Our journey starts with an introduction to cryptography, the science aiming to defend protocols against saboteurs. Protocol is a list of steps that one (or more people) must follow in order to achieve something. 
And so, cryptography is about taking into account the adversaries who are looking to take advantage of you.

## 1.2 Symmetric cryptography: What is symmetric encryption?
One of the fundamental concepts of cryptography is *symmetric encryption*. It is used in a majority of cryptographic algorithms in this book. and it is, thus, extremely important.

> [!NOTE]
> By the way, a type of cryptographic algorithm is often referred to as a
*primitive*. You can think of a primitive as the smallest, useful construction you
can have in cryptography, and it is often used with other primitives in order to
build a protocol.

Imagine for now that the primitive is a black box that provides two functions:
- `ENCRYPT`
- `DECRYPT`
The first function, `ENCRYPT`, works by talking a *secret key* (usually a large number) and a *message*. It then outputs a series of random-looking numbers. We will call that output the encrypted message.

![[Pasted image 20241001014510.png]]

The second function, `DECRYPT`, is the inverse of the first one. It takes the same secret key and the random output of the first function (the encrypted message) and then it finds the original message. 

![[Pasted image 20241001014627.png]]

The actual process is shown below:

![[Pasted image 20241001014810.png]]

(1) Alice uses the `ENCRYPT` function with a secret key to transform her message into noise. (2) She then passes the encrypted message to her messenger, who will not learn anything about the underlying message. (3) Once Bob receives the encrypted message, he can recover the original content by using the `DECRYPT` function with the same secret key Alice used.

## 1.3 Kerckhoff's principle: Only the key is kept secret

> [!NOTE]
> A cryptographic algorithm can be considered broken in many ways. For
an encryption algorithm, you can imagine several ways to attack the algorithm: the secret key can be leaked to the attacker, messages can be decrypted without the help of the key, some information about the message can be revealed just by looking at the encrypted message, and so on. Anything that would somehow weaken the assumptions we made about the algorithm could be considered a break.

A strong notion came out of the long process of trial and error that cryptography went through: to obtain confidence in the security claims made by a cryptographic primitive, the primitive has to be analyzed in the open by experts. Short of that, you are relying on *security through obscurity*, which hasn't worked historically. This is why *cryptographers* (the people who build) usually use the help of *cryptaanalysts* (the people who break) in order to analyze the security of a construction. 