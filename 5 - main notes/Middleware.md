**2025-01-29 19:30**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md)

## Middleware
We have 3 command handlers (and we'll add more) that all start by ensuring that a user is logged in.
- `addfeed`
- `follow`
- `following`

They all share this code (or something similar):

```go
user, err := s.db.GetUser(context.Background(), s.cfg.CurrentUserName)
if err != nil {
	return err
}
```

Let's create some "middleware" abstracts this away from us. In addition, if we need to modify this code for any reason later, there will be only one place that must be edited.

> [!NOTE] 
> Middleware is a way to wrap a function with additional functionality. It is a common pattern that allows us to write DRY code.

SO, we need to create logged-in middleware. It will allow us to change the function signature of our handlers that require a logged in user to accept a user as an argument and DRY up our code. Here's the function signature of middleware:

```go
middlewareLoggedIn(handler func(s *state, cmd command, user database.User) error) func(*state, command) error
```

You'll notice it's a higher order function that takes a handler of the "logged in" type and returns a "normal" handler that we can register. Example of usage:

```go
cmds.register("addfeed", middlewareLoggedIn(handlerAddFeed))
```











## References
[Boot.dev Blog Aggregator Tutorial](https://www.boot.dev/lessons/d049abb2-c733-4986-a33a-73f05e2ea06c)