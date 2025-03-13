**2025-02-10 14:57**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md) [course](../2%20-%20tags/course.md)

## Ch 7. Authorization
While authentication is about verifying *who* a user is, authorization is about verifying *what a user is allowed to do*.

For example, a hypothetical YouTuber `ThePrimeagen` should be allowed to edit and delete the videos on his account, and everyone should be allowed to view them. Another absolutely-not-real YouTuber `TEEJ` should be able to view `ThePrimeagen`'s videos, but not edit or delete them.

Authorization logic is just the code that enforces these kinds of rules.

### Authentication vs. Authorization
As we covered briefly, authentication and authorization are two different things.

#### Authentication
Verify *who* a user is, typically by asking for a password, api key, or other credentials.

#### Authorization
Only allow a verified user to perform actions that *they* are allowed to perform. Sometimes it's based on exactly who they are, but often it's based on a role, like "admin" or "owner".

## References
[Learn HTTP Servers in Go Ch 7.](https://www.boot.dev/lessons/be14c814-e6c2-4b96-a361-e33bcfe71f00)