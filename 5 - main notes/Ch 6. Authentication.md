**2025-02-06 15:57**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md) [course](../2%20-%20tags/course.md)

## Ch 6. Authentication
### Authentication With Passwords
Authentication is the process of verifying *who* a user is. If you don't have a secure authentication system, your back-end system will be open to attack!

Imagine if I could make an HTTP request to the YouTube API and upload a video to *your* channel.
YouTube's authentication system prevents this from happening by verifying that I am who I say I am.

#### Passwords
Passwords are a common way to authenticate users. You know how they work: When a user signs up for a new account, they choose a password. When they log in, they enter their password again. The server will then compare the password they entered with the password that was stored in the database.

There are 2 *really important* things to consider when storing passwords:
1. **Storing passwords in plain text is awful.** If someone gets access to your database, they will be able to see all of your users' passwords. If you store in plain text, you are giving away your users' passwords to anyone who gets access to your database.
2. **Password strength matters.** If you allow users to choose weak passwords, they will be more likely to reuse the same password on other websites. If someone gets access to your database, they will be able to log in to your users' other accounts.

We won't be writing code to validate passwords strength in this course, but you get the idea: you can enforce rules in your HTTP handlers to make sure passwords are of a certain length and complexity.

#### Hashing
On the other hand, we *will* be writing code to store passwords in a way that prevents them from being read by anyone who gets access to your database. This is called *hashing*. Hashing is a one-way function. It takes a string as input and produces a string as output. The output string is called a *hash*.

### Password 
 It's really bad idea for users to reuse the same passwords across sites. If someone figures out their password for one site, they can try it on other sites. If they get lucky, they can log in to and compromise many of their accounts.

Unfortunately, it's very common for users to reuse passwords. We can't force users to not reuse passwords on the server side, but we can take steps to make it harder for them to reuse passwords. Namely, we can require that passwords are strong.

#### Passwords Should Be Strong
The most important factor for the strength of a password is its *entropy*. Entropy is a measure of how many possible combinations of characters there are in a string. To put it simply:
- The longer the password the better
- Special characters and capitals should always be allowed
- Special characters and capitals aren't as important as length

#### Passwords Should Never Be Stored in Plain Text 
The most critical thing we can do to protect our users' passwords is to *never* store them in plain text. We should use cryptographically strong key derivation functions (which are a special class of hash functions) to store passwords in a way that prevents them from being ready by anyone who gets access to your database.

### Types of Authentication
Here are a few of the most common authentication methods you'll see in the wild:
1. Password + ID (username, email, etc.)
2. 3rd Party Authentication ("Sign in with Google", "Sign in with GitHub", etc.)
3. Magic Links
4. API Keys

#### 1. Password + ID
This the most common type of authentication that requires a manual login from a user. When users use password managers, it's one of the most secure ways to authenticate users, unfortunately, many users don't, so it's not as secure as it could be.

That said, it's a valid choice.

#### 2. 3rd Party Authentication
- Lower friction by allowing users to user their existing accounts to log in.
- Outsource the security of your users' passwords to a company,
- Unfortunately, if users don't have an account with that 3rd party, when won't be able to log in.

#### 3. Magic Links
- Relies on assumption that the user's email is something that they have unique access to.
- The webserver sends a link to the user's email and encode a unique token in that link. 
- User clicks the link -> webserver decodes the token -> `https://example.com/login?token=...`

#### 4. API Keys
- API Key is just a long, secure string that uniquely identifies a user or system.
- They're intended to be used in code -> they don't need to be memorized -> can be much longer and double as identifier.
- `bd_JDS543J3n5NMKspDXNRlowiqw523lKHK32K43kl`

### JWTs
### What Is a JWT?
- A JWT is a JSON Web Token.
- It's a cryptographically signed JSON object that contains information about the user.
- Once the token is created by the server, the data in the token can't be changed without the server knowing.

*When your servers issues a JWT to Bob, Bob can use that token to make requests as Bob to your API. Bob won't be able to change the token to make requests as Alice.*

### Authentication With JWTs
Let's take a closer look at how JWTs work in the authentication flow.

![](../attachments/Pasted%20image%2020250206233611.png)

#### Step 1: Login
- We user don't want to enter username and password every time he wanted to make a request to an API.
- User enters a username and password -> server should respond with a *token* that's saved in the client's device.
- The token remains valid until it expires, at which point the user will need to log in again.

#### Step 2: Using the Token
When the user wants to make a request to the API, they send the token along with the request in the HTTP headers. The server can then verify that the token is valid, which means the user is who they say they are.

### JWT Review 
JWTs are cryptographically signed JSON objects taht contain information about an authenticated user.

#### JWTs Can't Be Changed
- Once the token is created by a server, the data in the token can't be changed without the server being aware of it.
- *When your server issues a JWT to Bob, Bob can use that token to make requests as Bob to your API. Bob won't be able to change the token to make requests as Alice.*

#### JWTs Are Not Encrypted
- JWTs are not encrypted.
- Anyone who has the token can read the data (like the expiry and the user id) in the token.
- You should never store sensitive information in a JWT. It's just a way to authenticate a user.
- [jwt.io](https://jwt.io/) - great tool playing around with them and learning how they work.

### Revoking JWTs
- One of the main benefits of JWTs is that they're *stateless*.
- The server doesn't need to keep track of which users are logged in via JWT.
- The server just needs to issue a JWT to a user and the user can use that JWT to authenticate themselves.
- Statelessness is *fast and scalable* because your server doesn't need to consult a database to see if a user is currently logged in.
- JWTs can't be revoked. If  a user's JWT is stolen, there's no easy way to stop the JWT from being used.
- The JWT's we've been using so far are more specifically *access tokens*.
- Access tokens are: stateless, short-lived (15m-24h), irrevocable.
- The shorter the lifespan, the more secure they are. This create a poor user experience. We don't want users to have to log in every 15 minutes.

#### A Solution: Refresh Tokens
- Refresh tokens don't provide access to resources directly, but they can be used to get new access tokens.
- Refresh tokens are much longer lived, and they *can* be revoked.
- They are: stateful, long-lived (24h-60d), revocable.
- Refresh tokens are used to keep users logged in for longer periods of time, and they can be revoked if a user's access token is compriomised.

### Cookies
HTTP *cookies* are one of the most talked about, but least understood, aspects of web.

When cookies are talked about in the news, they're usually implied to simple be privacy-stealing bad guys. While cookies can certainly invade your privacy, that's not what they *are*.

#### What Is an HTTP Cookie?
A cookie is a small piece of data that a server sends to a client. The client then dutifully stores the cookie and sends it back to the server on subsequent requests.

Cookies can store any arbitrary data:
- A user's name or other tracking information;
- A JWT (refresh and access tokens);
- Items in a shopping cart;
- etc.

The server decides *what* to put in a cookie, and the client's job is simply to store it and send it back.

#### How Do Cookies Work?
Simply put, cookies work through HTTP headers.

Cookies are sent from the server to the client in the `Set-Cookie` header. Cookie are most popular for web (browser-based) applications because browsers *automatically* send any cookies they have back to the server in the `Cookie` header.

#### Why Aren't We Using Cookies?
Simply put, Chirpy's API is designed to be consumed by mobile apps and other servers. Coolies are primarily for browsers.

A good use-case for cookies is to serve as a more strict and secure transport layer for JWTs within the context of a browser-based application.

For example, when using *httpOnly cookies*, you can ensure that 3rd party JavaScript that's being executed on your website can't access any cookies. That's a lot better than storing JWT's in the browser's local storage, where it's easily accessible to an JavaScript running on the page.

## References
[Learn HTTP Servers in Go Ch 6.](https://www.boot.dev/lessons/294e5c16-d1e8-4836-871c-dedc98581236)