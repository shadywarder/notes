Hypertext Transfer Protocol *Secure* or <u>HTTPS</u> is an extension of the HTTP protocol. HTTPS secures the data transfer between client and server by <u>encrypting</u> all of the communication.

HTTPS allows a client to safely share sensitive information with the server through an HTTP request, such as credit card information, passwords. or bank account numbers.

## Security and Encryption \
HTTPS requires that the client use <u>SSL</u> or <u>TLS</u> to protect requests and traffic by encrypting the information in the request. You don't need to manually handle encryption or decryption - it's all done for you by the protocol. **HTTPS is simply HTTP with built-in security!**

![[Pasted image 20240929183716.png]]

### HTTPS != privacy
We won't cover *how encryption works* in this course, but it's important to understand *what it does and doesn't do*, at least in regards to HTTPS. 
- HTTPS will encrypt the data in a request (like passwords, headers, body information, query parameters etc.). You and the recipient are the only once who can read that information.
- HTTPS will not hide *who you are* or that you'rec communicating with the give server. If you don't want your wife who knows how to sniff network traffic to know you're using Boot.dev, HTTPS won't help.

### HTTPS verifies the server
In addition to encrypting the information within a request, HTTPS uses <u>digital signatures</u> to prove that you're communicating with the server that you think you are. If a hacker were to intercept an HTTPS request by tapping into a network cable, they wouldn't be able to successfully pretend they are your bank's web server.