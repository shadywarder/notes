**2025-02-05 13:02**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md) [course](../2%20-%20tags/course.md)

## Ch 5. Storage
### Storage
Arguably the most important part of your typical web application is the storage of data. It would be pretty useless if each time you logged into your account on YouTube, Twitter or GitHub, all of your subscriptions, tweets, or repositories were gone.

#### Memory vs. Disk
When you run a program on your computer (like our HTTP server), the program is loaded into *memory*. Memory is a lot like a scratch pad. It's fast, but it's not permanent. If the program terminates or restarts, the data in memory is *lost*.

When you're building a web server, any data you store in memory (in your program's variables) is lost when the server is restarted. Any important data needs to be saved to disk via the file system.

#### Option 1: Raw Files
We *could* take our user's data, serialize it to JSON, and save it to disk in `.json` files (or any other format for that matter). It's simple, and will even work for small application. Trouble is, it will run into problems *fast*:
- **Concurrency.** If two requests try to write to the same file at the same time, you'll get overwritten data.
- **Scalability.** It's not efficient to read and write large files to disk for every request.
- **Complexity.** You'll have to write a lot of code to manage the files, and the chances of bugs are high.

#### Option 2: a Database
At the end of the day, a database technology like MySQL, PostgresSQL, or MongoDB "just" writes files to disk. The difference is that they *also* come with all the fancy code and algorithms that make managing those file efficient and safe. In the case of a SQL database, the files are abstracted away from us entirely. You just write SQL queries and let the DB handle the rest.

### Collections and Singletons
We're building a fairly *RESTful API*.

REST is a set of guidelines for how to build APIs. It's not a standard, but it's a set of conventions that many people follow. Not all back-end APIs are RESTful, but many are. As a back-end developer, you'll need to know how to build RESTful APIs.

#### Collections and Singletons
In REST, it's conventional to name all of your endpoints after the resource that they represent and for the name to be plural. That's why we use `POST /api/chips` to create a new chirp instead of `POST /api/chirp`.

To get a collection of resources it's conventional to use a `GET` request to the plural name of the resource. So we are going to use `GET /api/chirps` to get all of the chips.

To get a *singleton*, or a *single instance* of a resource, it's conventional to use a `GET` request to the plural name of the resource, followed by the `ID`of the resource. So we are going to use `GET /api/chirps/94b7e44c-3604-42e3-bef7-ebfcc3efff8f` to get the chirp with ID `94b7e44c-3604-42e3-bef7-ebfcc3efff8f`.

## References
[Learn HTTP Servers in Go Ch 5.](https://www.boot.dev/lessons/c3e215a5-1d8f-437b-9f89-3606118800ec)